//final project

//double width of light and fix off-center problem?

const int pins[] = {13, 12, 11, 10, 9, 8, 7, 6, 5, 4};
const int in0 = 0;
const int in1 = 1;
int base0;
int base1;
int curLight = pins[5];

void setup() {
  for (int p = 0; p < 10; p++){
    pinMode(pins[p], OUTPUT);
  }
  Serial.begin(9600);
  calibrate();
  pinMode(3, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() {
  if (!digitalRead(3)){  //if button pressed
    calibrate();
  }
  moveLight();
  printStatus();
}

void calibrate(){  //calibration and light pattern
  Serial.print("calibrating...");
  delay(100);
  int b0[] = {0, 0, 0};
  int b1[] = {0, 0, 0};
  for (int i = 0; i < 3; i++){
    for (int p = 0; p <= 9; p++){
      light(pins[p]);
    }
    for (int p = 8; p >= 1; p--){
      light(pins[p]);
    }
    b0[i] = analogRead(in0);
    b1[i] = analogRead(in1);
  }
  base0 = (b0[0] + b0[1] + b0[2]) / 3;  //intentionally left as an int
  base1 = (b1[0] + b1[1] + b1[2]) / 3;
  
  Serial.print("BASE:");
  Serial.print(base0);
  Serial.print(", ");
  Serial.println(base1);

  digitalWrite(2, HIGH);  //blink LED twice
  delay(100);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);
  digitalWrite(2, LOW);
}

void moveLight(){
  int cur0 = analogRead(in0);
  int cur1 = analogRead(in1);
  if (withinRange(cur0, cur1, 10)){
    light(curLight);
  }
  if (cur0 < cur1){
    //left
    if (withinRange(cur0, cur1, 20) && !withinRange(cur0, cur1, 10)){
      light(curLight + 1);
    }
    if (withinRange(cur0, cur1, 35) && !withinRange(cur0, cur1, 20)){
      light(curLight + 2);
    }
    if (withinRange(cur0, cur1, 50) && !withinRange(cur0, cur1, 35)){
      light(curLight + 3);
    }
    if (withinRange(cur0, cur1, 65) && !withinRange(cur0, cur1, 50)){
      light(curLight + 4);
    }
    if (withinRange(cur0, cur1, 1000) && !withinRange(cur0, cur1, 65)){
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
    if (withinRange(cur0, cur1, 1000) && !withinRange(cur0, cur1, 60)){
      light(curLight - 4);
    }
  }
  
}

void light(int pinNumber){ //lights pin with pinNumber for set amount of time
  digitalWrite(pinNumber, HIGH);
  delay(40);
  digitalWrite(pinNumber, LOW);
}

void printStatus() {  //debug
  Serial.print(base0);
  Serial.print(", ");
  Serial.print(base1);
  Serial.print("  ||  ");
  Serial.print(analogRead(in0));
  Serial.print(", ");
  Serial.println(analogRead(in1));
}

bool withinRange(int n0, int n1, int range){  //T if n1 and n0 within range
  return abs(n1 - n0) < range;
}
