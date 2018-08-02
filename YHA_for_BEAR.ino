//Harry Potter piezo music from http://www.instructables.com/id/Arduino-Harry-Potter-Theme-Song/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "        " //ex. blah_blah_blah.firebaseio.com
#define FIREBASE_AUTH "        " //This is the Legacy Credential. Proj Settings/Service Accounts/Database Secret
#define WIFI_SSID "EWSD_Guest" //Change as needed
#define WIFI_PASSWORD "wifi@EWSD" //Change as needed

#define buzzerPin D2 //you don't have to use this pin

#define ESP8266_SSID_PREFIX "Bear" //The first part of the SSID that your esp8266 will broadcast, to quickly see it on a network.
ESP8266WebServer server;
//password must be at least 8 characters
const char WiFiAPPSK[] = "123455678"; //Personalized password

const char INDEX_HTML[] =
  "<!DOCTYPE HTML>"
  "<html>"
  "<head>"
  "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
  "<title>ESP8266</title>"
  "<style>"
    "body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: Maroon; }"
  "</style>"
  "</head>"
  "<body>"
  "<h1>ESP8266 Direct Access Demo</h1>"
  "<button onclick='toggleLED()'>Toggle LED</button>"
  "<button onclick='buzzBuzzer()'>Buzz Buzzer</button>"
  "<script>"
    "function toggleLED(){"
      "fetch('/toggleLED').then(stream=>stream.text()).then(text=>console.log(text))"
    "}"
    "function buzzBuzzer(){"
      "fetch('/buzzBuzzer').then(stream=>stream.text()).then(text=>console.log(text))"
    "}"
  "</script>"
  "</body>"
  "</html>";

int LED = D5; //You can always add more LEDs
int buzzer_pin = D2;

struct MusicStruct {  //I lifted this from online
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
}Music;

struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
}Length;

int tempo = 400;  //you don't need to mess with this variable

void setup()
{
  Serial.begin(115200); //to look at your serial monitor
  setupWiFi();
  
  pinMode(LED, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  server.on("/",sendIndex);
  server.on("/toggleLED", toggleLED); //This is for your browser web page
  server.on("/buzzBuzzer", buzzBuzzer); //This is for your browser web page
  server.begin();
  Serial.println("");
  Serial.println("");
  Serial.print("Server running on http://192.168.4.1/");
  Serial.println("");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setBool("share/buzz", false);
  if(Firebase.failed()){
    Serial.print("Firebase connection failed!");
    Serial.println("");
    Serial.print(Firebase.error());
  } else {
    Serial.print("Firebase connection success!");
  }
  Serial.println("");
}

int timePassed (int time) {
  int diff = 0;
  if (millis() <= time) {
    diff = (69666 - time) + millis();
  } else {
    diff = millis() - time;
  }
  return diff;
}

int checkFirebaseTime = 0;
bool buzz = false; 

void loop()  //Added to stop the annoying beeping
{
  if (timePassed (checkFirebaseTime) >= 1000  && Firebase.success()) {
    buzz = Firebase.getBool("share/buzz");
    Serial.println();
    Serial.print("buzz :  ");
    Serial.print(buzz);
    if(buzz) buzzBuzzer();
    checkFirebaseTime = millis();
  }
  server.handleClient();
}

void sendIndex(){
  server.send(200,"text/html",INDEX_HTML);  
}

void toggleLED(){
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  //server.send(204,"");
  server.send(200,"text/plain","Toggle LED!\n");
}

void buzzBuzzer(){ //I created a function called harryPotter() that I'm calling here.  You can create your own function.
  //server.send(204,"");
  Firebase.setBool("share/buzz", false);
  server.send(200,"text/plain","Buzz Buzzer!\n");
  //tone( pin number, frequency in hertz, duration in milliseconds);
  digitalWrite(LED, HIGH); // turn LED on...I don't understand why HIGH means ON on this pin
  harryPotter();
  delay(450);
  digitalWrite(LED, LOW); //turn LED off
}

//Add this function
void setTone(int pin, int note, int duration) {
  tone(pin, note, duration);
  delay(duration);
  noTone(pin);
}

/*
 My harryPotter () function is below.
1.  Copy and paste it and give it a new name
2.  Experiment with notes and tempo
3.  Call the new function in the loop 
 */

void harryPotter() {
  setTone(buzzer_pin, Music.B, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.one_half);
  setTone(buzzer_pin, Music.G, tempo * Length.half);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.E, tempo * Length.two);
  setTone(buzzer_pin, Music.B2, tempo * Length.one);
  setTone(buzzer_pin, Music.A2, tempo * Length.two_half);
  setTone(buzzer_pin, Music.Fs, tempo * Length.two_half);
  
  setTone(buzzer_pin, Music.E, tempo * Length.one_half);
  setTone(buzzer_pin, Music.G, tempo * Length.half);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.Ds, tempo * Length.two);
  setTone(buzzer_pin, Music.F, tempo * Length.one);
  setTone(buzzer_pin, Music.B, tempo * Length.two_half);
  delay(500);
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP_STA);
  //Set up Access Point
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.println();
  Serial.print("Local IP: ");
  Serial.println();
  Serial.println(WiFi.localIP());
  
  // Set up Station
  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = ESP8266_SSID_PREFIX + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, 0, AP_NameString.length() + 1);

  for (int i=0; i<AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);
  //AP_NameChar is the SSID for the Wireless Access Point
  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}
