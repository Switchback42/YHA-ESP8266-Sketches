//Use with authentic NeoPixels
//Reminder:  You need to download a couple of libraries
/* NodeMCU & Neopixel Cheerlights by Marc de Vinck
  CheerLights originally created by Hans Scharler

  Lots of code borrowed from CheerLights & Adafruit

  Adafruit Neopixels - https://www.adafruit.com/products/1312
  Cheerlights - http://www.cheerlights.com
  ThingSpeak - https://www.thingspeak.com

  Project link -  https://blog.adafruit.com/2016/05/06/feather-huzzah-neopixel-cheerlighs/ ‎
*/

#include <ESP8266WiFi.h> // Include the ESP8266 Library
#include <ThingSpeak.h> // Include the ThingSpeak library
#include <Adafruit_NeoPixel.h> // Include the adafruit Neopixel Library

#define PIN            D2 // What pin is the data being sent to the Neopixels.  D2 on NodeMCU
#define NUMPIXELS      12 // How many Neopixels are you using?

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // Set up the Neopixels
int delayval = 500; // delay for half a second

WiFiClient  client;

//const char* ssid     = "Wifi0DC7"
//const char* password = "Wiskeydog"; // Enter your WiFi password
const char* ssid     = "BurlingtonTelecomGuest"; // Enter your WiFi network name
const char* password = NULL; 
const char* host = "api.thingspeak.com";
unsigned long cheerLightsChannelNumber = 1417; // The channel of Cheerlights


void setup() {
  //pinMode(LED_BUILTIN, OUTPUT);
  //(LED_BUILTIN, LOW); //turns onboard LED on
  
  pixels.begin(); // Start up Neopixels

  Serial.begin(115200); // Get ready for serial communications and display the connetion status 
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi network -  ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
}

String colorName[] = {"none", "red", "pink", "green", "blue", "cyan", "white", "warmwhite", "oldlace", "purple", "magenta", "yellow", "orange", "1999"}; // List of CheerLights color names

int colorRGB[][3] = {     0,  0,  0,  // "none"  // Map of RGB values for each of the Cheerlight color names
                          255,  0,  0,  // "red"
                          255, 192, 203, // "pink"
                          0, 255,  0, // "green"
                          0,  0, 255, // "blue"
                          0, 255, 255, // "cyan",
                          255, 255, 255, // "white",
                          255, 223, 223, // "warmwhite",
                          255, 223, 223, // "oldlace",
                          128,  0, 128, // "purple",
                          255,  0, 255, // "magenta",
                          255, 255,  0, // "yellow",
                          255, 165,  0, // "orange"}
                          128, 0, 128}; // "1999 Prince purple"

void loop() {

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/channels/1417/field/1/last.json";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500); // Just a quick pause to let everything settle
  String color = ThingSpeak.readStringField(cheerLightsChannelNumber, 1); //Read the Cheerlight color and print to the serial monitor
  Serial.println(color);
  setColor(color);
  delay(18000);
}

void setColor(String color)
{
  // Look through the list of colors to find the one that was requested
  for (int iColor = 0; iColor <= 13; iColor++)
  {
    if (color == colorName[iColor])
    {

      pixels.setPixelColor(0, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 1 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(1, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 2 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(2, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 3 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(3, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 3 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(4, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 4 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(5, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 5 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(6, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 6 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(7, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 7 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(8, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 8 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(9, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 9 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(10, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 10 color (kept them seperate for easy hacking & understanding)
      pixels.setPixelColor(11, pixels.Color (colorRGB[iColor][0], colorRGB[iColor][1], colorRGB[iColor][2])); // set pixel 11 color (kept them seperate for easy hacking & understanding)
      pixels.show(); // This sends the updated pixel color to the hardware.

      delay(delayval); // Delay for a period of time (in milliseconds).

    }
  }
}
