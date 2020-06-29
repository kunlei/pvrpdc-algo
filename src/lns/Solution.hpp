#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <vector>
#include <iostream>
#include "src/data/DataPond.hpp"
#include "src/common/Route.hpp"

namespace pvrpdc {

class Solution {
 public:
  friend std::ostream &operator<<(std::ostream &, const Solution &);

 public:
  Solution(const DataPond &dataPond);
  ~Solution();

  void calObj();

 private:
  /**
   * reference to the data
   */
  const DataPond &dataPond;
  /**
   * a vector of customer selected service patterns
   * size: 1 * numNodes
   */
  std::vector<int> cusPattVec;
  /**
   * customers covered by vehicles
   * size: numVehicles * numNodes
   */
  std::vector<std::vector<bool>> vehCusVec;
  /**
   * the set of routes in the solution
   * size: numDays * numVehicles
   */
  std::vector<std::vector<Route *>> routes;
  /**
   * total traveling cost
   */
  double totCost;
};
std::ostream &operator<<(std::ostream &, const Solution &);

}

#endif