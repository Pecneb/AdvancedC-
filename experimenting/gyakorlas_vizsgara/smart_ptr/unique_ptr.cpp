#include <memory> /* unique_ptr, shared_ptr, weak_ptr */

using namespace std;

struct S {

	unique_ptr< S > m;

};

int main() {

	unique_ptr< S > s = make_unique< S >();

	s->m = make_unique< S >();

	swap( s, s->m );

	return 0;
	
}
