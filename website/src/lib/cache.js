const TTL_MS = 7 * 24 * 60 * 60 * 1000;

export function cacheGet(key) {
  try {
    const raw = localStorage.getItem(key);
    if (!raw) return null;
    const { value, expires } = JSON.parse(raw);
    if (typeof expires !== 'number' || Date.now() > expires) {
      localStorage.removeItem(key);
      return null;
    }
    return value;
  } catch {
    return null;
  }
}

export function cacheSet(key, value) {
  try {
    localStorage.setItem(
      key,
      JSON.stringify({ value, expires: Date.now() + TTL_MS })
    );
  } catch {
    // ignore quota errors
  }
}
