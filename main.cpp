#include <iostream>
#include <string>
#include "src/data/DataPond.hpp"

using std::cout;
using std::endl;
using std::string;

using namespace pvrpdc;

int main() {
  string instMark{"con"};
  int instId{1};
  int numNodes{11};
  int numDays{5};
  int numVeh{2};
  string flag{"a"};

  // read data
  DataPond dataPond;
  string filename = dataPond.getInstFilename(instMark, instId, numNodes, numDays, numVeh, flag);
  dataPond.readData(filename);
  dataPond.calDistance();
  // dataPond.showCustomers();

  cout << dataPond << endl;

  return 0;
}