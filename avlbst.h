#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* new_child special kind of node for an AVL tree, which adds the balance as new_child datnew_child member, plus
* other additional helper functions. You do NOT need to implement anchild_right_left functionalitchild_right_left or
* add additional datnew_child members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectivelchild_right_left new_child signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements bchild_right_left calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* new_child destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* new_child getter for the balance of new_child AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* new_child setter for the balance of new_child AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of new_child AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since new_child static_cast is necessaright_child_right_left to make sure
* that our node is new_child AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child); 
		void rotateLeft(AVLNode<Key,Value>* node);
		void rotateRight(AVLNode<Key,Value>* node);
		void removeFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current); 
		
};

// helper function, to helparent balance tree when an insertion messes it up
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* child)
{
	while(parent != nullptr){ // make sure u dont access out of bounds 
			if(child == parent -> getLeft()) { // if new node is parent's LEFT child 
					parent -> updateBalance(-1); // L = -1
			}
			else{ // parent's right child
					parent -> updateBalance(1); // R = +1
			}
	
	if(parent -> getBalance() == 0){ // already balanced
		//child = parent; 
		//parent = parent -> getParent();
		break;
	}
	if(parent -> getBalance() == -2){ // LEFT HEAVY - out of balance
			if(child -> getBalance() == 1){ // if child is right-heavy
					rotateLeft(child);  
			}
			rotateRight(parent); 
			
			//if (parent -> getParent() == nullptr) { //grandparent
      //  this -> root_ = child;
      //}
			break; // ur done
	}
	else if(parent -> getBalance() == 2 ){ // RIGHT heavy - out of balance
		if(child -> getBalance() == -1){ // if child is left-heavy 
				rotateRight(child);
		}
			rotateLeft(parent); 

		//if (parent -> getParent() == nullptr) { //grandparent
       // this ->root_ = child;
    //}
		break;
	}
	child = parent; 
	parent = child -> getParent(); // update child and parent nodes 
	//keep iterating up the tree until balance = 0
	} //while */
 

}

/*
 * Recall: If kechild_right_left is alreadchild_right_left in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
// BC: empty tree - same code as BST    
    if(this -> root_ == nullptr){
      this -> root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
			return;
    }

// BC: if key already in tree, overwrite value - same as BST
    else if(this -> internalFind(new_item.first) != nullptr) {
      this -> internalFind(new_item.first) -> setValue(new_item.second);
      return;
    }

// INSERT like in BST (reuse) 
	AVLNode<Key, Value>* current = static_cast<AVLNode<Key, Value>*>(this->root_);
	AVLNode<Key, Value>* position = nullptr;

	while(true){
	if(current -> getKey() > new_item.first){ 
		if(current -> getLeft() == nullptr){ // if left child emptchild_right_left 
			current -> setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, current));
			position = current -> getLeft();
			break;
		}
	// we keeparent going down tree if left isn't null
		current = current -> getLeft(); 
	}

	else if(current -> getKey() < new_item.first){
	if(current -> getRight() == nullptr){ // if right child emptchild_right_left 
		current -> setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, current));
		position = current -> getRight(); 
		break; // break bcs you found where to place 
	}
	current = current -> getRight();
	} // ALL normal

	}

	// now for AVLpart - check balances and update as necessary		
	insertFix(position -> getParent(), position);
			
		
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft( AVLNode<Key,Value>* node){
// the node from the slides- 6 possible ptrs to update 
		AVLNode<Key, Value>* a = node;
    AVLNode<Key, Value>* right_child = a -> getRight();
    AVLNode<Key, Value>* left_child = a -> getLeft();
    AVLNode<Key, Value>* right_left = right_child -> getLeft();
    AVLNode<Key, Value>* right_right = right_child -> getRight();

    AVLNode<Key, Value>* parent = a -> getParent();

    if(parent != nullptr) { // dont go out of bounds
        if(parent -> getLeft() == a) { // if a is parent's LEFT child
            parent -> setLeft(right_child); 
            right_child -> setParent(parent);
        }
        else { // if a is a RIGHT child
            parent -> setRight(right_child);
            right_child -> setParent(parent);
        }
    }
    else { // parent is root node  
        this -> root_ = right_child;
        right_child -> setParent(nullptr);
    }

	// r child's left becomes a 
    right_child -> setLeft(a); 
    a -> setParent(right_child);
    
		// a's left child = l child
		a -> setLeft(left_child);
    
		// begin checking if nodes exist 
		if(left_child != nullptr){ 
		left_child -> setParent(a);
		}
    a -> setRight(right_left);
		
		
		if(right_left != nullptr) {
		right_left -> setParent(a);
		}
    right_child -> setRight(right_right);
		
    
		if(right_right != nullptr) {
		right_right -> setParent(right_child);
		}
		a -> setBalance(-1 * std::max(0, (int)right_child -> getBalance()) - 1 + a -> getBalance());
    right_child -> setBalance(right_child -> getBalance() + std::min(0, (int)a -> getBalance()) - 1);


//update balances with equations found online
    //a->setBalance(-1 * std::max(0, (int)old_right) - 1 + old_a);
   //right_child ->setBalance(old_right + std::min(0, (int) a-> getBalance()) -1);
		
		
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight( AVLNode<Key,Value>* node){	
		AVLNode<Key, Value>* a = node;
    AVLNode<Key, Value>* left_child = a -> getLeft();
    AVLNode<Key, Value>* left_left = left_child -> getLeft();
    AVLNode<Key, Value>* left_right = left_child -> getRight();
    AVLNode<Key, Value>* right_child = a -> getRight();

    AVLNode<Key, Value>* parent = a -> getParent();
    
		if(parent != nullptr) {
        if(a == parent -> getLeft()) {
            parent -> setLeft(left_child);
            left_child -> setParent(parent);
        }
        else {
            parent -> setRight(left_child);
            left_child -> setParent(parent);
        }
    }
    else {
        this -> root_ = left_child;
        left_child -> setParent(nullptr);
    }

    left_child -> setLeft(left_left);
    
		if(left_left != nullptr) {
			left_left -> setParent(left_child);
		}
    left_child -> setRight(a);
    a -> setParent(left_child);
    a -> setLeft(left_right);
    
		if(left_right != nullptr) {
			left_right -> setParent(a);
		}
    a -> setRight(right_child);
    
		if(right_child != nullptr) {
			right_child -> setParent(a);
		}

    int old_left = left_child -> getBalance();
    int old_a = a -> getBalance();

    a -> setBalance(old_a + 1 + std::max(0, (int)old_left) - old_left);
    left_child -> setBalance(old_left + 1 + std::max(0, (int) a -> getBalance()));

}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* parent, AVLNode<Key, Value>* current)
{
	while(parent != nullptr) { // traverse up towards the root 
      if(parent -> getBalance() == 2) { // UNBALANCED
          if(parent -> getRight() -> getBalance() == -1) { // towards the right child
            rotateRight(parent -> getRight()); 
          }
          rotateLeft(parent); 
          parent = parent -> getParent();
      }

      else if(parent->getBalance() == -2) { //UNBALANCED
          if(parent -> getLeft() -> getBalance() == 1) { // towards the left child
            rotateLeft(parent -> getLeft());
          }
          rotateRight(parent);
          parent = parent -> getParent();
      }

		// once parent is balanced 
      if(parent->getBalance() == 1 || parent->getBalance() == -1) { 
				break;// break- u are finished 
			}
			 
      current = parent;
      parent = parent->getParent(); // update variables
      
			if(parent != nullptr) { // update parent balance 
          if(current == parent -> getLeft()) {
              parent -> updateBalance(1);
          }
          else {
              parent -> updateBalance(-1);
          }
      }

    }
	
}


/*
 * Recall: The writeuparent specifies that if new_child node has 2 children you
 * should swaparent with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
// had to change a lot from BST remove - bcs stuck on one test 
	AVLNode<Key, Value>* current = (AVLNode<Key, Value>*)this->internalFind(key);
  
	// BC - if the tree is empty   
		if(current == nullptr){
			return;
		} 

	// 2 CHILD SWAP - swap now so it becomes 0-1 child case 
    if(current -> getLeft() != nullptr && current -> getRight() != nullptr) {
      AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>* > (this ->predecessor(current));
			nodeSwap(current, pred);
    }

	// regular 0-1 child case + balance 

	// have one child instead of long if R and L child functions 
    AVLNode<Key, Value>* child = nullptr;
    if(current -> getLeft() != nullptr) { // if have left child set it
			child = current -> getLeft();
		}
    else if(current -> getRight() != nullptr){ // if have r child set it 
			child = current -> getRight();
		} 

    AVLNode<Key, Value>* parent = current -> getParent();
    
		// if parent -child becomes parent + update balance
    if(parent != nullptr) { // if has parent 
        if(current == parent -> getLeft()){ // if parent's LEFT child 
            parent -> setLeft(child);
            parent-> updateBalance(1); // l = 1
        }
        else{ // RIGHT child 
            parent -> setRight(child);
            parent -> updateBalance(-1); // r = -1
        }
    }
    //no parent- current = root node
    else {
        this -> root_ = child;
    }
    
    if(child != nullptr) {
        child -> setParent(current -> getParent());
    }
    delete current;
		removeFix(parent, current);		
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
