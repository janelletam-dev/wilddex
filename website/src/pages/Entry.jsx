import { useEffect, useMemo, useState } from 'react';
import { useNavigate, useParams } from 'react-router-dom';
import { fromSlug, toSlug, padEntry, randomSlug, entryNumberFor } from '../lib/slug.js';
import { cacheGet, cacheSet } from '../lib/cache.js';
import { generateEntry, askQuestion, fetchTTS } from '../lib/api.js';
import PixelSprite from '../components/PixelSprite.jsx';
import RarityStars from '../components/RarityStars.jsx';
import StatBar from '../components/StatBar.jsx';
import LoadingScan from '../components/LoadingScan.jsx';
import Typewriter from '../components/Typewriter.jsx';

const STAT_COLORS = {
  speed: '#85b7eb',
  wit: '#9fe1cb',
  power: '#f09595',
  stealth: '#fac775',
  survival: '#97c459',
};

function setMeta(name, content, isProperty = false) {
  const attr = isProperty ? 'property' : 'name';
  let el = document.querySelector(`meta[${attr}="${name}"]`);
  if (!el) {
    el = document.createElement('meta');
    el.setAttribute(attr, name);
    document.head.appendChild(el);
  }
  el.setAttribute('content', content);
}

export default function Entry() {
  const { slug } = useParams();
  const navigate = useNavigate();
  const animalName = useMemo(() => fromSlug(slug), [slug]);

  const [entry, setEntry] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const [activeQuestion, setActiveQuestion] = useState(null);
  const [answer, setAnswer] = useState('');
  const [askLoading, setAskLoading] = useState(false);

  const [audio, setAudio] = useState(null);
  const [speaking, setSpeaking] = useState(false);
  const [ttsHidden, setTtsHidden] = useState(false);

  const [toast, setToast] = useState('');

  useEffect(() => {
    if (!animalName) {
      setLoading(false);
      setError('not-found');
      return;
    }
    let cancelled = false;
    setLoading(true);
    setError(null);
    setEntry(null);
    setActiveQuestion(null);
    setAnswer('');

    const key = `wd:entry:${slug}`;
    const cached = cacheGet(key);
    if (cached) {
      setEntry(cached);
      setLoading(false);
      return;
    }

    generateEntry(animalName)
      .then((data) => {
        if (cancelled) return;
        cacheSet(key, data);
        setEntry(data);
      })
      .catch(() => {
        if (cancelled) return;
        setError('generate');
      })
      .finally(() => {
        if (!cancelled) setLoading(false);
      });

    return () => {
      cancelled = true;
    };
  }, [animalName, slug]);

  useEffect(() => {
    return () => {
      if (audio) {
        audio.pause();
      }
    };
  }, [audio]);

  useEffect(() => {
    if (!animalName) {
      document.title = 'WildDex — Not found';
      return;
    }
    const title = entry?.commonName || animalName;
    document.title = `${title} · WildDex`;
    const desc = entry?.description?.split('.')[0] || `Discover the ${title} on WildDex.`;
    setMeta('description', desc);
    setMeta('og:title', `${title} · WildDex`, true);
    setMeta('og:description', desc, true);
    setMeta('og:type', 'article', true);
  }, [entry, animalName]);

  async function handleListen() {
    if (!entry?.narrationScript) return;
    try {
      setSpeaking(true);
      const blob = await fetchTTS(entry.narrationScript);
      const url = URL.createObjectURL(blob);
      const a = new Audio(url);
      setAudio(a);
      a.onended = () => {
        setSpeaking(false);
        URL.revokeObjectURL(url);
      };
      a.onerror = () => {
        setSpeaking(false);
        setTtsHidden(true);
      };
      await a.play();
    } catch {
      setSpeaking(false);
      setTtsHidden(true);
    }
  }

  async function handleAsk(question) {
    setActiveQuestion(question);
    setAnswer('');
    setAskLoading(true);
    try {
      const { answer: a } = await askQuestion(animalName, question);
      setAnswer(a || '');
    } catch {
      setAnswer('Charles is consulting his notes. Try again in a moment.');
    } finally {
      setAskLoading(false);
    }
  }

  function handleShare() {
    if (navigator.clipboard) {
      navigator.clipboard.writeText(window.location.href).then(() => {
        setToast('Link copied');
        setTimeout(() => setToast(''), 1800);
      });
    }
  }

  function handleDiscover() {
    navigate(`/creature/${randomSlug(slug)}`);
  }

  if (!animalName) {
    return (
      <div className="min-h-screen flex flex-col items-center justify-center px-4 text-center">
        <PixelSprite name="?" size={96} />
        <h1 className="font-pixel text-wd-accent-light text-lg mt-6 mb-2">UNKNOWN</h1>
        <p className="text-sm text-wd-text mb-6">
          This creature hasn't been discovered yet.
        </p>
        <button
          onClick={() => navigate('/')}
          className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
        >
          Back to WildDex
        </button>
      </div>
    );
  }

  const displayName = entry?.commonName || animalName;
  const entryNum = entry?.entryNumber || entryNumberFor(animalName);

  return (
    <div className="min-h-screen px-4 py-6 sm:py-10 max-w-2xl mx-auto">
      <div className="flex items-center justify-between mb-4 text-xs">
        <button
          onClick={() => navigate('/')}
          className="text-wd-accent hover:text-wd-accent-light"
        >
          ← WildDex
        </button>
        <div className="flex items-center gap-3">
          <span className="font-pixel text-[10px] text-wd-accent">
            WILDDEX #{padEntry(entryNum)}
          </span>
          {entry?.rarity && <RarityStars rarity={entry.rarity} />}
        </div>
      </div>

      {loading && <LoadingScan />}

      {error === 'generate' && !entry && (
        <div className="bg-wd-bg-card border border-wd-bg-bar rounded-lg p-6 text-center my-8">
          <p className="text-sm text-wd-text mb-4">
            This creature is being studied... check back soon!
          </p>
          <button
            onClick={() => window.location.reload()}
            className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
          >
            Try again
          </button>
        </div>
      )}

      {entry && (
        <>
          <div className="flex flex-col items-center mb-6">
            <PixelSprite name={displayName} size={260} className="mb-4 w-[70vw] h-[70vw] max-w-[320px] max-h-[320px]" />
            <h1 className="font-pixel text-wd-accent-light text-xl sm:text-2xl text-center leading-snug">
              {displayName}
            </h1>
            {entry.scientificName && (
              <p className="text-[11px] italic text-wd-text-muted mt-2">
                {entry.scientificName}
              </p>
            )}
          </div>

          <div className="bg-wd-bg-card border border-wd-bg-bar rounded-lg p-4 mb-5">
            <div className="grid grid-cols-2 gap-3 text-sm text-white">
              {entry.classification && (
                <div><span className="text-white font-semibold text-xs tracking-wider">CLASS</span><br />{entry.classification}</div>
              )}
              {entry.family && (
                <div><span className="text-white font-semibold text-xs tracking-wider">FAMILY</span><br />{entry.family}</div>
              )}
              {entry.sizeRange && (
                <div><span className="text-white font-semibold text-xs tracking-wider">SIZE</span><br />{entry.sizeRange}</div>
              )}
              {entry.weightRange && (
                <div><span className="text-white font-semibold text-xs tracking-wider">WEIGHT</span><br />{entry.weightRange}</div>
              )}
            </div>
          </div>

          <div className="bg-wd-bg-card border border-wd-bg-bar rounded-lg p-4 mb-5 flex flex-col gap-2">
            <StatBar label="Speed" value={entry.speed} color={STAT_COLORS.speed} delay={0} />
            <StatBar label="Wit" value={entry.wit} color={STAT_COLORS.wit} delay={100} />
            <StatBar label="Power" value={entry.power} color={STAT_COLORS.power} delay={200} />
            <StatBar label="Stealth" value={entry.stealth} color={STAT_COLORS.stealth} delay={300} />
            <StatBar label="Survival" value={entry.survival} color={STAT_COLORS.survival} delay={400} />
          </div>

          {entry.description && (
            <p className="text-sm leading-relaxed text-wd-text mb-5">
              {entry.description}
            </p>
          )}

          {!ttsHidden && entry.narrationScript && (
            <div className="mb-6">
              <button
                onClick={handleListen}
                disabled={speaking}
                className="w-full bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-3 text-sm hover:border-wd-accent-light transition-colors disabled:opacity-60"
              >
                {speaking ? 'Charles is speaking...' : 'Listen to Charles'}
              </button>
            </div>
          )}

          {entry.questions && entry.questions.length > 0 && !activeQuestion && (
            <div className="mb-6">
              <h3 className="text-xs text-wd-text-secondary uppercase tracking-wider mb-3">
                Ask Charles
              </h3>
              <div className="flex flex-col gap-2">
                {entry.questions.slice(0, 2).map((q, i) => (
                  <button
                    key={i}
                    onClick={() => handleAsk(q)}
                    className="text-left bg-wd-bg-card border border-wd-bg-bar hover:border-wd-accent rounded-lg p-3 text-sm text-wd-text transition-colors"
                  >
                    {q}
                  </button>
                ))}
              </div>
            </div>
          )}

          {activeQuestion && (
            <div className="mb-6 bg-wd-bg-card border border-wd-bg-bar rounded-lg p-4">
              <p className="text-xs text-wd-text-secondary mb-2">{activeQuestion}</p>
              {askLoading ? (
                <p className="text-sm text-wd-text-muted">Charles is thinking...</p>
              ) : (
                <Typewriter text={answer} className="text-sm text-wd-text leading-relaxed" />
              )}
              <button
                onClick={() => { setActiveQuestion(null); setAnswer(''); }}
                className="mt-3 text-xs text-wd-accent hover:text-wd-accent-light"
              >
                ← Back to entry
              </button>
            </div>
          )}

          <div className="flex flex-col sm:flex-row gap-2 mb-8">
            <button
              onClick={handleDiscover}
              className="flex-1 bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
            >
              Discover another
            </button>
            <button
              onClick={handleShare}
              className="flex-1 bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
            >
              Share
            </button>
          </div>
        </>
      )}

      {toast && (
        <div className="fixed bottom-6 left-1/2 -translate-x-1/2 bg-wd-bg-surface border border-wd-accent text-wd-accent-light text-xs px-4 py-2 rounded-full shadow-lg">
          {toast}
        </div>
      )}
    </div>
  );
}
