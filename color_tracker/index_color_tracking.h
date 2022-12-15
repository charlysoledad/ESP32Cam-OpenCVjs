static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>COLOR DETECTION</title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width,initial-scale=1" />
    <script async src="https://docs.opencv.org/master/opencv.js" type="text/javascript"></script>
  </head>

  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: Verdana, Geneva, Tahoma, sans-serif 
    }
    html {
      background-color: #3a3a3a;
      color: #f0f0f0;
    }
    body{
      width: 100%;
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    button{
      padding: 8px 16px;
      margin: 12px 0;
      cursor: pointer;
    }

    .title {
      margin-bottom: 8px;
    }
    .gridProcessed {  display: grid;
      grid-template-columns: 1fr 1fr;
      grid-template-rows: 1fr 1fr;
      gap: 16px 16px;
      grid-auto-flow: row dense;
      justify-content: center;
      align-content: center;
      justify-items: center;
      align-items: center;
      grid-template-areas:
        "view1 view2"
        "view3 view3";
    }

    .view1 { grid-area: view1; }

    .view2 { grid-area: view2; }

    .view3 { grid-area: view3; }

    .section {
      width: 100%;
      display: flex;
      flex-direction: row;
      align-items: center;
      flex-wrap: nowrap;
      justify-content: center;
      gap: 25px;
    }

    .col {
      text-align: center;
    }

    @media screen and (-webkit-min-device-pixel-ratio:0) {
      .redTable input[type='range'] {
        margin-left: 10px;
        overflow: hidden;
        width: 120px;
        -webkit-appearance: none;
        background-color: #410909;
      }
      
      .redTable input[type='range']::-webkit-slider-runnable-track {
        height: 10px;
        -webkit-appearance: none;
        color: #13bba4;
        margin-top: -1px;
      }
      
      .redTable input[type='range']::-webkit-slider-thumb {
        width: 10px;
        -webkit-appearance: none;
        height: 10px;
        cursor: ew-resize;
        background: #e4e3e3;
        box-shadow: -80px 0 0 80px #f74343;
      }
      .blueTable input[type='range'] {
        margin-left: 10px;
        overflow: hidden;
        width: 120px;
        -webkit-appearance: none;
        background-color: #180941;
      }
      
      .blueTable input[type='range']::-webkit-slider-runnable-track {
        height: 10px;
        -webkit-appearance: none;
        color: #13bba4;
        margin-top: -1px;
      }
      
      .blueTable input[type='range']::-webkit-slider-thumb {
        width: 10px;
        -webkit-appearance: none;
        height: 10px;
        cursor: ew-resize;
        background: #e4e3e3;
        box-shadow: -80px 0 0 80px #437cf7;
      }
    }

    .redTable input[type="range"]::-moz-range-progress {
      background-color: #f74343; 
    }
    .redTable input[type="range"]::-moz-range-track {  
      background-color: #410909;
    }
    /* IE*/
    .redTable input[type="range"]::-ms-fill-lower {
      background-color: #f74343; 
    }
    .redTable input[type="range"]::-ms-fill-upper {  
      background-color: #410909;
    } 
    
    .blueTable input[type="range"]::-moz-range-progress {
      background-color: #437cf7; 
    }
    .blueTable input[type="range"]::-moz-range-track {  
      background-color: #180941;
    }
    /* IE*/
    .blueTable input[type="range"]::-ms-fill-lower {
      background-color: #437cf7; 
    }
    .blueTable input[type="range"]::-ms-fill-upper {  
      background-color: #180941;
    } 


  </style>

  <body>
    <div class="section">
      <div class="col">
      <h2 class="title">Controls</h2>
      <div class="buttons">
        <button id="restartBtn">Restart</button>
        <button id="stopBtn">Toggle Flash</button>
      </div>
      </div>
    </div>
    <div class="section">
      <div class="col">
        <h2>Original Source</h2>
        <img id="originalImage" src="" alt="" width="360px" height="240px"  style="display: none;"/>
        <canvas id="canvasInput" style="display: none;" ></canvas>
      </div>
      <div class="col">
        
        <table class="redTable">
          <thead>
            <tr>
              <th>RED COLOR</th>
            </tr>
          </thead>
          <tr>
            <td>H min:&#160;&#160;&#160;<span id="RED_HMIN"></span></td>
            <td>
              <input
                type="range"
                id="red_hmin"
                min="0"
                max="179"
                value="50"
                class="slider"
              />
            </td>
            <td>H max:&#160;&#160;&#160;<span id="RED_HMAX"></span></td>
            <td>
              <input
                type="range"
                id="red_hmax"
                min="0"
                max="179"
                value="179"
                class="slider"
              />
            </td>
          </tr>
          <tr>
            <td>S min:&#160;&#160;&#160;<span id="RED_SMIN"></span></td>
            <td>
              <input
                type="range"
                id="red_smin"
                min="0"
                max="255"
                value="55"
                class="slider"
              />
            </td>
            <td>S max:&#160;&#160;&#160;<span id="RED_SMAX"></span></td>
            <td>
              <input
                type="range"
                id="red_smax"
                min="0"
                max="255"
                value="255"
                class="slider"
              />
            </td>
          </tr>
          <tr>
            <td>V min:&#160;&#160;&#160;<span id="RED_VMIN"></span></td>
            <td>
              <input
                type="range"
                id="red_vmin"
                min="0"
                max="255"
                value="100"
                class="slider"
              />
            </td>
            <td>V max:&#160;&#160;&#160;<span id="RED_VMAX"></span></td>
            <td>
              <input
                type="range"
                id="red_vmax"
                min="0"
                max="255"
                value="255"
                class="slider"
              />
            </td>
          </tr>
        </table>
        <table class="blueTable">
          <thead>
            <tr>
              <th>BLUE COLOR</th>
            </tr>
          </thead>
          <tr>
            <td>H min:&#160;&#160;&#160;<span id="BLUE_HMIN"></span></td>
            <td>
              <input
                type="range"
                id="blue_hmin"
                min="0"
                max="179"
                value="11"
                class="slider"
              />
            </td>
            <td>H max:&#160;&#160;&#160;<span id="BLUE_HMAX"></span></td>
            <td>
              <input
                type="range"
                id="blue_hmax"
                min="0"
                max="179"
                value="100"
                class="slider"
              />
            </td>
          </tr>
          <tr>
            <td>S min:&#160;&#160;&#160;<span id="BLUE_SMIN"></span></td>
            <td>
              <input
                type="range"
                id="blue_smin"
                min="0"
                max="255"
                value="102"
                class="slider"
              />
            </td>
            <td>S max:&#160;&#160;&#160;<span id="BLUE_SMAX"></span></td>
            <td>
              <input
                type="range"
                id="blue_smax"
                min="0"
                max="255"
                value="255"
                class="slider"
              />
            </td>
          </tr>
          <tr>
            <td>V min:&#160;&#160;&#160;<span id="BLUE_VMIN"></span></td>
            <td>
              <input
                type="range"
                id="blue_vmin"
                min="0"
                max="255"
                value="60"
                class="slider"
              />
            </td>
            <td>V max:&#160;&#160;&#160;<span id="BLUE_VMAX"></span></td>
            <td>
              <input
                type="range"
                id="blue_vmax"
                min="0"
                max="255"
                value="255"
                class="slider"
              />
            </td>
          </tr>
        </table>
      </div>
    </div>
    <br />


    <button id="processImage">Process Image</button>
    <h2 class="title">Processed</h2>
    <div class="gridProcessed">
      <div class="view1">
        <h2 class="title">Red Masked</h2>
    <canvas style="display: none;" id="redMasked"></canvas>
      </div>
      <div class="view2">
        <h2 class="title">Blue Masked</h2>
    <canvas style="display: none;" id="blueMasked"></canvas>
      </div>
      <div class="view3">
        <h2 class="title">Tracked Masked</h2>
    <canvas style="display: none;" id="processedImage"></canvas>
    <iframe id="ifr" style="display:none"></iframe>

      </div>

    </div>

    <script text="text/javascript">
      let timer;
        let counter = 0;
        const host = document.location.origin;

        const originalSource = document.getElementById("originalImage");
        const originalCanvas = document.getElementById("canvasInput");
        const context = originalCanvas.getContext("2d");

        const processedSource = document.getElementById("processedImage");
        const redMasked = document.getElementById("redMasked");
        const blueMasked = document.getElementById("blueMasked");
        const processedContext = processedSource.getContext("2d");
        const redContext = redMasked.getContext("2d");
        const blueContext = blueMasked.getContext("2d");

        const processImage = document.getElementById("processImage");
        const threshold = document.getElementById("threshold");
        const thresholdValue = document.getElementById("threshValue");

        const restartBtn = document.getElementById("restartBtn");
        const stopBtn = document.getElementById("stopBtn");

        const ifr = document.getElementById('ifr');

        let RED_HMAX = 255;
        let RED_HMIN = 50;
        let RED_SMAX = 255;
        let RED_SMIN = 55;
        let RED_VMAX = 255;
        let RED_VMIN = 100;

        let BLUE_HMAX = 100;
        let BLUE_HMIN = 12;
        let BLUE_SMAX = 255;
        let BLUE_SMIN = 102;
        let BLUE_VMAX = 255;
        let BLUE_VMIN = 60;
        let updated = false;
        let isSended = false;

        originalSource.onload = function (event) {
          clearInterval(timer);
          counter = 0;
          originalCanvas.setAttribute("width", originalSource.width);
          originalCanvas.setAttribute("height", originalSource.height);
          originalCanvas.style.display = "block";

          redMasked.setAttribute("width", originalSource.width);
          redMasked.setAttribute("height", originalSource.height);
          redMasked.style.display = "block";

          blueMasked.setAttribute("width", originalSource.width);
          blueMasked.setAttribute("height", originalSource.height);
          blueMasked.style.display = "block";

          processedSource.setAttribute("width", originalSource.width);
          processedSource.setAttribute("height", originalSource.height);
          processedSource.style.display = "block";

          context.drawImage(
            originalSource,
            0,
            0,
            originalSource.width,
            originalSource.height
          );

          processingImage();
        };

        restartBtn.onclick = function () {
          fetch(host + "/?restart=stop");
        };
        stopBtn.onclick = function() {
          fetch(location.origin+"/?flash=stop");
        }

        async function processingImage() {
          console.log("Processing...");

          var RED_HMAXslider = document.getElementById("red_hmax");
        var RED_HMAXoutput = document.getElementById("RED_HMAX");
        RED_HMAXoutput.innerHTML = RED_HMAXslider.value;
        RED_HMAXslider.oninput = function () {
          RED_HMAXoutput.innerHTML = this.value;
          RED_HMAX = parseInt(RED_HMAXoutput.innerHTML, 10);
           
        };

        var RED_HMINslider = document.getElementById("red_hmin");
        var RED_HMINoutput = document.getElementById("RED_HMIN");
        RED_HMINoutput.innerHTML = RED_HMINslider.value;
        RED_HMINslider.oninput = function () {
          RED_HMINoutput.innerHTML = this.value;
          RED_HMIN = parseInt(RED_HMINoutput.innerHTML, 10);
           
        };

        var RED_SMAXslider = document.getElementById("red_smax");
        var RED_SMAXoutput = document.getElementById("RED_SMAX");
        RED_SMAXoutput.innerHTML = RED_SMAXslider.value;
        RED_SMAXslider.oninput = function () {
          RED_SMAXoutput.innerHTML = this.value;
          RED_SMAX = parseInt(RED_SMAXoutput.innerHTML, 10);
           
        };

        var RED_SMINslider = document.getElementById("red_smin");
        var RED_SMINoutput = document.getElementById("RED_SMIN");
        RED_SMINoutput.innerHTML = RED_SMINslider.value;
        RED_SMINslider.oninput = function () {
          RED_SMINoutput.innerHTML = this.value;
          RED_SMIN = parseInt(RED_SMINoutput.innerHTML, 10);
           
        };

        var RED_VMAXslider = document.getElementById("red_vmax");
        var RED_VMAXoutput = document.getElementById("RED_VMAX");
        RED_VMAXoutput.innerHTML = RED_VMAXslider.value;
        RED_VMAXslider.oninput = function () {
          RED_VMAXoutput.innerHTML = this.value;
          RED_VMAX = parseInt(RED_VMAXoutput.innerHTML, 10);
           
        };

        var RED_VMINslider = document.getElementById("red_vmin");
        var RED_VMINoutput = document.getElementById("RED_VMIN");
        RED_VMINoutput.innerHTML = RED_VMINslider.value;
        RED_VMINslider.oninput = function () {
          RED_VMINoutput.innerHTML = this.value;
          RED_VMIN = parseInt(RED_VMINoutput.innerHTML, 10);
           
        };

        var BLUE_HMAXslider = document.getElementById("blue_hmax");
        var BLUE_HMAXoutput = document.getElementById("BLUE_HMAX");
        BLUE_HMAXoutput.innerHTML = BLUE_HMAXslider.value;
        BLUE_HMAXslider.oninput = function () {
          BLUE_HMAXoutput.innerHTML = this.value;
          BLUE_HMAX = parseInt(BLUE_HMAXoutput.innerHTML, 10);
           
        };

        var BLUE_HMINslider = document.getElementById("blue_hmin");
        var BLUE_HMINoutput = document.getElementById("BLUE_HMIN");
        BLUE_HMINoutput.innerHTML = BLUE_HMINslider.value;
        BLUE_HMINslider.oninput = function () {
          BLUE_HMINoutput.innerHTML = this.value;
          BLUE_HMIN = parseInt(BLUE_HMINoutput.innerHTML, 10);
           
        };

        var BLUE_SMAXslider = document.getElementById("blue_smax");
        var BLUE_SMAXoutput = document.getElementById("BLUE_SMAX");
        BLUE_SMAXoutput.innerHTML = BLUE_SMAXslider.value;
        BLUE_SMAXslider.oninput = function () {
          BLUE_SMAXoutput.innerHTML = this.value;
          BLUE_SMAX = parseInt(BLUE_SMAXoutput.innerHTML, 10);
           
        };

        var BLUE_SMINslider = document.getElementById("blue_smin");
        var BLUE_SMINoutput = document.getElementById("BLUE_SMIN");
        BLUE_SMINoutput.innerHTML = BLUE_SMINslider.value;
        BLUE_SMINslider.oninput = function () {
          BLUE_SMINoutput.innerHTML = this.value;
          BLUE_SMIN = parseInt(BLUE_SMINoutput.innerHTML, 10);
           
        };

        var BLUE_VMAXslider = document.getElementById("blue_vmax");
        var BLUE_VMAXoutput = document.getElementById("BLUE_VMAX");
        BLUE_VMAXoutput.innerHTML = BLUE_VMAXslider.value;
        BLUE_VMAXslider.oninput = function () {
          BLUE_VMAXoutput.innerHTML = this.value;
          BLUE_VMAX = parseInt(BLUE_VMAXoutput.innerHTML, 10);
           
        };

        var BLUE_VMINslider = document.getElementById("blue_vmin");
        var BLUE_VMINoutput = document.getElementById("BLUE_VMIN");
        BLUE_VMINoutput.innerHTML = BLUE_VMINslider.value;
        BLUE_VMINslider.oninput = function () {
          BLUE_VMINoutput.innerHTML = this.value;
          BLUE_VMIN = parseInt(BLUE_VMINoutput.innerHTML, 10);
           
        };
          
          let isRed = false;
          let isBlue = false;
          let sourceImg = cv.imread(originalSource);

          let frameHSV = new cv.Mat(sourceImg.rows, sourceImg.cols, sourceImg.type());
          cv.cvtColor(sourceImg, frameHSV, cv.COLOR_BGR2HSV, 0);

          let blueMask = new cv.Mat();
          let blue_low = new cv.Mat(frameHSV.rows, frameHSV.cols, frameHSV.type(), [
            BLUE_HMIN,
            BLUE_SMIN,
            BLUE_VMIN,
            0,
          ]);
          let blue_high = new cv.Mat(frameHSV.rows, frameHSV.cols, frameHSV.type(), [
            BLUE_HMAX,
            BLUE_SMAX,
            BLUE_VMAX,
            255,
          ]);
          cv.inRange(frameHSV, blue_low, blue_high, blueMask);

          let redMask = new cv.Mat();
          let red_low = new cv.Mat(frameHSV.rows, frameHSV.cols, frameHSV.type(), [
            RED_HMIN,
            RED_SMIN,
            RED_VMIN,
            0,
          ]);
          let red_high = new cv.Mat(frameHSV.rows, frameHSV.cols, frameHSV.type(), [
            RED_HMAX,
            RED_SMAX,
            RED_VMAX,
            255,
          ]);
          cv.inRange(frameHSV, red_low, red_high, redMask);

          let contoursColor = new cv.Scalar(255, 255, 255);
          let rectangleColor = new cv.Scalar(10, 255, 10);

          let blueCountered = new cv.Mat(
            sourceImg.rows,
            sourceImg.cols,
            sourceImg.type()
          );
          let blue_contours = new cv.MatVector();
          let blue_hierarchy = new cv.Mat();

          let redCountered = new cv.Mat(
            sourceImg.rows,
            sourceImg.cols,
            sourceImg.type()
          );
          // let redTrack = cv.Mat.zeros(redCountered.rows, redCountered.cols, cv.CV_8UC3);
          let red_contours = new cv.MatVector();
          let red_hierarchy = new cv.Mat();

          try{
            cv.cvtColor(frameHSV, sourceImg, cv.COLOR_HSV2BGR, 0);
            
            cv.threshold(redMask, redCountered, 1, 200, cv.THRESH_BINARY);
            cv.findContours(
              redCountered,
              red_contours,
              red_hierarchy,
              cv.RETR_CCOMP,
              cv.CHAIN_APPROX_SIMPLE
            );

            cv.threshold(blueMask, blueCountered, 177, 200, cv.THRESH_BINARY);
            cv.findContours(
              blueCountered,
              blue_contours,
              blue_hierarchy,
              cv.RETR_CCOMP,
              cv.CHAIN_APPROX_SIMPLE
            );
  
            if (red_contours.get(0)) {
              isRed = true;
              updated = false;
              let red_cnt = red_contours.get(0);
              let rotatedRect = cv.minAreaRect(red_cnt);
              let vertices = cv.RotatedRect.points(rotatedRect);
  
              let rect = cv.boundingRect(red_cnt);
              /*let point1 = new cv.Point(rect.x, rect.y);
              let point2 = new cv.Point(rect.x + rect.width, rect.y + rect.height);
              cv.rectangle(sourceImg, point1, point2, rectangleColor, 1, cv.LINE_AA, 0); */
  
              for (let i = 0; i < 4; i++) {
                cv.line(
                  sourceImg,
                  vertices[i],
                  vertices[(i + 1) % 4],
                  rectangleColor,
                  1,
                  cv.LINE_AA,
                  0
                );
              }
  
              cv.putText(
                sourceImg,
                "RED Detected",
                new cv.Point(rect.x, rect.y - 5),
                cv.FONT_HERSHEY_SIMPLEX,
                0.5,
                rectangleColor,
                1,
                cv.LINE_AA
              );
              // red_cnt.delete();
            }else if (blue_contours.get(0)) {
              isBlue = true;
              updated = false;
              // cv.cvtColor(frameHSV, sourceImg, cv.COLOR_HSV2BGR, 0);
              let blue_cnt = blue_contours.get(0);
              let rotatedRect = cv.minAreaRect(blue_cnt);
              let vertices = cv.RotatedRect.points(rotatedRect);
  
              let rect = cv.boundingRect(blue_cnt);
              /*let point1 = new cv.Point(rect.x, rect.y);
              let point2 = new cv.Point(rect.x + rect.width, rect.y + rect.height);
              cv.rectangle(sourceImg, point1, point2, rectangleColor, 1, cv.LINE_AA, 0); */
  
              for (let i = 0; i < 4; i++) {
                cv.line(
                  sourceImg,
                  vertices[i],
                  vertices[(i + 1) % 4],
                  rectangleColor,
                  1,
                  cv.LINE_AA,
                  0
                );
              }
              cv.putText(
                sourceImg,
                "BLUE Detected",
                new cv.Point(rect.x, rect.y - 5),
                cv.FONT_HERSHEY_SIMPLEX,
                0.4,
                rectangleColor,
                1,
                cv.LINE_AA
              );
  
              // blue_cnt.delete();
            }else {
              cv.putText(
                sourceImg,
                "Nothing Detected",
                new cv.Point((sourceImg.cols/2)-5, (sourceImg.rows/2)-2),
                cv.FONT_HERSHEY_SIMPLEX,
                0.4,
                rectangleColor,
                1,
                cv.LINE_AA
              );
            }
  
            if ((isBlue || isRed) && !updated) {
              fetch(
                document.location.origin + "/?colors=" + (isRed?1:0) + ";" + (isBlue?1:0) + ";stop"
              );
            }else {
              fetch(location.origin +"/?colors=0;0;stop");
            }
          }catch(err){
            console.log(err);
          }

          if(isRed){
            cv.imshow("redMasked", redCountered);
          }
          if(isBlue){
            cv.imshow("blueMasked", blueCountered);
          }
          cv.imshow("processedImage", sourceImg);
          // cv.imshow("mask2Canvas", redTrack);

          /* MAIN ITEMS */
          sourceImg.delete();
          frameHSV.delete();

          /* BLUE TRACK */
          // blueTrack.delete();
          blue_contours.delete();
          blue_hierarchy.delete();
          blueCountered.delete();
          blueMask.delete();
          blue_low.delete();
          blue_high.delete();

          /* RED TRACK */
          // redTrack.delete();
          red_contours.delete();
          red_hierarchy.delete();
          redCountered.delete();
          redMask.delete();
          red_low.delete();
          red_high.delete();
          
          setTimeout(function () {
            originalSource.src =location.origin+'/?colorDetect='+Math.random();
          }, 500);
          
        }

        processImage.onclick = function () {
          try {
            clearInterval(timer);
            timer = setInterval(() => {
              error_handle();
            }, 5000);
            // originalSource.src = location.origin + imgs[randomImg];
            originalSource.src =location.origin+'/?colorDetect='+Math.random();

            processingImage();
          } catch (error) {
            console.log(error);
          }
        };

        var Module = {
          onRuntimeInitialized() {
            onOpenCvReady();
          },
        };

        function onOpenCvReady() {
          //alert("onOpenCvReady");
          console.log("OpenCV IS READY!!!");
          processingImage();
          // processingImage();
          // document.body.classList.remove("loading");
        }

        function error_handle() {
          counter++;
          clearInterval(timer);
          if (counter <= 2) {
            console.log("Get still error. Restart ESP32-CAM " + counter + " times.");
            timer = setInterval(function () {
              processImage.click();
            }, 10000);
            ifr.src = document.location.origin + "?restart";
          } else
            console.log(
              "Get still error. <br>Please close the page and check ESP32-CAM."
            );
        }

    </script>
  </body>
</html>
)rawliteral";
