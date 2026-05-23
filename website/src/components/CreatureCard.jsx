import PixelSprite from './PixelSprite.jsx';
import RarityStars from './RarityStars.jsx';
import { padEntry } from '../lib/slug.js';

export default function CreatureCard({ name, index, onClick }) {
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
