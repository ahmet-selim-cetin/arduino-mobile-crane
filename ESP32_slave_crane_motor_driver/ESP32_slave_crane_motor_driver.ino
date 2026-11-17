#include <BluetoothSerial.h>
#include <ESP32Servo.h>

Servo FRservo;
Servo VINCservo;
BluetoothSerial SerialBT;

#define ServoFRpin 19
#define ServoVINCpin 18
#define enA 25
#define enB 21
#define in1 26
#define in2 27
#define in3 33
#define in4 32

String sayi;
int aci=0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Server"); // Bluetooth cihaz adı
  Serial.println("Bluetooth başlatıldı, eşleşme bekleniyor...");
    
    
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  FRservo.setPeriodHertz(50);
  VINCservo.setPeriodHertz(50);

  FRservo.attach(ServoFRpin,500,2400);
  VINCservo.attach(ServoVINCpin,500,2400);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
ledcAttach(enA,5000,8);
ledcAttach(enB,5000,8);

  FRservo.write(aci);
  VINCservo.write(aci);
  delay(1000);
  Serial.println("FRservo full test başlatiliyor...");
  for (int i = 0;i < 180;i++){
   VINCservo.write(i);
   delay(10);
   
  }
   /* VINCservo.write(0);    // 0 derece
  delay(1000);

  VINCservo.write(90);   // 90 derece
  delay(1000);

  VINCservo.write(180);  // 180 derece
  delay(1000);*/
    Serial.println("FRservo full test tamamlandı");





  // put your setup code here, to run once:
  
}

void loop() {
  if (SerialBT.available()){
    String data = SerialBT.readStringUntil('\n');
    data.trim();
    Serial.println("BT den geldi :" + data);

    if (data.startsWith("Yjs") || data.startsWith("Xjs")){
      int index = data.indexOf(":");
      sayi = data.substring(index + 1);
    }

  
    if (data == "Right"){
      aci = aci + 5;
      VINCservo.write(aci);
    }

    if (data == "Left"){
      aci = aci - 5;
      VINCservo.write(aci);
    }

    if (data == "Up"){
      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      analogWrite(enA,200);
    }

    if (data == "Down"){
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      analogWrite(enA,200);
    }

    if (data == "None"){
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      analogWrite(enA,0);
    }

    if (data.startsWith("Yjs")){  
      int sayiServoMap = map(sayi.toInt(),0,1023,0,180);
        for (int d = 0;d < sayiServoMap;d++){
          FRservo.write(d);
        }
        delay(30);
    }

    if (data.startsWith("Yjs") && sayi == " None"){
      FRservo.write(90);
    }

    if (data.startsWith("Xjs") && sayi.toInt() < 490){
      int sayiMotMap = map(sayi.toInt(),0,490,230,0);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
      analogWrite(enB,sayiMotMap);
    }

    if (data.startsWith("Xjs") && sayi.toInt() > 540){
      int sayiMotMapBCK = map(sayi.toInt(),540,1023,0,230);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(enB,sayiMotMapBCK);
    }

    if (data.startsWith("Xjs") && sayi == " None"){
      Serial.println(sayi);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
      analogWrite(enB,0);
    }
  }
  // put your main code here, to run repeatedly:
//delay(50);
}
