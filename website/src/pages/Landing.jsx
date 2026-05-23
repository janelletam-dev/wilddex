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
      <header className="text-center mb-10">
        <h1 className="font-pixel text-wd-accent-light text-3xl sm:text-4xl md:text-5xl leading-tight mb-4">
          WILDDEX
        </h1>
        <p className="text-wd-text-secondary text-sm sm:text-base">
          The real-world creature encyclopedia
        </p>
      </header>

      <section className="mb-10 max-w-2xl mx-auto text-center">
        <p className="text-sm sm:text-base text-wd-text leading-relaxed">
          WildDex turns every animal into a pocket-sized adventure. Pick a creature,
          listen to Charles narrate, and explore the wild from your phone.
        </p>
      </section>

      <section className="mb-10 max-w-xl mx-auto">
        <input
          type="text"
          value={query}
          onChange={(e) => setQuery(e.target.value)}
          placeholder="Search creatures..."
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
        <h2 className="text-xs sm:text-sm text-wd-text-secondary uppercase tracking-wider mb-4 text-center">
          All creatures — {filtered.length} discovered
        </h2>
        <div className="grid grid-cols-2 sm:grid-cols-3 md:grid-cols-4 gap-3 sm:gap-4">
          {filtered.map(({ name, idx }) => (
            <CreatureCard
              key={name}
              name={name}
              index={idx}
              onClick={() => navigate(`/creature/${toSlug(name)}`)}
            />
          ))}
        </div>
        {filtered.length === 0 && (
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
          WildDex began as a tiny Cardputer — a credit-card-sized handheld that
          fits in your pocket. Spot an animal, look it up on the device, and
          scan the QR code to jump into the full experience here.
        </p>
      </section>

      <footer className="text-center text-xs text-wd-text-muted py-6 border-t border-wd-bg-bar">
        Creative Stallion · WildDex
      </footer>
    </div>
  );
}
