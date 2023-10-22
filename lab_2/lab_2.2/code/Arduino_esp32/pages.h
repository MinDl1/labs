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
  <label for="log">Login:</label>
  <input type="text" id="log" placeholder="MinDl1" name="log"><br><br>
  <label for="pass">Password:</label>
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
      window.location.href = "/Auth"
    }
  };
  xhttp.open ("POST", "?login=" + login + "&passwd=" + passwd, true);
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
</Style>
<h1> Lab 4 </h1>
  <button id = Read class = "button1" onclick = 'getData("read")'> readData </button>
  <BR>
  <BR>
  <div class = "readData">
  Приложена карта: <span id = "readData"> 0 </span> <br>
  </div>
  <div class = "writeData">
  Прочитана карта: <span id = "writeData"> 0 </span> <br>
  </div>
  <div class = "output">
  Вывод: <span id = "output"> 0 </span> <br>
  </div>
</DIV>

<Script>

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData("read");
}, 2000); // частота обновления 2000 мсек

function getData (par) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var parse_resp = this.responseText.split(",");
      if(par == "read"){
        document.getElementById ("readData"). innerHTML = parse_resp[0];
        document.getElementById ("writeData"). innerHTML = parse_resp[1];
        document.getElementById ("output"). innerHTML = parse_resp[2];
      }
    }
  };
  if(par == "read"){
    xhttp.open ("POST", "getData?read_write=r", true);
  }
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";

const char MAIN_page_admin[] PROGMEM = R"=====(
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
</Style>
<h1> Lab 4 </h1>
  <form action="/code">
  <label for="code">Code:</label>
  <input type="text" id="code" placeholder="some_code" name="code"><br><br>
  </form>
  <button id = Write class = "button2" onclick = 'getData("write")'> writeData </button>
  <button id = Read class = "button1" onclick = 'getData("read")'> readData </button>
  <button id = openB class = "button3" onclick = 'getData("open")'> open </button>
	<button id = block class = "button4" onclick = 'getData("block")'> block/unblock </button>
  <BR>
  <BR>
  <div class = "readData">
  Приложена карта: <span id = "readData"> 0 </span> <br>
  </div>
  <div class = "writeData">
  Прочитана карта: <span id = "writeData"> 0 </span> <br>
  </div>
  <div class = "output">
  Вывод: <span id = "output"> 0 </span> <br>
  </div>
  <div class = "blocked">
  Заблокированно: <span id = "blocked"> 0 </span> <br>
  </div>
</DIV>

<Script>
var so = 0;
setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  if(so == 0){
    getData("read");
  }
}, 2000); // частота обновления 2000 мсек

function sleep(time) {
   return new Promise(resolve => setTimeout(resolve, time));
}

function getData (par) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var parse_resp = this.responseText.split(",");
      if(par == "read"){
        document.getElementById ("readData"). innerHTML = parse_resp[0];
        document.getElementById ("writeData"). innerHTML = parse_resp[1];
        document.getElementById ("output"). innerHTML = parse_resp[2];
        document.getElementById ("blocked"). innerHTML = parse_resp[3];
      }
      else if(par == "open"){
        document.getElementById ("output"). innerHTML = parse_resp[1];
        document.getElementById ("blocked"). innerHTML = parse_resp[2];
      }
      else if(par == "block"){
        document.getElementById ("output"). innerHTML = parse_resp[0];
        document.getElementById ("blocked"). innerHTML = parse_resp[1];
      }
      else if (par == "write"){
        document.getElementById ("readData"). innerHTML = parse_resp[0];
        document.getElementById ("writeData"). innerHTML = parse_resp[1];
        document.getElementById ("output"). innerHTML = parse_resp[2];
        document.getElementById ("blocked"). innerHTML = parse_resp[3];
        so = 0;
      }
    }
  };
  if(par == "read"){
    xhttp.open ("POST", "getData?read_write=r", true);
  }
  if(par == "write"){
    so = 1;
    sleep(4000);
    xhttp.open ("POST", "getData?read_write=w&wrin="+document.getElementById("code").value, true);
  }
  if(par == "open"){
    xhttp.open ("POST", "getData?open=o", true);
  }
  if(par == "block"){
    xhttp.open ("POST", "getData?open_close=c", true);
  }
  xhttp.send ();
}

</Script>
</Body>
</HTML>
)=====";