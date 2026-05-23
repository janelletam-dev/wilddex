export default function PixelSprite({ name, size = 64, className = '' }) {
  const letter = (name || '?').trim().charAt(0).toUpperCase();
  const fontSize = Math.max(12, Math.floor(size * 0.4));
  return (
    <div
      className={`wd-sprite-anim flex items-center justify-center bg-wd-bg-surface border-2 border-wd-accent-dim rounded-lg ${className}`}
      style={{ width: size, height: size }}
      aria-label={name ? `Pixel sprite for ${name}` : 'Pixel sprite'}
    >
      <span
        className="font-pixel text-wd-accent-light"
        style={{ fontSize }}
      >
        {letter}
      </span>
    </div>
  );
}
