#include "robograb.hpp"
#include "databaseHandler.hpp"

#ifdef __APPLE__
#include "mac_sensor.hpp"
#else
#include "sensor.hpp"
#endif
#include <string>

 int mainTest(int argc, char *argv[]) {


  if (argc == 1 || !strcmp(argv[1],"updateSensor")) {

	//test values
 	const char* sensorID = "sensor1";
 	const int temperature = 23;
 	const int sunlight = 10;

    DatabaseHandler *databaseHandler_ = new DatabaseHandler();
    databaseHandler_->updateSensorValue(sensorID,temperature,sunlight);
  

  }
 else if(argc == 1 || !strcmp(argv[1],"updateRobotPosition")){

 	//test values
 	const char* nodePosition = "node23";
 	const char* robotID = "bluetoothID";

 	DatabaseHandler *databaseHandler_ = new DatabaseHandler();
    databaseHandler_->sendRobotPosition(4, 3,robotID);
 }

  else if(argc == 1 || !strcmp(argv[1],"updateRobotStatus")){

 	//test values
 	bool isAvailable = false;
 	const char* robotID = "bluetoothID";

 	DatabaseHandler *databaseHandler_ = new DatabaseHandler();
    databaseHandler_->updateRobotStatus(isAvailable,robotID);
 }
  


  else {
    printf("%s\n", "Please specifify a valid parameter");
  }


     return 0;
}
