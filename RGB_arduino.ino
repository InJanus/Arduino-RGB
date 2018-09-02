

struct rgb{
  int green;
  int blue;
  int red;
};

int bluepin = 11;
int greenpin = 9;
int redpin = 10; 
int switchpin = 2;

int fadepin = 8;
int randompin = 7;
int deathpin = 4;
int brightpin = 3;
int mydelay = 1000;

int redmax = 255;
int bluemax = 255;
int greenmax = 255;

int dialswitch = 0;
int inputswitch = 0;
double endtime = 1;
bool fade = true;
bool dials = false;
bool dialflag = false;
bool randomvalue = false;

int redcount = 0;
int bluecount = 0;
int greencount = 0;


int count = 0;
int mynum;
//int thetime = 0;

bool HRO = false;

rgb thecolor;




void setup() {
  Serial.begin(9600);
  pinMode(redpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(switchpin, INPUT);
  pinMode(fadepin, INPUT);
  pinMode(randompin, INPUT);
  pinMode(deathpin, INPUT);
  pinMode(brightpin, INPUT);
  
  endtime = endtime*1.0;
  //Serial.write(redinc*1);
  //print(8888,DEC);
}

bool checkDial(){
  bool output = false;
  
   dialswitch = digitalRead(switchpin);
    if((dialswitch == HIGH)){
    if(dialflag == false){
      dials = !dials;
        thecolor.red = 0;
        thecolor.green = 0;
        thecolor.blue = 0;
        count = 0;
      output = true;
    }

    dialflag = true;
  }else{
    dialflag = false;
  }
  return output;
 }

 bool checkSwitch(){
  //this is for checking the switches on the other options
  
  inputswitch = digitalRead(fadepin);

  if(inputswitch == HIGH){
    fade = true;
  }else{
    fade = false;
    
  }

  inputswitch = digitalRead(randompin);

  if(inputswitch == HIGH){
    randomvalue = true;
  }else{
    randomvalue = false;
  }
  
 }

 bool checkBright(){
  bool output;
  inputswitch = digitalRead(brightpin);
  if(inputswitch == HIGH){
    output = true;
    for(;;){
      inputswitch = digitalRead(brightpin);
      analogWrite(redpin, redmax);
      analogWrite(bluepin, bluemax);
      analogWrite(greenpin, greenmax);
      redmax = (analogRead(0)/4);
      if(redmax > 255){
        redmax = 255;
      }
      bluemax = (analogRead(1)/4);
      if(bluemax > 255){
        bluemax = 255;
      }
      greenmax = (analogRead(2)/4);
      if(greenmax > 255){
        greenmax = 255;
      }
      if(inputswitch == LOW){
        break;
      }
    }
  }else{
    output = false;
  }
 }

 double getTime(){
  inputswitch = digitalRead(deathpin);
  if(inputswitch == HIGH){
    return 20.0;
  }
  return (analogRead(3)*6)+200;
 }
 

void setColor(rgb color){
  
    
    static rgb prev;
    rgb setcolors;
    setcolors.red = (int)((redmax/255.0)*color.red);
    setcolors.blue = (int)((bluemax/255.0)*color.blue);
    setcolors.green = (int)((greenmax/255.0)*color.green);

  
    double secondsfade = getTime(); //3 seconds
    if(dials == true){
      secondsfade = 1.0;
    }
     if(fade == true){
    double reddiff = ((setcolors.red-prev.red)/secondsfade);
    double bluediff = ((setcolors.blue-prev.blue)/secondsfade);
    double greendiff = ((setcolors.green-prev.green)/secondsfade);
  
    for(int i = 1; i <= (int)secondsfade; i++){
      analogWrite(redpin, (int)((prev.red)+(reddiff*i)));
      analogWrite(bluepin, (int)((prev.blue)+(bluediff*i)));
      analogWrite(greenpin, (int)((prev.green)+(greendiff*i)));
      delay(1);
      if(checkDial() == true){
        break;
      }if(checkBright() == true){
        break;
      }
    }
  
    analogWrite(redpin, setcolors.red);
    analogWrite(bluepin, setcolors.blue);
    analogWrite(greenpin, setcolors.green);
  
    prev.red = setcolors.red;
    prev.blue = setcolors.blue;
    prev.green = setcolors.green;
  }else{
    analogWrite(redpin, setcolors.red);
    analogWrite(bluepin, setcolors.blue);
    analogWrite(greenpin, setcolors.green);
    delay(secondsfade);
  }

  
}

void loop() {

  checkDial();
  checkSwitch();
  checkBright();
  Serial.print(redmax);
  Serial.print("\n");
  Serial.print(bluemax);
  Serial.print("\n");
  Serial.print(greenmax);
  Serial.print("\n");

  if(dials){
    thecolor.red = analogRead(0)/4;
    thecolor.blue = analogRead(1)/4;
    thecolor.green = analogRead(2)/4;
  }else{
    if(randomvalue == true){
      mynum = rand()%8;
    }
    mynum = count%7;
    switch (mynum){
      case 0:
        thecolor.red = 255;
        thecolor.green = 0;
        thecolor.blue = 0;
        break;
      case 1:
        thecolor.red = 255;
        thecolor.green = 50;
        thecolor.blue = 0;
        break;
       case 2:
        thecolor.red = 255;
        thecolor.green = 60;
        thecolor.blue = 128;
        break;
       case 3:
        thecolor.red = 0;
        thecolor.green = 0;
        thecolor.blue = 255;
        break;
       case 4:
        thecolor.red = 255;
        thecolor.green = 255;
        thecolor.blue = 255;
        break;
       case 5:
        thecolor.red = 0;
        thecolor.green = 255;
        thecolor.blue = 0;
        break;
       case 6:
        thecolor.red = 255;
        thecolor.green = 255;
        thecolor.blue = 0;
        break;
       case 7:
        thecolor.red = 50;
        thecolor.green = 0;
        thecolor.blue = 255;
        break;
    }
    
  
    
  
    
  
    count++;
    count = count%8;
    }
  
  setColor(thecolor);


}


