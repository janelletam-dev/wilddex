import { Routes, Route } from 'react-router-dom';
import Landing from './pages/Landing.jsx';
import Entry from './pages/Entry.jsx';
import NotFound from './pages/NotFound.jsx';

export default function App() {
  return (
    <Routes>
      <Route path="/" element={<Landing />} />
      <Route path="/creature/:slug" element={<Entry />} />
      <Route path="*" element={<NotFound />} />
    </Routes>
  );
}
