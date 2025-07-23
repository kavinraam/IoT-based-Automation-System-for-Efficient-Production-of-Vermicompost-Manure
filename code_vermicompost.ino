
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#include "ThingSpeak.h"

const char* ssid     = "";
const char* password = "";
unsigned long myChannelNumber = ;
const char * myWriteAPIKey = "";
// Set up a TCP server on port 8080
WiFiServer server(8080);
WiFiClient  client;
// Define the DHT sensor object
#define DHTPIN D3
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Define the input pins
const int inputPin1 = D2;
const int inputPin2 = D1;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the input pins
  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);
  ThingSpeak.begin(client);
}

void loop() {
  // Wait for a client to connect
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for data from the client
  Serial.println("New client");
  while(!client.available()){
    delay(1);
  }

  // Read the HTTP request from the client
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Construct the HTTP response
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int inputState1 = digitalRead(inputPin1);
  int inputState2 = digitalRead(inputPin2);
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: text/html\r\n\r\n";
  response += "<html><head>";
  response += "<style>body {background-color: lightblue;} h1 {color: white; text-align: center;} p {font-family: verdana; font-size: 20px; text-align: center;} .box {width: 50px; height: 50px; margin: 0 auto;}</style>";
  
  response += "</head><body>";
  response += "<h1>IOT BASED AUTOMATION SYSTEM FOR EFFIECIENT PRODUCTION OF VERMICOMPOST MANURE</h1>";
  Serial.println(inputState1);
  if (inputState1 == HIGH) {
    response += "<h1>GAS Status</h1>";
    response += "<p>HIGH</p>";
    response += "<div class=\"box\" style=\"background-color:red;\"></div>";
  } else {
    response += "<h1>Gas Status</h1>";
    response += "<p>LOW</p>";
    response += "<div class=\"box\" style=\"background-color:green;\"></div>";
  }
  
  if (inputState2 == HIGH) {
    response += "<h1>Moisture Status</h1>";
    response += "<p>HIGH</p>";
    response += "<div class=\"box\" style=\"background-color:red;\"></div>";
  } else {
    response += "<h1>Moisture Status</h1>";
    response += "<p>LOW</p>";
    response += "<div class=\"box\" style=\"background-color:green;\"></div>";
  }
  
  response += "<h1>DHT Sensor Readings</h1>";
  response += "<p>Temperature: ";
  response += String(temperature);
  response += "&deg;C</p>";
  response += "<p>Humidity: ";
  response += String(humidity);
  response += "%</p>";

  // Add some JavaScript code to refresh the page every 5 seconds
  response += "<script>setTimeout(function() { location.reload(); }, 5000);</script>";
  
  response += "</body></html>";
  
  // Send the HTTP response to the client
  client.print(response);
  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, inputState1);
  ThingSpeak.setField(4, inputState2);
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  //Serial.println(x);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(1);
  Serial.println("Client disonnected");

  // Wait for 1 second before taking another reading
  delay(4000);
}
