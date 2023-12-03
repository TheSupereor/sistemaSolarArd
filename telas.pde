import gifAnimation.*;


import processing.sound.*;
SoundFile file;
SoundFile file1;
SoundFile file2;

PImage img;

PImage img1;

PImage img2;

PImage img3;

PImage img4;


Gif myAnimation;
Gif myAnimation1;
Gif myAnimation2;
int value = 0;


void setup() {

  fullScreen();

  myAnimation = new Gif(this, "earth.gif");

  myAnimation1 = new Gif(this, "sol.gif");

  myAnimation2 = new Gif(this, "lua.gif");

  myAnimation.play();

  myAnimation1.play();

  myAnimation2.play();
  



  img = loadImage("TELA 1.png");

  img1 = loadImage("borda.png");

  img2 = loadImage("tela terra.png");

  img3 = loadImage("tela sol.png");

  img4 = loadImage("tela lua.png");

  file1 = new SoundFile(this, "musica.mp3");
  file1.loop();
  file1.amp(0.5);


  file = new SoundFile(this, "audio intro.wav");
  file.play();
  file.amp(0.5);

  file2 = new SoundFile(this, "audio switch.mp3");
  

}

void draw() {

  image(img, 0, 0, width, height);
  
  if(keyCode == UP){
    terra();
  }

  if(keyCode == RIGHT){
    lua();
  }

  if(keyCode == LEFT){
    sol();
  }
}

void keyPressed(){
  if(value == 0)
  {
    file2.play();
  }
}

void terra(){

image(img2, 0,0,width, height);
image(myAnimation, width/33, height/16.5, width*0.261, height*0.468);

image(img1, 0, 0, width, height);
}

void sol(){

image(img3, 0, 0, width, height);
image(myAnimation1, width/33, height/16.5, width*0.261, height*0.468);

image(img1, 0, 0, width, height);
}

void lua(){

image(img4, 0, 0, width, height);
image(myAnimation2, width/33, height/16.5, width*0.261, height*0.468);

image(img1, 0, 0, width, height);
}
