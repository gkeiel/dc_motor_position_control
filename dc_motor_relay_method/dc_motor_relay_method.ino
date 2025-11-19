#include <TimerOne.h>

float r, y, e, u, u_c, t, t_s;
float dead = 5;
int flag_i, i = 0, r_high = 45, r_low = -45;


void Timer1_ISR(void){
  flag_i = 1;
}

void setup() {
  // values
  r   = 0;
  t   = 0;
  t_s = 0.002;

  // declares pins as output
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

  // initializes serial communication
  Serial.begin(115200);
  Timer1.initialize(t_s*1000000);     // interruption every t_s seconds
  Timer1.attachInterrupt(Timer1_ISR);
}

void measurement(){
  // read sensor
  float y_m = analogRead(A0)*(5.0/1023);
  y_m = y_m*720 -1800;
  y = y_m;
}

void reference(){
  t += t_s;

  float T = 10.0;
  float D = 0.5;
  float t_on = fmod(t, T);
  
  if (t_on <D*T) r = r_high;
  else           r = r_low;
}

void control(){
  // reference
  reference();

  // error
  e = r -y;

  // relay method
  const int umax = 1000;
  if (e > dead)  u = umax;
  else if (e < -dead) u = -umax;

  // limit control signal
  if (u >  umax) u = umax;
  if (u < -umax) u = -umax;
  
  // PWM from 0 to 255
  u_c = abs(u)*(255.0/umax);
  if (u >= 0){
    analogWrite(5, u_c); // PWM
    analogWrite(3, 0);   // 0
  }
  else{
    analogWrite(5, 0);   // 0
    analogWrite(3, u_c); // PWM
  }
}

void communication(){

  while (Serial.available() > 0){
    // read serial input
    char c = Serial.read();
    if (c == '+'){
      dead +=.5;
    }
    if (c == '-'){
      dead -=.5;
      if (dead < 0) dead = 0;
    }
  }

  // print signals
  if ( i == 10 ){
    Serial.print(r, 2);
    Serial.print(" ");
    Serial.print(y, 2);
    Serial.print(" ");
    Serial.print(dead, 2);
    Serial.print(" ");
    Serial.println(u, 2);
    i = 0;
  }
  i++;
}

void loop(){
  if (flag_i == 1){
    measurement();
    control();
    communication();
    flag_i = 0;
  }
}