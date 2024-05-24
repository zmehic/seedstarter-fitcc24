#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <DHT11.h>
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define FIREBASE_HOST "seedstarter-f9b21-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "9kYvaeMdIRNFA0WmoNqyCv4rBapIGyCDOptrQIyF"
#define WIFI_SSID "Zaim"
#define WIFI_PASSWORD "102030102030"


#define LIGHTS 5
#define FAN1 4
#define FAN2 0
#define DH11 16
#define HEATER 2
#define WATER 14
#define MIST 12

const int SOILH = A0;

FirebaseData firebaseData;

DHT11 dht11(DH11);

bool Temp;
  bool Fan;
  bool Light;
  bool Water;
  bool Mist;
  int tempValue;
  int humidityValue;
  int soilHumidityValue;
  bool Auto;
  bool SemiAuto;
  bool Manual;
  float soilHumidityPercentage;
  int semitemp;
  int semihumidity;
  int semisoil;

  const char* serverName = "http://worldtimeapi.org/api/timezone/Europe/Sarajevo";
  unsigned long lastTime = 0;
  unsigned long timerDelay = 900000;
  String date;

void setup(){
  Serial.begin(115200);

  pinMode(LIGHTS, OUTPUT);
  pinMode(FAN1,OUTPUT);
  pinMode(FAN2,OUTPUT);
  pinMode(HEATER,OUTPUT);
  pinMode(WATER,OUTPUT);
  pinMode(MIST,OUTPUT);

  digitalWrite(LIGHTS,HIGH);
  digitalWrite(FAN1,HIGH);
  digitalWrite(FAN2,HIGH);
  digitalWrite(HEATER,HIGH);
  digitalWrite(WATER,HIGH);
  digitalWrite(MIST,HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to...");
  Serial.print(WIFI_SSID);

  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
   Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());            
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   

  Firebase.reconnectWiFi(true);
  Firebase.setMaxRetry(firebaseData, 5);
  Serial.println();    
  delay(1000);

}

void loop (){

  

  delay(250);
  Serial.println("Citam temp: ");
  tempValue=dht11.readTemperature();
  delay(150);
  Serial.print(tempValue);
  delay(200);
  Serial.println("Citam vlaznost: ");
  humidityValue=dht11.readHumidity();
    Serial.print(humidityValue);
  delay(200);
  soilHumidityValue=analogRead(SOILH);
  delay(200);
  soilHumidityPercentage=(100-((soilHumidityValue/1023.00)*100));
  delay(200);

  if ((millis() - lastTime) > timerDelay){
      lastTime=millis();
      date = httpGETRequest(serverName);
      JSONVar myObject = JSON.parse(date);

      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      JSONVar keys = myObject.keys();
      JSONVar value = myObject["datetime"];

      FirebaseJson json;
      if(humidityValue<0)
      {
        humidityValue=0;
      }

      Serial.println(value);
      json.set("DateTime", JSON.stringify(value));
      json.set("Humidity", soilHumidityPercentage);
      json.set("SoilHumidity", humidityValue);
      json.set("Temp", tempValue);

      if (Firebase.pushJSON(firebaseData, "/Hourly", json)) {

      } else {
        Serial.println(firebaseData.errorReason());
      }

  }

  if(Firebase.setInt(firebaseData, "Status/Temperature", tempValue))
  {
    Serial.println("Temperatura: ");
    Serial.print(tempValue);
    Serial.println("°C");
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(100);
  if(Firebase.setInt(firebaseData, "Status/Humidity", humidityValue))
  {
    Serial.println("Vlažnost zraka: ");
    Serial.print(humidityValue);
    Serial.println("%");
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(100);

  if(Firebase.setInt(firebaseData, "Status/GroundHumidity", int(soilHumidityPercentage)))
    {
    Serial.println("Vlažnost tla: ");
    Serial.print(soilHumidityPercentage);
    Serial.println("%");
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

  if(Firebase.getBool(firebaseData,"/Mode/Auto",&Auto))
  {
    Serial.println("Auto: ");
    Serial.print(Auto);
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

  if(Firebase.getBool(firebaseData,"/Mode/SemiAuto",&SemiAuto))
  {
    Serial.println("SemiAuto: ");
    Serial.print(SemiAuto);
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

  if(Firebase.getBool(firebaseData,"/Mode/Manual",&Manual))
  {
    Serial.println("Manual: ");
    Serial.print(Manual);
  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

  if(Manual==true)
  {
    if(Firebase.getBool(firebaseData,"/Control/Temp",&Temp))
  {
    Serial.print("Temperatura: ");
    Serial.println(Temp);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

  if(Firebase.getBool(firebaseData,"Control/Fan",&Fan))
  {
    Serial.print("Fan: ");
    Serial.println(Fan);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

  if(Firebase.getBool(firebaseData,"Control/Light", &Light))
  {
    Serial.print("Light: ");
    Serial.println(Light);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

  if(Firebase.getBool(firebaseData,"/Control/Water",&Water))
  {
    Serial.print("Water: ");
    Serial.println(Water);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);
  if(Firebase.getBool(firebaseData,"/Control/Mist",&Mist))
  {
    Serial.print("Mist: ");
    Serial.println(Mist);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);
  if(Fan==true)
  {
    Serial.println("FanOn");
    onPin(FAN1);
    onPin(FAN2);
  }
  else if(Fan==false)
  {
     Serial.println("FanOff");
    offPin(FAN1);
    offPin(FAN2);
  }

  if(Light==true)
  {
    Serial.println("LightON");
    onPin(LIGHTS);
  }
  else if(Light==false)
  {
    Serial.println("LightOFF");
    offPin(LIGHTS);
  }

  if(Temp==true){
    Serial.println("HeaterOn");
    onPin(HEATER);
  }
  else if(Temp==false)
  {
    Serial.println("HeaterOff");
    offPin(HEATER);
  }
  if(Water==true){
    Serial.println("WaterOn");
    onPin(WATER);

  }
  else if(Water==false)
  {
    Serial.println("WaterOff");
    offPin(WATER);
  }
  if(Mist==true){
    Serial.println("MistOn");
    onPin(MIST);

  }
  else if(Mist==false)
  {
    Serial.println("MistOff");
    offPin(MIST);
  }
}
else if(SemiAuto==true)
{
  if(Firebase.getInt(firebaseData,"SemiValues/Humidity",&semihumidity))
  {
    Serial.println("SemiHumidity: ");
    Serial.print(semihumidity);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);
  if(Firebase.getInt(firebaseData,"SemiValues/Temp",&semitemp))
  {
    Serial.println("SemiTemp: ");
    Serial.print(semitemp);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);
  if(Firebase.getInt(firebaseData,"SemiValues/SoilHumidity",&semisoil))
  {
    Serial.println("SemiSoil: ");
    Serial.print(semisoil);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  delay(200);

/*    digitalWrite(LIGHTS,HIGH);
  digitalWrite(FAN1,HIGH);
  digitalWrite(FAN2,HIGH);
  digitalWrite(HEATER,HIGH);
  digitalWrite(WATER,HIGH);
  digitalWrite(MIST,HIGH);
*/
  onPin(LIGHTS);
  if(soilHumidityPercentage<semisoil)
  {
    onPin(WATER);
  }else
  {
    offPin(WATER);
  }

  if(tempValue<semitemp)
  {
    onPin(HEATER);
  }else
  {
    offPin(HEATER);
  }

  if(humidityValue==semihumidity)
  {
    offPin(MIST);
    offPin(FAN1);
    offPin(FAN2);
  }
  else if(humidityValue>semihumidity)
  {
    offPin(MIST);
    onPin(FAN1);
    onPin(FAN2);
  }
  else if(humidityValue<semihumidity)
  {
    onPin(MIST);
    offPin(FAN1);
    offPin(FAN2);
  }

  delay(200);
}
else if(Auto==true)
{
  if(Firebase.getInt(firebaseData,"Selected/Crop/Humidity",&semihumidity))
  {
    Serial.println("Selected Humidity: ");
    Serial.print(semihumidity);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  if(Firebase.getInt(firebaseData,"Selected/Crop/Temp",&semitemp))
  {
    Serial.println("Selected Temperature: ");
    Serial.print(semitemp);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }
  if(Firebase.getInt(firebaseData,"Selected/Crop/SoilHumidity",&semisoil))
  {
    Serial.println("Selected Soil Humidity: ");
    Serial.print(semisoil);

  }
  else
  {
    Serial.println(firebaseData.errorReason());
  }

  onPin(LIGHTS);
  if(soilHumidityPercentage<semisoil)
  {
    onPin(WATER);
  }else
  {
    offPin(WATER);
  }

  if(tempValue<semitemp)
  {
    onPin(HEATER);
  }else
  {
    offPin(HEATER);
  }

  if(humidityValue==semihumidity)
  {
    offPin(MIST);
    offPin(FAN1);
    offPin(FAN2);
  }
  else if(humidityValue>semihumidity)
  {
    offPin(MIST);
    onPin(FAN1);
    onPin(FAN2);
  }
  else if(humidityValue<semihumidity)
  {
    onPin(MIST);
    offPin(FAN1);
    offPin(FAN2);
  }

  delay(200);
}
 
}

  

/*  if (Firebase.pushJSON(fbdo, "/test/append", json)) {

    Serial.println(fbdo.dataPath());

    Serial.println(fbdo.pushName());

    Serial.println(fbdo.dataPath() + "/"+ fbdo.pushName());

  } else {
    Serial.println(fbdo.errorReason());
  }
*/
void onPin(int8_t pin) {
  digitalWrite(pin, LOW);
}

void offPin(int8_t pin) {
  digitalWrite(pin, HIGH);
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
  