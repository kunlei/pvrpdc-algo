#ifndef NODE_HPP
#define NODE_HPP
#include "src/data/Customer.hpp"

namespace pvrp {
  
/**
 * 
 */
class Node {
 public:
  Node();
  ~Node();

 private:
  Node *prev;
  Node *next;

  Customer *cus;

};

}

#endif