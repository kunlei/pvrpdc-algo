#ifndef LNS_ALGO_HPP
#define LNS_ALGO_HPP
#include "Solution.hpp"
#include "src/data/DataPond.hpp"

namespace pvrpdc {

class LnsAlgo {
 public:

 public:
  LnsAlgo(DataPond &dataPond);
  ~LnsAlgo();

  void initialize();
  void run();
  void output();

 private:
  /**
   * 
   */
  DataPond &dataPond;
  /**
   * 
   */
  Solution sol;
  /**
   * 
   */
  Solution bestSol;
};

}

#endif