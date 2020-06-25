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
     << "\tmaxStops: " << v.maxStops
     << "}";
  return os;
}

/**
 * constructor
 */
Vehicle::Vehicle(int idx,
                 int maxLoad,
                 int maxDuration,
                 int maxStops) : idx(idx),
                                 maxLoad(maxLoad),
                                 maxDuration(maxDuration),
                                 maxStops(maxStops) {
}

/**
 * destructor
 */
Vehicle::~Vehicle() {
  // nothing to do
}


}