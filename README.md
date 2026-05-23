# 🦊 WildDex — The Real-World Creature Encyclopedia

> A pocket-sized AI-powered Pokédex that runs on the M5Stack Cardputer. Type an animal name, get an Attenborough-style entry with stats, narration, and follow-up questions. Built with Claude API and ElevenLabs TTS.

![WildDex](https://img.shields.io/badge/Platform-M5Stack_Cardputer-00C9A7?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-blue?style=flat-square)
![Status](https://img.shields.io/badge/Status-Active_Development-brightgreen?style=flat-square)

## What is WildDex?

WildDex turns a credit card-sized M5Stack Cardputer into an AI-powered animal encyclopedia. Think of it as a real-life Pokédex — but for actual animals.

**Type an animal → get stats, facts, and narration → discover more**

### Features

- 🎮 **Turquoise cosmic pixel art UI** — retro Game Boy aesthetic with a cosmic twist
- 🧠 **Claude AI generates entries** — Attenborough-style descriptions with real animal data
- 📊 **RPG stat bars** — Speed, Wit, Power, Stealth, Survival ratings for every creature
- 🗣️ **Voice narration** — ElevenLabs TTS reads entries aloud via "Charles" narrator voice
- 🎵 **Chiptune sounds** — boot jingle, typing bips, scan trill, discovery fanfare
- 📝 **Typewriter text** — descriptions scroll letter by letter with classic Pokédex bips
- ❓ **Follow-up questions** — Claude suggests and answers curiosity questions
- 📋 **Browse list** — scroll through 80 pre-loaded animals, filter by typing
- 🎲 **Random encounter** — discover a surprise animal
- 🔤 **Spelling tolerance** — Claude figures out what you meant

## Hardware

- **M5Stack Cardputer** (or Cardputer ADV)
- WiFi connection (home WiFi or phone hotspot)
- Optional: Micro SD card for future caching

## Quick Start

### 1. Install Arduino IDE

Download from [arduino.cc](https://www.arduino.cc/en/software)

### 2. Add M5Stack board support

Go to **Arduino IDE → Settings → Additional boards manager URLs** and add:

```
https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
```

Then go to **Tools → Board → Boards Manager**, search "M5Stack" and install it.

### 3. Install libraries

Go to **Tools → Manage Libraries** and install:

- `M5Cardputer`
- `ArduinoJson` by Benoit Blanchon

### 4. Configure

Open `firmware/wilddex.ino` and update these lines with your credentials:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
const char* CLAUDE_API_KEY = "YOUR_ANTHROPIC_API_KEY";
const char* ELEVENLABS_API_KEY = "YOUR_ELEVENLABS_API_KEY";
```

You need:
- [Anthropic API key](https://console.anthropic.com/) for Claude
- [ElevenLabs API key](https://elevenlabs.io/) for voice narration (free tier works)

### 5. Flash

- Select **Tools → Board → M5Cardputer**
- Select your port under **Tools → Port**
- Click Upload (→ arrow)

### 6. Use it!

- **Type** an animal name and press **Enter** to search
- **B** to browse the animal list
- **R** to discover a random animal
- **Q** to see follow-up questions
- **A** to hear Charles narrate
- **DEL** to go back

## Controls

| Screen | Key | Action |
|--------|-----|--------|
| Input | `Enter` | Search animal |
| Input | `B` | Browse animal list |
| Input | `R` | Random encounter |
| Browse | `W/S` | Scroll up/down |
| Browse | `Enter` | Select animal |
| Browse | Type | Filter list |
| Browse | `DEL` | Back |
| Entry | `Q` | Show questions |
| Entry | `A` | Voice narration |
| Entry | `R` | Show last answer |
| Entry | `Enter` | New search |
| Entry | `DEL` | Back to input |
| Questions | `1/2` | Ask question |
| Questions | `DEL` | Back to entry |
| Answer | `R` | Back to entry |
| Answer | `Enter` | New search |

## Colour Palette — Turquoise Cosmic

| Colour | Hex | Usage |
|--------|-----|-------|
| Deep ocean | `#0a2a2a` | Background |
| Dark water | `#071f1f` | Card surfaces |
| Reef | `#0f3a3a` | Borders, bar backgrounds |
| Turquoise | `#5dcaa5` | Primary accent |
| Mint | `#9fe1cb` | Headings, highlights |
| Pale ice | `#e1f5ee` | Primary text |
| Deep teal | `#1d9e75` | Subtle accents |

## Project Structure

```
wilddex/
├── firmware/
│   └── wilddex.ino          # Cardputer firmware (Arduino)
├── website/                   # Companion web app (coming soon)
├── docs/
│   ├── PRD-WildDex.md        # Product requirements - Cardputer
│   └── PRD-WildDex-Website.md # Product requirements - Website
├── README.md
├── CONTRIBUTING.md
└── LICENSE
```

## Roadmap

- [x] Core animal lookup with Claude API
- [x] Stat bars (Speed, Wit, Power, Stealth, Survival)
- [x] Typewriter text with bips
- [x] Browse list with 80 animals
- [x] Random encounter
- [x] Follow-up questions with Q&A
- [x] Voice narration (ElevenLabs)
- [x] Turquoise cosmic theme
- [ ] QR code display → companion website
- [ ] Companion web app (React + Vercel)
- [ ] Pixel art sprites for each animal
- [ ] SD card caching (entries + audio)
- [ ] App launcher (WildDex + Claude Buddy + more)
- [ ] Dog Breeds series
- [ ] Collection tracking with "spotted in wild" tagging
- [ ] Display Cards (LinkedIn QR, conference badges)
- [ ] Step counter
- [ ] Voice input (speak instead of type)
- [ ] Battle mode

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. We welcome:

- New animals in the browse database
- UI improvements and new themes
- Bug fixes
- New features from the roadmap
- Pixel art sprites
- Documentation improvements

## API Costs

WildDex uses two paid APIs, but costs are minimal:

- **Claude API**: ~$0.003 per animal lookup
- **ElevenLabs**: Free tier gives ~50 narrations/month

With SD card caching (coming soon), repeat lookups are free.

## Credits

Built by [Janelle Tamayo](https://creativestallion.com) — Product Designer, Vibe Coder, Intentional Builder.

Inspired by Pokémon, David Attenborough, and the joy of discovering the natural world.

Special thanks to Sir David Attenborough for turning 100 and still inspiring wonder. 🎂

## License

MIT License — see [LICENSE](LICENSE) for details.
# wilddex
