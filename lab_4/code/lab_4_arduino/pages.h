const char Auth_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button {
  background-color: #4CAF50;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
input[type=text], select {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}
div {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
}
</Style>
<h1> Lab 4 </h1>
<form action="/send_auth">
  <label for="fname">Login:</label>
  <input type="text" id="log" placeholder="MinDl1" name="log"><br><br>
  <label for="lname">Password:</label>
  <input type="text" id="pass" placeholder="********" name="pass"><br><br>
</form>

	<button id = send_log_pass class="button" onclick = 'sendData( document.getElementById("log").value, document.getElementById("pass").value)'> login </button>
    <BR>
    <BR>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button1 {
  background-color: #66CDAA;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button2 {
  background-color: #808080;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button3 {
  background-color: #FF4500;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {
  background-color: #8B4513;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.DHT11 {
  background-color: #66CDAA;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.MQ135 {
  background-color: #808080;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.Flame_s {
  background-color: #FF4500;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.Pump_Wet {
  background-color: #8B4513;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</Style>
<h1> Lab 4 </h1>
	<button id = DHT11 class = "button1" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 class = "button2" onclick = 'getHandle("MQ135")'> MQ135 </button>
	<button id = Flame_sensor class = "button3" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet class = "button4" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  <div class = "DHT11">
  Значение Temp: <span id = "DHT11_temp"> 0 </span> <br>
  Значение Wetness: <span id = "DHT11_wet"> 0 </span> <br>
  </div>
  <div class = "MQ135">
  Значение PPM: <span id = "MQ135_ppm"> 0 </span> <br>
  </div>
  <div class = "Flame_s">
  Значение Flame: <span id = "Flame_sens"> 0 </span> <br>
  </div>
  <div class = "Pump_Wet">
  Значение Pump: <span id = "Pump_work"> 0 </span> <br>
  Значение Wet_ground: <span id = "Wet_ground"> 0 </span> <br>
  </div>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char DHT11_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button1 {
  background-color: #4CAF50;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button2 {
  background-color: #808080;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button3 {
  background-color: #FF4500;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {
  background-color: #8B4513;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.DHT11 {
  background-color: #66CDAA;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</Style>
<h1> Lab 4 </h1>
	<button id = Main_page class = "button1" onclick = 'getHandle("Root")'> Main page </button>
	<button id = MQ135 class = "button2" onclick = 'getHandle("MQ135")'> MQ135 </button>
	<button id = Flame_sensor class = "button3" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet class = "button4" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  <div class = "DHT11">
  Значение DHT11_temp: <span id = "DHT11_temp"> 0 </span> <br>
  Значение DHT11_wet: <span id = "DHT11_wet"> 0 </span> <br>
  </div>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char MQ135_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button1 {
  background-color: #4CAF50;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button2 {
  background-color: #66CDAA;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button3 {
  background-color: #FF4500;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {
  background-color: #8B4513;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.MQ135 {
  background-color: #808080;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</Style>
<h1> Lab 4 </h1>
	<button id = Main_page class = "button1" onclick = 'getHandle("Root")'> Main page </button>
	<button id = DHT11 class = "button2" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = Flame_sensor class = "button3" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet class = "button4" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  <div class = "MQ135">
  Значение MQ135_ppm: <span id = "MQ135_ppm"> 0 </span> <br>
  </div>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char Flame_sensor_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button1 {
  background-color: #4CAF50;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button2 {
  background-color: #66CDAA;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button3 {
  background-color: #808080;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {
  background-color: #8B4513;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.Flame_s {
  background-color: #FF4500;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</Style>
<h1> Lab 4 </h1>
	<button id = Main_page class = "button1" onclick = 'getHandle("Root")'> Main page </button>
	<button id = DHT11 class = "button2" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 class = "button3" onclick = 'getHandle("MQ135")'> MQ135 </button>
  <button id = Pump_Wet class = "button4" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  <div class = "Flame_s">
  Значение Flame_sens: <span id = "Flame_sens"> 0 </span> <br>
  </div>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char Pump_Wet_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<Style>
html{
	font-family: Helvetice;
    display:inline-block;
    margin: 0px auto;
    text-align: center;
}
.button1 {
  background-color: #4CAF50;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button2 {
  background-color: #66CDAA;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button3 {
  background-color: #808080;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.button4 {
  background-color: #FF4500;
  border: 1;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
.Pump_Wet {
  background-color: #8B4513;
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}
</Style>
<h1> Lab 4 </h1>
	<button id = Main_page class = "button1" onclick = 'getHandle("Root")'> Main page </button>
	<button id = DHT11 class = "button2" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 class = "button3" onclick = 'getHandle("MQ135")'> MQ135 </button>
  <button id = Flame_sensor class = "button4" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <BR>
  <BR>
  <div class = "Pump_Wet">
  Значение Pump_work: <span id = "Pump_work"> 0 </span> <br>
  Значение Wet_ground: <span id = "Wet_ground"> 0 </span> <br>
  </div>
</DIV>

<Script>
function sendData (login, passwd) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("DHT11_temp");
  getData("DHT11_wet");
  getData("MQ135_ppm");
  getData("Flame_sens");
  getData("Pump_work");
  getData("Wet_ground");
}, 2000); // частота обновления 2000 мсек


function getData (sensor) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById (sensor). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+sensor, true);
  xhttp.send ();
}

function getHandle(handle) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("lab"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "get"+handle, true);
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";