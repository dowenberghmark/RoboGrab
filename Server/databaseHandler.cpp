#include "databaseHandler.hpp"
#include "map.hpp"
#include <vector>


DatabaseHandler::DatabaseHandler() {

}

DatabaseHandler::~DatabaseHandler() {

}

void DatabaseHandler::createJSONfromMap(Map * inMap) {

    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{}};
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
