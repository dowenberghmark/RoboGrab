#include "sensortomap.hpp"
#include <chrono>
#include <cassert>
//void one_sensor();
// TODO: Fix a module calculation to map every shelf
SensorToMap::SensorToMap(int number_sensors, Map * map){
  this->sensormap = map;
  this->amount_shelves = map->get_amount_shelves();
  this->x = map->getX() - 2;
  this->y = (map->getY() - 1) / 3 * 2;
  this->number_sensor = number_sensors;
  //assert(this->amount_shelves == (this->x * this->y) );
  //may have problem with rest in integer division.... and i'm counting wrong by 2 division and need some jumping be th shelfs..........
  x_part = this->x / number_sensor;
  y_part = this->y/2 * 3;// / number_sensor;
  
  int start = BLUETOOTH_MAC.size();

  our_thread = new std::thread[number_sensor];
  sensor_list = new std::vector<Sensor*>[number_sensor];
 
  for (uint i = 0; i < BLUETOOTH_MAC.size()   ; i++) {
    
    const char * mac_tmp;
    mac_tmp = (BLUETOOTH_MAC.at(i)).c_str();
    our_thread[i] = this->init(mac_tmp, i);
        
  }
  
  for (int i = start; i < number_sensor ; i++) {
  
    const char * mac_tmp;
    mac_tmp = NULL;
    our_thread[i] = this->init(mac_tmp, i);
        
  }
  
  for (int i = 0; i < this->number_sensor; i++) {
    our_thread[i].join();
    //our_thread[i].detach();
  }
  //std::this_thread::sleep_for(std::chrono::seconds(15));
}
std::thread  SensorToMap::init(const char * mac, uint id){
  
  return std::thread([=] {one_sensor(mac,id);});
}

SensorToMap::~SensorToMap(){
  for (int i = 0; i < this->number_sensor; i++) {
    //our_thread[i].join();
  }

  
}

// void SensorToMap::one_sensor(const char * mac){
  
//   Sensor * sensor;
//   if (mac == NULL) {
//     sensor = new Sensor();
//   }else{
//     sensor = new Sensor((char*)mac);
//   }
//   int counter = 0;
//   sensor_list->push_back(sensor);
//   for (uint i = (id * this->x_part) + 1; i < ((id + 1) * this->x_part)  + 1; i++) {
//     for (int j =  1; j <  this->y_part ; j++) {
//       if (j % 3 == 0) {
//         j++;
//       }
  
//       Shelf * node = (Shelf *)sensormap->get_node(i,j);
//       node->sensor_values.temp = sensor->get_temp();
//       node->sensor_values.humidity = sensor->get_humidity();
//       counter++;
//     }
//   }
  

// }
void SensorToMap::one_sensor(const char * mac, uint id){
  Sensor * sensor;
  if (mac == NULL) {
    sensor = new Sensor((int)id);
  }else{
    sensor = new Sensor((char*)mac,(int) id);
  }
  
  sensor_list->push_back(sensor);
  
  shelf = sensormap->getShelfNodes();
  update_values();
  
}
/*
  &&
          sensor->id * this->y_part <= node->getY() &&
          (sensor->id + 1) * this->y_part > node->getY()

*/
void SensorToMap::update_values(){
  for (sensor : *sensor_list){
    sensor->loop();
   
    for (node : *shelf){
      if ((sensor->id * this->x_part) <= node->getX() &&
          ((sensor->id + 1) * this->x_part) >= node->getX()) {
        
        node->sensor_values.temp = sensor->get_temp();
        node->sensor_values.humidity = sensor->get_humidity();   
      }
          
    }
  }
}

void SensorToMap::remove_connection(){
  for (int i ; i < this->number_sensor; i++) {
    sensor_list->at(i)->~Sensor();
  }

}
