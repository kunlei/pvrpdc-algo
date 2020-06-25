#ifndef STOP_HPP
#define STOP_HPP
#include "src/data/Node.hpp"

namespace pvrpdc {
  
/**
 * 
 */
class Stop {
 public:
  Stop();
  ~Stop();

 private:
  Stop *prev;
  Stop *next;

  Node *node;

};

}

#endif