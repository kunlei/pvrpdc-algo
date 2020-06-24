#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP
#include <vector>
#include <iostream>

namespace pvrpdc {

/**
 * define a customer class.
 * 
 * A customer object represents a location with demand to be fulfilled.
 * It is also associated with a service time required to perform the
 * service. 
 * 
 * A customer is also given a list of candidate service patterns that
 * indicates on which days it can be serviced.
 * 
 * Note that the customer with index 0 indicates the depot.
 */
class Customer {
 public:
  friend std::ostream &operator<<(std::ostream &, const Customer &c);

 public:
  Customer(int idx, double lat, double lon,
           int srvTime, int demand,
           int srvFreq, int numPatterns,
           int numDays);
  ~Customer();
  Customer() = delete;
  Customer(const Customer &) = delete;
  Customer &operator=(const Customer &) = delete;
  Customer(Customer &&) = delete;
  Customer &operator=(Customer &&) = delete;

  // accessors
  int getIdx() const { return idx; }
  double getLatitude() const { return lat; }
  double getLongitude() const { return lon; }
  int getSrvTime() const { return srvTime; }
  int getDemand() const { return demand; }
  int getSrvFreq() const { return srvFreq; }

  /**
   * initialize distance vector
   * 
   * @param numCus   no. of customers in the instance, including the depot
   */
  void initDistVec(int numCus);

  /**
   * set distance to another customer
   * 
   * @param cusIdx  index of the customer, starting from 0
   * @param dist    value of the distance
   */
  void setDist(int cusIdx, double dist) { distToOtherCus.at(cusIdx) = dist; }

  /**
   * obtain distance to another customer
   * 
   * @param cusIdx  index of the customer, starting from 0
   */
  double getDist(int cusIdx) const { return distToOtherCus.at(cusIdx); }

  /**
   * add service pattern for this customer
   * 
   * @param pIdx      index of the pattern
   * @param numDays   size of the pattern
   * @param val       content of the pattern
   */
  void addPattern(int pIdx, int numDays, size_t val);

  /**
   * get the total number of service patterns
   */
  int getNumPatterns() const { return numPatterns; }

  /**
   * get the service pattern indicated by the input index
   * 
   * @param pIdx  index of the pattern
   * @return a reference to the pattern
   */
  std::vector<bool> &getPattern(int pIdx) { return patterns.at(pIdx); }

 private:
  size_t numToBinary(size_t num);

 private:
  /**
   * unique index of this customer
   */
  int idx;
  /**
   * latitude and longitude
   */
  double lat;
  double lon;
  /**
   * distance to other customers
   */
  std::vector<double> distToOtherCus;
  /**
   * service time
   */
  int srvTime;
  /**
   * demand
   */
  int demand;
  /**
   * number of days that need service
   */
  int srvFreq;
  /**
   * number of service patterns
   */
  int numPatterns;
  /**
   * list of service patterns
   */
  std::vector<std::vector<bool>> patterns;
};
std::ostream &operator<<(std::ostream &, const Customer &c);

}

#endif