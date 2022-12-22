#include "PMS.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); // RX, TX

/*------- set PM.25 ------*/
PMS pms(mySerial);
PMS::DATA data;


// ถ้าต้องการให้ relay ติดก็ส่งค่า 0  ถ้าต้องการให้ relay ดับก็ส่งค่า 1 
int relay1 = 7; // ต่อกับขา in1 ของบอร์ดรีเลย์

int relay2 = 6; // ต่อกับขา in2 ของบอร์ดรีเลย์

int relay3 = 5; // ต่อกับขา in3 ของบอร์ดรีเลย์

int relay4 = 4; // ต่อกับขา in4 ของบอร์ดรีเลย์

int pwm = 9;
int pm;
int sw = 8;


void setup() {          
mySerial.begin(9600);
 // Timer0 setup for Arduino UNO pin D5,D6 for Arduino Mega2560 pin D4,D13 ***Timer0 use for millis(), delay()***

  //for Timer0: f=16Mhz/(prescale*256)
  
  //TCCR0B = 0;
  //TCCR0B |= (1 << CS00);                    //No prescale ,f = 16Mhz/(256) = 62.5Khz, CS00=0, CS01=0, CS02=1
  //TCCR0B |= (1 << CS01);                   //prescale = 8 ,f = 16Mhz/(256*8) = 7.8Khz, CS00=0, CS01=1, CS02=0
  //TCCR0B |= (1 << CS01) | (1 << CS00);     //prescale = 64 ,f = 16Mhz/(256*64) = 976.5 hz, CS00=1, CS01=1, CS02=0
  //TCCR0B |= (1 << CS02);                   //prescale = 256 ,f = 16Mhz/(256*256) = 244 hz, CS00=0, CS01=0, CS02=1
  //TCCR0B |= (1 << CS02) | (1 << CS00);     //prescale = 1024 ,f = 16Mhz/(256*1024) = 61 hz, CS00=1, CS01=0, CS02=1

  //for Timer1-5: f=16Mhz/(prescale*510)
  
  // Timer1 setup for Arduino UNO pin D9,D10 for Arduino Mega2560 pin D11, D12
  
   TCCR1B = 0;
   //TCCR1B |= (1 << CS10);                    //No prescale ,f = 16Mhz/(510) = 31.25Khz, CS10=0, CS11=0, CS12=1
  TCCR1B |= (1 << CS11);                    //prescale = 8 ,f = 16Mhz/(510*8) = 3.9Khz, CS10=0, CS11=1, CS12=0
   //TCCR1B |= (1 << CS11) | (1 << CS10);     //prescale = 64 ,f = 16Mhz/(510*64) = 490 hz, CS10=1, CS11=1, CS12=0
  //TCCR1B |= (1 << CS12);                   //prescale = 256 ,f = 16Mhz/(510*256) = 122 hz, CS10=0, CS11=0, CS12=1
  //TCCR1B |= (1 << CS12) | (1 << CS10);     //prescale = 1024 ,f = 16Mhz/(510*1024) = 30.5 hz, CS10=1, CS11=0, CS12=1

  // Timer2 setup for Arduino UNO pin D3,D11 for Arduino Mega2560 pin D9, D10
  
  //TCCR2B = 0;
  //TCCR2B |= (1 << CS20);                    //No prescale ,f = 16Mhz/(510) = 31.25Khz, CS20=1, CS21=0, CS22=0
  //TCCR2B |= (1 << CS21);                   //prescale = 8 ,f = 16Mhz/(510*8) = 3.9Khz, CS20=0, CS21=1, CS22=0
  //TCCR2B |= (1 << CS21) | (1 << CS20);     //prescale = 32 ,f = 16Mhz/(510*32) = 980 hz, CS20=1, CS21=1, CS22=0
  //TCCR2B |= (1 << CS22);                   //prescale = 64 ,f = 16Mhz/(510*64) = 490 hz, CS20=0, CS21=0, CS22=1
  //TCCR2B |= (1 << CS22) | (1 << CS20);     //prescale = 128 ,f = 16Mhz/(510*128) = 245 hz, CS20=1, CS21=0, CS22=1
  //TCCR2B |= (1 << CS22) | (1 << CS21);     //prescale = 256 ,f = 16Mhz/(510*128) = 122.5 hz, CS20=0, CS21=1, CS22=1
  //TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);     //prescale = 1024 ,f = 16Mhz/(510*1024) = 30.6 hz, CS20=1, CS21=1, CS22=1

  // Timer3 setup for Arduino Mega2560 pin D5, D3, D2
  
  //TCCR3B = 0;
  //TCCR3B |= (1 << CS30);                    //No prescale ,f = 16Mhz/(510) = 31.25Khz, CS30=0, CS31=0, CS32=1
  //TCCR3B |= (1 << CS31);                   //prescale = 8 ,f = 16Mhz/(510*8) = 3.9Khz, CS30=0=0, CS31=1, CS32=0
  //TCCR3B |= (1 << CS31) | (1 << CS30);     //prescale = 64 ,f = 16Mhz/(510*64) = 490 hz, CS30=0=1, CS31=1, CS32=0
  //TCCR3B |= (1 << CS32);                   //prescale = 256 ,f = 16Mhz/(510*256) = 122 hz, CS30=0=0, CS31=0, CS32=1
  //TCCR3B |= (1 << CS32) | (1 << CS30);     //prescale = 1024 ,f = 16Mhz/(510*1024) = 30.5 hz, CS30=0=1, CS31=0, CS32=1

   // Timer4 setup for Arduino Mega2560 pin D6, D7, D8
  
  //TCCR4B = 0;
  //TCCR4B |= (1 << CS40);                    //No prescale ,f = 16Mhz/(510) = 31.25Khz, CS40=1, CS41=0, CS42=0
  //TCCR4B |= (1 << CS41);                   //prescale = 8 ,f = 16Mhz/(510*8) = 3.9Khz, CS40=0, CS41=1, CS42=0
   //TCCR4B |= (1 << CS41) | (1 << CS40);     //prescale = 64 ,f = 16Mhz/(510*64) = 490 hz, CS40=1,CS41=1, CS42=0
  //TCCR4B |= (1 << CS42);                   //prescale = 256 ,f = 16Mhz/(510*256) = 122 hz, CS40=0, CS41=0, CS42=1
  //TCCR4B |= (1 << CS42) | (1 << CS40);     //prescale = 1024 ,f = 16Mhz/(510*1024) = 30.5 hz, CS40=1, CS41=0, CS42=1

   // Timer5 setup for Arduino Mega2560 pin D44, D45, D46
  
  //TCCR5B = 0;
  //TCCR5B |= (1 << CS50);                    //No prescale ,f = 16Mhz/(510) = 31.25Khz, CS50=1, CS51=0, CS52=0
  //TCCR5B |= (1 << CS51);                   //prescale = 8 ,f = 16Mhz/(510*8) = 3.9Khz, CS50=0, CS51=1, CS52=0
  //TCCR5B |= (1 << CS51) | (1 << CS50);     //prescale = 64 ,f = 16Mhz/(510*64) = 490 hz, CS50=1,CS51=1, CS52=0
  //TCCR5B |= (1 << CS52);                   //prescale = 256 ,f = 16Mhz/(510*256) = 122 hz, CS50=0, CS51=0, CS52=1
  //TCCR5B |= (1 << CS52) | (1 << CS50);     //prescale = 1024 ,f = 16Mhz/(510*1024) = 30.5 hz, CS50=1, CS51=0, CS52=1

  
 Serial.begin(9600);
 pinMode(relay1, OUTPUT); 
 pinMode(relay2, OUTPUT);    
 pinMode(relay3, OUTPUT);    
 pinMode(relay4, OUTPUT);
 pinMode(pwm, OUTPUT);
 pinMode(sw, OUTPUT);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรตำแหน่งที่0 แถวที่ 1 เตรียมพิมพ์ข้อความ
  lcd.print("PM2.5 Test"); //พิมพ์ข้อความ 
  lcd.setCursor(2, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
  lcd.print("...Begin..."); //พิมพ์ข้อความ
  digitalWrite(relay1, 1);   // สั่งเปิดรีเลย์
  digitalWrite(relay2, 1);   // สั่งเปิดรีเลย์  
}

void loop() {

   // digitalWrite(relay1, 0);   // สั่งปิดรีเลย์ motor
    //digitalWrite(relay2, 0);   // สั่งปิดรีเลย์ fan
    lcd.setCursor(0, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("...level :"); //พิมพ์ข้อความ 
    

    
   /*-------- PM 2.5 and fan motor ----------*/
  if (pms.read(data)) {
    pm = data.PM_AE_UG_2_5;
    Serial.println(pm);
    lcd.setCursor(12, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print(data.PM_AE_UG_2_5); //พิมพ์ข้อความ 
  }

    
  if ((data.PM_AE_UG_2_5>=51) && (data.PM_AE_UG_2_5<=80)){
    Serial.println("work1 :");
    Serial.println(data.PM_AE_UG_2_5);
    lcd.setCursor(12, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print(data.PM_AE_UG_2_5); //พิมพ์ข้อความ 
    lcd.setCursor(12, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("..1"); //พิมพ์ข้อความ 
    digitalWrite(relay1, 0)                                                               ;   // สั่งเปิดรีเลย์
    digitalWrite(relay2, 0);   // สั่งเปิดรีเลย์
    digitalWrite(sw, HIGH);
    analogWrite(pwm,192);
     
    }
if ((data.PM_AE_UG_2_5>=81) && (data.PM_AE_UG_2_5<=110)){
    Serial.println("work2 :");
    Serial.println(data.PM_AE_UG_2_5);
    lcd.setCursor(12, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print(data.PM_AE_UG_2_5); //พิมพ์ข้อความ 
    lcd.setCursor(12, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("..2"); //พิมพ์ข้อความ 
    digitalWrite(relay1, 0);   // สั่งเปิดรีเลย์
    digitalWrite(relay2, 0);   // สั่งเปิดรีเลย์
    digitalWrite(sw, HIGH);
    analogWrite(pwm,128);
   
    }

if (data.PM_AE_UG_2_5 >= 111){
    Serial.println("work3 :");
    Serial.println(data.PM_AE_UG_2_5);
    lcd.setCursor(12, 0); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print(data.PM_AE_UG_2_5); //พิมพ์ข้อความ 
    lcd.setCursor(12, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("..3"); //พิมพ์ข้อความ 
    digitalWrite(relay1, 0);   // สั่งเปิดรีเลย์
    digitalWrite(relay2, 0);   // สั่งเปิดรีเลย์
    digitalWrite(sw, HIGH);
    analogWrite(pwm,0);
    
    }


if (data.PM_AE_UG_2_5 <= 50){
    digitalWrite(relay1, 1);   // สั่งเปิดรีเลย์
    digitalWrite(relay2, 1);   // สั่งเปิดรีเลย์
    digitalWrite(sw, LOW);
    
    lcd.setCursor(12, 1); // กำหนดให้ เคอร์เซอร์ อยู่ตัวอักษรกำแหน่งที3 แถวที่ 2 เตรียมพิมพ์ข้อความ
    lcd.print("..0"); //พิมพ์ข้อความ 
  
  }

}
