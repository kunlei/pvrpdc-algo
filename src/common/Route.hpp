#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <map>
#include <list>
#include <iostream>
#include "Stop.hpp"

namespace pvrpdc {

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
  Stop *head;
  Stop *tail;
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