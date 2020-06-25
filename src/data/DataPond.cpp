#include "DataPond.hpp"
#include <regex>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

namespace pvrpdc {

using std::ios;
using std::pow;
using std::ceil;
using std::cout;
using std::endl;
using std::stoi;
using std::stod;
using std::sqrt;
using std::vector;
using std::string;
using std::ostream;
using std::ifstream;
using std::to_string;
using std::stringstream;

/**
 * output to console/file/string
 */
ostream &operator<<(ostream &os, const DataPond &dp) {
  os << "DataPond{numVehicles: " << dp.numVehicles
     << "\tnumNodes: " << dp.numNodes
     << "\tnumDays: " << dp.numDays << endl;

  // show vehicles
  os << "\tshow available vehicles: " << endl;
  for (int v = 0; v < dp.numVehicles; ++v) {
    os << "\t" << *(dp.vehicles.at(v)) << endl;
  }

  // show nodes
  os << "\tshow nodes: " << endl;
  for (int n = 0; n < dp.numNodes; ++n) {
    os << "\t" << *(dp.nodes.at(n)) << endl;
  }
  
  os << "}" << endl;
  return os;
}

/**
 * constructor
 */
DataPond::DataPond() : numDays(0),
                       numVehicles(0),
                       numNodes(0),
                       numCustomers(0) {
}

/**
 * destructor
 */
DataPond::~DataPond() {
  // remove all vehicles
  for (auto &v : vehicles) {
    delete v;
  }
  vehicles.clear();

  // remove all customers
  for (auto &c : nodes) {
    delete c;
  }
  nodes.clear();
}

/**
 * read instance data from file
 * @param instMark type of the instance, "new", "old" or "con"
 * @param instId integer id of the instance
 */
string DataPond::getInstFilename(string instMark, int instId,
                                 int numNodes, int numDays, int numVeh, string flag) {
  // derive filename
  string filename = "instance/";
  if (instMark == "new") {
    filename += "new/pr";
    if (instId < 10) {
      filename += "0" + to_string(instId) + ".txt";
    } else {
      filename += to_string(instId) + ".txt";
    }
  } else if (instMark == "old") {
    filename += "old/p";
    if (instId < 10) {
      filename += "0" + to_string(instId) + ".txt";
    } else {
      filename += to_string(instId) + ".txt";
    }
  } else if (instMark == "con") {
    // example filename: test21-p3-m4-b.dat
    filename += "con/test" + 
                to_string(numNodes) + 
                "-p" + to_string(numDays) +
                "-m" + to_string(numVeh) +
                "-" + flag + ".dat";
  } else {
    cout << "DataPond::error in reading instance file, exit...\n";
    return "";
  }
  cout << "instance filename: " << filename << endl;
  return filename;
}

/**
 * read instance data
 */
void DataPond::readData(string filename) {
  cout << "DataPond::readData()...start..." << endl;
  // create input file stream
  ifstream infile(filename, ios::in);
  if (!infile.is_open()) {
    cout << "\tinstance file cannot open!" << endl
         << "DataPond::readData()...complete, error!!!" << endl;
    infile.close();
    return;
  }

  int num;

  // read first line
  infile >> num >> numVehicles >> numCustomers >> numDays;
  numNodes = numCustomers + 1;
  cout << "\tfirst line read...\n";

  // read vehicles
  int maxDuration{0}, maxLoad{0};
  for (int i = 0; i < numDays; ++i) {
    infile >> maxDuration >> maxLoad;
  }

  int maxStops = static_cast<int>(ceil(0.75 * numCustomers / numVehicles));
  for (int v = 0; v < numVehicles; ++v) {
    Vehicle *pv = new Vehicle(v, maxLoad, maxDuration, maxStops);
    vehicles.push_back(pv);
  }
  cout << "\tvehicle info read...\n";

  // read individual customers
  int idx;
  double lat, lon;
  int srvTime, demand;
  int srvFreq, numPatterns;
  size_t pattVal;
  string strCol;
  for (int i = 0; i < numNodes; ++i) {
    infile >> idx;
    infile >> lat >> lon;
    infile >> srvTime >> demand;
    infile >> srvFreq >> numPatterns;

    Node *pn = new Node(idx, lat, lon,
                        srvTime, demand,
                        srvFreq, numPatterns, 
                        numDays);

    if (numPatterns > 0) {
      for (int p = 0; p < numPatterns; ++p) {
        infile >> pattVal;
        pn->addPattern(p, numDays, pattVal);
      }
    }
    nodes.push_back(pn);
  }
  infile.close();
  cout << "DataPond::readData()...complete!" << endl;
}

/**
 * calculate distance between customers
 */
void DataPond::calDistance() {
  // initialize distance vector
  for (auto &c : nodes) {
    c->initDistVec(numNodes);
  }

  // calculate distance
  for (int i = 0; i < numNodes; ++i) {
    for (int j = i; j < numNodes; ++j) {
      auto ci = nodes.at(i);
      auto cj = nodes.at(j);
      double dist = calDistance(ci->getLatitude(), ci->getLongitude(),
                                cj->getLatitude(), cj->getLongitude());
      ci->setDist(j, dist);
      cj->setDist(i, dist);
    }
  }
}

/**
 * show all customers
 */
void DataPond::showCustomers() const {
  cout << "show all customers..\n";
  for (auto pc : nodes) {
    cout << *pc << endl;
  }
}

/**
 * compute distance between two points using their corresponding latitude and longitude
 */
double DataPond::calDistance(double lat1, double lon1, double lat2, double lon2) {
  return roundDouble(sqrt(pow(lat1 - lat2, 2.0) + pow(lon1 - lon2, 2.0)));
}

/**
 * round a double value
 */
double DataPond::roundDouble(double val) {
  double precision = 10000.0;
  return (int) (val * precision + (val < 0 ? -0.5 : 0.5)) / precision;
}
  
}