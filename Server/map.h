#ifndef MAP_H
#define MAP_H
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
};

class Shelf: public Node
{
 public:
  Shelf(int x0, int y0, Node * l, Node * r, Node * f, Node * b);
  //Shelf(int x0, int y0);
  
  ~Shelf();
  void print_node_name();
  bool up_connected();
  bool down_connected();
  bool left_connected();
  bool right_connected();

};
class Map
{
private:
  int size_x, size_y;
  void traverse_map(int x, int y);
  void traverse_map_vertical(int x, int y);
  void traverse_map_inverse(int x, int y);
  
public:
  Node * root,* opposite;
  Map(int x0, int y0);

  virtual ~Map();


  void traverse_map();
  // inverse function makes it look like the layout in design documents
  void traverse_map_inverse();

  Node * get_node(int x, int y);
  
};



#endif /* MAP_H */
