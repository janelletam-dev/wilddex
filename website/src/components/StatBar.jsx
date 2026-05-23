import { useEffect, useState } from 'react';

export default function StatBar({ label, value, color, delay = 0, max = 10 }) {
  const [width, setWidth] = useState(0);
  const target = Math.max(0, Math.min(max, Number(value) || 0));
  const pct = (target / max) * 100;

  useEffect(() => {
    const t = setTimeout(() => setWidth(pct), delay);
    return () => clearTimeout(t);
  }, [pct, delay]);

  return (
    <div className="flex items-center gap-2 text-xs">
      <span className="w-16 text-wd-text-secondary uppercase">{label}</span>
      <div className="flex-1 h-1.5 bg-wd-bg-bar rounded-full overflow-hidden">
        <div
          className="h-full rounded-full transition-all duration-500 ease-out"
          style={{ width: `${width}%`, backgroundColor: color }}
        />
      </div>
      <span className="w-6 text-right text-wd-accent-light">{target}</span>
    </div>
  );
}
