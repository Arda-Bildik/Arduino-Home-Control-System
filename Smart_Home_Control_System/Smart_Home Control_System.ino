/*
 Arduino Tabanlı Ev Kontrol Sistemi

 Pin Açıklamaları
 Analog:
 a0 - a1 Güneş Paneli Voltaj Ölçümü
 geçici olarak yok ---> A2 - A3 - A4 LM35 Sıcaklık Sensörü

 Dijital:
 42 - 43 - 44 - 45 - 46 - 47 - 48 - 49 Röle Tetik Pinleri

 */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 #include <UTFT.h>
#include <URTouch.h>
#include <UTFT_Buttons.h>
#include <SPI.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX          


//fontlar
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

//Güneş paneli ve Batarya voltaj okuması için tanımlamalar
float vout1 = 0.0;
float vout2 = 0.0;
float vin1 = 0.0;
float vin2 = 0.0;
int value1 = 0;
int value2 = 0;
float r1 = 100000.0; 
float r2 = 10000.0;

int a1;
int a0;



//LM 35 sensörleri için gerekli tanımlamalar
//ev termometre
int lm351 = 10;
int okunanVoltaj1;
float sicaklik11;
int okunanVoltaj11;
float sicaklik111;
//açık hava termometre
int lm352 = 11;
int okunanVoltaj2;
float sicaklik22;
int okunanVoltaj22;
float sicaklik222;
//havuz termometre
int lm353 = 12;
int okunanVoltaj3;
float sicaklik33;
int okunanVoltaj33;
float sicaklik333;

//tanımlamalar
UTFT          myGLCD(ILI9341_16,38,39,40,41);
URTouch        myTouch(6,5,4,3,2);
UTFT_Buttons  myButtons(&myGLCD, &myTouch);


int nrl1,nrl2,nrl3,nrl4,nrl5,nrl6,nrl7,nrl8,vanaa1,vanaa2 = 0;
int sicaklik , voltaj_deger,sicaklik2 , voltaj_deger2,rl1,rl2,rl3,rl4,rl5,rl6,rl7,rl8, nm1, nm2, nm3, nm4, nm5, nm6, nm7, nm8, nm9, nm0_sifregir, del_geri, enter ,pressed_button,geri,rolekont,vanakont,vana1,vana2 ;

int sifre = 0;
int resetcounter=0;
int gelenascii;
int lcddurum = 0;
void setup()
{


Serial.begin(9600);
mySerial.begin(9600);

  digitalWrite(42,HIGH);
  digitalWrite(43,HIGH);
  digitalWrite(44,HIGH);
  digitalWrite(45,HIGH);
  digitalWrite(46,HIGH);
  digitalWrite(47,HIGH);
  digitalWrite(48,HIGH);
  digitalWrite(49,HIGH);
  digitalWrite(8,LOW);
  pinMode(8,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  pinMode(46,OUTPUT);
  pinMode(47,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);

  

  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);
  myButtons.setTextFont(BigFont);
  myButtons.setSymbolFont(Dingbats1_XL);
  myGLCD.setBackColor(VGA_TRANSPARENT);

}

void loop()
{
  
  
  myButtons.deleteAllButtons();
  myGLCD.clrScr();

resetcounter = 0 ;

   myGLCD.setColor(VGA_WHITE);
myGLCD.clrScr();
myGLCD.print("Ev Kontrol Paneli",CENTER,5);
sicaklik = myButtons.addButton(60,40, 200,  30, "Sicakliklar",BUTTON_DISABLED);  
voltaj_deger = myButtons.addButton(60,80, 200,  30, "Voltajlar");
nm0_sifregir = myButtons.addButton(60,  190, 200,  30, "Sifre Gir");
 myButtons.drawButtons();


while(1) 
  {
devam:
        myGLCD.print("Ev Kontrol Paneli",CENTER,5);
        if(lcddurum==0){
         if(resetcounter>=1330){
        lcddurum = 1;
        digitalWrite(8,HIGH);
      }
      }else if(myTouch.dataAvailable() == true){
              lcddurum = 0;
      resetcounter=0;
      digitalWrite(8,LOW);
     
      goto devam;
      }

    resetcounter ++;    
    Serial.println(resetcounter);
    

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }




   
  }
  
  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));



    



   
    if (myTouch.dataAvailable() == true)
    {

      pressed_button = myButtons.checkButtons();

      if (pressed_button==nm0_sifregir)
      {
      goto sifrekeypad;
      }

      if (pressed_button==sicaklik)
      {
      goto sicaklik;
      }

      if (pressed_button==voltaj_deger)
      {
      goto voltajdeger;
      }
  
   
  } }   
  return;


//-----------------------------------------------------

//Voltaj Görüntüleme
voltajdeger:

resetcounter = 0 ; 

while(1){
  
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myButtons.deleteButton(nm0_sifregir);
myButtons.deleteButton(sicaklik);
myButtons.deleteButton(voltaj_deger);
myGLCD.clrScr();
del_geri = myButtons.addButton(10,  200, 85,  30, "Geri");
 myButtons.drawButtons();

interloop1:
myGLCD.print("Ev Kontrol Paneli",CENTER,5);
//batarya
//r1 100000.0
//r2 10000.0

 value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
myGLCD.print("-Batarya Voltaji-",CENTER,40);
myGLCD.print(String(vin1),CENTER,70);

myGLCD.print("-Panel Voltaji-",CENTER,100);
myGLCD.print(String(vin2),CENTER,130);

   
while(1) 
  {

    

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    

  }


  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));

    
    myGLCD.print("Ev Kontrol Paneli",CENTER,5);
           if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        
        goto devam;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;

      pressed_button = myButtons.checkButtons();

      if (pressed_button==del_geri)
      {
        myButtons.deleteButton(del_geri);
   return;
      }
    }else{goto interloop1;}
  }
  goto interloop1;
}

//--------------------------------------------------
 
//Sıcaklık görüntüleme
 sicaklik:
 resetcounter=0;
while(1){
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myButtons.deleteButton(nm0_sifregir);
myButtons.deleteButton(sicaklik);
myButtons.deleteButton(voltaj_deger);
myGLCD.clrScr();
del_geri = myButtons.addButton(10,  200, 85,  30, "Geri");
 myButtons.drawButtons();

interloop2:

okunanVoltaj1 = analogRead(lm351);
  sicaklik11 = (okunanVoltaj1*5000)/1023; 


  
  okunanVoltaj2 = analogRead(lm352);
  sicaklik22 = okunanVoltaj2 / 9.31; 

  okunanVoltaj3 = analogRead(lm353);
  sicaklik33 = okunanVoltaj3/ 9.31; 
  

myGLCD.print("Ev Kontrol Paneli",CENTER,5);
//ev sicaklık
myGLCD.print("-Ev Sicaklik-",CENTER,40);
myGLCD.print(String(sicaklik11),CENTER,65);
//dışarı sıcaklık
myGLCD.print("-Acik Hava Sicaklik-",CENTER,95);
myGLCD.print(String(sicaklik22),CENTER,120);   
//havuz sıcaklık
myGLCD.print("-Havuz Sicaklik-",CENTER,155);
myGLCD.print(String(sicaklik33),CENTER,180);   




   
while(1) 
  {

    

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    

  }

  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));

    
     if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        
        goto devam;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      pressed_button = myButtons.checkButtons();

      if (pressed_button==del_geri)
      { 
        myButtons.deleteButton(del_geri);
   return;
      }
    }else{goto interloop2;}
  }
  goto interloop2;
}
//---------------------------------------------------- 


//Şifre Giriş
sifrekeypad:
while(1){
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myButtons.deleteAllButtons();
myGLCD.clrScr();
interloop3:


myGLCD.clrScr();
         geri = myButtons.addButton( 5  , 35 , 80 , 25, "Geri");
          nm1 = myButtons.addButton( 20  ,95  , 85 ,  25,  "1");
          nm2 = myButtons.addButton( 120  ,95  , 85 ,  25 ,"2");
          nm3 = myButtons.addButton( 220 ,95  , 85 ,  25 ,"3"); 
          nm4 = myButtons.addButton( 20  ,130 , 85 ,  25, "4");
          nm5 = myButtons.addButton( 120  ,130 , 85 ,  25, "5");
          nm6 = myButtons.addButton( 220 ,130 , 85 ,  25 ,"6");
          nm7 = myButtons.addButton( 20  ,165 , 85 ,  25 ,"7"); 
          nm8 = myButtons.addButton( 120  ,165 , 85 ,  25 ,"8");  
          nm9 = myButtons.addButton( 220 ,165 , 85 ,  25 ,"9");
     del_geri = myButtons.addButton( 20  ,200 , 85 ,  25, "Del"); 
 nm0_sifregir = myButtons.addButton( 120  ,200 , 85 ,  25 ,"0"); 
        enter = myButtons.addButton( 220 ,200 , 85 ,  25 ,"Enter");

  myButtons.drawButtons();

sifre=0;

while(1) 
  {
    

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    
  }

  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));

    
    myGLCD.setColor(VGA_WHITE);
    myGLCD.print("Ev Kontrol Paneli",CENTER,5);
      if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        
        goto geg;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      pressed_button = myButtons.checkButtons();

      if (pressed_button==geri)
      {

        geg:
myButtons.deleteAllButtons();
myGLCD.clrScr();
         return;
   }
      
 
  
   myGLCD.setColor(VGA_WHITE);

 
      
if(pressed_button == nm1){
sifre += 1;
delay(100);
}

if(pressed_button == nm2){
sifre += 2;
delay(100);
}
  
if(pressed_button == nm3){
sifre += 3;
delay(100);
}
 
if(pressed_button == nm4){
sifre += 4;
delay(100);
}

if(pressed_button == nm5){
sifre += 5;
delay(100);
}

if(pressed_button == nm6){
sifre += 6;
delay(100);
}

if(pressed_button == nm7){
sifre += 7;
delay(100);
}

if(pressed_button == nm8){
sifre += 8;
delay(100);
}

if(pressed_button == nm9){
sifre += 9;
delay(100);
}

if(pressed_button == nm0_sifregir){
delay(100);
}

if(pressed_button == del_geri){
sifre = 0;
delay(100);
}

if(pressed_button == enter ){
if(sifre == 19){
  delay(100);
  
  myGLCD.clrScr();
myButtons.deleteAllButtons();
myGLCD.setColor(VGA_WHITE);
myGLCD.print("Ev Kontrol Paneli",CENTER,5);
  myGLCD.setColor(VGA_LIME);
  myGLCD.print("Sifre Dogru",CENTER,95);
myGLCD.print("Erisim Onaylandi",CENTER,120);
delay(400);
goto anamenu;
  }else{
    delay(100);
    
 myGLCD.clrScr();
myButtons.deleteAllButtons();
myGLCD.setColor(VGA_WHITE);
myGLCD.print("Ev Kontrol Paneli",CENTER,5);
 myGLCD.setColor(VGA_RED);
myGLCD.print("Sifre Yanlis",CENTER,95);
myGLCD.print("Erisim Engellendi",CENTER,120);
sifre=0;
delay(400);
    goto interloop3;
  }}}}}

    
//------------------------------------------
//şifre korumalı kontrol paneli






anamenu:

while(1){
interloopanamenu: 



myGLCD.setColor(VGA_WHITE);
myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myGLCD.clrScr();
myButtons.deleteAllButtons();
sicaklik2 = myButtons.addButton(60,40, 200,  30, "Sicakliklar",BUTTON_DISABLED);  
voltaj_deger2 = myButtons.addButton(60,80, 200,  30, "Voltajlar");
rolekont = myButtons.addButton(60,  120, 200,  30, "Roleler");
vanakont = myButtons.addButton(60,  160, 200,  30, "Vanalar",BUTTON_DISABLED);
geri = myButtons.addButton( 10,  200, 85,  30, "Geri");
myButtons.drawButtons();






while(1) 
  {
    

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    
  }

    
      mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
      if(resetcounter==1330){
        
        goto geri;
      }
    resetcounter ++;    
    Serial.println(resetcounter);
    
    
    if (myTouch.dataAvailable() == true)
    {
      
      resetcounter=0;

      
      pressed_button = myButtons.checkButtons();

      if (pressed_button==geri)
      {
        geri:
        resetcounter=0;
         Serial.println(resetcounter);
         myButtons.deleteButton(geri);
         myButtons.deleteButton(rolekont);
         myButtons.deleteButton(sicaklik2);
         myButtons.deleteButton(voltaj_deger2);
         myButtons.deleteButton(vanakont);
         myGLCD.clrScr();
         return;
        
        }

      if (pressed_button==rolekont)
      {
      goto roleler;
      }

      if (pressed_button==sicaklik2)
      {
      goto sicaklik2;
      }

      if (pressed_button==voltaj_deger2)
      {
      goto voltajdeger2;
      }
      if (pressed_button==vanakont)
      {
      goto vanalar;
      }


      
      }
  }
 
 





 


//-----------------------------------------------------
//Voltaj Görüntüleme
voltajdeger2:
while(1){
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myButtons.deleteButton(rolekont);
myButtons.deleteButton(sicaklik2);
myButtons.deleteButton(voltaj_deger2);
myButtons.deleteButton(vanakont);
myGLCD.clrScr();
geri = myButtons.addButton(10,  200, 85,  30, "Geri");
 myButtons.drawButtons();

interloop4:

myGLCD.print("Ev Kontrol Paneli",CENTER,5);
//batarya
 value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
myGLCD.print("-Batarya Voltaji-",CENTER,40);
myGLCD.print(String(vin1),CENTER,70);

myGLCD.print("-Panel Voltaji-",CENTER,100);
myGLCD.print(String(vin2),CENTER,130);

   
while(1) 
  {


  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    

  }

  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));

      if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        goto anamenu;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      pressed_button = myButtons.checkButtons();

      if (pressed_button==geri)
      {
        myButtons.deleteButton(geri);
   goto interloopanamenu;
      }
   
  }
  goto interloop4;
}

//--------------------------------------------------
 
//Sıcaklık görüntüleme
 sicaklik2:
while(1){
  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
myButtons.deleteButton(rolekont);
myButtons.deleteButton(sicaklik2);
myButtons.deleteButton(voltaj_deger2);
myButtons.deleteButton(vanakont);
myGLCD.clrScr();
geri = myButtons.addButton(10,  200, 85,  30, "Geri");
 myButtons.drawButtons();

interloop5:


 okunanVoltaj11 = analogRead(lm351);
  sicaklik111 = okunanVoltaj11 / 9.31; 

  okunanVoltaj22 = analogRead(lm352);
  sicaklik222 = okunanVoltaj22 / 9.31; 

  okunanVoltaj33 = analogRead(lm353);
  sicaklik333 = okunanVoltaj33/ 9.31; 

myGLCD.print("Ev Kontrol Paneli",CENTER,5);
//ev sicaklık
myGLCD.print("-Ev Sicaklik-",CENTER,40);
myGLCD.print(String(sicaklik111),CENTER,65);
//dışarı sıcaklık
myGLCD.print("-Acik Hava Sicaklik-",CENTER,95);
myGLCD.print(String(sicaklik222),CENTER,120);   
//havuz sıcaklık
myGLCD.print("-Havuz Sicaklik-",CENTER,155);
myGLCD.print(String(sicaklik333),CENTER,180);   



while(1) 
  {

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   


  }


  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));


   
      if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        goto anamenu;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      
      pressed_button = myButtons.checkButtons();

      if (pressed_button==geri)
      {
        myButtons.deleteButton(geri);
   goto interloopanamenu;
      }
    }goto interloop5;
  }
  goto interloop5;
}



//-----------------------------------------------------
//Vana Kontrol
vanalar:

  myGLCD.clrScr();

  myGLCD.print("Ev Kontrol Paneli",CENTER,5);
  
myButtons.deleteAllButtons();

myGLCD.clrScr();
geri = myButtons.addButton(10,  200, 85,  30, "Geri");
vana1 = myButtons.addButton(  10  ,95  , 100 , 35,  "Vana 1");
vana2 = myButtons.addButton( 205  ,95  , 100 ,  35 ,"Vana 2");

 myButtons.drawButtons();

interloop7:

myGLCD.setColor(VGA_WHITE);
myGLCD.print("Ev Kontrol Paneli",CENTER,5);

   
while(1) 
  {

  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }else if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }

      if(gelenascii==99){
    nrl2=1;
    digitalWrite(43,HIGH);
   }else if(gelenascii==100){
    nrl2=0;
    digitalWrite(43,LOW);
   }

   if(gelenascii==101){
    nrl3=1;
    digitalWrite(44,HIGH);
   }else if(gelenascii==102){
    nrl3=0;
    digitalWrite(44,LOW);
   }

      if(gelenascii==103){
    nrl4=1;
    digitalWrite(45,HIGH);
   }else if(gelenascii==104){
    nrl4=0;
    digitalWrite(45,LOW);
   }

   if(gelenascii==105){
    nrl5=1;
    digitalWrite(46,HIGH);
   }else if(gelenascii==106){
    nrl5=0;
    digitalWrite(46,LOW);
   }

      if(gelenascii==107){
    nrl6=1;
    digitalWrite(47,HIGH);
   }else if(gelenascii==108){
    nrl6=0;
    digitalWrite(47,LOW);
   }

      if(gelenascii==109){
    nrl7=1;
    digitalWrite(48,HIGH);
   }else if(gelenascii==110){
    nrl7=0;
    digitalWrite(48,LOW);
   }

      if(gelenascii==111){
    nrl8=1;
    digitalWrite(49,HIGH);
   }else if(gelenascii==112){
    nrl8=0;
    digitalWrite(49,LOW);
   }
    

  }

  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));
    
    myGLCD.print("Ev Kontrol Paneli",CENTER,5);
      if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        goto anamenu;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      pressed_button = myButtons.checkButtons();
      
//vana 1

if (pressed_button==vana1 ){
if(vanaa1==0  ){
vanaa1=1;
}else if(vanaa1==1 ){
vanaa1=0;
}}

//vana 2
if (pressed_button==vana2  ){
if(vanaa2==0  ){
vanaa2=1;
}else if(vanaa2==1 ){
vanaa2=0;
}}


 
      if (pressed_button==geri)
      {
        myButtons.deleteAllButtons();
   goto interloopanamenu;
      }
 }
if(vanaa1==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(125,112,10);
 
}
if(vanaa1==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(125,112,10);
 

 
} 

//------------------------------------------------

if(vanaa2==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(185,112,10);
 
}
if(vanaa2==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(185,112,10);
 
}  

   
 
  goto interloop7;
}


//---------------------------------------------
//Röle Kontrolleri
roleler:
resetcounter = 0;

while(1){
  


myButtons.deleteAllButtons();

myGLCD.clrScr();
myGLCD.print("Ev Kontrol Paneli",CENTER,5);


          geri = myButtons.addButton( 5  , 35 , 80 , 25, "Geri");
          rl1 = myButtons.addButton(  10  ,95  , 100 , 25,  "Role 1");
          rl2 = myButtons.addButton( 205  ,95  , 100 ,  25 ,"Role 2");
          rl3 = myButtons.addButton( 10 ,130  , 100 ,  25 ,"Role 3"); 
          rl4 = myButtons.addButton( 205  ,130 , 100 ,  25, "Role 4");
          rl5 = myButtons.addButton( 10  ,165 , 100 ,  25, "Role 5");
          rl6 = myButtons.addButton( 205 ,165 , 100 ,  25 ,"Role 6");
          rl7 = myButtons.addButton( 10  ,200 , 100 ,  25 ,"Role 7"); 
          rl8 = myButtons.addButton( 205  ,200 , 100 ,  25 ,"Role 8");  
          
 myButtons.drawButtons();

digitalWrite(42,HIGH);
 
interloop6:




while(1) 
  {
    
  if (mySerial.available()) {
   gelenascii  = mySerial.read() ;
   //Serial.println(gelenascii);
   
   if(gelenascii==98){
    nrl1=0;
    digitalWrite(42,LOW);
   }else if(gelenascii==97){
    nrl1=1;
    digitalWrite(42,HIGH);
   }

      if(gelenascii==99){
    nrl2=0;
    digitalWrite(43,LOW);
   }else if(gelenascii==100){
    nrl2=1;
    digitalWrite(43,HIGH);
   }

   if(gelenascii==101){
    nrl3=0;
    digitalWrite(44,LOW);
   }else if(gelenascii==102){
    nrl3=1;
    digitalWrite(44,HIGH);
   }

      if(gelenascii==103){
    nrl4=0;
    digitalWrite(45,LOW);
   }else if(gelenascii==104){
    nrl4=1;
    digitalWrite(45,HIGH);
   }

   if(gelenascii==105){
    nrl5=0;
    digitalWrite(46,LOW);
   }else if(gelenascii==106){
    nrl5=1;
    digitalWrite(46,HIGH);
   }

      if(gelenascii==107){
    nrl6=0;
    digitalWrite(47,LOW);
   }else if(gelenascii==108){
    nrl6=1;
    digitalWrite(47,HIGH);
   }

      if(gelenascii==109){
    nrl7=0;
    digitalWrite(48,LOW);
   }else if(gelenascii==110){
    nrl7=1;
    digitalWrite(48,HIGH);
   }

      if(gelenascii==111){
    nrl8=0;
    digitalWrite(49,LOW);
   }else if(gelenascii==112){
    nrl8=1;
    digitalWrite(49,HIGH);
   }
   

  }


  mySerial.flush();
  
  value1 = analogRead(0);
   vout1 = (value1 * 5.0) / 1024.0; 
   vin1 = vout1 / (r2/(r1+r2)); 
   if (vin1<0.09) {
   vin1=0.0;
   }

   
//panel
 value2 = analogRead(1);
   vout2 = (value2 * 5.0) / 1024.0; 
   vin2 = vout2 / (r2/(r1+r2)); 
   if (vin2<0.09) {
   vin2=0.0;
   }
a0 = analogRead(0);
a1 = analogRead(1);

mySerial.print(String(vin1) + String("/") + String(vin2));

      if(resetcounter==615){
                myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
        goto anamenu;
      }
    resetcounter ++;    
   
    if (myTouch.dataAvailable() == true)
    {
resetcounter = 0;
      
      pressed_button = myButtons.checkButtons();

//röle 1

if (pressed_button==rl1 ){
if(nrl1==0  ){
nrl1=1;
}else if(nrl1==1 ){
nrl1=0;
}}

//röle 2
if (pressed_button==rl2  ){
if(nrl2==0  ){
nrl2=1;
}else if(nrl2==1 ){
nrl2=0;
}}

//röle 3
if (pressed_button==rl3  ){
if(nrl3==0 ){
nrl3=1;
}else if(nrl3==1  ){
nrl3=0;
}}

//röle 4
   if (pressed_button==rl4  ){
if(nrl4==0 ){
nrl4=1;
}else if(nrl4==1 ){
nrl4=0;
}}

//röle 5
if (pressed_button==rl5 ){
if(nrl5==0){
nrl5=1;
}else if(nrl5==1 ){
nrl5=0;
}}

//röle 6
   if (pressed_button==rl6 ){
if(nrl6==0  ){
nrl6=1;
}else if(nrl6==1 ){
nrl6=0;
}}

//röle 7
if (pressed_button==rl7  ){
if(nrl7==0){
nrl7=1;
}else if(nrl7==1){
nrl7=0;
}}

//röle 8
if (pressed_button==rl8 ){
if(nrl8==0 ){
nrl8=1;
}else if(nrl8==1  ){
nrl8=0;
}}



      if (pressed_button==geri)
      {
        myButtons.deleteAllButtons();
        myGLCD.clrScr();
        myGLCD.setColor(VGA_WHITE);
   goto interloopanamenu;
      }
    
     //-----------------------------------

}  


if(nrl1==0){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(125,107,10);
 digitalWrite(42,LOW);
}
if(nrl1==1){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(125,107,10);
 digitalWrite(42,HIGH);
}  

if(nrl2==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(185,107,10);
 digitalWrite(43,LOW);
}
if(nrl2==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(185,107,10);
 digitalWrite(43,HIGH);
}  
//------------------------------------
if(nrl3==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(125,142,10);
 digitalWrite(44,LOW);
}
if(nrl3==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(125,142,10);
 digitalWrite(44,HIGH);
}  

if(nrl4==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(185,142,10);
 digitalWrite(45,LOW);
}
if(nrl4==0){
  myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(185,142,10);
 digitalWrite(45,HIGH);
}
//-----------------------------------
if(nrl5==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(125,177,10);
 digitalWrite(46,LOW);
}
if(nrl5==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(125,177,10);
 digitalWrite(46,HIGH);
}  

if(nrl6==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(185,177,10);
 digitalWrite(47,LOW);
}
if(nrl6==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(185,177,10);
 digitalWrite(47,HIGH);
}  
//---------------------------------
if(nrl7==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(125,212,10);
 digitalWrite(48,LOW);
}
if(nrl7==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(125,212,10);
 digitalWrite(48,HIGH);
}  

if(nrl8==1){
myGLCD.setColor(VGA_LIME);
 myGLCD.fillCircle(185,212,10);
 digitalWrite(49,LOW);
}
if(nrl8==0){
myGLCD.setColor(VGA_RED);
 myGLCD.fillCircle(185,212,10);
 digitalWrite(49,HIGH);
}
goto interloop6;
  }
  
}


  
  }
}

}
