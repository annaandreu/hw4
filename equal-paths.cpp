#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
bool check_depth(Node * current_node, int current_depth, int &first_leaf_depth)
{
    if(current_node == nullptr){ // BC empty tree 
        return true; 
    }

    // if hit a leaf node 
    if(current_node -> left == nullptr && current_node -> right == nullptr){
        if(first_leaf_depth == 0){ // if this is the first leaf node 
            first_leaf_depth = current_depth; //set first leaf's depth the current one
        }
        // if 2+ leaf node, compare the first depth with the next 
        else if (current_depth == first_leaf_depth){ // if equal 
            return true;
        }
        else if (current_depth != first_leaf_depth){ // not equal 
            return false;
        }
    }
   
   // recursively call again to move along tree
    return check_depth(current_node -> left, current_depth+1, first_leaf_depth) &&
    check_depth(current_node -> right, current_depth+1, first_leaf_depth);

}   

bool equalPaths(Node * root)
{
    // Add your code below
    int current_depth = 0;
    int first_leaf_depth = 0; 
    return check_depth(root, current_depth, first_leaf_depth);
    
}    



    

    
    
    
    
    
    