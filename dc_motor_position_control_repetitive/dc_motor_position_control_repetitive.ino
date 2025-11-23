#include <TimerOne.h>
# define MAX_BUF 200

// signals variables
float r, y, e, x_r1, y_r1, u, u_r, u_c, t, t_s;
// parameters variables
float k_p, k_r, b, a;
// flags and counters variables
int flag_i = 0, i = 0, idx = 0, t_ini = 5, n_counter = 0, N_eff;

// constants
const int w = 1000, n = 5;
const float sine_a = 90, omega = 2.0*PI*0.1, tau = -(1.0/omega)*(atan(omega/w) -2*PI);
float e_buffer[MAX_BUF];


void Timer1_ISR(void){
  flag_i = 1;
}

void setup() {
  // time values
  t   = 0;
  t_s = 0.002;

  // controller gains
  k_p = 130;
  k_r = 40;

  // controller filter coefficients
  b     = w*t_s/(2.0 +w*t_s);
  a     = (2.0 -w*t_s)/(2.0 +w*t_s);
  N_eff = round((10 +tau)/(t_s*n));
  if (N_eff > MAX_BUF) N_eff = MAX_BUF;

  // initialize values
  x_r1 = 0.0;
  y_r1 = 0.0;
  for (int k = 0; k < N_eff; k++) e_buffer[k] = 0.0;

  // declares pins as output
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

  // initializes serial communication
  Serial.begin(115200);
  Timer1.initialize(t_s*1000000);     // interruption every t_s seconds
  Timer1.attachInterrupt(Timer1_ISR);
}

float LPF(float x_r){
  float y_r = b*x_r +b*x_r1 +a*y_r1;

  x_r1 = x_r;
  y_r1 = y_r;

  return y_r;
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
  e = r -y;
  if (abs(e)<dead) e = 0.0;

  // control signal
  if (++n_counter >= n){
    n_counter = 0;

    // repetitive output
    float y_r = LPF(e_buffer[idx]);
    u_r = k_r*(e +y_r);
    
    // update past values and index
    e_buffer[idx] = e;
    idx++;
    if (idx >= N_eff) idx = 0;
  }
  else{
    u_r = 0;
  }
  u = k_p*e +u_r;
  
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