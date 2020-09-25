/*
 * THIS CODE DESCRIBE HELICOPTER RUNNING PRINCIPLE
 * 
 *  SEVERUS 9/20/2020
 */
#include <Servo.h>
#include <SPI.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 512

Adafruit_NeoPixel pixels(200, 10, NEO_GRB + NEO_KHZ800);         //DEFINE RGB LEDS
Adafruit_NeoPixel pixels3(200, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2(200, 9, NEO_GRB + NEO_KHZ800);

Servo myservo0;                                                 //DEFINE SERVO MOTORS
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;

int buton = 36;
int buton2 = 34;
int buton3 = 32;

#define no2PmpLow 53                                            
#define no2Pmp    51
#define backupPmpLow 49
#define backupPmpMdl 47
#define no1PmpMdlLow 45
#define backupOn 43
#define no1PmpMdl 41
#define apuAccu 39

#define tailRtr 52
#define tail2On 50
#define collecttive 48
#define sasOff 46
#define boostServo 44
#define yaw 42
#define sas 40
#define trim_ 38

#define stage2orta 37
#define stage1orta 35
#define hyd2Press 33
#define hyd1Press 31
#define pri2Press 29
#define pri1Press 27
#define stage2sag 25
#define stage1sag 23
//=================================================
void setup() {


 myservo0.attach(A0);   //Servo Motor
 myservo1.attach(A1);
 myservo2.attach(A2);
 myservo3.attach(A3);
 myservo4.attach(A4);
 myservo5.attach(A5);
 myservo6.attach(A6);
 myservo7.attach(A7);
 
  pinMode(buton,INPUT);    //Buton
  pinMode(buton2,INPUT);
  pinMode(buton3,INPUT);
 
  pinMode(8,OUTPUT);     //LED
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
                                                                                                     
  pinMode(no2PmpLow,OUTPUT);      //NO:2 PUMP LOW
  pinMode(no2Pmp,OUTPUT);         //NO:2 PUMP
  pinMode(backupPmpLow,OUTPUT);   //BACKUP PUMP LOW
  pinMode(backupPmpMdl,OUTPUT);   //BACKUP PUMP MODULE
  pinMode(no1PmpMdlLow,OUTPUT);   //NO:1 LOW
  pinMode(backupOn,OUTPUT);       //BACKUP ON
  pinMode(no1PmpMdl,OUTPUT);      // NO:1 PUMP MODULE
  pinMode(apuAccu,OUTPUT);        // APU ACCUMULATOR
  pinMode(tailRtr,OUTPUT);       //TAIL RTR SERVO
  pinMode(tail2On,OUTPUT);       //#2 TAIL ON
  pinMode(collecttive,OUTPUT);   //COLLECTTIVE
  pinMode(sasOff,OUTPUT);        //SAS OFF
  pinMode(boostServo,OUTPUT);    //BOOST SERVO
  pinMode(yaw,OUTPUT);           //YAW BOOST
  pinMode(sas,OUTPUT);           //SAS
  pinMode(trim_,OUTPUT);         //trim
  pinMode(stage2orta,OUTPUT);    //2.Stage orta
  pinMode(stage1orta,OUTPUT);    //1.Stage orta
  pinMode(hyd2Press,OUTPUT);     //2 HYD Press
  pinMode(hyd1Press,OUTPUT);     //1 HYD Press
  pinMode(pri2Press,OUTPUT);     //#2 PRI Press
  pinMode(pri1Press,OUTPUT);     //#1 PRI Servo
  pinMode(stage2sag,OUTPUT);     //2.stage sağ
  pinMode(stage1sag,OUTPUT);     //1.stage sağ
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif

  pixels.begin();
  pixels2.begin();
  pixels3.begin();
  basla();
  sira1on();
  isik1on();
  sira3on();
  
}
//=========================================================
void loop() {
  
  if(digitalRead(buton)==HIGH){ 
    sira1();
  }
  if(digitalRead(buton2)==HIGH){
    sira2();
  }
  if(digitalRead(buton3)==HIGH){
    sira3();
  }

}
//=========================================================
void sira1(){     //NO:1 PUMP MODULE AND LED'S THAT SHOULD BE LİT AFTER
  
    basla();
    delay(1000);
    isik1on();
    sira1on();
    delay(5000);
    isik1off();
    sira1off();
  
}
//=========================================================
void sira2(){                     //ALTERNATELY, FIRST NO:1PUMP LEDS THAN NO:2 PUMP LEDS
                                  //BACKUP PUMP RUNING WHEN OTHER PUMPS FAULT
     basla();  
     delay(1000);  
     backupisik();
     backupisik2();
     digitalWrite(backupPmpMdl,LOW);
     digitalWrite(apuAccu,LOW);
     digitalWrite(tailRtr,LOW);
     myservo1.write(0);
     //digitalWrite(pri2Press,LOW);
     //sira1on();     
     delay(5000);
     isik1off();
     myservo1.write(90);
     digitalWrite(pri2Press,HIGH);
     sira1off();
     backupisikoff();
     digitalWrite(backupPmpMdl,HIGH);
     digitalWrite(apuAccu,HIGH);
     digitalWrite(tailRtr,HIGH);
     delay(2000);
     digitalWrite(backupPmpMdl,LOW);  
     digitalWrite(apuAccu,LOW);
     digitalWrite(tailRtr,LOW);
     //sira3on();

     backup2isik();
     
     pixels3.clear();
  for(int i=24; i<200; i++) {
    pixels3.setPixelColor(i, pixels3.Color(250, 0, 0));
    pixels3.show();
    delay(10);
    if(i==30){
      myservo0.write(0);      
    }
    if(i==41){
      myservo6.write(0);
      digitalWrite(yaw,LOW);
      digitalWrite(collecttive,LOW);
    }
    if(i==64){
      myservo5.write(0);
      digitalWrite(trim_,LOW);

    }
    if(i==106){
      myservo4.write(0);
      digitalWrite(sas,LOW);
    }
    if(i==120){
      myservo2.write(0);
      
    }
    if(i==160){
      stage2on();
    }
  } 
  
  pixels2.clear();
  for(int e=0; e<38; e++) {
    pixels2.setPixelColor(e, pixels2.Color(250, 0, 0));
    if(9<e<15){
      pixels2.setPixelColor(e, pixels2.Color(0, 0, 0));
    }
    pixels2.show();
    delay(10);
  }
     delay(2000);
     backup2isikoff();
     digitalWrite(backupPmpMdl,HIGH);
     digitalWrite(apuAccu,HIGH);
     digitalWrite(tailRtr,HIGH);
     //digitalWrite(pri2Press,LOW);
     sira3off();
  
}
//=========================================================
void sira3(){                  //NO:2 PUMP MODULE AND LED'S THAT SHOULD BE LİT AFTER
   basla();
   delay(1000);
   sira3on();
   delay(5000);
   sira3off();
  
}
//=========================================================
void stage1on(){
  digitalWrite(stage1orta,LOW);
  digitalWrite(stage1sag,LOW);

}
//=========================================================
void stage1off(){
  digitalWrite(stage1orta,HIGH);
  digitalWrite(stage1sag,HIGH);

}
//=========================================================
void stage2on(){
  digitalWrite(stage2orta,LOW);
  digitalWrite(stage2sag,LOW);

}
//=========================================================
void stage2off(){
  digitalWrite(stage2orta,HIGH);
  digitalWrite(stage2sag,HIGH);

}
//=========================================================
void saguston(){
  digitalWrite(trim_,LOW);
  digitalWrite(sas,LOW);
  

}
//=========================================================
void sagustoff(){
  digitalWrite(trim_,HIGH);
  digitalWrite(sas,HIGH);
  digitalWrite(yaw,HIGH);
  digitalWrite(collecttive,HIGH);
}
//=========================================================
void basla(){
  
  myservo0.write(90);   
  myservo1.write(90); 
  myservo2.write(90);
  myservo3.write(90);
  myservo4.write(90);
  myservo5.write(90);
  myservo6.write(90);
  myservo7.write(90);
  
  for(int l=23;l<54;l++){
    digitalWrite(l, HIGH);
  }
}
//=========================================================
void sira1on(){

  
  digitalWrite(no1PmpMdl,LOW);  
  //stage1on();
}
//=========================================================
void sira1off(){

  digitalWrite(no1PmpMdl,HIGH);

  stage1off();
  digitalWrite(pri1Press,LOW);
  digitalWrite(no1PmpMdlLow,LOW);
  digitalWrite(hyd1Press,LOW);
  digitalWrite(tail2On,LOW);
}

//=========================================================
void sira3on(){
  digitalWrite(no2Pmp,LOW);
    isik3on();
   
   //saguston();
}
//=========================================================
void sira3off(){
   isik3off();
   digitalWrite(no2Pmp,HIGH);  
   sagustoff();  
   digitalWrite(no2PmpLow,LOW);
   digitalWrite(hyd2Press,LOW);
   digitalWrite(sasOff,LOW);
   digitalWrite(boostServo,LOW);
}
void isik1on(){
  pixels.clear();
  for(int i=0; i<120; i++) {
    pixels.setPixelColor(i, pixels.Color(250, 0, 0));
    pixels.show();
    delay(20);
    if(i==30){
      myservo3.write(0);      
    }
    if(i==79){
      myservo7.write(0);
    }
    if(i==110){
      stage1on();
    }
  }  
}
void isik1off(){
  pixels.clear();
  myservo3.write(90);
  myservo7.write(90);
  for(int i=0; i<120; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.show();
  }  
}
//==================================================
void isik3on(){
  pixels3.clear();
  for(int i=0; i<200; i++) {
    pixels3.setPixelColor(i, pixels3.Color(250, 0, 0));
    pixels3.show();
    delay(20);
    if(i==30){
      myservo0.write(0);      
    }
    if(i==41){
      myservo6.write(0);
      digitalWrite(yaw,LOW);
      digitalWrite(collecttive,LOW);
    }
    if(i==64){
      myservo5.write(0);
      digitalWrite(trim_,LOW);

    }
    if(i==106){
      myservo4.write(0);
      digitalWrite(sas,LOW);
    }
    if(i==120){
      myservo2.write(0);
      
    }
    if(i==160){
      stage2on();
    }
  }  
}
void isik3off(){
  stage2off();
  pixels3.clear();
  myservo0.write(90);
  myservo2.write(90);
  myservo6.write(90);
  myservo4.write(90);
  myservo5.write(90);

  for(int i=0; i<200; i++) {
    pixels3.setPixelColor(i, pixels3.Color(0, 0, 0));
    pixels3.show();
  }  
}
//================================================
void isik2on(){
  pixels2.clear();
  for(int i=0; i<150; i++) {
    pixels2.setPixelColor(i, pixels2.Color(250, 0, 0));
    if(15<i<38){
      pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
    }
    pixels2.show();
    delay(20);
  }  
}
void isik2off(){
  pixels2.clear();
  myservo3.write(90);
  myservo7.write(90);
  for(int i=0; i<104; i++) {
    pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
    pixels2.show();
  }  
}

void backupisik2(){
  pixels.clear(); 
  for(int i=23; i<120; i++) {
    pixels.setPixelColor(i, pixels.Color(250, 0, 0));
    pixels.show();
    delay(20);
    if(i==30){
      myservo3.write(0);      
    }
    if(i==79){
      myservo7.write(0);
    }
    if(i==110){
      stage1on();
    }
  }
}

void backupisik(){
  pixels2.clear();
  for(int k=0; k<14; k++) {
    pixels2.setPixelColor(k, pixels2.Color(250, 0, 0));   
       pixels2.show();
    delay(20);

  }
   for(int i=38; i<100; i++) {
    pixels2.setPixelColor(i, pixels2.Color(250, 0, 0));   
       pixels2.show();
    delay(20);

  }
}
void backupisikoff(){
  pixels2.clear();
  for(int k=0; k<14; k++) {
    pixels2.setPixelColor(k, pixels2.Color(0, 0, 0));   
       pixels2.show();
    delay(20);

  }
   for(int i=38; i<100; i++) {
    pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));   
       pixels2.show();
    delay(20);

  }
}
//=========================================================
void backup2isik(){
  pixels2.clear();
  for(int k=0; k<38; k++) {
    pixels2.setPixelColor(k, pixels2.Color(250, 0, 0));   
       pixels2.show();
    delay(20);

  }

}
void backup2isikoff(){
  pixels2.clear();
  for(int k=0; k<38; k++) {
    pixels2.setPixelColor(k, pixels2.Color(0, 0, 0));   
       pixels2.show();
    delay(20);

  }

}
