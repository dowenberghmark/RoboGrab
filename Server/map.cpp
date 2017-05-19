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
bool Crossroad::up_connected(){
  return (this->up != NULL);
}
bool Crossroad::down_connected(){
  return (this->down != NULL);
}
bool Crossroad::left_connected(){
    Node* p = new Crossroad(1,1,NULL,NULL,NULL,NULL);
  return (this->left != NULL && typeid(*p) == typeid(*(this->left))  );
}
bool Crossroad::right_connected(){
  Node* p = new Crossroad(1,1,NULL,NULL,NULL,NULL);
  return (this->right != NULL && typeid(*p) == typeid(*(this->right)));
}


std::string Crossroad::get_node_type() {
  return "Crossroad";
}

Crossroad::~Crossroad(){}

Shelf::Shelf(int x0, int y0, Node * l, Node * r, Node * f, Node * b):Node(x0, y0, l, r, f, b){}

void Shelf::print_node_name(){
  printf("Shelf");

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
          else
            tmp = new Shelf(j,i, previous_pos,NULL,NULL,NULL);
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
