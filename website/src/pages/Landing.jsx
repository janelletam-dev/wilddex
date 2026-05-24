import { useMemo, useRef, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { ANIMALS } from '../data/animals.js';
import { toSlug, randomSlug } from '../lib/slug.js';
import CreatureCard from '../components/CreatureCard.jsx';

export default function Landing() {
  const navigate = useNavigate();
  const [query, setQuery] = useState('');
  const gridRef = useRef(null);

  const filtered = useMemo(() => {
    const q = query.trim().toLowerCase();
    if (!q) return ANIMALS.map((name, idx) => ({ name, idx }));
    return ANIMALS
      .map((name, idx) => ({ name, idx }))
      .filter(({ name }) => name.toLowerCase().includes(q));
  }, [query]);

  function goRandom() {
    navigate(`/creature/${randomSlug()}`);
  }

  function scrollToGrid() {
    gridRef.current?.scrollIntoView({ behavior: 'smooth', block: 'start' });
  }

  return (
    <div className="min-h-screen px-4 py-8 sm:px-6 sm:py-12 max-w-6xl mx-auto">
      <header className="text-center mb-8">
        <h1 className="font-pixel text-wd-accent-light text-3xl sm:text-4xl md:text-5xl leading-tight mb-4">
          WILDDEX
        </h1>
        <p className="text-wd-text-secondary text-sm sm:text-base">
          An encyclopedia of wild things
        </p>
      </header>

      <section className="mb-8 max-w-2xl mx-auto text-center">
        <p className="text-sm sm:text-base text-wd-text leading-relaxed">
          Tap any creature. Charles will narrate its story in the voice of a
          wildlife documentary, plus you can ask him anything else you want to know.
        </p>
      </section>

      <section className="mb-10 max-w-2xl mx-auto">
        <ol className="grid grid-cols-3 gap-2 sm:gap-3 text-center">
          <li className="bg-wd-bg-card border border-wd-bg-bar rounded-lg px-2 py-3">
            <div className="font-pixel text-wd-accent text-[10px] mb-2">01</div>
            <div className="text-xs sm:text-sm text-wd-text">Pick a creature</div>
          </li>
          <li className="bg-wd-bg-card border border-wd-bg-bar rounded-lg px-2 py-3">
            <div className="font-pixel text-wd-accent text-[10px] mb-2">02</div>
            <div className="text-xs sm:text-sm text-wd-text">Listen to Charles</div>
          </li>
          <li className="bg-wd-bg-card border border-wd-bg-bar rounded-lg px-2 py-3">
            <div className="font-pixel text-wd-accent text-[10px] mb-2">03</div>
            <div className="text-xs sm:text-sm text-wd-text">Ask him anything</div>
          </li>
        </ol>
      </section>

      <section className="mb-10 max-w-xl mx-auto">
        <input
          type="text"
          value={query}
          onChange={(e) => setQuery(e.target.value)}
          placeholder="Find an animal..."
          className="w-full bg-wd-bg-card border-2 border-wd-bg-bar focus:border-wd-accent rounded-full px-4 py-3 text-sm text-wd-text placeholder:text-wd-text-muted outline-none"
        />
        <div className="flex gap-3 mt-4 justify-center">
          <button
            onClick={goRandom}
            className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm hover:border-wd-accent-light transition-colors"
          >
            Random
          </button>
          <button
            onClick={scrollToGrid}
            className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm hover:border-wd-accent-light transition-colors"
          >
            Browse A-Z
          </button>
        </div>
      </section>

      <section ref={gridRef} className="mb-12">
        <h2 className="text-xs sm:text-sm text-wd-text-secondary uppercase tracking-wider mb-2 text-center">
          All creatures · {filtered.length} in the dex
        </h2>
        <p className="text-center text-[11px] text-wd-text-muted mb-6">
          Swipe to flip through
        </p>
        {filtered.length > 0 ? (
          <div className="wd-deck flex gap-6 overflow-x-auto px-[16vw] py-6 -mx-4 sm:-mx-6">
            {filtered.map(({ name, idx }) => (
              <CreatureCard
                key={name}
                name={name}
                index={idx}
                variant="deck"
                onClick={() => navigate(`/creature/${toSlug(name)}`)}
              />
            ))}
          </div>
        ) : (
          <p className="text-center text-wd-text-muted text-sm mt-8">
            No creatures match that name.
          </p>
        )}
      </section>

      <section className="mb-12 max-w-2xl mx-auto text-center">
        <h2 className="font-pixel text-wd-accent-light text-base sm:text-lg mb-4">
          ABOUT
        </h2>
        <p className="text-sm text-wd-text leading-relaxed">
          WildDex started on a Cardputer, a handheld about the size of a credit
          card. Spot an animal, look it up on the device, scan the QR code, and
          you land here. No Cardputer? You can still explore everything from
          this site.
        </p>
      </section>

      <footer className="text-center text-xs text-wd-text-muted py-6 border-t border-wd-bg-bar leading-relaxed">
        <div>Made by Janelle Tamayo</div>
        <div className="mt-1">For Sir David Attenborough, with thanks for 100 years of wonder</div>
      </footer>
    </div>
  );
}
