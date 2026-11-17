#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int buttonDeger = 0;
int Xdeger = 0;
int Ydeger = 0;
int Ymap = 0;
int Xmap = 0;
int SeriSayisi = 4;
long dortToplamX = 0;
long dortToplamY = 0;
int dortToplamOrtX;
int dortToplamOrtY;
bool xOluBolge = false;
bool yOluBolge = false;

#define Xpin A8
#define Ypin A9
//#define button A10
#define sag 1
#define sol 2
#define ust 3
#define alt 4
#define slct 5
#define bos 6
int lastState = 0;
int preState = 0;

void setup() {
  lcd.begin(16, 2);
     pinMode(Xpin,INPUT);
     pinMode(Ypin,INPUT);
   
    Serial.begin(9600);
    Serial1.begin(9600);
  // put your setup code here, to run once:
}

void loop() {
   Ydeger = analogRead(Ypin);
  Xdeger = analogRead(Xpin);
   Ymap = map(Ydeger,0,1023,0,180);
  Xmap = map(Xdeger,0,1023,0,150);

  if (Xdeger < 500 || Xdeger > 530){
    for (int q = 0; q < SeriSayisi; q++){
      dortToplamX = dortToplamX + analogRead(Xpin);
    delay(10);
    }
  }

  if (Ydeger < 500 || Ydeger > 530){
    for (int d = 0;d < SeriSayisi; d++){
      dortToplamY = dortToplamY + analogRead(Ypin);
    delay(10);
    }
  }

  dortToplamOrtX = dortToplamX/SeriSayisi;
  dortToplamOrtY = dortToplamY/SeriSayisi;
  dortToplamX = 0;
  dortToplamY = 0;
  Xmap = map(dortToplamOrtX,0,1023,0,150);
  Ymap = map(dortToplamOrtY,0,1023,0,180);
  Serial.println(Xdeger);
  //Serial.println(Xdeger);
  buttonDeger = analogRead(A0);
  //Serial.println(buttonDeger);
  //****************************************
  // BUTON TESPİT BLOĞU
  if (buttonDeger >= 0 && buttonDeger <= 67) {
    lastState = sag;

  } else if (buttonDeger >= 67 && buttonDeger < 222) {
    lastState = ust;

  } else if (buttonDeger >= 222 && buttonDeger < 397) {
    lastState = alt;

  } else if (buttonDeger >= 397 && buttonDeger < 604) {
    lastState = sol;

  } else if (buttonDeger >= 604 && buttonDeger < 1000) {
    lastState = slct;

  } else
    lastState = bos;

  // BUTON TESPİT SON
  //***********************************************

  //****************************************
  // BUTON DEĞİŞİMİ VAR MI?
  if (Xdeger <= 490 || Xdeger >= 540){
    Serial1.println("Xjs Deger:" + String(Xdeger));
    xOluBolge = false;
  }
  if (Ydeger <= 490 || Ydeger >= 540){
    Serial1.println("Yjs Deger: " + String(Ydeger));
    yOluBolge = false;
  }

  if (Xdeger > 490 && Xdeger < 540 && !xOluBolge){
    Serial1.println("Xjs Deger: None");
    xOluBolge = true;
  }
  
  if (Ydeger > 490 && Ydeger < 540 && !yOluBolge){
    Serial1.println("Yjs Deger: None");
    yOluBolge = true;
  }

  if (lastState == slct && preState != lastState) {
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Select");
     lcd.setCursor(0, 2);
    lcd.print(buttonDeger);
    Serial1.println("Select");
    Serial.println("Select");
      preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ
  }

  if (lastState == ust && preState != lastState) {
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Up");
     lcd.setCursor(0, 2);
    lcd.print(buttonDeger);
    Serial1.println("Up");
    Serial.println("Up");
      preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ
  }

  if (lastState == sag) {
    if (preState != lastState) {
      lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Right");
       lcd.setCursor(0, 2);
      lcd.print(buttonDeger);
        preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ
    }
    Serial1.println("Right");
    Serial.println("Right");
  }

  if (lastState == alt && preState != lastState) {
    lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Down");
     lcd.setCursor(0, 2);
    lcd.print(buttonDeger);
    Serial1.println("Down");
    Serial.println("Down");
    preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ
  }

  if (lastState == sol) {
    if (preState != lastState) {
      lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Left");
       lcd.setCursor(0, 2);
      lcd.print(buttonDeger);
        preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ
    }
    Serial1.println("Left");
    Serial.println("Left");
  }

  if (lastState == bos && preState != lastState) {
    lcd.clear();
    lcd.print("Dugmeye Basiniz");
    Serial1.println("None");
    Serial.println("None");
    
    preState = lastState;  // !!!!!! TOGGLE ÖNEMLİ a
  }
  // --------------------------!!!!!!!!!!!!!!!
  delay(60);
  // BUTON DEĞİŞİMİ VAR MI SON BLOK

}