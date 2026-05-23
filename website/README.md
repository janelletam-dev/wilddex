# WildDex Companion Website

React + Vite + Tailwind. The web companion to the WildDex Cardputer.

## Local dev

```
cd website
npm install
npm run dev
```

Copy `.env.example` to `.env.local` and fill in `CLAUDE_API_KEY` and `ELEVENLABS_API_KEY`.

## Deploy

Deploy to Vercel. Set the same env vars in the project settings. `vercel.json` rewrites all non-`/api` paths to `index.html` for SPA routing.
