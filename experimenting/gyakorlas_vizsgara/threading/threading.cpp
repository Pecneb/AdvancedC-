#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <utility>
#include <vector>
#include <algorithm>

#define ROWS 1000
#define COLS 1000

typedef std::vector< std::vector< int > > VectorMTX;

typedef VectorMTX::iterator VMTX_it;

typedef std::vector< std::thread > ThreadV;

void multiplicateByTen( int &x ) {
    
    x *= 10;

}

void printer( int x ) { std::cout << x << ' '; }

int main() {

    VectorMTX vmtx;

    for ( int i = 0; i < ROWS; i++ ) {
        
        std::vector< int > v;
        
        vmtx.push_back( v );
        
        for ( int j = 0; j < COLS; j++ ) {
        
            vmtx[ i ].push_back( j );
        
        } /* j */

    } /* i */

    ThreadV tv;

    for ( int i = 0; i < ROWS; i++ ) {

        for ( int j = 0; j < COLS; j++) {
        
            tv.push_back( std::thread( multiplicateByTen, std::ref( vmtx[ i ][ j ] ) ) );
                    
        } /* j */

    } /* i */

    for ( ThreadV::iterator tit = tv.begin(); tit != tv.end(); tit++ ) {
    
        tit->join();
    
    }

    for ( auto it = vmtx.begin(); it != vmtx.end(); it++ ) {
    
        for ( auto sit = it->begin(); sit != it->end(); sit++ ) {
    
            printer( *sit );
    
        } /* COLS */
    
        std::cout << '\n';
    
    } /* ROWS */
    
    return 0;

}
