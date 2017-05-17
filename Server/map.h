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
  virtual void print_nodename(void)=0;
};

class Crossroad: public Node {
 
public:

  Crossroad(int x0, int y0, Node * l, Node * r, Node * f, Node * b);
  void print_nodename(void);
  ~Crossroad();
};

class Shelf: public Node
{
 public:
  Shelf(int x0, int y0);
  void print_nodename(void);
  ~Shelf();
};
class Map
{
private:
  int size_x, size_y;
  
public:
  Node * root,* opposite;
  Map(int x0, int y0);
  void traverse_map();
  void traverse_map(int x, int y);
  void traverse_map_vertical(int x, int y);
  void traverse_map_inverse(int x, int y);
  virtual ~Map();
};



#endif /* MAP_H */
