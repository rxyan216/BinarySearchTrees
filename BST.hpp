#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */
  virtual ~BST() {
    this->clear();   // call the clear method
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */
  virtual std::pair<iterator,bool> insert(const Data& item) {
    BSTNode<Data> *p = root, *prev = nullptr;
    while (p != nullptr) {                    // if p is not null
      prev = p;                               // assign p to prev
      if (item < p->data)                     // if item is less than data
        p = p->left;                          // p points to left child
      else if (item > p->data)                // if item is greater than data
        p = p->right;                         // p points to right child
      else break;
    }
    if (root == nullptr) {                    // if root is null
      root = new BSTNode<Data>(item);         // insert item to root
      isize++;                                // add isize
      return std::make_pair(iterator(root), 1);
    }
    else if (item < prev->data) {             // if item is less than data
      prev->left = new BSTNode<Data>(item);   // insert item to left child
      prev->left->parent = prev; 
      isize++;                                // add isize
      return std::make_pair(iterator(prev->left), 1);
    }
    else if (item > prev->data) {             // if item is greater than data
      prev->right = new BSTNode<Data>(item);  // insert item to right child
      prev->right->parent = prev;
      isize++;                                // add isize
      return std::make_pair(iterator(prev->right), 1);
    }
    else
      return std::make_pair(iterator(prev), 0);
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */
  iterator find(const Data& item) const {
    BSTNode<Data> *p = root, *prev = nullptr;
    while (p != nullptr) {                   // if p is not null
      prev = p;                              // assign p to prev
      p = p->left;                           // p points to left child
    }
    while (prev != nullptr) {                // if prev is not null
      if (prev->data != item)                // if data does not equal to item
        prev = prev->successor();            // prev points to its successor
      else
        return typename BST<Data>::iterator(prev);
    }
    return this->end();
  }

  
  /** Return the number of items currently in the BST.
   */
  unsigned int size() const {
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */
  void clear() {
    BSTNode<Data> *q[isize];                // define an pointer array
    BSTNode<Data> *p = root, *prev = nullptr;
    while (p != nullptr) {                  // if p is not null
      prev = p;                             // assign p to prev
      p = p->left;                          // p points to left child
    }
    for (int i = 0; i < isize; i++) {
      q[i] = prev;                          // assign prev to q[i]
      prev = prev->successor();             // prev points to its successor
    }
    for (int i = 0; i < isize; i++) {
      delete q[i];                          // delete q[i]
      q[i] = nullptr;                       // q[i] points to null
    }
    isize = 0;                              // assign 0 to isize 
    std::cout<<"Clearance is completed!\n";
  }

  /** Return true if the BST is empty, else false.
   */
  bool empty() const {
    if (isize == 0)                         // if isize equals to 0
      return 1;
    else
      return 0;
  }

  /** Return an iterator pointing to the first item in the BST.
   */
  iterator begin() const {
    BSTNode<Data> *p = root, *prev = nullptr;
    while (p != nullptr) {                  // if p is not null
      prev = p;                             // assign p to prev
      p = p->left;                          // p points to left child
    }
    return typename BST<Data>::iterator(prev);
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

  

 };


#endif //BST_HPP
