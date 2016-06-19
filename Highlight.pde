int divs = 100;
int opacity = 0;
int rect_width = 2;

$( document ).on( "mousemove", function( event ) {
	mouseX = event.pageX;
});

void setup() {
  size(window.innerWidth, 5);
  frameRate(30);
  noStroke();
}

void draw() {
  if (width != window.innerWidth) {
  	  size(window.innerWidth, 5);
  }
  fill(200, 175, 0);
  rect(0, 0, width, height);
  
  for (int i = 0; i < divs; i++) {
    fill(255, 255, 255, opacity);
    rect(-1*(mouseX + rect_width * (i - divs/2)) + window.innerWidth, 0, rect_width, height);
    if (i < divs / 2) {
      opacity += 5;
    }
    else {
      opacity -= 5; 
    }
  }
}
