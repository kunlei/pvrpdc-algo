#include "Customer.hpp"
#include <iostream>
#include <cmath>

namespace pvrp {

using std::pow;
using std::cout;
using std::endl;
using std::ostream;
using std::vector;

/**
 * output to file/string/console
 */
ostream &operator<<(ostream &strm, const Customer &c) {
  strm << "Customer{idx: " << c.idx
       << "\tlat: " << c.lat
       << "\tlon: " << c.lon << endl
       << "\tsrvTime: " << c.srvTime
       << "\tdemand: " << c.demand << endl
       << "\tsrvFreq: " << c.srvFreq
       << "\tnumPatterns: " << c.numPatterns
       << endl
       << "\tavailable patterns: " << endl;
  if (!c.patterns.empty()) {
    int numDays = (int)c.patterns.at(0).size();
    strm << "\tday: ";
    for (int d = 0; d < numDays; ++d) {
      strm << "\t" << d;
    }
    strm << endl;

    for (auto &patt : c.patterns) {
      strm << "\t";
      for (const auto &v : patt) {
        strm << "\t" << v;
      }
      strm << endl;
    }
  }

  strm << "\tdistance vector: " << endl;
  int numCustomers = (int) c.distToOtherCus.size();
  for (int i = 0; i < numCustomers; ++i) {
    strm << "\t" << i << "(" << c.distToOtherCus.at(i) << ")";
  }
  strm << endl;
  strm << "}";
  return strm;
}

/**
 * constructor
 */
Customer::Customer(int idx, double lat, double lon,
                   double srvTime, int demand,
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
Customer::~Customer() {

}

/**
 * initialize empty distance vector
 */
void Customer::initDistVec(int numCus) {
  distToOtherCus.reserve(numCus);
  for (int i = 0; i < numCus; ++i) {
    distToOtherCus.push_back(0);
  }
}

/**
 * add a candidate service pattern
 */
void Customer::addPattern(int pIdx, int numDays, size_t val) {
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
size_t Customer::numToBinary(size_t num) {
  if (num == 0) {
    return 0;
  } else {
    return num % 2 + 10 * numToBinary(num / 2);
  }
}

}