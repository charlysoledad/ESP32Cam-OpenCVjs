let timer;
let counter = 0;
const host = "tu_IP";

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

const ifr = document.getElementById("ifr");

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
  fetch(host + "/?restart=stop", { mode: "no-cors" });
};
stopBtn.onclick = function () {
  fetch(host + "/?flash=stop", { mode: "no-cors" });
};

async function processingImage() {
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
  originalSource.crossOrigin = "Anonymous";
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
  let blue_M00Array = [0];

  let redCountered = new cv.Mat(
    sourceImg.rows,
    sourceImg.cols,
    sourceImg.type()
  );
  // let redTrack = cv.Mat.zeros(redCountered.rows, redCountered.cols, cv.CV_8UC3);
  let red_contours = new cv.MatVector();
  let red_hierarchy = new cv.Mat();
  let red_M00Array = [0];

  try {
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

    if (red_contours.size() > 0) {
      let cnt;
      let Moments;
      for (let kR = 0; kR < red_contours.size(); kR++) {
        cnt = red_contours.get(kR);
        Moments = cv.moments(cnt, false);
        red_M00Array[kR] = Moments.m00;
      }

      let maxArea = MaxAreaArg(red_M00Array, frameHSV.rows * frameHSV.cols);

      if (maxArea >= 0) {
        let red_cnt = red_contours.get(
          MaxAreaArg(red_M00Array, frameHSV.rows * frameHSV.cols)
        );
        let area = red_cnt.size().width * red_cnt.size().height;
        if (area > 60) {
          isRed = true;
          let rotatedRect = cv.minAreaRect(red_cnt);
          let vertices = cv.RotatedRect.points(rotatedRect);

          let rect = cv.boundingRect(red_cnt);

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
        }
        red_cnt.delete();
      }
      cnt.delete();
    }
    if (blue_contours.size() > 0) {
      let cnt;
      let Moments;
      for (let kR = 0; kR < blue_contours.size(); kR++) {
        cnt = blue_contours.get(kR);
        Moments = cv.moments(cnt, false);
        blue_M00Array[kR] = Moments.m00;
      }

      let maxArea = MaxAreaArg(blue_M00Array, frameHSV.rows * frameHSV.cols);

      if (maxArea >= 0) {
        let blue_cnt = blue_contours.get(
          MaxAreaArg(blue_M00Array, frameHSV.rows * frameHSV.cols)
        );
        let area = blue_cnt.size().width * blue_cnt.size().height;
        if (area > 60) {
          isBlue = true;
          let rotatedRect = cv.minAreaRect(blue_cnt);
          let vertices = cv.RotatedRect.points(rotatedRect);

          let rect = cv.boundingRect(blue_cnt);

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
        }
        blue_cnt.delete();
      }
      cnt.delete();
    } else {
      cv.putText(
        sourceImg,
        "Nothing Detected",
        new cv.Point(sourceImg.cols / 2 - 55, sourceImg.rows / 2 + 4),
        cv.FONT_HERSHEY_SIMPLEX,
        0.4,
        rectangleColor,
        1,
        cv.LINE_AA
      );
    }

    if (isBlue || isRed) {
      fetch(
        host + "/?colors=" + (isRed ? 1 : 0) + ";" + (isBlue ? 1 : 0) + ";stop",
        { mode: "no-cors" }
      );
    } else {
      fetch(host + "/?colors=0;0;stop", { mode: "no-cors" });
    }
  } catch (err) {
    console.log(err);
  }

  if (isRed) {
    cv.imshow("redMasked", redCountered);
  }
  if (isBlue) {
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
    originalSource.src = host + "/?colorDetect=" + Math.random();
  }, 750);
}

processImage.onclick = function () {
  try {
    clearInterval(timer);
    timer = setInterval(() => {
      error_handle();
    }, 5000);
    // originalSource.src = location.origin + imgs[randomImg];
    originalSource.src = host + "/?colorDetect=" + Math.random();

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
function MaxAreaArg(arr, aarea) {
  if (arr.length == 0) {
    return -1;
  }

  var max = arr[0];
  var maxIndex = 0;
  var dupIndexCount = 0; //duplicate max elements?

  if (arr[0] >= 0.9 * aarea) {
    max = 0;
  }

  for (var i = 1; i < arr.length; i++) {
    if (arr[i] > max && arr[i] < 0.99 * aarea) {
      maxIndex = i;
      max = arr[i];
      dupIndexCount = 0;
    } else if (arr[i] == max && arr[i] != 0) {
      dupIndexCount++;
    }
  }

  if (dupIndexCount == 0) {
    return maxIndex;
  } else {
    return -2;
  }
} //end MaxAreaArg

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
    ifr.src = host + "?restart";
  } else
    console.log(
      "Get still error. <br>Please close the page and check ESP32-CAM."
    );
}
