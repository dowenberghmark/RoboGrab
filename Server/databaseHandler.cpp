#include "databaseHandler.hpp"
//#include <vector>


DatabaseHandler::DatabaseHandler() {

}

DatabaseHandler::~DatabaseHandler() {

}

void DatabaseHandler::createJSONfromMap(Map * inMap) {
    //only once
    mongocxx::instance inst{};
    //connect to a server running on localhost on port 27017
    //this should be changed to mongocxx::uri uri("mongodb://xxx.xxx.xxx.xxx:27017");
    mongocxx::client conn{mongocxx::uri{}};

    //choose database & collection to access
    mongocxx::database db = conn["warehouseSWE"];
    auto collection = db["map"];

    bsoncxx::builder::basic::document document{};

    std::vector<Node*> node_list = inMap->getMapNodes();

    collection.delete_one(bsoncxx::builder::stream::document{} << "mapName" << "Uppsala Warehouse" << finalize);

    int nodeID = 0;
    document.append(kvp("mapName","Uppsala Warehouse"));
    document.append(kvp("nodes", [&nodeID,&node_list](sub_array nodes) {
        for (std::vector<Node*>::iterator it = node_list.begin() ; it != node_list.end(); ++it) {
            nodes.append("node"+std::to_string(nodeID),[&it](sub_document node){
                node.append(kvp("x",(*it)->getX()));
                node.append(kvp("y",(*it)->getY()));
                node.append(kvp("type",(*it)->get_node_type()));
                node.append(kvp("neighbors",[&it](sub_array neighbors){
                    if((*it)->left)
                        neighbors.append("left");
                    if((*it)->up)
                        neighbors.append("up");
                    if((*it)->right)
                    neighbors.append("right");
                    if((*it)->down)
                    neighbors.append("down");
                }));
            });
            nodeID++;
        }
    }));


    collection.insert_one(document.view());
    auto cursor = collection.find({});

    //Print out document to confirm success
    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;
    }
}


void DatabaseHandler::updateSensorValue(const char* sensorID, int temp, int sun){
    //only once
    mongocxx::instance inst{};
    //connect to a server running on localhost on port 27017
    //this should be changed to mongocxx::uri uri("mongodb://xxx.xxx.xx.xxx:27017");
    mongocxx::client conn{mongocxx::uri{}};

    //choose database & collection to access
    mongocxx::database db = conn["warehouseSWE"];
    auto collection = db["sensors"];

    const char* id = sensorID;


    collection.update_one(
        document{} << "_id" << sensorID << finalize,
        document{} << "$set" << open_document <<
        "sunlight" << sun << close_document << finalize);

    collection.update_one(document{} << "_id" << sensorID << finalize,
        document{} << "$set" << open_document <<
        "temperature" << temp << close_document << finalize);
}

void DatabaseHandler::sendRobotPosition(const char* nodePosition, const char* robotID){
    //only once
     mongocxx::instance inst{};
    //connect to a server running on localhost on port 27017
    //this should be changed to mongocxx::uri uri("mongodb://xxx.xxx.xx.xxx:27017");
    mongocxx::client conn{mongocxx::uri{}};

    //choose database & collection to access
    mongocxx::database db = conn["warehouseSWE"];
    auto collection = db["robots"];

    collection.update_one(
        document{} << "_id" << robotID << finalize,
        document{} << "$set" << open_document <<
        "position" << nodePosition << close_document << finalize);
}

void DatabaseHandler::updateRobotStatus(bool isAvailable, const char* robotID){
        //only once
     mongocxx::instance inst{};
    //connect to a server running on localhost on port 27017
    //this should be changed to mongocxx::uri uri("mongodb://xxx.xxx.xx.xxx:27017");
    mongocxx::client conn{mongocxx::uri{}};

    //choose database & collection to access
    mongocxx::database db = conn["warehouseSWE"];
    auto collection = db["robots"];

    collection.update_one(
        document{} << "_id" << robotID << finalize,
        document{} << "$set" << open_document <<
        "available" << isAvailable << close_document << finalize);
}
