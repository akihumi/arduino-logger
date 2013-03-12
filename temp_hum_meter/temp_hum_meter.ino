#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <LiquidCrystal.h>

int const BL = 1;
int const TEMPSENSOR = 0;
int const HUMSENSOR = 1;
int const INTERVAL = 3600;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x87, 0x52};
byte server[] = {23, 23, 231, 180};
int counter;
float temp;
float hum;
float v = 4.8;

EthernetClient client;

void setup();
void loop();
void setup(){
  Serial.begin(9600);
  pinMode(BL, OUTPUT);
  digitalWrite(BL, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ethernet begin...");
  lcd.setCursor(0, 1);
  if(Ethernet.begin(mac) == 1){
    lcd.print("success");
  }else{
    lcd.print("failed!");
  }
  delay(1000);
  lcd.clear();
  temp = 0;
  hum = 0;
  counter = 0;

}
void senddata(float temp, float hum){
  if(client.connect("housedata.herokuapp.com", 80)){
    client.print("GET /senddatastatus?temp=");
    client.print(temp);
    client.print("&hum=");
    client.print(hum);
    client.println(" HTTP/1.1");
    client.println("Host: housedata.herokuapp.com");
    client.println();

    Serial.println("send server");
  }else{
    Serial.println("connot connect");
  }
  delay(1000);
  client.stop();
}

void loop(){
  Ethernet.maintain()
  temp = analogRead(TEMPSENSOR);
  hum = analogRead(HUMSENSOR);
  
  hum = ((v/1024) * hum) * 100;
  temp = (((v / 1024) * temp) * 100) -60;
  // send data per 1hour 
  if(counter % INTERVAL == 0){
    senddata(temp, hum);
    
    counter = 0;
   }

  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.setCursor(10, 0);
  lcd.print((char) 0xDF);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(hum);
  lcd.setCursor(10, 1);
  lcd.print("% ");
  counter += 5;
  Serial.println(counter);
  delay(5000);
}
