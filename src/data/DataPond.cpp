#include "DataPond.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <cmath>

namespace pvrpdc {

using std::ostream;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::ios;
using std::ifstream;
using std::stringstream;
using std::vector;
using std::stoi;
using std::stod;
using std::sqrt;
using std::pow;

/**
 * output to console/file/string
 */
ostream &operator<<(ostream &strm, const DataPond &dp) {
  strm << "DataPond{numVehicles: " << dp.numVehicles
       << "\tnumCustomers: " << dp.numNodes
       << "\tnumDays: " << dp.numDays
       << "\tmaxDuration: " << dp.maxDuration
       << "\tmaxLoad: " << dp.maxLoad
       << "}";
  return strm;
}

/**
 * constructor
 */
DataPond::DataPond() : numVehicles(0),
                       numNodes(0),
                       numCustomers(0),
                       numDays(0),
                       maxDuration(0),
                       maxLoad(0) {
}

/**
 * destructor
 */
DataPond::~DataPond() {
  // remove all customers
  for (auto &c : customers) {
    delete c;
  }
  customers.clear();
}

/**
 * read instance data from file
 * @param instMark type of the instance, "new" or "old"
 * @param instId integer id of the instance
 */
void DataPond::readData(string instMark, int instId) {
  cout << "DataPond::start reading instance file...\n";
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
  } else {
    cout << "DataPond::error in reading instance file, exit...\n";
    return;
  }
  cout << "\tfilename: " << filename << "\n";

  // create input file stream
  ifstream infile(filename, ios::in);
  
  string line, word;
  vector<string> row;

  // read first line
  getline(infile, line);
  stringstream s(line);
  while (getline(s, word, ' ')) {
    row.push_back(word);
  }
  numVehicles = stoi(row.at(1)); 
  numNodes = stoi(row.at(2));
  numCustomers = numNodes - 1;
  numDays = stoi(row.at(3));
  cout << "\tfirst line read...\n";

  // read constraints on vehicle
  for (int i = 0; i < numDays; ++i) {
    getline(infile, line);
    stringstream s(line);
    row.clear();
    while (getline(s, word, ' ')) {
      row.push_back(word);
    }
    maxDuration = stoi(row.at(0));
    maxLoad = stoi(row.at(1));
  }
  cout << "\tvehicle info read...\n";

  // read individual customers
  int idx;
  double lat, lon;
  int srvTime, demand;
  int srvFreq, numPatterns;
  size_t pattVal;
  int colIdx{0};
  string strCol;
  for (int i = 0; i < numNodes; ++i) {
    infile >> idx;
    infile >> lat >> lon;
    infile >> srvTime >> demand;
    infile >> srvFreq >> numPatterns;

    Customer *pCus = new Customer(idx, lat, lon,
                                  srvTime, demand,
                                  srvFreq, numPatterns, 
                                  numDays);

    if (numPatterns > 0) {
      for (int p = 0; p < numPatterns; ++p) {
        infile >> pattVal;
        pCus->addPattern(p, numDays, pattVal);
      }
    }
    customers.push_back(pCus);
  }
  infile.close();
  cout << "DataPond::start reading instance file...\n";
}

/**
 * calculate distance between customers
 */
void DataPond::calDistance() {
  // initialize distance vector
  for (auto &c : customers) {
    c->initDistVec(numNodes);
  }

  // calculate distance
  for (int i = 0; i < numNodes; ++i) {
    for (int j = i; j < numNodes; ++j) {
      auto ci = customers.at(i);
      auto cj = customers.at(j);
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
  for (auto pc : customers) {
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