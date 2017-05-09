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


int Clkpin = 9; //RGB LED Clock Pin (Digital 9)
int Datapin = 8; //RGB LED Data Pin (Digital 8)

SoftwareSerial blueToothSerial(RxD,TxD);

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
char recvChar[4];
int counter;
void setup()
{
  Serial.begin(9600);
  dht.begin();

 pinMode(RxD, INPUT); // Setup the Arduino to receive INPUT from the bluetooth shield on Digital Pin 6
 pinMode(TxD, OUTPUT); // Setup the Arduino to send data (OUTPUT) to the bluetooth shield on Digital Pin 7
 pinMode(13,OUTPUT); // Use onboard LED if required.
 //setupBlueToothConnection(); //Used to initialise the Bluetooth shield
 
 pinMode(Datapin, OUTPUT); // Setup the RGB LED Data Pin
 pinMode(Clkpin, OUTPUT); // Setup the RGB LED Clock pin

}

void loop()
{
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    counter = Serial.available();
    //Print temp and humidity values to serial monitor
 /*   while( counter > 0){
      if(counter > 4){
        Serial.print("Too big message");
        counter = 0;
      }else{
      recvChar[4-counter] = (char)Serial.read();
      
      
      counter--;
      }
    
    }*/
    delay(2000); //Delay 2 sec.
 // if(recvChar == "read"){
    Serial.print("Humidity: ");
      Serial.print(hum);
      Serial.print(" %, Temp: ");
      Serial.print(temp);
      Serial.println(" Celsius");
      int i = 0;
      /*while( i < 4 ){
        recvChar[i] = 'p';
        i++;
      }*/
    
 // }
   //Serial.print(recvChar);
    

}




