#ifndef DATA_POND_HPP
#define DATA_POND_HPP
#include <vector>
#include <string>
#include <iostream>
#include "Node.hpp"
#include "Vehicle.hpp"

namespace pvrpdc {

class DataPond {
 public:
  friend std::ostream &operator<<(std::ostream &, const DataPond &);

 public:
  DataPond();
  ~DataPond();

  // data processing
  std::string getInstFilename(std::string instMark,
                              int instId,
                              int numNodes,
                              int numDays,
                              int numVeh,
                              std::string flag);
  void readData(std::string filename);
  void calDistance();
  void calSrvPattern();

  // accessors
  int getNumVehicles() const { return numVehicles; }
  int getNumNodes() const { return numNodes; }
  int getNumCustomers() const { return numCustomers; }
  int getNumDays() const { return numDays; }
  void showCustomers() const;
  const Node *getNode(int i) const { return nodes.at(i); }

 private:
  double calDistance(double lat1, double lon1, 
                     double lat2, double lon2);
  double roundDouble(double val);

 private:
  /**
   * number of days in the planning horizon
   */
  int numDays;
  /**
   * vehicles
   */
  int numVehicles;
  std::vector<Vehicle *> vehicles;
  /**
   * nodes, depot and customers
   */
  int numNodes;
  int numCustomers;
  std::vector<Node *> nodes;
};
std::ostream &operator<<(std::ostream &, const DataPond &);

}
#endif