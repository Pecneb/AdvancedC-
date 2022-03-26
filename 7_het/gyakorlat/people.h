#ifndef PEOPLE
#define PEOPLE

class Customer{
  std::chrono::seconds taskComplexity;
  bool isCurrentlyWaiting;
  bool isDone;
  public:

  Customer(std::chrono::seconds t) : taskComplexity(t),
  isCurrentlyWaiting(true),
  isDone(false) {}

  std::chrono::seconds getTaskComplexity() { return taskComplexity; }
  bool isWaiting() { return isCurrentlyWaiting; }
  void startServing() { isCurrentlyWaiting = false; }
  void setToDone() { isDone = true; setComplexity(std::chrono::seconds(0)); }
  void setComplexity(std::chrono::seconds c) { taskComplexity = c; }
  void stopServing() { isCurrentlyWaiting = true; }
  friend std::ostream& operator<<(std::ostream&, const Customer&);
};

std::ostream& operator<<(std::ostream& os, const Customer& c) {
  return os << "Placeholder for customer output!\n";
}

class Teller {
  std::deque<Customer>& customers;
  std::deque<Customer*> servedCustomers;
  bool isCurrentlyBusy;
  public:
  Teller(std::deque<Customer>& c) : customers(c), isCurrentlyBusy(false) {}
  bool isBusy() const {
    return isCurrentlyBusy;
  }
  void startedWorking() { isCurrentlyBusy = true; }
  void stoppedWorking() { isCurrentlyBusy = false; }
  void printServicedCustomers() const {
   for ( auto it = servedCustomers.cbegin(); it != servedCustomers.cend(); it++ ) {
     std::cout << "Customer " << *it << std::endl;
   }
  }
  void run() {
    startedWorking();
    int timeAvailable = 5;
    while (timeAvailable > 0) {
      for (int i = 0; i < customers.size(); i++) {
        Customer& cus = customers[i];
        if (cus.isWaiting()) {
          cus.startServing(); 
          int rtfc = cus.getTaskComplexity().count();
          if (timeAvailable > rtfc) {
            cus.setToDone();
            timeAvailable -= rtfc;
            servedCustomers.push_back(&cus);
          } else {
            cus.setComplexity(std::chrono::seconds(rtfc - timeAvailable));
            cus.stopServing();
            timeAvailable = 0;
          }
        }
      }
      if (timeAvailable != 0) timeAvailable -= 1;
    }
    stoppedWorking();
  }
};

#endif
