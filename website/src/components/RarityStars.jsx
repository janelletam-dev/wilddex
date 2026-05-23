export default function RarityStars({ rarity = 0, max = 5 }) {
  const stars = [];
  for (let i = 0; i < max; i++) {
    const filled = i < rarity;
    stars.push(
      <span
        key={i}
        className={filled ? 'text-wd-rarity' : 'text-wd-bg-bar'}
        aria-hidden="true"
      >
        ★
      </span>
    );
  }
  return (
    <span className="inline-flex gap-0.5 text-sm" aria-label={`Rarity ${rarity} of ${max}`}>
      {stars}
    </span>
  );
}
