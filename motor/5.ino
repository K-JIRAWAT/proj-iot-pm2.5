
/*------ กันชน ------*/
#define DISTANCE 25
#define SOUND_SPEED 0.034
const int trigPin1 = 13;
int echoPin1 = 12;
/*-------definning Inputs------*/
int LS = A2;     // left sensor
int RS  = A3;      // right sensor

/*-------definning Outputs------*/
int LM1 = 4;      // left motor
int LM2 =  5;       // left motor
int RM1 =  6;       // right motor
int RM2 =  7;       // right mถotor

/*-------PWM ควบคุมความเร็วมอเตอร์-----*/
int PWM1 = 10;    // PWM left motor 
int PWM2 = 11;    // PWM right motor

int SP1 = 90;  // Speed PWM สามารถปรับความเร็วได้ถึง 255
int SP2 = 180;  // Speed PWM สามารถปรับความเร็วได้ถึง 255
int SP3 = 255;  // Speed PWM สามารถปรับความเร็วได้ถึง 255
int sw = 8;
int swr = 0;

long duration1 , distanceCm1;
void setup() {
  
  Serial.begin(9600);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(sw, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}

void loop() {
  long duration1 , distanceCm1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distanceCm1 = duration1 * SOUND_SPEED / 2;
  Serial.print("Distance1 (cm): ");
  Serial.println(distanceCm1);
  //swr = digitalRead(sw);
  //if (swr == 1){
    //  digitalWrite(LM1, LOW);
      //digitalWrite(LM2, LOW);
      //digitalWrite(RM1, LOW);
      //digitalWrite(RM2, LOW);
    //}


/*--------------  เงื่อนไขการเดินตามเส้น  ---------------*/
  if (!(digitalRead(LS)) && !(digitalRead(RS)))    // Move Forward
    {
      analogWrite(PWM1, SP3);
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWM2, SP3);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      if (distanceCm1 <= DISTANCE ) {  //0-10
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
      
      }

    }


    if (!(digitalRead(LS)) && digitalRead(RS))    // Turn right
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      analogWrite(PWM2, SP3);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);

      if (distanceCm1 <= DISTANCE ) {  //0-10
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
      
      }

    }

    if (digitalRead(LS) && !(digitalRead(RS)))    // turn left
    {
      analogWrite(PWM1, SP3);
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
        if (distanceCm1 <= DISTANCE ) {  //0-10
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
    
      }

    }

    if (digitalRead(LS) && digitalRead(RS))    // stop
    {
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
    }


}
