#include <iostream>
#include <string>
#include "src/data/DataPond.hpp"

using std::cout;
using std::endl;
using std::string;

using namespace pvrp;

int main() {
  string instMark{"new"};
  int instId{1};

  // read data
  DataPond dataPond;
  dataPond.readData(instMark, instId);
  dataPond.calDistance();
  dataPond.showCustomers();

  cout << dataPond << endl;

  return 0;
}