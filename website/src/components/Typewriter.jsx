import { useEffect, useState } from 'react';

export default function Typewriter({ text, speed = 25, className = '' }) {
  const [shown, setShown] = useState('');

  useEffect(() => {
    setShown('');
    if (!text) return;
    let i = 0;
    const id = setInterval(() => {
      i += 1;
      setShown(text.slice(0, i));
      if (i >= text.length) clearInterval(id);
    }, speed);
    return () => clearInterval(id);
  }, [text, speed]);

  return (
    <p className={`wd-cursor whitespace-pre-wrap ${className}`}>{shown}</p>
  );
}
