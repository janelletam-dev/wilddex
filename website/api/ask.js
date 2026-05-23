function setCors(res) {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
}

export default async function handler(req, res) {
  setCors(res);
  if (req.method === 'OPTIONS') return res.status(204).end();
  if (req.method !== 'POST') return res.status(405).json({ error: 'method not allowed' });

  const apiKey = process.env.CLAUDE_API_KEY;
  if (!apiKey) return res.status(500).json({ error: 'missing CLAUDE_API_KEY' });

  const { animal, question } = req.body || {};
  if (!animal || !question) {
    return res.status(400).json({ error: 'animal and question required' });
  }

  const prompt = `Answer this question about the ${animal} in 2-3 short sentences in a warm David Attenborough narration style: ${question}`;

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
        max_tokens: 400,
        messages: [{ role: 'user', content: prompt }],
      }),
    });

    if (!response.ok) {
      const detail = await response.text();
      return res.status(502).json({ error: 'claude error', detail });
    }

    const data = await response.json();
    const answer = data?.content?.[0]?.text?.trim() || '';
    return res.status(200).json({ answer });
  } catch (e) {
    return res.status(500).json({ error: 'server error', detail: String(e) });
  }
}
