#include <iostream>
#include <ctime>
#include <chrono>
#include <functional>

int fibonacci(int n) {

	if ( n < 2 ) return n;

	return fibonacci( n - 1 ) + fibonacci( n - 2 );
	
}

template < typename returntype, typename argtype >

int timer( std::function< returntype( argtype ) > fn,
	argtype arg_1) {

	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

	fn( arg_1 );
	
	std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_time = end - start;
	
	std::cout << "elapsed seconds: " << elapsed_time.count();
	
}

int main() {

	timer< int, int >( fibonacci, 30 );
	
	return 0;
	
}