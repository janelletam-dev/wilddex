# Contributing to WildDex

Thanks for wanting to contribute! WildDex is a passion project and we welcome help from the community.

## Ways to contribute

### Add animals to the browse database
The easiest contribution! Add new animals to the `animalDB[]` array in `firmware/wilddex.ino`. Keep them alphabetically sorted.

### Create pixel art sprites
We need 32x32 or 64x64 pixel art sprites for each animal. Use the turquoise cosmic palette. Save as PNG with transparent background in `website/public/sprites/`.

### New themes
Add new colour palettes alongside the turquoise cosmic theme. Define your colours as RGB565 hex values at the top of the firmware.

### Bug fixes
Found a crash, display glitch, or connection issue? Open an issue or submit a PR.

### New features
Check the roadmap in README.md. Pick something and let us know you're working on it by opening an issue first.

## How to submit

1. Fork the repo
2. Create a branch: `git checkout -b feature/your-feature`
3. Make your changes
4. Test on a real Cardputer if possible
5. Submit a Pull Request with a clear description

## Code style

- Use descriptive function names
- Comment complex logic
- Keep functions under 50 lines where possible
- Use the `WD_` colour constants, not hardcoded values
- Test on M5Cardputer board before submitting

## Important

- Never commit API keys! The credential lines should always say `YOUR_*`
- Keep memory usage low — the Cardputer has limited RAM (no PSRAM)
- Test WiFi reconnection — connections drop often on ESP32

## Questions?

Open an issue or reach out to [@janelletamayo](https://github.com/janelletamayo).
