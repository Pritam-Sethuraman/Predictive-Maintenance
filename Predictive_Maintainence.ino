#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

char JSONMessage[500] = {0};

// WiFi Details
const char *ssid = "uniconverge_2_4g"; // Enter your WiFi name
const char *password = "uct@12345";  // Enter WiFi password

// MQTT Broker Details
const char *mqtt_broker = "192.168.18.80";
const char *topic = "esp32/test";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Setup Funtion
void setup() {  
  Serial.begin(115200);
  while(!Serial) {
    delay(100);
  }  

  // Connecting to WiFi Network
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Successfully connected to WiFi!!!");

  // Connecting to MQTT Broker
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while(!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s is connected to the mqtt broker\n", client_id.c_str());
    if(client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("EMQX MQTT Broker Connected!!!");
    }
    else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Testing  MPU6050
  Serial.println("MPU6050 Sensor Testing");
  if(!mpu.begin()) {
    Serial.println("Failed to detect MPU6050");
    while(1) {
      delay(10);
    }
  }

  //Publish & Subscribe
  client.publish(topic, "Hi EMQX, I'm ESP32");
  client.subscribe(topic);

  Serial.println("MPU6050 Detected!");
  
  // Setting Accelerometer Range
  Serial.print("Accelerometer range set to: ");
  switch(mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+- 2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+- 4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+- 2G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+- 16G");
      break;
  }

  // Setting Gyro Range
  Serial.print("Accelerometer range set to: ");
  switch(mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  // Setting Filter Bandwidth
  Serial.print("Filter bandwidth set to: ");
  switch(mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println(" ");
  delay(100);
}

// Callback Function
void callback(char *topic, byte *payload, unsigned int length) {
  Serial.println("=================================================================================================================================");
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for(int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("=================================================================================================================================");
}

// Loop Function
void loop() {
  // Get new sensor events with the readings
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  StaticJsonBuffer<256> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  /*
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(t.temperature);
  Serial.println(" degC");
  */

  json["X_Accl"] = a.acceleration.x;
  json["Y_Accl"] = a.acceleration.y;
  json["Z_Accl"] = a.acceleration.z;

  json["X_Gyro"] = g.gyro.x;
  json["Y_Gyro"] = g.gyro.y;
  json["Z_Gyro"] = g.gyro.z;
  
  json["Temperature"] = t.temperature;
  
  json.printTo(JSONMessage, sizeof(JSONMessage));

  client.publish(topic, JSONMessage);

  //Serial.println("-------------------------------------------");
  //Serial.println(JSONMessage);
  //Serial.println("-------------------------------------------");
  
  client.loop();
  delay(5000);
}
