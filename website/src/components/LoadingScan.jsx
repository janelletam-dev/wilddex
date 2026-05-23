export default function LoadingScan() {
  const widths = ['w-full', 'w-4/5', 'w-3/5'];
  return (
    <div className="flex flex-col items-center gap-3 py-8">
      <p className="text-xs text-wd-text-secondary uppercase tracking-wider">
        Exploring the wild...
      </p>
      <div className="w-full max-w-xs flex flex-col gap-2">
        {widths.map((w, i) => (
          <div
            key={i}
            className={`${w} mx-auto h-2 bg-wd-bg-bar rounded-full overflow-hidden relative`}
          >
            <div
              className="wd-scan-fill"
              style={{ animationDelay: `${i * 0.2}s` }}
            />
          </div>
        ))}
      </div>
    </div>
  );
}
