#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

class Person {
protected:
  std::string nev;
  unsigned int szulEv;
public:
  Person(const std::string& n, unsigned int e) : nev(n), szulEv(e) {}
  virtual std::string getNev() { return nev; }
  virtual unsigned int getSzulEv() { return szulEv; }
  virtual Person& setNev(std::string ujNev) { nev = ujNev; return *this; }
  virtual Person& setSzulEv(unsigned int ujEv) { szulEv = ujEv; return *this; }
};

class Employee : public Person {
  unsigned int id;
  int salary;
  public:
  Employee(std::string n, unsigned int e, unsigned int id) : Person(n, e), id(id) {}
  unsigned int getID() { return id; }
  int getSalary() { return salary; }
  Employee& setID(unsigned int newID) { id = newID; return *this; }
  Employee& setSalary(int newSalary) { salary = newSalary; return *this; }
};

class Company {
  std::string nev;
  public:
  Company(const std::string& nev) : nev(nev) { std::cout << "Constructor of company called.\n"; }
  ~Company() { std::cout << "Desctructor of company called.\n"; }
};

class Subcontractor : public Person {
  unsigned int tmpID;
  Company* cmp;
  unsigned int contract;
  public:
  Subcontractor(std::string n, unsigned int e, unsigned int id, Company* c, unsigned int con)
    : Person(n, e), tmpID(id), cmp(c), contract(con) 
  {}
};

template <typename IterableCollection, typename CollectionElementType = int, typename Unwrapper, typename ResultType = int>
ResultType accumulate(
    IterableCollection& collection,
    Unwrapper unwrapper,
    ResultType initValue = 0,
    std::function<ResultType(CollectionElementType, CollectionElementType)> aggregator = std::plus<int>()) {
  ResultType result = initValue;
  for (auto it = collection.begin(); it != collection.end(); it++) {
    result = aggregator(result, unwrapper(*it));
  }
  return result;
}

auto returnsSalaryIfEmployeeZeroIfNot = [](Person* p) -> int {
  if (Employee* e = dynamic_cast<Employee*>(p)) {
    return e->getSalary(); 
  }
  return 0;
};

int main()
{
    Company innotech{ "Innotech" };
    Company lafabulosa{ "La Fabulosa" };

    Employee doriangray{ "Dorian Gray", 1977, 12321 }; // nev, szuletes eve, employee id
    doriangray.setSalary(500000); // brutto 500.000 havi kereset

    Employee tomsawyer{ "Tom Sawyer", 1982, 19355 };
    tomsawyer.setSalary(565000);

    Employee ernonemecsek{ "Erno Nemecsek", 1955, 20133 };
    ernonemecsek.setSalary(800500);
    
    Subcontractor jenobaradlay{ "Eugene Baradlay", 1967, 45322, &innotech, 1500000 }; // nev, szuletes eve, temporary id, ceg pointer, masfel millios szerzodes

    Subcontractor sandortakaro{ "Alexander Blanket", 1971, 35881, &lafabulosa, 3200000 };

    std::vector<Person*> peopleAtCompany{ &doriangray, &tomsawyer, &ernonemecsek, &jenobaradlay, &sandortakaro };

     std::vector <int> justForFun{ 1,2,3,4,5 };

    int sumOfJustForFun = accumulate(justForFun, [](int x) -> int { return x; });
    int sumOfJustForFunPlus3 = accumulate(justForFun, [](int x) -> int { return x; }, 3);

    std::function <int(int, int)> prod = std::multiplies<int>();
    int productOfJustForFun = accumulate(justForFun, [](int x) -> int {return x; }, 1, prod);

    std::cout << "sum of justForFun     = " << sumOfJustForFun << std::endl; // 15 az osszeg
    std::cout << "sum of justForFun + 3 = " << sumOfJustForFunPlus3 << std::endl; // 18 az osszeg
    std::cout << "product of justForFun = " << productOfJustForFun << std::endl; // 120 a szorzat

    std::cout << "total salary of all employees = "
        << accumulate(peopleAtCompany, returnsSalaryIfEmployeeZeroIfNot)
        << std::endl; // csak az alkalmazottak fizeteset irja ki, vagyis 1.865.500-at
    int totalSubcontractedPeople = std::count_if(
        peopleAtCompany.begin(),
        peopleAtCompany.end(),
        [](Person* person) -> bool { return dynamic_cast<Subcontractor*>(person); }
    );

    std::cout << "total number of subcontracted people: " << totalSubcontractedPeople << std::endl; // 2 alvallalkozo van
}
