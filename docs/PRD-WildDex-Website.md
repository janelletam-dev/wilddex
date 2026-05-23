# WildDex Companion Website — Product Requirements Document

| Field    | Value                            |
|----------|----------------------------------|
| Project  | WildDex Companion Web App        |
| Version  | 1.0                              |
| Date     | 23 May 2026                      |
| Author   | Janelle D. Tamayo                |
| Status   | Draft                            |
| Parent   | WildDex PRD v1.0                 |

---

## 1. Overview / Problem Statement

WildDex lives on a Cardputer — a tiny credit card-sized device. When someone discovers an animal, they see a QR code on the Cardputer screen. Scanning that code should transport the viewer into a rich, beautiful experience on their phone: an animated pixel creature, full stat card, Attenborough-style narration, and follow-up questions to explore.

The companion website is the bridge between the Cardputer's hardware-limited screen and a full visual experience. It turns a 240x135 pixel stat card into a shareable, immersive animal page that anyone can enjoy, whether they own a Cardputer or not.

**Before the website:** You show someone your Cardputer. They think it's cool but can't take the experience with them. The moment passes.

**After the website:** They scan the QR code. Their phone fills with a glowing turquoise pixel tiger, animated stats, and Charles's voice narrating. They share the link. Their friend opens it. WildDex spreads.

---

## 2. Goals and Non-Goals

### Goals (v1)

- **G1:** When a user scans a QR code from the Cardputer, the website loads a beautiful, immersive animal entry page within 3 seconds
- **G2:** The website uses the same Claude API to generate Attenborough-style entries with stats, ensuring consistency with the Cardputer experience
- **G3:** Every animal page features an animated pixel art creature in the turquoise cosmic aesthetic
- **G4:** Users can listen to Charles narrate the entry via ElevenLabs TTS
- **G5:** Users can explore follow-up questions about the animal, answered by Claude
- **G6:** A landing page introduces WildDex and invites visitors to explore
- **G7:** The design is fully mobile-first since the primary use case is scanning a QR code with a phone
- **G8:** Every animal page has Open Graph meta tags for rich social media sharing
- **G9:** The website reflects the turquoise cosmic pixel art brand identity established in the design exploration

### Non-Goals (v1)

- **NG1:** User accounts, login, or registration
- **NG2:** Personal collection tracking or discovery logs
- **NG3:** Animal battles or multiplayer features
- **NG4:** Dog Breeds series (Wildlife only for v1 website)
- **NG5:** Camera-based animal identification
- **NG6:** Offline functionality (website requires internet)
- **NG7:** Admin dashboard or CMS

---

## 3. Target Users

### Primary: QR Code Scanners

People who see someone using a Cardputer, scan the QR code, and land on the website. They have no context about WildDex beyond "that person had a cool tiny gadget." The page must be instantly engaging and self-explanatory.

**Context:** Standing at a zoo, park, hackathon, or social gathering. On their phone. Attention span is 5 seconds before they decide to stay or leave.

### Secondary: Link Receivers

People who receive a shared WildDex link via text, social media, or messaging. They didn't see the Cardputer — they just got a link. The page must be compelling enough as a standalone experience.

### Tertiary: Curious Browsers

People who find wilddex.app directly — through search, a LinkedIn post, or word of mouth. The landing page must explain what WildDex is and let them explore animals.

---

## 4. User Flows

### Flow 1: QR Code Scan (Primary)

1. User sees a Cardputer owner looking up an animal
2. Owner presses QR button — QR code appears on Cardputer screen
3. User scans QR code with phone camera
4. Phone browser opens `wilddex.app/creature/bengal-tiger`
5. Page loads with animated pixel tiger, stats, description
6. User taps "Listen to Charles" — narration plays
7. User taps a follow-up question — Claude answers with typewriter animation
8. User shares the link with a friend

### Flow 2: Landing Page Discovery

1. User visits `wilddex.app` directly
2. Landing page shows WildDex branding, animated pixel creatures, and an explanation
3. User taps "Explore creatures" or a featured animal
4. Animal page loads with full experience
5. User discovers more animals via "Random creature" or search

### Flow 3: Social Media Share

1. User receives a WildDex link on WhatsApp/Instagram/Twitter
2. Link preview shows animal name, pixel art preview, and WildDex branding (Open Graph)
3. User taps the link
4. Full animal page loads
5. User explores, listens, shares further

---

## 5. Pages and Functional Requirements

### 5.1 Landing Page (`wilddex.app`)

| ID | Requirement |
|----|-------------|
| LAND-01 | Hero section with animated WildDex logo in turquoise cosmic pixel art style |
| LAND-02 | Tagline: "The real-world creature encyclopedia" or similar |
| LAND-03 | 3-4 featured animal cards with pixel art sprites that animate on hover/tap |
| LAND-04 | Brief explanation of what WildDex is (2-3 sentences max) |
| LAND-05 | "Explore a creature" search bar where users can type any animal name |
| LAND-06 | Quick action buttons: "Random" and "Browse A-Z" |
| LAND-07 | Full scrollable creature grid displaying all 80 animals in a 2-column layout |
| LAND-08 | Each creature card shows: pixel art sprite, common name, entry number, and rarity stars |
| LAND-09 | Tapping a creature card navigates to its full entry page |
| LAND-10 | Grid header shows "ALL CREATURES" with total count (e.g., "80 discovered") |
| LAND-11 | Grid loads progressively — first 20 visible, more load on scroll (infinite scroll or "Load more") |
| LAND-12 | Search bar filters the grid in real-time as user types |
| LAND-13 | "About" section below the grid explaining the Cardputer hardware device |
| LAND-14 | Footer with Creative Stallion branding and social links |

### 5.2 Animal Entry Page (`wilddex.app/creature/{slug}`)

| ID | Requirement |
|----|-------------|
| ENTRY-01 | URL format: `wilddex.app/creature/{slug}` where slug is the lowercase hyphenated animal name (e.g., `bengal-tiger`, `mantis-shrimp`) |
| ENTRY-02 | Page calls Claude API on load to generate the entry (same prompt structure as Cardputer) |
| ENTRY-03 | Entry data is cached after first generation so repeat visits don't call the API |
| ENTRY-04 | Animated pixel art sprite of the animal displayed prominently with idle animation (bounce, blink, sway) |
| ENTRY-05 | Entry number and rarity stars displayed in header |
| ENTRY-06 | Animal common name displayed in large pixel-style font |
| ENTRY-07 | Classification, family, size range, and weight range displayed |
| ENTRY-08 | Five stat bars (Speed, Wit, Power, Stealth, Survival) with coloured fills matching the Cardputer layout |
| ENTRY-09 | Description text in Attenborough style |
| ENTRY-10 | "Listen to Charles" button that calls ElevenLabs TTS API and plays narration |
| ENTRY-11 | Two follow-up questions displayed as tappable cards |
| ENTRY-12 | Tapping a question calls Claude API and displays the answer with a typewriter animation |
| ENTRY-13 | "Discover another creature" button linking to a random animal or back to search |
| ENTRY-14 | "Share" button that copies the page URL to clipboard |
| ENTRY-15 | Open Graph meta tags: title = animal name, description = first sentence, image = pixel art sprite |
| ENTRY-16 | Loading state: animated scan effect (bars filling up) while Claude generates the entry |

### 5.3 Error/404 Page

| ID | Requirement |
|----|-------------|
| ERR-01 | Custom 404 page in WildDex styling: "This creature hasn't been discovered yet!" |
| ERR-02 | Link back to landing page and "Random creature" button |
| ERR-03 | Pixel art of a question mark creature |

---

## 6. Design System

### 6.1 Colour Palette — Turquoise Cosmic

| Token | Hex | Usage |
|-------|-----|-------|
| `bg-deep` | #0a2a2a | Main background |
| `bg-card` | #071f1f | Card backgrounds |
| `bg-surface` | #0d3535 | Header, elevated surfaces |
| `bg-bar` | #0f3a3a | Stat bar backgrounds, borders |
| `accent-primary` | #5dcaa5 | Primary accent, labels, icons |
| `accent-light` | #9fe1cb | Headings, highlights |
| `accent-pale` | #e1f5ee | Primary text on dark backgrounds |
| `accent-dim` | #1d9e75 | Subtle accents, borders |
| `text-primary` | #e1f5ee | Main body text |
| `text-secondary` | #5dcaa5 | Labels, section headers |
| `text-muted` | #0f6e56 | Hints, timestamps |
| `stat-speed` | #85b7eb | Speed stat bar |
| `stat-wit` | #9fe1cb | Wit stat bar |
| `stat-power` | #f09595 | Power stat bar |
| `stat-stealth` | #fac775 | Stealth stat bar |
| `stat-survival` | #97c459 | Survival stat bar |
| `rarity-star` | #ef9f27 | Filled rarity star |
| `rarity-empty` | #0d3535 | Empty rarity star |

### 6.2 Typography

| Element | Font | Size | Weight |
|---------|------|------|--------|
| Logo / WildDex branding | Press Start 2P (Google Fonts) | 24-32px | 400 |
| Animal name | Press Start 2P | 20-24px | 400 |
| Section labels | Courier New / monospace | 10-12px | 400 |
| Stat labels | Courier New / monospace | 11px | 400 |
| Body text / descriptions | Courier New / monospace | 12-14px | 400 |
| Buttons | Courier New / monospace | 13px | 400 |

All text is monospace to maintain the retro pixel aesthetic. Press Start 2P is used for headings and branding only.

### 6.3 Component Styles

**Cards:** Dark background (`bg-card`), 1px solid border (`bg-bar`), 8px border radius, 12-16px padding.

**Stat bars:** 6px height, 3px border radius, coloured fill on dark background (`bg-deep`). Each stat has a unique colour.

**Buttons:** Dark background (`bg-surface`), 2px solid border (`accent-primary`), rounded corners (20px), monospace font, hover brightens border.

**Rarity stars:** Filled stars use `rarity-star` colour, empty stars use `rarity-empty`.

**Animations:**
- Pixel sprite: subtle bounce (translateY 2-4px), blink every 3 seconds
- Stat bars: fill animation on load (width transitions from 0 to target over 0.5s, staggered by 100ms per stat)
- Typewriter text: for Q&A answers, characters appear one at a time with a cursor
- Loading scan: horizontal bars fill from left to right

### 6.4 Pixel Art Assets

Each animal needs a pixel art sprite. Approach for v1:

- **Primary method:** AI-generated pixel art sprites via Perchance or Pokecut using consistent prompts
- **Style guide:** 32x32 or 64x64 pixel sprites, transparent background, turquoise-tinted colour palette
- **Prompt template:** "pixel art [animal name] sprite, 32x32, retro game style, facing right, clean edges, transparent background"
- **Storage:** Static assets in `/public/sprites/` directory, named by slug (e.g., `bengal-tiger.png`)
- **Fallback:** If no pre-made sprite exists, display a generic pixel silhouette with the animal's initial letter
- **CSS animation:** Sprites are animated using CSS keyframes (bounce, blink) not GIFs

---

## 7. Technical Architecture

### 7.1 Stack

| Layer | Technology |
|-------|-----------|
| Framework | React (Vite) |
| Styling | Tailwind CSS with custom turquoise theme |
| Font | Press Start 2P (Google Fonts) + system monospace |
| Hosting | Vercel (already connected) |
| Domain | wilddex.app (to be registered) |
| API | Anthropic Claude API (entry generation) |
| TTS | ElevenLabs API (voice narration) |
| Caching | Vercel KV or localStorage for generated entries |

### 7.2 API Architecture

```
Browser → Vercel API Route → Claude API → JSON entry
Browser → Vercel API Route → ElevenLabs → Audio stream
```

API keys are stored in Vercel environment variables, never exposed to the client. All API calls go through Vercel serverless functions.

### 7.3 Caching Strategy

| Layer | Cache | TTL |
|-------|-------|-----|
| Vercel API Route | Vercel KV store | Permanent (animal entries don't change) |
| Client | localStorage | 7 days |
| ElevenLabs audio | Vercel Blob storage | Permanent |

First request for "bengal-tiger" calls Claude API and caches the result. All subsequent requests serve from cache. This keeps API costs near zero after initial population.

### 7.4 Route Structure

```
/                           → Landing page
/creature/:slug             → Animal entry page
/creature/:slug?source=qr   → Animal entry page (from QR scan, tracks source)
/random                     → Redirects to a random animal entry
```

### 7.5 QR Code Integration

The Cardputer generates QR codes pointing to `wilddex.app/creature/{slug}?source=qr`. The slug is derived from the animal's common name (lowercase, hyphenated). The `source=qr` parameter helps track how many visitors come from Cardputer scans.

---

## 8. Non-Functional Requirements

| ID | Requirement |
|----|-------------|
| NFR-01 | **Performance:** Animal page loads in under 3 seconds on 4G mobile connection |
| NFR-02 | **Performance:** Cached entries load in under 1 second (no API call) |
| NFR-03 | **Responsive:** Fully responsive from 320px to 1440px. Mobile is the primary viewport |
| NFR-04 | **Accessibility:** Minimum 4.5:1 contrast ratio for all text on dark backgrounds |
| NFR-05 | **Accessibility:** All interactive elements have visible focus states |
| NFR-06 | **Accessibility:** Pixel art sprites have alt text describing the animal |
| NFR-07 | **SEO:** Each animal page has unique title, description, and Open Graph tags |
| NFR-08 | **SEO:** Landing page is indexable with structured data for the site |
| NFR-09 | **Privacy:** No analytics, no cookies, no tracking in v1. Only the `source=qr` URL parameter |
| NFR-10 | **Cost:** API caching ensures Claude and ElevenLabs costs stay under £5/month for typical usage |
| NFR-11 | **Reliability:** Graceful fallback if Claude API is unavailable — show cached data or friendly error |

---

## 9. Edge Cases

| Scenario | Behaviour |
|----------|-----------|
| Animal name in URL doesn't exist (e.g., `/creature/unicorn`) | Claude generates an entry anyway — it can handle fictional creatures with a note that they're mythological |
| Very long animal name in URL | Truncate display name, full name in meta tags |
| Claude API rate limited or down | Show cached version if available, otherwise display "This creature is being studied... check back soon!" with retry button |
| ElevenLabs API unavailable | Hide "Listen" button gracefully, show text-only experience |
| User visits on desktop, not mobile | Full experience works on desktop too, just optimised for mobile first |
| Multiple rapid QR scans | Each loads independently, no state conflicts |
| Offensive or inappropriate animal search | Claude's built-in safety handles this — won't generate harmful content |
| Slow connection | Progressive loading: show header and stats first, description fades in, sprite loads last |
| Shared link has no image for preview | Generate and cache a static OG image per animal using the pixel sprite |

---

## 10. Success Metrics

| Metric | Target | Measurement |
|--------|--------|-------------|
| Page load time | < 3 seconds on 4G | Vercel analytics |
| QR scan to page view | > 80% conversion | source=qr parameter tracking |
| Listen button usage | > 30% of visitors tap it | Client-side event (no external analytics) |
| Question exploration | > 20% tap a follow-up question | Client-side event |
| Share action | > 10% copy the link | Client-side event |
| API cost | < £5/month | Anthropic + ElevenLabs dashboards |
| Deployment | Live and functional within 2 weeks | Ship date |

---

## 11. Open Questions

1. **Domain:** Is `wilddex.app` available? Alternatives: `wilddex.io`, `mywilddex.com`, `wilddex.dev`
2. **Pixel art pipeline:** Batch generate with AI tools (Perchance) or generate on-demand? How many animals to pre-generate for launch?
3. **Audio caching:** Store generated TTS audio in Vercel Blob storage or regenerate each time? Caching is cheaper but requires storage.
4. **Social sharing image:** Generate static OG images per animal or use a generic WildDex image?
5. **Search on website:** Allow free-text search on the landing page, or only support pre-defined animals with a browse grid?
6. **Future series:** When Dog Breeds launches, should it be `wilddex.app/dogs/golden-retriever` or `wilddex.app/creature/golden-retriever`?

---

## Appendix A: Claude API Prompt (Website Version)

Same as Cardputer prompt but with longer descriptions allowed since screen space isn't limited:

```
System: You are WildDex, an animal encyclopedia that generates entries in the style of
David Attenborough narrating a nature documentary. Your tone is warm, reverent, full of
wonder, and occasionally dry-witted. Entries should be accessible to children aged 5-12
while still delighting adults.

Respond ONLY in valid JSON with this exact structure:
{
  "entryNumber": <number>,
  "commonName": "<string>",
  "scientificName": "<string>",
  "classification": "<e.g., Mammal>",
  "family": "<e.g., Canidae>",
  "region": "<primary habitat regions>",
  "habitat": "<e.g., Forests, grasslands, urban areas>",
  "sizeRange": "<e.g., 45-90cm>",
  "weightRange": "<e.g., 2-14kg>",
  "rarity": <1-5>,
  "speed": <1-10>,
  "wit": <1-10>,
  "power": <1-10>,
  "stealth": <1-10>,
  "survival": <1-10>,
  "description": "<3-4 sentences, Attenborough style>",
  "narrationScript": "<Full narration text for TTS, 4-6 sentences, Attenborough style>",
  "questions": ["<fun follow-up question 1>", "<fun follow-up question 2>"]
}
```

## Appendix B: Turquoise Cosmic Design Token Reference

```css
:root {
  --wd-bg-deep: #0a2a2a;
  --wd-bg-card: #071f1f;
  --wd-bg-surface: #0d3535;
  --wd-bg-bar: #0f3a3a;
  --wd-accent: #5dcaa5;
  --wd-accent-light: #9fe1cb;
  --wd-accent-pale: #e1f5ee;
  --wd-accent-dim: #1d9e75;
  --wd-text: #e1f5ee;
  --wd-text-secondary: #5dcaa5;
  --wd-text-muted: #0f6e56;
  --wd-stat-speed: #85b7eb;
  --wd-stat-wit: #9fe1cb;
  --wd-stat-power: #f09595;
  --wd-stat-stealth: #fac775;
  --wd-stat-survival: #97c459;
  --wd-rarity: #ef9f27;
  --wd-font-pixel: 'Press Start 2P', monospace;
  --wd-font-mono: 'Courier New', monospace;
}
```
