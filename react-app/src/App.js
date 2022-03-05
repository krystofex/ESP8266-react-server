import "./App.css";
import { useState, useEffect } from "react";
import axios from "axios";

function App() {
  const [led, setLed] = useState(false);

  // fetch led data
  useEffect(() => {
    axios.get("/api").then((res) => {
      setLed(res.data.led);
    });
  }, []);

  useEffect(() => {
    axios.get("/api", { params: { led: led } });
  }, [led]);

  return (
    <div className="App">
      <header className="App-header">
        <p>Led is {led ? "on" : "off"}</p>
        Turn
        <a className="App-link" onClick={() => setLed(!led)}>
          {led ? "off" : "on"}
        </a>
        <p>
          Edit <code>react-app/src/App.js</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;
