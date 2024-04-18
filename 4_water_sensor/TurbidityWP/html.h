/*
ESP32 HTML WebServer Page Code
http:://www.electronicwings.com
*/

const char html_page[] PROGMEM = R"rawSrting(
<!DOCTYPE html>
<html lang="en">

<head>
  <style>
    @import url("https://fonts.googleapis.com/css?family=Satisfy|Zilla+Slab");

    body {
      background: white;
    }

    .frame {
      position: absolute;
      top: 50%;
      left: 50%;
      width: 400px;
      height: 400px;
      margin-top: -200px;
      margin-left: -200px;
      border-radius: 2px;
      background-image: url("https://picsum.photos/200/300");

      box-shadow: 0.5rem 0.5rem 1rem rgba(0, 0, 0, 0.6);
      background: #201c29;
      font-family: sans-serif;
      color: #fff;
      -webkit-font-smoothing: antialiased;
      -moz-osx-font-smoothing: grayscale;
    }

    .card {
      position: absolute;
      top: 77px;
      left: 60px;
      height: 259px;
      width: 297px;
      background: #fff;
      border-radius: 5px;
      box-shadow: 0.5rem 0.5rem 1rem rgba(0, 0, 0, 0.6);
      overflow: hidden;
    }

    .card .header {
      position: relative;
      height: 60px;
      width: 100%;
      background: lightblue;
      color: #fff;
    }

    .card .header .big {
      position: absolute;
      font-family: sans-serif;
      font-size: 1.5rem;
    }

    .card .header .small {
      position: absolute;
      font-size: 1rem;
    }

    .card .header .title {
      top: 12px;
      left: 15px;
    }

    .card .header .date {
      top: 2.5rem;
      left: 15px;
    }

    .card .header .type {
      top: 14px;
      right: 15px;
    }

    .card .header .value {
      position: absolute;
      font-size: 1.5rem;
      top: 2rem;
      right: 15px;
    }

    .card .parameter {
      text-align: right;
      padding: 10px 0 14px 0;
    }

    .card .parameter span {
      position: relative;
      font-size: 0.85rem;
      color: #606060;
      line-height: 13px;
      padding: 0 10px 0 25px;
    }

    .card .parameter span:before {
      position: absolute;
      left: 6px;
      top: 6px;
      display: block;
      content: "";
      width: 11px;
      height: 4px;
      border-radius: 3px;
    }

    .card .parameter .red:before {
      background: greenyellow;
    }

    .card .parameter .blue:before {
      background: #547496;
    }

    .card .statistic {
      position: relative;
      height: 81px;
      width: 260px;
      margin: 0 auto;
    }

    .card .statistic .line-1,
    .card .statistic .line-3,
    .card .statistic .line-2 {
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      height: 2px;
      background: rgba(255, 192, 203, 0.3);
    }

    .card .statistic .line-2 {
      top: 40px;
    }

    .card .statistic .line-3 {
      top: inherit;
      bottom: 0;
    }

    .card .statistic .data svg {
      position: absolute;
      top: 0;
      left: 0;
      right: 0;
      bottom: 0;
      stroke-dasharray: 1000;
      stroke-dashoffset: 1000;
      -webkit-animation: 4s dash 0.5s linear forwards;
      animation: 4s dash 0.5s linear forwards;
    }

    @-webkit-keyframes dash {
      to {
        stroke-dashoffset: 0;
      }
    }

    @keyframes dash {
      to {
        stroke-dashoffset: 0;
      }
    }

    .card .statistic .data polyline {
      fill: none;
      stroke-width: 2;
      stroke-linecap: round;
    }

    .card .statistic .data.red polyline {
      stroke: #643a7a;
    }

    .card .statistic .data.blue polyline {
      stroke: #547496;
    }

    .card .statistic .data .tooltip {
      position: absolute;
      bottom: 13px;
      left: 50%;
      transform: translate3d(-50%, 10px, 0);
      font-weight: 600;
      font-size: 11px;
      line-height: 11px;
      color: greenyellow;
      padding: 8px 6px;
      border-radius: 3px;
      visibility: hidden;
      opacity: 0;
      transition: transform 0.4s ease-out 0s, opacity 0.4s ease-out 0s;
    }

    .card .statistic .data .tooltip:after {
      position: absolute;
      display: block;
      content: "";
      height: 6px;
      width: 6px;
      left: 50%;
      margin-left: -3px;
      bottom: -3px;
      transform: rotate(45deg);
    }

    .card .statistic .data [class^=point-] {
      position: absolute;
      width: 6px;
      height: 6px;
      border-radius: 3px;
      cursor: pointer;
      z-index: 10;
    }

    .card .statistic .data [class^=point-]:hover .tooltip {
      visibility: visible;
      opacity: 1;
      transform: translate3d(-50%, 0, 0);
    }

    .card .statistic .data.red [class^=point-],
    .card .statistic .data.red .tooltip,
    .card .statistic .data.red .tooltip:after {
      background: gre;
    }

    .card .statistic .data.red .point-1 {
      left: 7px;
      top: 43px;
    }

    .card .statistic .data.red .point-2 {
      left: 48px;
      top: 9px;
    }

    .card .statistic .data.red .point-3 {
      left: 88px;
      top: 20px;
    }

    .card .statistic .data.red .point-4 {
      left: 128px;
      top: 8px;
    }

    .card .statistic .data.red .point-5 {
      left: 169px;
      top: 35px;
    }

    .card .statistic .data.red .point-6 {
      left: 209px;
      top: 45px;
    }

    .card .statistic .data.red .point-7 {
      left: 249px;
      top: 16px;
    }

    .card .statistic .data.blue [class^=point-],
    .card .statistic .data.blue .tooltip,
    .card .statistic .data.blue .tooltip:after {
      background: #547496;
    }

    .card .statistic .data.blue .point-1 {
      left: 7px;
      top: 58px;
    }

    .card .statistic .data.blue .point-2 {
      left: 48px;
      top: 47px;
    }

    .card .statistic .data.blue .point-3 {
      left: 88px;
      top: 62px;
    }

    .card .statistic .data.blue .point-4 {
      left: 128px;
      top: 52px;
    }

    .card .statistic .data.blue .point-5 {
      left: 169px;
      top: 58px;
    }

    .card .statistic .data.blue .point-6 {
      left: 209px;
      top: 71px;
    }

    .card .statistic .data.blue .point-7 {
      left: 249px;
      top: 61px;
    }

    .card .days {
      width: 280px;
      margin: 0 auto;
    }

    .card .days .day {
      display: block;
      float: left;
      width: 14.2857142857%;
      font-size: 9px;
      color: #949494;
      line-height: 30px;
      text-transform: uppercase;
      text-align: center;
    }
  </style>
  <meta charset="UTF-8">
  <title>Water - Turbidity</title>
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/normalize/5.0.0/normalize.min.css">


</head>

<body>
  <!-- partial:index.partial.html -->
  <!-- Animates the numbers, add classes "odometer odometer-theme-default" and id "odometer"
<link rel="stylesheet" href="http://github.hubspot.com/odometer/themes/odometer-theme-default.css" />
<script src="http://github.hubspot.com/odometer/odometer.js"></script>
<link rel="stylesheet" href="odometer-theme-default.css" />
-->



  <div class="frame">
    <div class="card">
      <div class="header">
        <span class="title big">report</span>
        <span class="date small"></span>
        <span class="type small">Water Turbidity</span>
        <p><span id="Water" class="value">0%</span></p><br>


      </div>
      <div class="clearfix"></div>
      <div class="parameter">
        <span class="red">Water Turbidity</span>

      </div>
      <div class="statistic">
        <div class="line-1"></div>
        <div class="line-2"></div>
        <div class="line-3"></div>
        <div class="data red">
          <svg>
            <polyline points="9,46 50,12 90,23 130,11 171,38 211,48 251,19"></polyline>
          </svg>
          <div>
            <div class="point-1">
              <div class="tooltip">0</div>
            </div>
            <div class="point-7">
              <div class="tooltip" id="Water">0</div>
            </div>

            <div class="point-2">
              <div class="tooltip" id="Water">0</div>
            </div>
            <div class="point-3">
              <div class="tooltip" id="Water">20</div>
            </div>
            <div class="point-4">
              <div class="tooltip" id="Water">40</div>
            </div>
            <div class="point-5">
              <div class="tooltip" id="Water">60</div>
            </div>
            <div class="point-6">
              <div class="tooltip" id="Water">80</div>
            </div>
            <div class="point-7">
              <div class="tooltip" id="Water">100</div>
            </div>
          </div>
        </div>

        <!-- <div class="data blue">
			 	<svg>
			 		<polyline points="9,61 50,50 90,65 130,55 171,61 211,74 251,64"></polyline>    
			 	</svg>
			 	<div class="points">
			 		<div class="point-1">
			 			<div class="tooltip" id="Water">26</div>
			 		</div>
			 		<div class="point-2">
			 			<div class="tooltip" id="Water">41</div>
			 		</div>
			 		<div class="point-3">
			 			<div class="tooltip" id="Water">22</div>
			 		</div>
			 		<div class="point-4">
			 			<div class="tooltip" id="Water">36</div>
			 		</div>
			 		<div class="point-5">
			 			<div class="tooltip" id="Water">25</div>
			 		</div>
			 		<div class="point-6">
			 			<div class="tooltip" id="Water">13</div>
			 		</div>
			 		<div class="point-7">
			 			<div class="tooltip" id="Water">20</div>
			 		</div>
			 	</div>
			 </div> -->
      </div>
      <!-- <div class="days">
			<span class="day">Mon</span>
			<span class="day">Tue</span>
			<span class="day">Wed</span>
			<span class="day">Thu</span>
			<span class="day">Fri</span>
			<span class="day">Sat</span>
			<span class="day">Sun</span>
		</div> -->
    </div>
  </div>

  <div class="frame-2">
    <p>A turbidity sensor is a device used to measure the clarity of a liquid by determining the amount of suspended particles present in the fluid. Turbidity is a measure of the cloudiness or haziness of a fluid caused by suspended solids, such as sediment, silt, or other particles. Turbidity sensors are commonly employed in various industries and applications where water quality monitoring is crucial.</p>
  </div>

  <script>
    setInterval(function() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
    document.getElementById("WatValue").innerHTML = this.responseText;
    }
    };
    xhttp.open("GET", "readPurity", true);
    xhttp.send();
    },50);
    </script>

    <script>
      setInterval(function () {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("Water").innerHTML = this.responseText;
          }
        };
        xhttp.open("GET", "readPurity", true);
        xhttp.send();
      }, 50);
    </script>

</body>

</html>
)rawSrting";