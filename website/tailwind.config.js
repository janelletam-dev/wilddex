/** @type {import('tailwindcss').Config} */
export default {
  content: ['./index.html', './src/**/*.{js,jsx}'],
  theme: {
    extend: {
      colors: {
        'wd-bg-deep': '#0a2a2a',
        'wd-bg-card': '#071f1f',
        'wd-bg-surface': '#0d3535',
        'wd-bg-bar': '#0f3a3a',
        'wd-accent': '#5dcaa5',
        'wd-accent-light': '#9fe1cb',
        'wd-accent-pale': '#e1f5ee',
        'wd-accent-dim': '#1d9e75',
        'wd-text': '#e1f5ee',
        'wd-text-secondary': '#5dcaa5',
        'wd-text-muted': '#9fe1cb',
        'wd-stat-speed': '#85b7eb',
        'wd-stat-wit': '#9fe1cb',
        'wd-stat-power': '#f09595',
        'wd-stat-stealth': '#fac775',
        'wd-stat-survival': '#97c459',
        'wd-rarity': '#ef9f27',
      },
      fontFamily: {
        pixel: ['"Press Start 2P"', 'monospace'],
        mono: ['"Courier New"', 'monospace'],
      },
    },
  },
  plugins: [],
};
