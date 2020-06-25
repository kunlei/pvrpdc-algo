#include "Node.hpp"
#include <cmath>
#include <iostream>

namespace pvrpdc {

using std::pow;
using std::cout;
using std::endl;
using std::vector;
using std::ostream;

/**
 * output to file/string/console
 */
ostream &operator<<(ostream &os, const Node &c) {
  os << "Node{idx: " << c.idx
     << "\tlat: " << c.lat
     << "\tlon: " << c.lon << endl
     << "\tsrvTime: " << c.srvTime
     << "\tdemand: " << c.demand << endl
     << "\tsrvFreq: " << c.srvFreq
     << "\tnumPatterns: " << c.numPatterns << endl
     << "\tavailable patterns: " << endl;

  if (!c.patterns.empty()) {
    int numDays = (int)c.patterns.at(0).size();
    os << "\tday: ";
    for (int d = 0; d < numDays; ++d) {
      os << "\t" << d;
    }
    os << endl;

    for (auto &patt : c.patterns) {
      os << "\t";
      for (const auto &v : patt) {
        os << "\t" << v;
      }
      os << endl;
    }
  }

  os << "\tdistance vector: " << endl;
  int numNodes = (int) c.distToOtherNodes.size();
  for (int i = 0; i < numNodes; ++i) {
    os << "\t" << i << "(" << c.distToOtherNodes.at(i) << ")";
  }
  os << endl
     << "}";
  return os;
}

/**
 * constructor
 */
Node::Node(int idx, double lat, double lon,
           int srvTime, int demand,
           int srvFreq, int numPatterns,
           int numDays) : idx(idx),
                          lat(lat),
                          lon(lon),
                          srvTime(srvTime),
                          demand(demand),
                          srvFreq(srvFreq),
                          numPatterns(numPatterns) {
  // initialize the vector of service patterns, with each pattern itself
  // a vector of size 'numDays' and a 'true' value indicate a day that
  // service is needed, false otherwise
  patterns.reserve(numPatterns);
  vector<bool> patt(numDays, false);
  for (int p = 0; p < numPatterns; ++p) {
    patterns.push_back(patt);
  }
}

/**
 * destructor
 */
Node::~Node() {
  // nothing to do
}

/**
 * initialize empty distance vector
 */
void Node::initDistVec(int numCus) {
  distToOtherNodes.reserve(numCus);
  for (int i = 0; i < numCus; ++i) {
    distToOtherNodes.push_back(0);
  }
}

/**
 * add a candidate service pattern
 */
void Node::addPattern(int pIdx, int numDays, size_t val) {
  // get binary string
  size_t binaryVal = numToBinary(val);

  size_t base = static_cast<size_t>(pow(10, numDays - 1));
  int quotient, remainder;
  for (int i = 0; i < numDays; ++i) {
    quotient = binaryVal / base;
    remainder = binaryVal % base;
    patterns.at(pIdx).at(i) = (quotient != 0);
    binaryVal = remainder;
    base = base / 10;
  }
}

/**
 * transform a integer value into a string of binary numbers
 * for example, '3' will be translated into '11'.
 */
size_t Node::numToBinary(size_t num) {
  if (num == 0) {
    return 0;
  } else {
    return num % 2 + 10 * numToBinary(num / 2);
  }
}

}