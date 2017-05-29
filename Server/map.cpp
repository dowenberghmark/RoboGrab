#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "map.hpp"
#include <iostream>
#include <typeinfo>
#include <vector>
using namespace std;

Node::Node(int x0, int y0, Node * l = NULL, Node * r = NULL, Node* f = NULL, Node * b = NULL){
  left = l;
  right = r;
  up = f;
  down = b;
  x = x0;
  y = y0;
}
void Node::print_coordinate(){
  printf("(%d, %d) ",x,y);
}



Node::~Node(){}

int Node::getX(){
  return x;
}

int Node::getY(){
  return y;
}


Crossroad::Crossroad(int x0, int y0, Node * l, Node * r, Node * f, Node * b):Node(x0, y0, l, r, f, b){}


void Crossroad::print_node_name(){
  std::cout << ( "Crossroad");

}
//may have fucked it up..
bool Crossroad::up_connected(){
  return (this->up != NULL && this->right != NULL  );
}
bool Crossroad::down_connected(){
  return (this->down != NULL && this->left!= NULL );
}
bool Crossroad::left_connected(){
    Node* p = new Crossroad(1,1,NULL,NULL,NULL,NULL);
    return (this->left != NULL && typeid(*p) == typeid(*(this->left))  && (this-> right != NULL || this->getY() == 0));
}
bool Crossroad::right_connected(){
  Node* p = new Crossroad(1,1,NULL,NULL,NULL,NULL);
  return (this->right != NULL && typeid(*p) == typeid(*(this->right)));
}


std::string Crossroad::get_node_type() {
  return "Crossroad";
}

Crossroad::~Crossroad(){}

Shelf::Shelf(int x0, int y0, Node * l, Node * r, Node * f, Node * b):Node(x0, y0, l, r, f, b){
  struct sensor_data tmp;
  tmp.temp = 0.0;
  tmp.humidity = -2.0;
  sensor_values = tmp;
}

void Shelf::print_node_name(){
  printf("t:%.2f,h:%.2f", sensor_values.temp, sensor_values.humidity);

}

std::string Shelf::get_node_type() {
  return "Shelf";
}

Shelf::~Shelf(){}


bool Shelf::up_connected(){
  return (this->y % 3 == 2);
}
bool Shelf::down_connected(){
  return (this->y % 3 == 1);
}
bool Shelf::left_connected(){
  return false;
}
bool Shelf::right_connected(){
  return false;
}






Map::Map(int x0, int y0){
  
  size_x = x0;
  size_y = y0;
  amount_shelves = 0;
  root = NULL;
  Node *previous_row, * up_row, *previous_pos;

  for (int i = 0; i < size_y; i++) {

    for (int j = 0; j < size_x; j++) {
      if ( i % 1 == 0 ){
        Node *tmp ;
        //special case for root
        if (j ==0 && i == 0) {
          tmp = new Crossroad(j, i,NULL,NULL,NULL,NULL );
          root = tmp;

          up_row = root;
          previous_row = root;
        }
        //Creating link up vertical in the graph
        else if (j == 0) {
          tmp  = new Crossroad(j, i,NULL,NULL,NULL,up_row );
          previous_row = up_row;
          up_row->up = tmp;
          up_row = tmp;
        }
        //Creating link right horizontal and with the previous row up&down in the graph
        else {
          if (i %3 == 0 || j == size_x-1){
            tmp = new Crossroad(j, i, previous_pos,NULL,NULL,NULL );

          }
          else{
            amount_shelves++;
            tmp = new Shelf(j,i, previous_pos,NULL,NULL,NULL);
          }
          previous_pos->right = tmp;
          if (i > 0) {
             previous_row = previous_row->right;
             tmp->down = previous_row;
             previous_row->up = tmp;

          }
        }

        previous_pos = tmp;
        opposite = tmp;
      }
    }


  }
  init_shelf_vector();
}

void Map::traverse_map(){
  Node *conductor = root;
  Node *row_up = root->up;
  while (conductor !=NULL ) {
    conductor->print_node_name();
    conductor->print_coordinate();

    conductor = conductor->right;
    if (conductor == NULL && row_up !=NULL){
      conductor = row_up;
      row_up = conductor->up;
      printf("\n");
    }

  }
   printf("\n");
}


void Map::traverse_set_null_parent(){
  Node *conductor = root;
  Node *row_up = root->up;
  while (conductor !=NULL ) {
    conductor->parent = NULL;
    

    conductor = conductor->right;
    if (conductor == NULL && row_up !=NULL){
      conductor = row_up;
      row_up = conductor->up;
    }
  }
}
std::vector<Node*> Map::getMapNodes(){
  std::vector<Node*> out_v;
  Node *conductor = root;
  Node *row_up = root->up;
  while (conductor !=NULL ) {
    out_v.push_back(conductor);

    conductor = conductor->right;
    if (conductor == NULL && row_up !=NULL){
      conductor = row_up;
      row_up = conductor->up;
    }

  }
  return out_v;
}
std::vector<Shelf *>* Map::getShelfNodes(){
  return &this->shelf;
}
void Map::init_shelf_vector(){
  Node *conductor = root;
  Node *row_up = root->up;
  while (conductor !=NULL ) {
    if (conductor->get_node_type() == "Shelf") {
      this->shelf.push_back((Shelf *)conductor);
    }
    

    conductor = conductor->right;
    if (conductor == NULL && row_up !=NULL){
      conductor = row_up;
      row_up = conductor->up;
    }

  }
  
}

void Map::traverse_map_inverse(){

  Node *conductor = opposite;

  while (conductor->left != NULL)
    conductor = conductor->left;


  Node *row_up = conductor->down;  
  while (conductor !=NULL ) {
    conductor->print_node_name();
    conductor->print_coordinate();

    conductor = conductor->right;
    if (conductor == NULL && row_up !=NULL){
      conductor = row_up;
      row_up = conductor->down;
      printf("\n");
    }

  }
   printf("\n");
}


void Map::traverse_map(int x, int y){
  if(x <= size_x && y <= size_y ){
    Node * conductor = root;
    for (int i = 0; i < x-1; i++) {
      conductor = conductor->right;
    }
    for (int j = 0; j < y-1; j++) {
      conductor = conductor->up;
    }
    conductor->print_coordinate();
  }
}
void Map::traverse_map_vertical(int x, int y){
  if(x <= size_x && y <= size_y ){
    Node * conductor = root;
    for (int j = 0; j < y-1; j++) {
      conductor = conductor->up;
    }
    for (int i = 0; i < x-1; i++) {
      conductor = conductor->right;
    }

    conductor->print_coordinate();
  }
}
void Map::traverse_map_inverse(int x, int y){
  if(x <= size_x && y <= size_y ){
    Node * conductor = opposite;
    for (int j = 0; j < y-1; j++) {
      conductor = conductor->down;
    }
    for (int i = 0; i < x-1; i++) {
      conductor = conductor->left;
    }

    conductor->print_coordinate();
  }
}

Node * Map::get_node(int x,int y){
  Node * conductor = NULL;
  if(x <= size_x && y <= size_y ){
    conductor = root;
    for (int j = 0; j < y; j++) {
      conductor = conductor->up;
    }
    for (int i = 0; i < x; i++) {
      conductor = conductor->right;
    }
  
   
  }
    return conductor;
}


std::vector<std::string>  Map::path(Node * start, Node * end){
  std::vector<std::string> path_list;
  std::vector<std::string> reversed_path_list;
  std::vector<Node * > visited;
  std::vector<Node * > queue;
  visited.push_back(start);
  queue.push_back(start);
  
  bool check = false;
 
  Node * tmp;
  end->parent = NULL;

  while (!queue.empty()) {


        
    tmp = queue.at(0);
    queue.erase(queue.begin(),queue.begin()+1);

    if (tmp->getX() == end->getX() && tmp->getY() == end->getY()) {
      queue.erase(queue.begin(),queue.end());
    }else{
      if (tmp->up_connected()){
        
        check = true;
        for(auto k : visited  ){
          if (k == tmp->up)
            check = false;
        }
        if (check) {
          queue.push_back(tmp->up);
          visited.push_back(tmp->up);
          (tmp->up)->parent = tmp;
        }
      }
      if (tmp->down_connected()){
        check = true;
        
        for(auto k : visited  ){
          if (k == tmp->down)
            check = false;
        }
        if (check) {
          queue.push_back(tmp->down);
          visited.push_back(tmp->down);
          (tmp->down)->parent = tmp;
        }
      }if (tmp->right_connected()){
        check = true;
        
        for(auto k : visited  ){
          if (k == tmp->right)
            check = false;
          
        }
        if (check) {
          queue.push_back(tmp->right);
          visited.push_back(tmp->right);
          (tmp->right)->parent = tmp;
        }
      }if (tmp->left_connected()){
        
        check = true;

        for(auto k : visited  ){
          if (k == tmp->left)
            check = false;
        }
        if (check) {
          queue.push_back(tmp->left);
          visited.push_back(tmp->left);
          (tmp->left)->parent = tmp;
        }
      }
      
      
    }
    // ++i;
  }
  
  
  while(tmp->parent !=NULL){
    
    if( tmp->parent->up == tmp)
      reversed_path_list.push_back("up");
    else if( tmp->parent->down == tmp)
      reversed_path_list.push_back("down");
    else if( tmp->parent->left == tmp)
      reversed_path_list.push_back("left");
    else if( tmp->parent->right == tmp)
      reversed_path_list.push_back("right");
    tmp = tmp->parent;
  }

   for (int p = reversed_path_list.size()-1; p >=0 ; p--) {
     path_list.push_back(reversed_path_list.at(p));
   }
   this->traverse_set_null_parent();
  return path_list;
}




Map::~Map(){

  Node * tmp;
  Node *conductor = root;
  Node *row_up = root->up;

  while (conductor !=NULL) {
    tmp = conductor->right;
    free(conductor);
    conductor = tmp;
    if (conductor == NULL && row_up !=NULL){

      conductor = row_up;
      row_up = conductor->up;
    }
  }

}
