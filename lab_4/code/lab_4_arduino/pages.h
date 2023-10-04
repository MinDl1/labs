const char Auth_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "lab">
<h1> Lab_4 </h1>
<form action="/send_auth">
  <label for="fname">Login:</label>
  <input type="text" id="log" name="log"><br><br>
  <label for="lname">Password:</label>
  <input type="text" id="pass" name="pass"><br><br>
</form>

	<button id = send_log_pass type = "button" onclick = 'sendData( document.getElementById("log").value, document.getElementById("pass").value)'> login </button>
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
<h1> Lab_4 </h1>
	<button id = DHT11 type = "button" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 type = "button" onclick = 'getHandle("MQ135")'> MQ135 </button>
	<button id = Flame_sensor type = "button" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet type = "button" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  Значение Temp: <span id = "DHT11_temp"> 0 </span> <br>
  Значение Wetness: <span id = "DHT11_wet"> 0 </span> <br>
  Значение PPM: <span id = "MQ135_ppm"> 0 </span> <br>
  Значение Flame: <span id = "Flame_sens"> 0 </span> <br>
  Значение Pump: <span id = "Pump_work"> 0 </span> <br>
  Значение Wet_ground: <span id = "Wet_ground"> 0 </span> <br>
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
<h1> Lab_4 </h1>
	<button id = Main_page type = "button" onclick = 'getHandle("")'> Main page </button>
	<button id = MQ135 type = "button" onclick = 'getHandle("MQ135")'> MQ135 </button>
	<button id = Flame_sensor type = "button" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet type = "button" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  Значение DHT11_temp: <span id = "DHT11_temp"> 0 </span> <br>
  Значение DHT11_wet: <span id = "DHT11_wet"> 0 </span> <br>
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
<h1> Lab_4 </h1>
	<button id = Main_page type = "button" onclick = 'getHandle("")'> Main page </button>
	<button id = DHT11 type = "button" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = Flame_sensor type = "button" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <button id = Pump_Wet type = "button" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  Значение MQ135_ppm: <span id = "MQ135_ppm"> 0 </span> <br>
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
<h1> Lab_4 </h1>
	<button id = Main_page type = "button" onclick = 'getHandle("")'> Main page </button>
	<button id = DHT11 type = "button" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 type = "button" onclick = 'getHandle("MQ135")'> MQ135 </button>
  <button id = Pump_Wet type = "button" onclick = 'getHandle("Pump_Wet")'> Pump_Wet </button>
  <BR>
  <BR>
  Значение Flame_sens: <span id = "Flame_sens"> 0 </span> <br>
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
<h1> Lab_4 </h1>
	<button id = Main_page type = "button" onclick = 'getHandle("")'> Main page </button>
	<button id = DHT11 type = "button" onclick = 'getHandle("DHT11")'> DHT11 </button>
	<button id = MQ135 type = "button" onclick = 'getHandle("MQ135")'> MQ135 </button>
  <button id = Flame_sensor type = "button" onclick = 'getHandle("Flame_sensor")'> Flame_sensor </button>
  <BR>
  <BR>
  Значение Pump_work: <span id = "Pump_work"> 0 </span> <br>
  Значение Wet_ground: <span id = "Wet_ground"> 0 </span> <br>
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