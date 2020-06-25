#ifndef VEHICLE_HPP
#define VEHICLE_HPP
#include <iostream>

namespace pvrpdc {

class Vehicle {
 public:
  friend std::ostream &operator<<(std::ostream &, const Vehicle &);

 public:
  Vehicle(int idx, int maxLoad, int maxDuration, int maxStops);
  ~Vehicle();
  Vehicle() = delete;
  Vehicle(const Vehicle &) = delete;
  Vehicle &operator=(const Vehicle &) = delete;
  Vehicle(Vehicle &&) = delete;
  Vehicle &operator=(Vehicle &&) = delete;

  int getMaxStops() const { return maxStops; }

 private:
  /**
   * unique index
   */
  int idx;
  /**
   * max load
   */
  int maxLoad;
  /**
   * max duration
   */
  int maxDuration;
  /**
   * max. no. of customers that can be visited
   * by the vehicle on a route
   */
  int maxStops;
};
std::ostream &operator<<(std::ostream &, const Vehicle &);

}

#endif