#include "Vehicle.hpp"

namespace pvrpdc {

using std::cout;
using std::endl;
using std::ostream;

/**
 * output to file/string/console
 */
ostream &operator<<(ostream &os, const Vehicle &v) {
  os << "Vehicle{"
     << "idx: " << v.idx
     << "\tmaxLoad: " << v.maxLoad
     << "\tmaxDuration: " << v.maxDuration
     << "}";
  return os;
}

/**
 * constructor
 */
Vehicle::Vehicle(int idx,
                 int maxLoad,
                 int maxDuration) : idx(idx),
                                    maxLoad(maxLoad),
                                    maxDuration(maxDuration) {
}

/**
 * destructor
 */
Vehicle::~Vehicle() {
  // nothing to do
}


}