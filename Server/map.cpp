#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "map.h"

// TODO: Add exceptions / safeguards for traverse.


int main(int argc, char *argv[])
{
  Map a = Map(7,7);


  a.traverse_map();
  printf("%s\n", "");
  a.traverse_map(4,4);
  a.traverse_map_vertical(4,4);
  a.traverse_map_inverse(4,4);
  printf("%s\n","" );
// TODO: Fix print_nodename() works as supposed without the keyword virtual.
  a.root->print_nodename();
  return 0;
}

Node::Node(int x0, int y0, Node * l = NULL, Node * r = NULL, Node* f = NULL, Node * b = NULL){
  left = l;
  right = r;
  up = f;
  down = b;
  x = x0;
  y = y0;
}
void Node::print_coordinate(){
  printf("(%d, %d) \t",x,y);
}

void Node::print_nodename(void){
 printf("%s\t", "Node");
}
Node::~Node(){}


Crossroad::Crossroad(int x0, int y0, Node * l, Node * r, Node * f, Node * b):Node(x0, y0, l, r, f, b){}


void Crossroad::print_nodename (void){
 printf("%s\t", "Crossroad");
}

Crossroad::~Crossroad(){}

Shelf::Shelf(int x0, int y0):Node(x0, y0){}

void Shelf::print_nodename(void){
  printf("%s\t", "Shelf");
}

Shelf::~Shelf(){}


Map::Map(int x0, int y0){
  size_x = x0;
  size_y = y0;
  //root = (Node *) malloc(sizeof(Node) * (size_x * size_y));
  Node *previous_row, * up_row, *previous_pos; 
  
  for (int i = 0; i < size_y; i++) {
    
    for (int j = 0; j < size_x; j++) {
      if ( i % 1 == 0 ){ // should be  i % 3 == 0 
        Node *tmp = (Node*)malloc(sizeof(Crossroad));
        //special case for root
        if (j ==0 && i == 0) {
      
          root = tmp;
          *root = Crossroad(j, i,NULL,NULL,NULL,NULL );
          up_row = root;
          previous_row = root;
        }
        //Creating link up vertical in the graph
        else if (j == 0) {
          *tmp  = Crossroad(j, i,NULL,NULL,NULL,up_row );
          previous_row = up_row;
          up_row->up = tmp;
          up_row = tmp;
        }
        //Creating link right horizontal and with the previous row up&down in the graph
        else {
          *tmp = Crossroad(j, i, previous_pos,NULL,NULL,NULL );
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
  int counter = 0;
  Node *conductor = root;
  Node *row_up = root->up;  
  while (conductor !=NULL ) {
    
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
void Map::traverse_map(int x, int y){
  Node * conductor = root;
  for (int i = 0; i < x-1; i++) {
    conductor = conductor->right;
  }
  for (int j = 0; j < y-1; j++) {
    conductor = conductor->up;
  }
  conductor->print_coordinate();
}
void Map::traverse_map_vertical(int x, int y){
  Node * conductor = root;
  for (int j = 0; j < y-1; j++) {
    conductor = conductor->up;
  }
  for (int i = 0; i < x-1; i++) {
    conductor = conductor->right;
  }
  
  conductor->print_coordinate();
}
void Map::traverse_map_inverse(int x, int y){
  Node * conductor = opposite;
  for (int j = 0; j < y-1; j++) {
    conductor = conductor->down;
  }
  for (int i = 0; i < x-1; i++) {
    conductor = conductor->left;
  }
  
  conductor->print_coordinate();
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
