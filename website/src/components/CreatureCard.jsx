import PixelSprite from './PixelSprite.jsx';
import RarityStars from './RarityStars.jsx';
import { padEntry } from '../lib/slug.js';

export default function CreatureCard({ name, index, onClick, variant = 'grid' }) {
  if (variant === 'deck') {
    return (
      <button
        onClick={onClick}
        className="wd-deck-card shrink-0 w-[68vw] max-w-[280px] aspect-[3/4] bg-wd-bg-card border-2 border-wd-bg-bar rounded-2xl p-4 flex flex-col items-center justify-between text-left"
      >
        <div className="w-full flex items-center justify-between text-[10px]">
          <span className="font-pixel text-wd-accent">#{padEntry(index + 1)}</span>
          <RarityStars rarity={3} />
        </div>
        <PixelSprite name={name} size={180} className="!border-0 !bg-transparent" />
        <div className="w-full text-center font-pixel text-wd-accent-light text-xs leading-tight">
          {name}
        </div>
      </button>
    );
  }

  return (
    <button
      onClick={onClick}
      className="group text-left bg-wd-bg-card border border-wd-bg-bar rounded-lg p-3 flex flex-col items-center gap-2 transition-all duration-200 hover:scale-105 hover:border-wd-accent active:scale-100"
    >
      <PixelSprite name={name} size={56} />
      <div className="text-[10px] text-wd-accent">#{padEntry(index + 1)}</div>
      <div className="text-xs text-wd-text text-center leading-tight">{name}</div>
      <RarityStars rarity={3} />
    </button>
  );
}
