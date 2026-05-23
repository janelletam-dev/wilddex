import { useState } from 'react';
import { toSlug } from '../lib/slug.js';

export default function PixelSprite({ name, size = 64, className = '' }) {
  const [imgFailed, setImgFailed] = useState(false);
  const letter = (name || '?').trim().charAt(0).toUpperCase();
  const fontSize = Math.max(12, Math.floor(size * 0.4));
  const src = name ? `/sprites/${toSlug(name)}.png` : null;

  return (
    <div
      className={`wd-sprite-anim flex items-center justify-center bg-wd-bg-surface border-2 border-wd-accent-dim rounded-lg overflow-hidden ${className}`}
      style={{ width: size, height: size }}
      aria-label={name ? `Pixel sprite for ${name}` : 'Pixel sprite'}
    >
      {src && !imgFailed ? (
        <img
          src={src}
          alt={name || ''}
          width={size}
          height={size}
          onError={() => setImgFailed(true)}
          style={{ imageRendering: 'pixelated', width: '100%', height: '100%', objectFit: 'contain' }}
        />
      ) : (
        <span className="font-pixel text-wd-accent-light" style={{ fontSize }}>
          {letter}
        </span>
      )}
    </div>
  );
}
