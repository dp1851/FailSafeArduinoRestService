/*
  This a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.

  Written in 2015 by Marco Schwartz under a GPL license.
*/

// Import required libraries
#include <WiFiNINA.h>
#include <aREST.h>
#include <LiquidCrystal.h>
//specify LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int val=0;
int vall=0;
// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "iPhone";
const char* password = "seniorproject";
//IPAddress ip(192,168,1,190);

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Variables to be exposed to the API
int temperature;
int humidity;

// Declare functions to be exposed to the API
int ledControl(String command);

void setup(void)
{
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("DEV");
  lcd.setCursor(6,1);
  lcd.print("Patel");
  delay(5000);
  lcd.clear();
  // Start Serial
  Serial.begin(115200);
 pinMode(7,OUTPUT);
 pinMode(13, OUTPUT);

  // Init variables and expose them to REST API
  temperature = 24;
  humidity = 40;
  rest.variable("temperature",&temperature);
  rest.variable("humidity",&humidity);

  // Function to be exposed
  rest.function("led",ledControl);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp8266");

  // Connect to WiFi

  WiFi.begin(ssid, password);
 // WiFi.config(ip);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
    
    if (!client) {
      return;
    }
    
    while(!client.available()){
      delay(1);
    }
    
  rest.handle(client);
  val=digitalRead(7);
  
  
    if(val==1){
      //Serial.println(val);
      lcd.setCursor(6,0);
      lcd.print("Scan");
      lcd.setCursor(4,1);
      lcd.print("Detected");
      val=0;
      delay(5000);
      }
   
  vall=digitalRead(13);
  
    if(vall==1){
       //Serial.println(val);
      lcd.setCursor(6,0);
      lcd.print("User");
      lcd.setCursor(4,1);
      lcd.print("Approved");
      val=0;
      delay(5000);
  
      }
      
  lcd.clear();
}

// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();

  digitalWrite(6,state);
  return 1;
}
