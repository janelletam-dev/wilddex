const SYSTEM_PROMPT = `You are WildDex, an animal encyclopedia that generates entries in the style of David Attenborough narrating a nature documentary. Your tone is warm, reverent, full of wonder, and occasionally dry-witted. Entries should be accessible to children aged 5-12 while still delighting adults.

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
}`;

function setCors(res) {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
}

function stripFences(text) {
  return text
    .replace(/^```(?:json)?\s*/i, '')
    .replace(/\s*```\s*$/i, '')
    .trim();
}

export default async function handler(req, res) {
  setCors(res);
  if (req.method === 'OPTIONS') return res.status(204).end();
  if (req.method !== 'POST') return res.status(405).json({ error: 'method not allowed' });

  const apiKey = process.env.CLAUDE_API_KEY;
  if (!apiKey) return res.status(500).json({ error: 'missing CLAUDE_API_KEY' });

  const { animal } = req.body || {};
  if (!animal || typeof animal !== 'string') {
    return res.status(400).json({ error: 'animal required' });
  }

  try {
    const response = await fetch('https://api.anthropic.com/v1/messages', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'x-api-key': apiKey,
        'anthropic-version': '2023-06-01',
      },
      body: JSON.stringify({
        model: 'claude-sonnet-4-20250514',
        max_tokens: 800,
        system: SYSTEM_PROMPT,
        messages: [
          { role: 'user', content: `Generate a WildDex entry for: ${animal}` },
        ],
      }),
    });

    if (!response.ok) {
      const detail = await response.text();
      return res.status(502).json({ error: 'claude error', detail });
    }

    const data = await response.json();
    const text = data?.content?.[0]?.text || '';
    const cleaned = stripFences(text);

    let parsed;
    try {
      parsed = JSON.parse(cleaned);
    } catch {
      return res.status(502).json({ error: 'invalid json from claude', raw: cleaned });
    }
    return res.status(200).json(parsed);
  } catch (e) {
    return res.status(500).json({ error: 'server error', detail: String(e) });
  }
}
