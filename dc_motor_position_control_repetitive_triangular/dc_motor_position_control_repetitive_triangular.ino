#include <TimerOne.h>
# define MAX_BUF 250

// signals variables
float r, y, e, x_r1, y_r1, u, u_r, u_pwm, t, t_s, T;
// parameters variables
float k_p, k_r, k_c, b, a, tau, w_0;
int flag_i = 0, i = 0, idx = 0, t_ini = 5, n_counter = 0, N_eff, A;
// constants
const int w_c = 1000, n = 10;

float e_buffer[MAX_BUF];


void Timer1_ISR(void){
  flag_i = 1;
}

void setup() {
  T   = 5;
  A   = 90;
  w_0 = 2.0*PI*(1.0/T);
  tau = -(1.0/w_0)*(atanf(w_0/w_c) -2*PI);

  // time values
  t   = 0;
  t_s = 0.002;

  // controller gains
  k_p = 30;
  k_r = 60;
  k_c = (1.0/w_c)*sqrt(w_0*w_0 +w_c*w_c); // correction for infinite gain  

  // controller filter coefficients
  b     = k_c*w_c*t_s/(2.0 +w_c*t_s);
  a     = (-2.0 +w_c*t_s)/(2.0 +w_c*t_s);
  N_eff = round((tau)/(t_s*n));
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
  float y_r = b*x_r +b*x_r1 -a*y_r1;

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

  float tau = fmodf(t -t_ini +T/4.0, T);
  r         = (4.0*A/T)*fabsf(tau -T/2.0) -A;
}

void control(){
  const int dead = 0;
  const int umax = 1000;
  reference();

  // error
  e = r -y;
  if (abs(e)<dead) e = 0.0;

  // control signal
  if (t <t_ini){
    u_r = 0.0f;
  }
  else{
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
  }
  u = k_p*e +u_r;
  
  // limit control signal
  if (u < -umax) u = -umax;
  if (u >  umax) u = umax;

  // PWM from 0 to 255
  u_pwm = abs(u)*(255.0/umax);
  if (u >= 0){
    analogWrite(5, u_pwm);
    analogWrite(3, 0);
  }
  else{
    analogWrite(5, 0);
    analogWrite(3, u_pwm);
  }
}

void communication(){
  if (t < t_ini){
    return;
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