#include <TimerOne.h>

float r, y, e, e_1, e_2, u, u_p, u_r, u_c, u_1, u_2, t, t_s;
float k_p, k_r, c_1, c_2, c_3, c_4, c_5;
int flag_i, i = 0, t_ini = 10;
const float sine_a = 90, omega = 2.0*PI*0.1;


void Timer1_ISR(void){
  flag_i = 1;
}

void setup() {
  float b_0, b_1, b_2, a_0, a_1, a_2;

  // time values
  t   = 0;
  t_s = 0.002;

  // controller gains
  k_p = 92.6;
  k_r = 2909/500;

  // controller coefficients
  b_0 = 4*k_p +k_r*t_s;
  b_1 = -8*k_p;
  b_2 = 4*k_p -k_r*t_s;
  a_0 = omega*omega*t_s*t_s +4;
  a_1 = 2*omega*omega*t_s*t_s -8;
  a_2 = omega*omega*t_s*t_s +4;

  // controller coefficients normalized
  c_1 = b_0/a_0;
  c_2 = b_1/a_0;
  c_3 = b_2/a_0;
  c_4 = a_1/a_0;
  c_5 = a_2/a_0;
  
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

  float phi = omega*t;
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
  u_r = c_1*e +c_2*e_1 +c_3*e_2 -c_4*u_1 -c_5*u_2;
  u   = u_p +u_r;

  // limit control signal
  if (u < -umax) u = -umax;
  if (u >  umax) u = umax;

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
  e_2 = e_1;
  e_1 = e;
  u_2 = u_1;
  u_1 = u;
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