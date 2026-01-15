/**
 * Portrait
 * Lucas Meldrum
 * 
 * An abstract portrait containing many faces and eyes that follow the mouse
 * Click to change colors and in the 3D space for cool effects
 * Symbolizes vibrant personality (IDK LOL) just looks cool...
 * 
 */

"use strict";

// Pulse time
let pulse = 0;

// Pupil offset for following mouse
let pupilOffsetX, pupilOffsetY;

// Bigsphere
let bigSphere = {
  radius: 200,
  amount: 8,
  // Eyes
  eyes: {
    radius: 200,
    sizes: {
    pupil: 25,
    sclera: 10
    },
    fills: {
      sclera: 0,
      pupil: 255
    }
  }
};

// Minisphere 
let miniSphere = {
  radius: 7.5,
  // Eyes
  eyes: {
    radius: 7.5,
    fills: {
      sclera: 0,
      pupil: 255,
    }
  },
  fills: {
    r: 0,
    g: 0,
    b: 0
  }
};

// Background color
let backgroundColor = {
  fills: {
    r: 0,
    g: 0,
    b: 0
  }
};

// Setup the canvas, in 3D with normal material for the spheres
function setup() {
  createCanvas(500, 500, WEBGL);
  angleMode(DEGREES);
  normalMaterial();
}

// Draw, gets called once a frame
function draw() {
  // Copy current sphere colors
  backgroundColor.fills.r = miniSphere.fills.r;
  backgroundColor.fills.g = miniSphere.fills.g;
  backgroundColor.fills.b = miniSphere.fills.b;

  // Whichever color dominates the background is reduced by half
  if (miniSphere.fills.r > miniSphere.fills.g && miniSphere.fills.r > miniSphere.fills.b) {
    backgroundColor.fills.r = miniSphere.fills.r * 0.5;
  }
  else if (miniSphere.fills.g > miniSphere.fills.r && miniSphere.fills.g > miniSphere.fills.b) {
    backgroundColor.fills.g = miniSphere.fills.g * 0.5;
  }
  else if (miniSphere.fills.b > miniSphere.fills.r && miniSphere.fills.b > miniSphere.fills.g) {
    backgroundColor.fills.b = miniSphere.fills.b * 0.5;
  }

  // Change background based on conditionals
  background(backgroundColor.fills.r, backgroundColor.fills.g, backgroundColor.fills.b);

  // Pulse based on frame count and decrease (50 to 0)
  if (pulse > 0) {
    scale(1 + sin(frameCount * 10) * 0.2);
    pulse--;
  }

  // Allows for control of the canvas, in the 3D space
  orbitControl();

  // Draw main face sphere using little spheres
  push();
  drawSphere();
  pop();

  // Draw eyes
  drawEyes();
}

// Draw all spheres
function drawSphere() {
  for (let lat = -90; lat <= 90; lat += bigSphere.amount) {
    for (let lon = 0; lon < 360; lon += bigSphere.amount) {
      let px = bigSphere.radius * cos(lat) * cos(lon);
      let py = bigSphere.radius * sin(lat);
      let pz = bigSphere.radius * cos(lat) * sin(lon);

      push();
      translate(px, py, pz);
      // Body of the mini-sphere
      fill(miniSphere.fills.r, miniSphere.fills.g, miniSphere.fills.b);
      sphere(miniSphere.radius);
      // Add tiny eyes
      drawMiniEyes();
      pop();
    }
  }
}

// Pulse on mouse press (0-50)
function mousePressed() {
  pulse = 50;

  // Update .fills values with random colors
  miniSphere.fills.r = random(255);
  miniSphere.fills.g = random(255);
  miniSphere.fills.b = random(255);
}

// Draws eyes on a mini-sphere
function drawMiniEyes() {
  pupilOffsetX = map(mouseX, 0, width, -miniSphere.eyes.radius / 4, miniSphere.eyes.radius / 4);
  pupilOffsetY = map(mouseY, 0, height, -miniSphere.eyes.radius / 4, miniSphere.eyes.radius / 4);

  // Left eye
  push();
  translate(-miniSphere.eyes.radius / 2, -miniSphere.eyes.radius / 2, miniSphere.eyes.radius + 2);
  fill(miniSphere.eyes.fills.pupil);
  sphere(miniSphere.eyes.radius / 4);
  translate(pupilOffsetX, pupilOffsetY, miniSphere.eyes.radius/ 4);
  fill(miniSphere.eyes.fills.sclera);
  sphere(miniSphere.eyes.radius / 8);
  pop();

  // Right eye
  push();
  translate(miniSphere.eyes.radius / 2, -miniSphere.eyes.radius / 2, miniSphere.eyes.radius + 2);
  fill(miniSphere.eyes.fills.pupil);
  sphere(miniSphere.eyes.radius / 4);
  translate(pupilOffsetX, pupilOffsetY, miniSphere.eyes.radius / 4);
  fill(miniSphere.eyes.fills.sclera);
  sphere(miniSphere.eyes.radius / 8);
  pop();
}

// Draw the main eyes
function drawEyes() {

  // Rotate eyes based on frame count
  rotateWithFrameCount();

  // Left eye
  push();
  translate(-60, -50, bigSphere.eyes.radius - 10);
  fill(bigSphere.eyes.fills.pupil);
  sphere(bigSphere.eyes.sizes.pupil);
  translate(0, 0, 20);
  fill(bigSphere.eyes.fills.sclera);
  sphere(bigSphere.eyes.sizes.sclera);
  pop();

  // Right eye
  push();
  translate(60, -50, bigSphere.eyes.radius - 10);
  fill(bigSphere.eyes.fills.pupil);
  sphere(bigSphere.eyes.sizes.pupil);
  translate(0, 0, 20);
  fill(bigSphere.eyes.fills.sclera);
  sphere(bigSphere.eyes.sizes.sclera);
  pop();
}

// Rotate function found on the p5 documentation
function rotateWithFrameCount() {
  rotateZ(frameCount);
  rotateX(frameCount);
  rotateY(frameCount);
}

