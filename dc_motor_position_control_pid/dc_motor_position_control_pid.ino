#include <TimerOne.h>

float r, y, e, e_a, u, u_p, u_c, u_i, u_ia, u_d, u_da, k_p, k_i, k_d, p, t, t_s;
int flag_i, i = 0, t_ini = 5;
const float sine_a = 90, omega = 2.0*PI*0.1;


void Timer1_ISR(void){
  flag_i = 1;
}

void setup() {
  // PID gains ZN classic
  k_p = 138.9/2;
  k_i = k_p/0.02/8;
  k_d = k_p*0.005/2;

  // PID gains ZN no overshoot
  //k_p = 46.3;
  //k_i = k_p/0.02/6;
  //k_d = k_p*0.0132;
  
  // values
  p    = 1;
  e_a  = 0;
  u_ia = 0;
  u_da = 0;
  t    = 0;
  t_s  = 0.002;
  
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
  float fact = 450.0/128;
  y = (analogRead(A0) -511)*fact;
}

void reference(){
  t += t_s;

  if (t < t_ini){
    r = 0.0;
    return;
  }

  float phi = omega*(t -t_ini);
  r         = sine_a*sin(phi);
}

void control(){
  const int dead = 0;
  const int umax = 1000;
  reference();

  // error
  e   = r -y;
  if (abs(e)<dead) e = 0.0;

  // control signal
  u_p = k_p*e;
  u_i = u_ia +k_i*t_s*(e +e_a)/2;
  u_d = u_da*(2-p*t_s)/(2+p*t_s) +2*p*k_d/(2+p*t_s)*(e -e_a);
  u   = u_p +u_i +u_d;

  // limit control signal
  if (u < -umax) u = -umax;
  if (u >  umax) u =  umax;

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

  // update past values
  e_a  = e;
  u_ia = u_i;
  u_da = u_d;
}

void communication(){
  if (t < t_ini){
    return;
  }
  
  while (Serial.available() > 0){
    // set reference
    if (r < -360) r = -360;
    if (r > 360)  r = 360;
  }

  // print signals
  if ( i == 1 ){
    Serial.print(r, 2);
    Serial.print(" ");
    Serial.print(y, 2);
    Serial.print(" ");
    Serial.print(e, 2);
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