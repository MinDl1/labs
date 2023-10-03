const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<HTML>
<meta charset = "utf-8">
<Body>

<div id = "demo">
<h1> Аякс ... </h1>
	<button id = LEDState type = "button" onclick = "sendData(1900)"> 190.0 </button>
	<button type = "button" onclick = "sendData(2000)"> 200.0 </button>
	<button type = "button" onclick = "sendData(2100)"> 210.0 </button>
  <button type = "button" onclick = "sendData(2200)"> 220.0 </button>
	<BR>
  <BR>
</DIV>

<DIV>
	  Значение ADC: <span id = "ADCValue"> 0 </ span> <br>

</DIV>

<Script>
function sendData (led) {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("LEDState"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "setLED?LEDstate=" + led, true);
  xhttp.send ();
}

setInterval (function () {
  // Повторно вызвать функцию с интервалом 2 секунды
  getData();
}, 2000); // частота обновления 2000 мсек


function getData () {
  var xhttp = new XMLHttpRequest ();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById ("ADCValue"). innerHTML = this.responseText;
    }
  };
  xhttp.open ("GET", "readADC", true);
  xhttp.send ();
}


</Script>
</Body>
</HTML>
)=====";