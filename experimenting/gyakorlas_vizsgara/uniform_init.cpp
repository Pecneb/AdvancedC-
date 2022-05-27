#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

using namespace chrono;

typedef int(*fp)(int); // This is a function, that returns an int and waits an int as an arg.

typedef void(*swapFunc)(string&, string&); // This is a function, that, waits two string reference, to swap them. Returns nothing.

template<typename function_ptr, typename obj1> // Template function, for measure execution time.

decltype(auto) swapTime(function_ptr func, obj1& o1, obj1& o2) {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    func(o1, o2);

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2-t1);

    cout << "Exection time of function was: " << time_span.count() << '\n';

}

void xfunc(fp f, int a) {

    cout << f(a) << '\n';

}

int func(int a) {
 
    return 5*a;
}


void swap1(string& a, string& b) {
 
    string tmp(a);
 
    a = b;
 
    b = tmp;
}

void swap2(string& a, string& b) {
    
    string tmp(move(a));

    a = move(b);

    b = move(tmp);

}

int main() {

    xfunc(func, 15);

    string a("This is just a regular string.");
    
    string b("This is another string.");

    cout << a << '\t' << b << '\n';

    swapTime<swapFunc, string>(swap2, a, b);

    cout << a << '\t' << b << '\n';

    return 0;
}
