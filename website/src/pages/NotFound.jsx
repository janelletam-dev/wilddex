import { Link, useNavigate } from 'react-router-dom';
import PixelSprite from '../components/PixelSprite.jsx';
import { randomSlug } from '../lib/slug.js';

export default function NotFound() {
  const navigate = useNavigate();
  return (
    <div className="min-h-screen flex flex-col items-center justify-center px-4 text-center">
      <PixelSprite name="?" size={120} />
      <h1 className="font-pixel text-wd-accent-light text-lg sm:text-xl mt-6 mb-3">
        UNKNOWN CREATURE
      </h1>
      <p className="text-sm text-wd-text mb-6 max-w-xs">
        This creature hasn't been discovered yet!
      </p>
      <div className="flex flex-col sm:flex-row gap-2">
        <Link
          to="/"
          className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
        >
          Back to WildDex
        </Link>
        <button
          onClick={() => navigate(`/creature/${randomSlug()}`)}
          className="bg-wd-bg-surface border-2 border-wd-accent text-wd-accent-light rounded-full px-5 py-2 text-sm"
        >
          Random creature
        </button>
      </div>
    </div>
  );
}
