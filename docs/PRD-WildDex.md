# WildDex — Product Requirements Document

| Field    | Value                          |
|----------|--------------------------------|
| Project  | WildDex                        |
| Version  | 1.0                            |
| Date     | 22 May 2026                    |
| Author   | Janelle D. Tamayo              |
| Status   | Draft                          |

---

## 1. Overview / Problem Statement

People — especially kids and kids at heart — encounter animals in everyday life at parks, zoos, beaches, and on neighbourhood walks, yet have no fun, tactile way to learn about them in the moment. Searching online returns walls of dry Wikipedia text with no sense of wonder or discovery. WildDex transforms animal curiosity into a nostalgic, Pokédex-style experience through a pocket-sized M5Stack Cardputer device paired with a companion web app — combining Game Boy pixel aesthetics, chiptune sound effects, David Attenborough-style voice narration, and collectible animated pixel creatures.

**Before WildDex:** You see a cool animal. You Google it. You get a Wikipedia article. You skim two sentences and move on. No joy. No discovery. No memory.

**After WildDex:** You see a cool animal. You pull out a tiny card from your pocket. You type a few letters, select the animal, and a pixelated stat card fills the screen with chiptune fanfare. A warm narrator voice tells you something wonderful about this creature. You show your friend — they scan the QR code and an animated pixel sprite bounces on their phone. You just added #037 to your collection. 212 to go.

---

## 2. Goals and Non-Goals

### Goals (v1)

- **G1:** User can type any animal name or dog breed and receive a Pokédex-style entry in under 5 seconds
- **G2:** Entries are read aloud via David Attenborough-style voice narration through the Cardputer speaker
- **G3:** Full Game Boy pixelated UI with bitmap fonts, chunky borders, and retro colour palette
- **G4:** Chiptune sound effects for boot, typing, scanning, and discovery (authentic 8-bit square wave tones)
- **G5:** QR code displayed on Cardputer that links to a companion web page with animated pixel creature, photos, and stats
- **G6:** Two series at launch — Wildlife and Dog Breeds
- **G7:** Personal discovery collection with "spotted in the wild" tagging and date stamps
- **G8:** Random encounter button for surprise animal discoveries
- **G9:** Letter-based filtering system for browsing animals (type a letter, see matching animals, scroll and select)
- **G10:** Serve as a first hands-on Cardputer/embedded development learning project

### Non-Goals (v1 — Saved for Later)

- **NG1:** Camera-based animal recognition via M5Stack camera module (v2)
- **NG2:** Additional series beyond Wildlife and Dog Breeds (Cat Breeds, Marine Life, Reptiles, Birds — future expansions)
- **NG3:** User accounts, login, or cloud sync
- **NG4:** Multiplayer features, trading creatures, or social sharing beyond QR
- **NG5:** Leaderboards or competitive features
- **NG6:** Offline mode with cached entries (v1 requires WiFi)
- **NG7:** Custom pixel art per animal (v1 uses generated/placeholder sprites)

---

## 3. Target Users

### Primary User: Kids and Kids at Heart

**Who they are:** Children aged 5–12 and nostalgic adults (millennials and Gen Z who grew up with Pokémon and Game Boy). Curious, playful people who love animals and respond to retro gaming aesthetics.

**Context:** They encounter animals in everyday life — at the zoo with family, walking the dog at the park, spotting a bird in the garden, seeing a breed they don't recognise. They want to learn, but in a way that feels like play, not homework.

**Pain points:**
- Traditional sources (Google, Wikipedia) are dry and text-heavy
- Kids who can't read fluently are excluded from text-only learning
- There's no sense of progression or collection — no reward for curiosity
- No physical, tactile gadget that makes learning feel special

**Technical comfort:** Low to medium. The device must be immediately intuitive — type, select, enjoy. No setup, no configuration, no menus to navigate.

### Secondary User: The Builder (Janelle)

**Who they are:** A product designer and vibe coder using this project as her first experience with M5Stack Cardputer and embedded development.

**Context:** Learning embedded programming (Arduino/PlatformIO) while building something genuinely fun and portfolio-worthy. Also uses WildDex as a demo piece at hackathons, tech events, and in-person meetings.

### Tertiary User: Bystanders / QR Scanners

**Who they are:** Friends, family, strangers, and hackathon attendees who interact with WildDex by watching it in use or scanning a QR code with their phone.

**Context:** They don't touch the Cardputer. Their experience is entirely through the companion web page — scanning a QR, seeing the animated pixel creature, and possibly sharing the link.

---

## 4. Jobs to Be Done

| ID  | Job | Priority |
|-----|-----|----------|
| J1  | When I see an animal I'm curious about, I want to type its name and get a fun Pokédex-style entry, so I can learn about it in a way that feels like play | P0 |
| J2  | When an entry loads, I want to hear it narrated in a warm Attenborough-style voice, so even if I can't read well I still enjoy the experience | P0 |
| J3  | When I boot up WildDex, I want to hear a chiptune jingle and see a pixel splash screen, so it feels like turning on a Game Boy | P0 |
| J4  | When I start typing a letter, I want to see a filtered list of matching animals, so I can browse and select without spelling the full name | P0 |
| J5  | When I want to switch between Wildlife and Dog Breeds, I want to pick a series from a menu, so I can explore different categories | P1 |
| J6  | When I discover an animal, I want to mark it as "spotted in the wild" with a date, so I can build my real-world collection | P1 |
| J7  | When I want a surprise, I want to hit a random button and discover something unexpected, so every session feels exciting | P1 |
| J8  | When I want to show someone my creature, I want a QR code on screen so they can scan it and see an animated pixel version on their phone | P1 |
| J9  | When I want to see my progress, I want to view my discovery count and collection grid, so I feel motivated to find more | P2 |

---

## 5. Functional Requirements

### 5.1 Boot & Splash Screen

| ID | Requirement |
|----|-------------|
| BOOT-01 | On power-on, WildDex plays a rising 3-note chiptune jingle (Game Boy-style startup sound) |
| BOOT-02 | A pixel art splash screen displays the WildDex logo with a simple animation (e.g., pixel globe spinning or creature silhouette appearing) for 2–3 seconds |
| BOOT-03 | After splash, the device attempts WiFi connection. If successful, transitions to the Series Select screen. If failed, displays "No WiFi — connect to explore" with retry option |
| BOOT-04 | WiFi credentials are hardcoded in firmware (configurable before flashing). No on-device WiFi setup in v1 |

### 5.2 Series Select Screen

| ID | Requirement |
|----|-------------|
| SERIES-01 | After boot, user sees a menu with available series: "Wildlife" and "Dog Breeds" |
| SERIES-02 | Each series shows a pixel icon, the series name, and discovery progress (e.g., "37 / 200 discovered") |
| SERIES-03 | User navigates with arrow keys and selects with Enter |
| SERIES-04 | Selected series loads the Browse/Search screen filtered to that series |

### 5.3 Browse & Search (Letter Filter)

| ID | Requirement |
|----|-------------|
| BROWSE-01 | On the search screen, a text input field with blinking pixel cursor is displayed at the top |
| BROWSE-02 | Each keypress produces a small "bip" chiptune sound |
| BROWSE-03 | As the user types letters, a scrollable list below filters to show all animals in the current series whose names start with the typed string |
| BROWSE-04 | The list shows animal names in pixel font, with a "▶" selector arrow on the currently highlighted item |
| BROWSE-05 | User scrolls the list with arrow keys (Up/Down) |
| BROWSE-06 | Pressing Enter on a highlighted animal triggers the Scan/Loading sequence |
| BROWSE-07 | A "Random" shortcut key (e.g., pressing "R" or a dedicated key) selects a random undiscovered animal from the current series |
| BROWSE-08 | The animal name database is stored locally on the Cardputer as a JSON or header file — no API call needed for browsing |
| BROWSE-09 | The local database contains approximately 200 entries per series (200 Wildlife + 200 Dog Breeds for v1) |

### 5.4 Scan / Loading Animation

| ID | Requirement |
|----|-------------|
| SCAN-01 | When an animal is selected, a "scanning" animation plays: horizontal bars filling up, pixelated progress effect |
| SCAN-02 | The scanning animation plays a descending trill chiptune sound ("BWEE-DEE-DEE-DEET") |
| SCAN-03 | During this animation, the device sends an API request to Claude to generate the entry |
| SCAN-04 | If the API call takes longer than the animation (>3 seconds), the animation loops until the response arrives |
| SCAN-05 | On API failure or timeout (>15 seconds), display a pixel art error screen: "Signal lost! Try again?" with retry option |

### 5.5 Entry Display (Stat Card)

| ID | Requirement |
|----|-------------|
| ENTRY-01 | The entry screen displays in full pixelated Game Boy aesthetic with chunky double-line borders |
| ENTRY-02 | Entry layout includes: Series badge and entry number (e.g., "WILDLIFE #037"), animal common name, classification (type/family), region/habitat, size range, weight range, rarity rating (1–5 stars), and a 2–3 sentence fun fact description |
| ENTRY-03 | All text renders in a monospaced bitmap pixel font |
| ENTRY-04 | A triumphant 4-note discovery jingle plays when the entry first appears ("DA-DA-DA-DAAAA") |
| ENTRY-05 | Text in the description area appears letter by letter with "bip" sounds (typewriter effect), matching the Pokédex text scroll style |
| ENTRY-06 | If this is the user's first time viewing this animal, it is automatically added to their discovery collection with the current date |
| ENTRY-07 | Bottom of screen shows action keys: [A] Speak, [B] QR Code, [C] Wild Spot, [D] Back |

### 5.6 Voice Narration

| ID | Requirement |
|----|-------------|
| VOICE-01 | Pressing the "Speak" key sends the entry text to ElevenLabs TTS API |
| VOICE-02 | The prompt to Claude includes instructions to write in a David Attenborough narration style — warm, reverent, wonder-filled, with occasional dry wit |
| VOICE-03 | Audio plays through the Cardputer's built-in I2S speaker |
| VOICE-04 | While audio plays, a small animated speaker icon pulses on screen |
| VOICE-05 | User can press any key to stop playback |
| VOICE-06 | ElevenLabs voice is configured with a warm, measured British narrator tone. Specific voice ID to be determined during development |
| VOICE-07 | Audio streaming should begin playback as soon as the first chunk arrives (streaming mode, not wait-for-full-file) |

### 5.7 QR Code Display

| ID | Requirement |
|----|-------------|
| QR-01 | Pressing the "QR Code" key generates and displays a QR code on the Cardputer screen |
| QR-02 | The QR code links to the companion web app URL: `wilddex.app/creature/{series}/{slug}` (e.g., `wilddex.app/creature/wildlife/red-fox`) |
| QR-03 | QR code is rendered in high-contrast black on white for reliable scanning, even on the small 240x135 display |
| QR-04 | The animal name is displayed above or below the QR code so the user knows what they're sharing |
| QR-05 | Pressing any key returns to the entry screen |

### 5.8 Wild Spot (Collection Tagging)

| ID | Requirement |
|----|-------------|
| SPOT-01 | Pressing the "Wild Spot" key tags the current animal as "spotted in the wild" |
| SPOT-02 | A special chiptune sound plays (distinct from the discovery jingle) to confirm the spot |
| SPOT-03 | The current date is stored alongside the wild spot tag |
| SPOT-04 | On the entry screen, wild-spotted animals show a small paw print icon or "WILD ✓" badge |
| SPOT-05 | Wild spot data is stored locally on the Cardputer's flash storage (persistent across reboots) |
| SPOT-06 | An animal can only be wild-spotted once. Pressing the key again shows "Already spotted!" |

### 5.9 Collection Screen

| ID | Requirement |
|----|-------------|
| COLL-01 | Accessible from the series select screen or via a shortcut key |
| COLL-02 | Displays a grid of small pixel silhouettes for all animals in the current series |
| COLL-03 | Discovered animals show their silhouette filled in; undiscovered animals show as dark/greyed outlines or question marks |
| COLL-04 | Wild-spotted animals show a small paw print badge on their silhouette |
| COLL-05 | Top of screen shows progress: "Discovered: 37 / 200 | Wild Spotted: 12" |
| COLL-06 | User can scroll through the grid and press Enter on a discovered animal to view its entry |

### 5.10 Chiptune Sound System

| ID | Requirement |
|----|-------------|
| SFX-01 | All sound effects are generated programmatically using square wave tone sequences (no audio files for chiptunes) |
| SFX-02 | Sound effect library includes: boot jingle (3-note rising), typing bip (single short tone per keypress), scan trill (descending 4-note sequence), discovery jingle (4-note triumphant — C, E, G, high C), wild spot confirmation (2-note ping), error sound (descending two-tone buzz), random encounter sound (rapid ascending 6-note run) |
| SFX-03 | Each sound is defined as an array of {frequency, duration} pairs |
| SFX-04 | Volume is fixed at a comfortable level for the I2S speaker (no volume control in v1) |

### 5.11 Claude API Integration

| ID | Requirement |
|----|-------------|
| API-01 | WildDex sends HTTPS POST requests to the Anthropic Messages API (`api.anthropic.com/v1/messages`) |
| API-02 | Model: `claude-sonnet-4-20250514` (balances quality and speed for a responsive device) |
| API-03 | System prompt instructs Claude to respond in a structured JSON format containing: entry number, common name, scientific name, classification, family, region, habitat, size range, weight range, rarity (1–5), description (2–3 sentences in David Attenborough narration style — warm, wonder-filled, occasionally witty), and a one-line narration script for TTS |
| API-04 | The user message contains the animal name and the series context (e.g., "Generate a WildDex entry for: Red Fox (Wildlife series)") |
| API-05 | Max tokens: 500 (entries should be concise for the small screen) |
| API-06 | API key is hardcoded in firmware (acceptable for a personal device; not exposed publicly) |
| API-07 | Response is parsed on-device from JSON into display fields |
| API-08 | Entries are cached locally after first retrieval — subsequent lookups for the same animal load from cache without an API call |

### 5.12 ElevenLabs TTS Integration

| ID | Requirement |
|----|-------------|
| TTS-01 | WildDex sends the narration text to the ElevenLabs TTS API via HTTPS |
| TTS-02 | Audio format: MP3 at the lowest acceptable quality for the Cardputer speaker (reduces bandwidth and latency) |
| TTS-03 | Audio is streamed and playback begins as soon as the first chunk is received |
| TTS-04 | TTS API key is hardcoded in firmware alongside the Claude API key |
| TTS-05 | TTS audio is cached locally alongside the entry data — repeat plays don't hit the API |

### 5.13 Companion Web App

| ID | Requirement |
|----|-------------|
| WEB-01 | Single-page web application hosted at `wilddex.app` (or similar domain) |
| WEB-02 | Route structure: `wilddex.app/creature/{series}/{slug}` (e.g., `/creature/wildlife/red-fox`) |
| WEB-03 | Each creature page displays: animated pixel sprite of the animal (bouncing, blinking, idle animation), the full stat card (matching the Cardputer layout but responsive for mobile), real photos of the animal (sourced from a free image API or curated set), a "Listen" button that plays the Attenborough-style narration, and the series badge and entry number |
| WEB-04 | The page is styled in the same Game Boy / retro pixel aesthetic as the Cardputer UI — pixel fonts, chunky borders, retro colour palette |
| WEB-05 | The page is fully responsive and optimised for mobile (primary use case is scanning a QR code with a phone) |
| WEB-06 | No login or account system in v1. The web page is a standalone viewer |
| WEB-07 | Built with React (aligning with Janelle's existing stack) |
| WEB-08 | When a creature page is loaded, it calls the Claude API to generate the entry (or serves from cache/pre-generated data) |
| WEB-09 | Open Graph meta tags are set so sharing the link on social media shows the animal name, a preview image, and "WildDex" branding |

---

## 6. Non-Functional Requirements

| ID | Requirement |
|----|-------------|
| NFR-01 | **Performance:** Entry generation (Claude API call → display) must complete within 5 seconds on a stable WiFi connection |
| NFR-02 | **Performance:** Letter filter browsing must feel instant — list filtering happens locally with no perceptible lag |
| NFR-03 | **Performance:** Voice narration should begin playing within 2 seconds of pressing the Speak key |
| NFR-04 | **Reliability:** The device must handle API failures gracefully — show friendly error messages, never crash or freeze |
| NFR-05 | **Storage:** Local cache (entries + TTS audio + collection data) must fit within the Cardputer's available flash storage (typical: 8MB available for user data). Cache strategy: LRU eviction if storage runs low |
| NFR-06 | **Accessibility:** Text on the Cardputer screen must be legible — minimum effective font size given the 240x135 display. High contrast pixel font (light text on dark background or vice versa) |
| NFR-07 | **Accessibility:** Voice narration serves as the primary accessibility feature — ensuring the experience works for users who can't read the small screen |
| NFR-08 | **Battery:** The Cardputer runs on its built-in battery. WiFi + API calls + speaker are power-intensive — target a minimum of 30 minutes of active use per charge |
| NFR-09 | **Web App Performance:** Companion web page must load in under 3 seconds on a mobile connection |
| NFR-10 | **Web App Responsiveness:** Companion web page must render correctly on mobile screens (360px and up) |
| NFR-11 | **Data Privacy:** No user data is collected or transmitted beyond API calls. No analytics, no tracking, no accounts in v1 |

---

## 7. User Flows

### Flow 1: First Boot & Discovery (Happy Path)

1. User powers on the Cardputer
2. Chiptune boot jingle plays; pixel splash screen shows WildDex logo for 2–3 seconds
3. Device connects to WiFi (credentials pre-configured)
4. Series Select screen appears: "Wildlife" and "Dog Breeds"
5. User selects "Wildlife" with arrow keys and Enter
6. Browse screen appears with blinking cursor
7. User types "F" — list filters to show Fox (Red), Fox (Arctic), Flamingo, Frog, etc.
8. User types "FO" — list narrows to Fox (Red), Fox (Arctic)
9. User presses Down arrow to highlight "Fox (Red)" and presses Enter
10. Scan animation plays with descending trill sound; API call fires in background
11. Entry stat card appears with discovery jingle — Fox #037, stats, rarity stars, fun description
12. Description text scrolls in letter by letter with bip sounds
13. User presses [A] — narration plays through speaker in Attenborough-style voice
14. User presses [B] — QR code appears on screen
15. Friend scans QR code → phone opens `wilddex.app/creature/wildlife/red-fox` with animated pixel fox, photos, and full stats
16. User presses [C] — "Spotted in the wild!" confirmation sound plays; paw print badge appears
17. User presses [D] — returns to browse screen to discover more

### Flow 2: Random Encounter

1. User is on the Browse screen
2. User presses the Random key
3. Wild encounter sound plays (rapid ascending notes)
4. A random undiscovered animal from the current series is selected
5. Scan animation plays; API call fires
6. Entry appears — surprise! It's a Pangolin!
7. Discovery jingle plays; animal added to collection

### Flow 3: QR Code Scan (Bystander)

1. Someone sees the WildDex owner using the device
2. Owner navigates to an entry and presses [B] for QR code
3. Bystander scans QR code with their phone camera
4. Phone browser opens `wilddex.app/creature/wildlife/pangolin`
5. Page loads with animated pixel pangolin sprite, stat card, real photos
6. Bystander taps "Listen" button — Attenborough narration plays from their phone
7. Bystander shares the link with a friend

---

## 8. Design and Technical Constraints

### Hardware

| Component | Specification |
|-----------|--------------|
| Device | M5Stack Cardputer (ESP32-S3) |
| Display | 240 x 135 px TFT LCD (ST7789) |
| Input | Built-in QWERTY keyboard |
| Audio | I2S speaker (supports tone generation and MP3 playback) |
| Connectivity | WiFi 802.11 b/g/n |
| Storage | 8MB Flash (shared with firmware; ~4–6MB available for user data) |
| Battery | Built-in LiPo |

### Firmware Stack

| Layer | Technology |
|-------|-----------|
| IDE | Arduino IDE or PlatformIO |
| Framework | Arduino (ESP32-S3 core) |
| Graphics | TFT_eSPI library or LovyanGFX for the ST7789 display |
| Audio (chiptune) | Programmatic tone generation via I2S (square wave synthesis) |
| Audio (TTS) | MP3 decoding via ESP8266Audio or similar library |
| HTTP Client | WiFiClientSecure + HTTPClient (for HTTPS API calls) |
| JSON Parsing | ArduinoJson library |
| QR Code | QRCode library for ESP32 |
| Local Storage | SPIFFS or LittleFS for cached entries and collection data |

### API Layer

| Service | Purpose | Auth |
|---------|---------|------|
| Anthropic Claude API | Generate animal entries (structured JSON) | API key (hardcoded) |
| ElevenLabs TTS API | Generate Attenborough-style voice narration | API key (hardcoded) |

### Companion Web App Stack

| Layer | Technology |
|-------|-----------|
| Framework | React (Vite) |
| Styling | Tailwind CSS with custom retro/pixel theme |
| Fonts | Press Start 2P or similar pixel web font |
| Hosting | Vercel (already connected) |
| Domain | `wilddex.app` (to be registered) |
| Image API | Unsplash API, Pexels API, or similar for animal photos |

### Design Constraints

| Constraint | Detail |
|-----------|--------|
| Colour palette | Game Boy-inspired greens (#0F380F, #306230, #8BAC0F, #9BBC0F) OR Pokédex red scheme — to be decided during visual design phase |
| Typography | Monospaced bitmap pixel font on Cardputer; Press Start 2P on web |
| Screen real estate | 240x135 is extremely limited — every pixel counts. Max ~15 characters per line at readable size; ~8 lines of content |
| Audio quality | I2S speaker is small — voice narration should be optimised for clarity at low fidelity (mid-range frequencies, moderate speed) |
| Pixel art | v1 uses simple silhouette sprites or procedurally generated shapes — not hand-drawn per-animal pixel art (scope constraint) |

---

## 9. Edge Cases and Error Handling

| Scenario | Expected Behaviour |
|----------|-------------------|
| No WiFi available at boot | Display friendly message: "No WiFi found! Connect to a network to start exploring." Show retry button |
| WiFi disconnects mid-session | Cached entries still viewable. New lookups show: "Signal lost! Reconnect to discover more." |
| Claude API returns error (rate limit, server error) | Display pixel art error screen with retry option. Do not crash. Message: "The WildDex signal is fuzzy... try again?" |
| Claude API returns malformed JSON | Catch parsing error, show generic error screen, log error to serial for debugging |
| ElevenLabs API fails or times out | Show message: "Voice unavailable — read the entry on screen!" Entry remains fully usable without audio |
| User types gibberish that matches no animal | Empty filter list shows: "No creatures found! Try another name." |
| User types a real animal not in the local database | Not found in v1 (database is curated). Show: "This creature hasn't been catalogued yet!" Future: allow free-text lookup |
| Cache storage full | Evict oldest cached entries (LRU) to make room for new ones. Collection/discovery data is never evicted |
| User tries to wild-spot an already-spotted animal | Show: "Already spotted! 🐾" with a gentle sound. No duplicate entries |
| QR code too small to scan reliably | Use QR code version with lowest error correction and shortest possible URL to maximise module size on 240x135 screen |
| Battery dies during API call | No special handling needed — ESP32 handles power loss gracefully. Cached data persists in flash |
| Very long animal name overflows screen | Truncate with "..." on the Cardputer display. Full name shown on companion web app |
| Companion web page accessed without valid slug | Show a friendly 404: "This creature hasn't been discovered yet!" with a link to the WildDex homepage |
| Multiple rapid key presses | Debounce input — ignore keypresses during animations or active API calls to prevent duplicate requests |

---

## 10. Success Metrics

| Metric | Target | How to Measure |
|--------|--------|----------------|
| Build completion | Ship a working v1 within 4 weeks | Functional Cardputer firmware + companion web page deployed |
| Animal database coverage | 200 Wildlife + 200 Dog Breeds entries in local database | Count entries in the JSON/header file |
| Entry generation speed | < 5 seconds from selection to stat card display | Manual testing with timer |
| Voice narration quality | Narration sounds warm, engaging, and Attenborough-like | Subjective listening test — would you show this to a friend? |
| Demo reaction | At least 3 people say "that's amazing" when shown the device | Count reactions at events/meetups |
| Collection engagement | Builder (Janelle) personally discovers 50+ animals within first month | Check collection counter |
| QR code reliability | QR code scans successfully on first attempt > 90% of the time | Test across 3+ phone models |
| Web companion load time | < 3 seconds on mobile | Lighthouse test |
| Learning outcome | Comfortable writing Arduino/ESP32 code by project end | Self-assessment |

---

## 11. Open Questions

1. **Colour palette:** Game Boy greens or Pokédex red? Could offer both as a firmware setting.
2. **ElevenLabs voice ID:** Which specific voice best approximates a warm British naturalist? Needs testing during development.
3. **Pixel art approach:** Hand-drawn silhouettes for common animals? AI-generated sprites? Procedural shapes? This decision affects scope significantly.
4. **Animal database source:** Curate the 200+200 list manually? Pull from an existing taxonomy API? Need to define the list and data format.
5. **Domain availability:** Is `wilddex.app` available? Alternatives: `wilddex.io`, `mywilddex.com`, etc.
6. **Companion web app image source:** Unsplash API (free, good quality) vs. Pexels API vs. curated image set?
7. **Entry number assignment:** Are entry numbers fixed per animal (Red Fox is always #037) or assigned in discovery order? Fixed numbers feel more authentic to the Pokédex.
8. **Rarity rating criteria:** What makes an animal 1-star vs. 5-star? Based on global population? Likelihood of encountering in the UK? Or purely fun/arbitrary?
9. **Screen character limit:** Need to prototype actual text layout on 240x135 to confirm how many characters/lines fit at a readable pixel font size.
10. **Cost per entry:** Claude API + ElevenLabs TTS per lookup — estimate cost to ensure it's sustainable for personal use. Caching mitigates repeat lookups.
11. **Future camera module:** Which M5Stack camera module is compatible with the Cardputer for the v2 animal recognition feature?

---

## Appendix A: Sound Design Reference

| Sound | Notes | Approximate Frequencies |
|-------|-------|------------------------|
| Boot jingle | 3-note rising tone (Game Boy startup feel) | C5 (523Hz), E5 (659Hz), G5 (784Hz) — 100ms each |
| Typing bip | Single short high tone per keypress | A6 (1760Hz) — 30ms |
| Scan trill | Descending 4-note sequence (Pokédex scan) | G5, E5, C5, G4 — 80ms each |
| Discovery jingle | Triumphant 4-note sequence | C5 (100ms), E5 (100ms), G5 (100ms), C6 (300ms) |
| Wild spot confirmation | Warm 2-note ping | E5 (100ms), G5 (200ms) |
| Random encounter | Rapid ascending 6-note run | C4, D4, E4, F4, G4, A4 — 60ms each |
| Error sound | Descending two-tone buzz | E4 (200ms), C4 (300ms) |

## Appendix B: Series Data Structure

```json
{
  "series": "wildlife",
  "version": 1,
  "animals": [
    {
      "id": 1,
      "name": "Red Fox",
      "slug": "red-fox",
      "searchTerms": ["fox", "red fox"]
    },
    {
      "id": 2,
      "name": "African Elephant",
      "slug": "african-elephant",
      "searchTerms": ["elephant", "african elephant"]
    }
  ]
}
```

## Appendix C: Claude API Prompt Template

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
  "description": "<2-3 sentences, Attenborough style>",
  "narrationScript": "<Full narration text for TTS, 4-6 sentences, Attenborough style>"
}

User: Generate a WildDex entry for: {animal_name} ({series_name} series). Entry number: {entry_number}.
```
