import { Home } from "./pages/Home";
import { ChartTest } from "./components/ChartTest";
import { Dashboard } from "./pages/Dashboard";

// Rotas
import { Routes } from "./routes";
import { BrowserRouter as Router } from "react-router-dom";

// Estilos
import { GlobalStyle } from "./styles/global";

function App() {
  return (
    <Router>
      <Routes />
      <GlobalStyle />
    </Router>
  );
}

export default App;
