import { ANIMALS } from '../data/animals.js';

export function toSlug(name) {
  return name
    .toLowerCase()
    .replace(/\(/g, '')
    .replace(/\)/g, '')
    .replace(/\s+/g, '-');
}

export function fromSlug(slug) {
  const match = ANIMALS.find((a) => toSlug(a) === slug);
  return match || null;
}

export function entryNumberFor(name) {
  const idx = ANIMALS.findIndex((a) => a === name);
  return idx >= 0 ? idx + 1 : 0;
}

export function padEntry(n) {
  return String(n).padStart(3, '0');
}

export function randomSlug(exclude) {
  let pick;
  do {
    pick = ANIMALS[Math.floor(Math.random() * ANIMALS.length)];
  } while (toSlug(pick) === exclude && ANIMALS.length > 1);
  return toSlug(pick);
}
