/**
 * Variation Menu
 * Custom clickable menu with a Yar cursor
 */

"use strict";

let state = "menu";

//Menu buttons
let buttons = [
    { label: "Yars Revenge p5", x: 100, y: 150, w: 300, h: 60, target: "v1" },
    { label: "Yars PvP (2)   ", x: 100, y: 250, w: 300, h: 60, target: "v2" },
    { label: "Yars DarkSound ", x: 100, y: 350, w: 300, h: 60, target: "v3" }
];

//Draw menu
function menuDraw() {
    background(0);

    for (let b of buttons) {
        drawMenuButton(b);
    }

    drawYarCursor(mouseX, mouseY);
}

//Draw a single button
function drawMenuButton(btn) {
    let hover =
        mouseX > btn.x &&
        mouseX < btn.x + btn.w &&
        mouseY > btn.y &&
        mouseY < btn.y + btn.h;

    push();
    rectMode(CORNER);
    stroke(255);
    strokeWeight(2);
    fill(hover ? 70 : 40);
    rect(btn.x, btn.y, btn.w, btn.h, 10);

    fill(255);
    textAlign(CENTER, CENTER);
    textSize(26);
    text(btn.label, btn.x + btn.w / 2, btn.y + btn.h / 2);
    pop();
}

//Mouse click detection
function menuMousePressed() {
    for (let b of buttons) {
        if (
            mouseX > b.x &&
            mouseX < b.x + b.w &&
            mouseY > b.y &&
            mouseY < b.y + b.h
        ) {
            state = b.target;

            if (b.target === "v1") v1Setup();
            if (b.target === "v2") v2Setup();
            if (b.target === "v3") v3Setup();
        }
    }
}

//Keyboard for menu
function menuKeyPressed(event) {
    if (event.keyCode === 86) { state = "v1"; v1Setup(); } // V
    if (event.keyCode === 87) { state = "v2"; v2Setup(); } // W
    if (event.keyCode === 88) { state = "v3"; v3Setup(); } // X
}

//Draw Yar cursor
function drawYarCursor(x, y) {
    push();
    translate(x, y);
    noStroke();

    fill(255, 200, 50);
    ellipse(0, 0, 12, 18);

    fill(180, 220, 255, 180);
    ellipse(-10, -2, 12, 20);
    ellipse(10, -2, 12, 20);

    fill(255, 0, 0);
    ellipse(-3, -4, 3, 3);
    ellipse(3, -4, 3, 3);

    pop();
}
