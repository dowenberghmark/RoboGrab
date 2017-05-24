//Libraries
#include <DHT.h>
#include <SoftwareSerial.h>

//Constants
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define uint8 unsigned char
#define uint16 unsigned int
#define uint32 unsigned long int

#define RxD 0 // This is the pin that the Bluetooth (BT_TX) will transmit to the Arduino (RxD)
#define TxD 1 // This is the pin that the Bluetooth (BT_RX) will receive from the Arduino (TxD)
 
#define DEBUG_ENABLED 1



SoftwareSerial blueToothSerial(RxD,TxD);

//Variables
int chk;
float hum;  //Stores humidity value
float oldHum;
float temp; //Stores temperature value
float oldTemp;
String recvChar;
int counter;
String sending_string;
int tester;
void setup()
{
  Serial.begin(9600);
  dht.begin();
  tester = 0;
 pinMode(RxD, INPUT); // Setup the Arduino to receive INPUT from the bluetooth shield on Digital Pin 6
 pinMode(TxD, OUTPUT); // Setup the Arduino to send data (OUTPUT) to the bluetooth shield on Digital Pin 7
// pinMode(13,OUTPUT); // Use onboard LED if required.
  blueToothSerial.begin(38400);
  //blueToothSerial.write("AT+NAME=ARDTEAM2");
}

void loop()
{

    /*   // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (blueToothSerial.available())
    Serial.write(blueToothSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available()){
    blueToothSerial.write(Serial.read());
    Serial.print("yay");
  }*/
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    counter = Serial.available();
    //Print temp and humidity values to serial monitor
    if( counter > 0){
      
      recvChar = Serial.readStringUntil('!');
      
      //Serial.print("Command: ");
      //Serial.println(recvChar);
      
      //}
      
      if (recvChar == "rt"){
        Serial.print(String(temp) +"          "+ '\n');
        //delay(200);
        counter -= 3;
      }
      if (recvChar == "rh"){
        Serial.print(String(hum) + "          "+ '\n'); 
      //  delay(200);
        counter -=3;
      }
      
    }
   recvChar = ""; 
  if (oldHum != hum || oldTemp != temp ){
    sending_string = "t " + String(temp) + " h " + String(hum) + "\n";
    delay(5000);
    Serial.print(sending_string);
    oldHum = hum;
    oldTemp = temp;
  }
}




