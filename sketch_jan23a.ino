//final project

//add
//button for calibration
//multiple base readings


const int pins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const int in0 = 0;
const int in1 = 1;
int base0;
int base1;
int curLight;

void setup() {
  for (int p = 0; p < 10; p++){
    pinMode(pins[p], OUTPUT);
  }
  Serial.begin(9600);

  calibrate();
}

void loop() {
  moveLight();
  printStatus();
}

void calibrate(){
  //visual pattern for calibration
  delay(1000);
  for (int p = 0; p <= 9; p++){
    light(pins[p]);
  }
  for (int p = 8; p >= 1; p--){
    light(pins[p]);
  }
  base0 = analogRead(in0);
  base1 = analogRead(in1);
  curLight = pins[5];
  Serial.print("BASE");
  Serial.print(base0);
  Serial.print(", ");
  Serial.println(base1);
}

void moveLight(){
  int cur0 = analogRead(in0);
  int cur1 = analogRead(in1);
  /*
  if (withinRange(base0, cur0, 30) && withinRange(base1, cur1, 30)){
    light(curLight);
  }else if ((base0 - cur0) > (base1 - cur1)){
    //base 0
    light(curLight + 2);
  }else{
    //base 1
    light(curLight - 2);
  }
  */
  if (withinRange(cur0, cur1, 10)){
    light(curLight);
  }
  if (cur0 < cur1){
    //left
    if (withinRange(cur0, cur1, 20) && !withinRange(cur0, cur1, 10)){
      light(curLight + 1);
    }
    if (withinRange(cur0, cur1, 40) && !withinRange(cur0, cur1, 20)){
      light(curLight + 2);
    }
    if (withinRange(cur0, cur1, 60) && !withinRange(cur0, cur1, 40)){
      light(curLight + 3);
    }
    if (withinRange(cur0, cur1, 80) && !withinRange(cur0, cur1, 60)){
      light(curLight + 4);
    }
    if (withinRange(cur0, cur1, 120) && !withinRange(cur0, cur1, 80)){
      light(curLight + 5);
    }
  }else{
    //right
    if (withinRange(cur0, cur1, 20) && !withinRange(cur0, cur1, 10)){
      light(curLight - 1);
    }
    if (withinRange(cur0, cur1, 40) && !withinRange(cur0, cur1, 20)){
      light(curLight - 2);
    }
    if (withinRange(cur0, cur1, 60) && !withinRange(cur0, cur1, 40)){
      light(curLight - 3);
    }
    if (withinRange(cur0, cur1, 80) && !withinRange(cur0, cur1, 60)){
      light(curLight - 3);
    }
    if (withinRange(cur0, cur1, 120) && !withinRange(cur0, cur1, 80)){
      light(curLight - 3);
    }
  }
  
}

void light(int pinNumber){ //lights pin with pinNumber for set amount of time
  digitalWrite(pinNumber, HIGH);
  delay(50);
  digitalWrite(pinNumber, LOW);
}

void printStatus() {
  Serial.print(analogRead(in0));
  Serial.print(", ");
  Serial.println(analogRead(in1));
}

bool withinRange(int n0, int n1, int range){ // TRUE if n1 within range of range of n0
  return abs(n1 - n0) < range;
}
