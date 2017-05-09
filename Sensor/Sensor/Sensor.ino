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
    
   /*
   while(1){
     if(blueToothSerial.available()){//check if there's any data sent from the remote bluetooth shield
         recvChar = blueToothSerial.read();
         Serial.print(recvChar); // Print the character received to the Serial Monitor (if required)
         
         //If the character received = 'r' , then change the RGB led to display a RED colour
         if(recvChar=='r'){
           Send32Zero(); // begin
           //DataDealWithAndSend(255, 0, 0); // first node data
           temp= dht.readTemperature();
           DatSend((uint32)temp);
           Send32Zero(); // send to update data 
         }
       

       }
       
       //You can use the following code to deal with any information coming from the Computer (serial monitor)
       if(Serial.available()){
       recvChar = Serial.read();
       
       //This will send value obtained (recvChar) to the phone. The value will be displayed on the phone.
       blueToothSerial.print(recvChar);
     }
   }*/
}
/*

//The following code is necessary to setup the bluetooth shield ------copy and paste----------------
void setupBlueToothConnection()
{
 blueToothSerial.begin(38400); //Set BluetoothBee BaudRate to default baud rate 38400
 blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
 blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n"); //set the bluetooth name as "SeeedBTSlave"
 blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
 blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
 delay(2000); // This delay is required.
 blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
 Serial.println("The slave bluetooth is inquirable!");
 delay(2000); // This delay is required.
 blueToothSerial.flush();
}


//The following code snippets are used update the colour of the RGB LED-----copy and paste------------
void ClkProduce(void){
 digitalWrite(Clkpin, LOW);
 delayMicroseconds(20); 
 digitalWrite(Clkpin, HIGH);
 delayMicroseconds(20); 
}
 
void Send32Zero(void){
 unsigned char i;
 for (i=0; i<32; i++){
 digitalWrite(Datapin, LOW);
 ClkProduce();
 }
}
 
uint8 TakeAntiCode(uint8 dat){
 uint8 tmp = 0;
 if ((dat & 0x80) == 0){
 tmp |= 0x02; 
 }
 
 if ((dat & 0x40) == 0){
 tmp |= 0x01; 
 }
 
 return tmp;
}
 
// gray data
void DatSend(uint32 dx){
 uint8 i;
 for (i=0; i<32; i++){
 if ((dx & 0x80000000) != 0){
 digitalWrite(Datapin, HIGH);
 } else {
 digitalWrite(Datapin, LOW);
 }
 
 dx <<= 1;
 ClkProduce();
 }
}



// data processing
void DataDealWithAndSend(uint8 r, uint8 g, uint8 b){
 uint32 dx = 0;
 
 dx |= (uint32)0x03 << 30; // highest two bits 1，flag bits
 dx |= (uint32)TakeAntiCode(b) << 28;
 dx |= (uint32)TakeAntiCode(g) << 26; 
 dx |= (uint32)TakeAntiCode(r) << 24;
 
 dx |= (uint32)b << 16;
 dx |= (uint32)g << 8;
 dx |= r;
 
 DatSend(dx);
}*/



