#include "Solution.hpp"
#include <cstdlib>

namespace pvrpdc {

using std::rand;
using std::cout;
using std::endl;
using std::ostream;

/**
 * output to file/string/console
 */
ostream &operator<<(ostream &os, const Solution &s) {
  return os;
}

/**
 * constructor
 */
Solution::Solution(const DataPond &dataPond) : dataPond(dataPond) {
  int numNodes = dataPond.getNumNodes();
  int numVehicles = dataPond.getNumVehicles();
  int numDays = dataPond.getNumDays();

  // randomly initialize customer service pattern
  cusPattVec.reserve(numNodes);
  for (int i = 0; i < numNodes; ++i) {
    cusPattVec.push_back(0);
  }
  for (int i = 1; i < numNodes; i++) {
    const Node *pn = dataPond.getNode(i);
    int numPatterns = pn->getNumPatterns();
    cusPattVec.at(i) = rand() % numPatterns;
  }

  // assign customers to vehicles


  // derive vehicle routes on each day
}

/**
 * destructor
 */
Solution::~Solution() {

}

/**
 * compute objective value
 */
void Solution::calObj() {

}

}