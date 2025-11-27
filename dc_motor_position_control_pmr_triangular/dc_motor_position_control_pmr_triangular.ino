#include <TimerOne.h>

float r, y, e, u, u_p, u_r, u_pwm, t, t_s, T;
float k_p, k_r, xi, w_0;
int flag_i = 0, k = 0, t_ini = 5, A;
const int m = 6, h[6] = {1, 3, 5, 7, 9, 11};

struct res_mode{
  float k_r;                  // gain
  float c1, c2, c3, c4, c5;   // coefficients
  float u1, u2;               // past u_r(k-1), u_r(k-2)
  float e1, e2;               // past e(k-1), e(k-2)  
};
res_mode mode[m];

void Timer1_ISR(void){
  flag_i = 1;
}

void res_coeff(res_mode &h, float omega, float xi, float k_r, float t_s){
  // controller coefficients with pre-warping
  // a_0*u_r(k) = b_0*e(k) +b_1*e(k-1) +b_2*e(k-2) -a_1*u_r(k-1) -a_2*u_r(k-2)
  float alpha = omega/tanf(omega*t_s/2.0);
  float a_0 = alpha*alpha +2.0*xi*omega*alpha +omega*omega;
  float a_1 = -2.0*alpha*alpha +2.0*omega*omega;
  float a_2 = alpha*alpha -2*xi*omega*alpha +omega*omega;
  float b_0 = k_r*alpha;
  float b_1 = 0;
  float b_2 = -k_r*alpha;
  
  // u_r(k) = c_1*e(k) +c_2*e(k-1) +c_3*e(k-2) -c_4*u_r(k-1) -c_5*u_r(k-2) 
  h.c1 = b_0/a_0;
  h.c2 = b_1/a_0; // -> c_2 = 0
  h.c3 = b_2/a_0;
  h.c4 = a_1/a_0;
  h.c5 = a_2/a_0;

  // initialize values
  h.e1 = h.e2 = 0.0;
  h.u1 = h.u2 = 0.0;
}

void setup() {
  T   = 5;
  A   = 90;
  w_0 = 2.0*PI*(1.0/T);

  // time values
  t   = 0;
  t_s = 0.002;

  // controller gains
  k_p = 50;
  k_r = 50;
  xi  = 0.001;

  //
  for(int i = 0; i < m; i++){
    float w_h = h[i]*w_0;
    res_coeff(mode[i], w_h, xi, k_r/h[i], t_s);
  }
 
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

  float tau = fmodf(t -t_ini +T/4.0, T);
  r         = (4.0*A/T)*fabsf(tau -T/2.0) -A;
}

void control(){
  const int dead = 1, umax = 1000;
  reference();

  // error
  e = r -y;
  if (fabsf(e)<dead) e = 0.0;

  // control signal
  u_p = k_p*e;
  u_r = 0.0;
  for(int i = 0; i < m; i++){
    res_mode &h = mode[i];
    float u_h = h.c1*e +h.c2*h.e1 +h.c3*h.e2 -h.c4*h.u1 -h.c5*h.u2;

    h.e2 = h.e1;
    h.e1 = e;
    h.u2 = h.u1;
    h.u1 = u_h;
    u_r += u_h;
  }
  u   = u_p +u_r;

  // limit control signal
  if (u < -umax) u = -umax;
  if (u > umax)  u = umax;

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
  if ( k == 1 ){
    Serial.print(r, 2);
    Serial.print(" ");
    Serial.print(y, 2);
    Serial.print(" ");
    Serial.print(e, 2);
    Serial.print(" ");
    Serial.println(u, 2);
    k = 0;
  }
  k++;
}

void loop(){
  if (flag_i == 1){
    measurement();
    control();
    communication();
    flag_i = 0;
  }
}