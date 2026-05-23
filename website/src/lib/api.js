export async function generateEntry(animal) {
  const res = await fetch('/api/generate', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ animal }),
  });
  if (!res.ok) throw new Error('generate failed');
  return res.json();
}

export async function askQuestion(animal, question) {
  const res = await fetch('/api/ask', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ animal, question }),
  });
  if (!res.ok) throw new Error('ask failed');
  return res.json();
}

export async function fetchTTS(text) {
  const res = await fetch('/api/tts', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ text }),
  });
  if (!res.ok) throw new Error('tts failed');
  return res.blob();
}
