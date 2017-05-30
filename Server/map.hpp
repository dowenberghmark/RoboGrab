#ifndef MAP_H
#define MAP_H
#include <string.h>
#include <string>
#include <vector>
#include "main.hpp"


class Node{
protected:
  int x, y;  
  
public:
  Node  *left,* right,* up, *down;
  Node(int x0, int y0, Node * l , Node * r , Node * f, Node * b);
  
  virtual ~Node();
  void print_coordinate();
  virtual void print_node_name()=0;
  virtual bool up_connected()=0;
  virtual bool down_connected()=0;
  virtual bool left_connected()=0;
  virtual bool right_connected()=0;
  Node * parent;
  int getX();
  int getY();
  virtual std::string get_node_type()=0;
};

class Crossroad: public Node {
 
public:

  Crossroad(int x0, int y0, Node * l, Node * r, Node * f, Node * b);
  
  ~Crossroad();
  void print_node_name();
  bool up_connected();
  bool down_connected();
  bool left_connected();
  bool right_connected();
  std::string get_node_type();
  
};

class Shelf: public Node
{
 public:
  Shelf(int x0, int y0, Node * l, Node * r, Node * f, Node * b);
  //Shelf(int x0, int y0);
  struct sensor_data  sensor_values;
  
  ~Shelf();
  void print_node_name();
  bool up_connected();
  bool down_connected();
  bool left_connected();
  bool right_connected();
  std::string get_node_type();
};
class Map
{
private:
  int size_x, size_y, amount_shelves;
  
  std::vector<Shelf *> shelf;
  void init_shelf_vector();
  
  
public:
  
  Node * root,* opposite;
  Map(int x0, int y0);
  void traverse_map();
  std::vector<Shelf *> shelves_list;

 std::string path(Node * start, Node * end);
  
  // inverse function makes it look like the layout in design documents
  void traverse_map_inverse();
  void traverse_map(int x, int y);
  void traverse_map_vertical(int x, int y);
  void traverse_map_inverse(int x, int y);
  void  traverse_set_null_parent();
  
  int getX(){return this->size_x;};
  int getY(){return this->size_y;};
  int get_amount_shelves(){return this->amount_shelves;};

  std::vector<Shelf *>* getShelfNodes();
  std::vector<Node* > getMapNodes();
  Node * get_node(int x, int y);
  bool up_connected();
  bool down_connected();
  bool left_connected();
  bool right_connected();
  virtual ~Map();
};



#endif /* MAP_H */
