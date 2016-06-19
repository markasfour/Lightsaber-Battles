StarSystem S;

var height_footer = $("#footer").height();

void setup() {
  size(window.innerWidth, height_footer);
  //surface.setResizable(true);
  S = new StarSystem();
  for (int i = 0; i < width + (height/2); i++) {
    S.addStar(); 
  }
}

void draw() {
  if (width != window.innerWidth) {
  	  size(window.innerWidth, height_footer);
	  S = new StarSystem();
  	  for (int i = 0; i < width + (height/2); i++) {
    	S.addStar(); 
	  }
  }
  fill(0); //<>//
  rect(0, 0, width, height);
  frameRate(1);
  S.run();
}

class StarSystem {
  ArrayList<Star> stars;

  StarSystem() {
    stars = new ArrayList<Star>(); 
  }

  void addStar() {
    stars.add(new Star()); 
  }
  
  void run() {
    fill(255, 255, 255);
    for (int i = 0; i < stars.size(); i++) {
      stars.get(i).display(); 
    }
  }
}

class Star {
  PVector location;
 
  Star() {
    location = new PVector(random(width), random(height)); 
  }
  
  void display() {
    ellipse(location.x, location.y, 2, 2); 
  }
}
