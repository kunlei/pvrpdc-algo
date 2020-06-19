#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <list>
#include <map>
#include <iostream>
#include "Node.hpp"

namespace pvrp {

class Route {
 public:
  friend std::ostream &operator<<(std::ostream &, const Route &);

 public:
  Route();
  ~Route();

 private:
  /**
   * linked list of visited nodes
   */
  Node *head;
  Node *tail;
  /**
   * no. of visited customers on route
   */
  int numCustomers;
  /**
   * total duration
   */
  double totDura;
  /**
   * total demand fulfilled by the route
   */
  int totDemand;
};
std::ostream &operator<<(std::ostream &, const Route &);

}

#endif