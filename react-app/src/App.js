import "./App.css";
import { useState, useEffect } from "react";
import axios from "axios";

function App() {
  const [led, setLed] = useState(null);

  // fetch led data
  useEffect(() => {
    console.log("fetching led data");
    axios.get("/api").then((res) => {
      console.log(res);
      setLed(res.data.led);
    });
  }, []);

  if (led === null)
    return (
      <div className="App">
        <header className="App-header">loading...</header>
      </div>
    );

  return (
    <div className="App">
      <header className="App-header">
        <p>Led is {led ? "on" : "off"}</p>
        Turn
        <a
          className="App-link"
          onClick={() => {
            const newLedVal = !led;
            setLed(newLedVal);
            axios.get("/api", { params: { led: newLedVal } });
          }}
        >
          {led ? "off" : "on"}
        </a>
      </header>
    </div>
  );
}

export default App;
