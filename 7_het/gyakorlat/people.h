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
  return os << "Customer with ID: " << &c << std::endl; // was lazy to implement ID Customers, so using Customer object's mem address OMEGALUL
}

class Teller {
  std::deque<Customer>& customers; // all customers
  std::deque<Customer*> servedCustomers; // customers that already being served
  bool isCurrentlyBusy; // status of Teller, true if working, false if not working
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
  void run() { // teller start to serve customers
    startedWorking(); // teller status set to working
    int timeAvailable = 5; // time frame available to teller for serving
    while (timeAvailable > 0) {
      for ( auto cus = customers.begin(); cus != customers.end(); cus++ ) {
        if ((*cus).isWaiting()) { // if theres customers waiting start serving them
          (*cus).startServing(); 
          servedCustomers.push_back(&(*cus)); // add customer to the deque of served customers
          int rtfc = (*cus).getTaskComplexity().count();
          if (timeAvailable > rtfc) {
            (*cus).setToDone(); // if teller got more time, than customer's time then customer can be served completely, set status of customer to DONE
            timeAvailable -= rtfc; // subtract customer's time from teller's available time to serve
            customers.erase(cus); // erase customer from waiting customer's deque
            servedCustomers.erase(std::find(servedCustomers.begin(), servedCustomers.end(), &(*cus)));
          } else {
            (*cus).setComplexity(std::chrono::seconds(rtfc - timeAvailable)); // if teller's time is not enough to serve the customer, then just sub the available time from customer's serving time
            (*cus).stopServing(); // teller's service window is ended, stop serving customer, (we'll get them next time boys)
            timeAvailable = 0;
          }
        }
      }
      timeAvailable -= 1; // if there is no customer, teller's serving time should end sometime, so we must subtract from timeAvailable
    }
    stoppedWorking(); // teller status isBusy set to false, (not working atm)
  }
};

#endif
