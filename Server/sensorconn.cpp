#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <string.h>

struct sensor_data
{
  float temp, humidity;
};

class Sensor{

 public:
  //void connect();
  Sensor(char * bluetooth_mac);
  ~Sensor(void);
  float get_temp();
  float get_humidity();
  void exit_loop();
 private:
  float get_sensor_temp();
  float get_sensor_humidity();
  
  void loop();
  float command(char * command);
  struct sensor_data current_vals;
  
  struct sockaddr_rc addr;
  char sensor_mac[18];// = "30:14:12:12:13:29";
  const int buffer_size = 16;
  char *buffer;
  int sock, status;
  bool loop_control;
  
  
  
};

//Constructor
Sensor::Sensor(char * bluetooth_mac){
  printf("%s\n","Setting up connection" );
  
  buffer = (char *)malloc(sizeof(char)*buffer_size);
  strncpy(sensor_mac, bluetooth_mac, 18);

  // allocate a socket
  if ((sock = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM)) < 0){
    printf("Socket failure code: %d\n", sock);
    exit(EXIT_FAILURE);
  }
  // set the connection parameters (who to connect to)
  addr.rc_family = AF_BLUETOOTH;
  addr.rc_channel = (uint8_t) 1;
  str2ba( sensor_mac, &addr.rc_bdaddr );

  loop_control = true;
  
  if ((status = connect(sock, (struct sockaddr *)&addr, sizeof(addr))) < 0){
    printf("connect failure code:%d\n", status );
    perror("Error");
    exit(EXIT_FAILURE);
  }
  
  //this->current_vals.temp = this->get_sensor_temp();
  
  //this->current_vals.humidity = this->get_sensor_humidity();
  printf("%s\n","Finished init connection" );
  //this->loop();
}

Sensor::~Sensor(void){
  free(buffer);
  close(sock);
  printf("%s\n", "cleaned");
}

void Sensor::exit_loop(){
  this->loop_control = false;
}


float Sensor::get_temp(){
  return this->current_vals.temp;
}
    

float Sensor::get_humidity(){
  return this->current_vals.humidity;
}


float Sensor::command(char* command){
  
  strcpy(buffer, command);
  send(this->sock,buffer, buffer_size, 0);
  //sleep(1);
  recv(this->sock,buffer, buffer_size, MSG_WAITALL);
  
  return strtof(buffer, NULL);
}

float Sensor::get_sensor_temp(){
  char  tmp[] = "rt!";
  
  return (this->current_vals.temp = this->command(tmp));
}

float Sensor::get_sensor_humidity(){
  char tmp[] =  "rh!";
  return (this->current_vals.humidity = this->command(tmp));
}

void Sensor::loop(){
  // send a message
  if( this->status == 0 ) {
    
    char received[buffer_size];
    char received1[buffer_size];
    float tmpTemp = 0;
    float tmpHum = 0;
    while(this->loop_control){
      //printf("%s\n", "In loop" );
      recv(sock, buffer,buffer_size,MSG_WAITALL);
      sscanf(buffer, "%s %f %s %f", received, &tmpTemp, received1, &tmpHum);
      //      printf("After recv data, with buffer: %s\n", buffer);
      if (tmpTemp != this->current_vals.temp) {
        this->current_vals.temp = tmpTemp;
        printf("Temp: %f Humidity: %f \n", current_vals.temp, current_vals.humidity );
      }
      
      if (tmpHum != this->current_vals.humidity) {
        this->current_vals.humidity = tmpHum;
        printf("Temp: %f Humidity: %f \n", current_vals.temp, current_vals.humidity );
      }
      
      
    }
  }
  
  if( status < 0 ){
    perror("uh oh");
    
  }

}



class BluetoothScanner
{
 public:
  BluetoothScanner(void);
  virtual ~BluetoothScanner(void);
 private:
  void scan();
  inquiry_info *ii = NULL;
  int max_rsp, num_rsp;
  int dev_id, sock, len, flags;
  int i;
  char addr[19] = { 0 };
  char name[248] = { 0 };
  
  
};
BluetoothScanner::BluetoothScanner(void){
  dev_id = hci_get_route(NULL);
  sock = hci_open_dev( dev_id );

  if (dev_id < 0 || sock < 0) {
    perror("opening socket");
    exit(1);
  }
  len = 8;
  max_rsp = 255;
  flags = IREQ_CACHE_FLUSH;
  this->scan();
}
BluetoothScanner::~BluetoothScanner(void){
  free( ii );
  close(sock);
}

void BluetoothScanner::scan(){
  ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
  num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
  if( num_rsp < 0 ) perror("hci_inquiry");
  for (i = 0; i < num_rsp; i++) {
    ba2str(&(ii+i)->bdaddr, addr);
    memset(name, 0, sizeof(name));
    if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
                             name, 0) < 0)
      strcpy(name, "[unknown]");
    printf("%s %s\n", addr, name);
  }
 
}

int main(int argc, char **argv)
{

  // TODO: Clean up with a nicer commands
  if (argc > 1){
    BluetoothScanner ss;
  }
  if (argc > 0) {
    char * mac = (char*)malloc(19);
    strcpy(mac, "30:14:12:12:13:29"); 
    Sensor sensor(mac);
    strcpy(mac, "20:14:12:12:03:32"); 
    Sensor sensor2(mac);

    for (int i = 0; i < 5; i++) {
      printf("Sensor 1 Temp: %f  Sensor 2 Temp: %f", sensor.get_temp(), sensor2.get_temp());
      
    }
   
    free(mac);
  }
  
  return 0;
}
