#include <iostream>
#include <vector>
#include <string>
#include <functional>

/* Logs the operations operating on type A value */
template< typename A >
class LoggerMonad {

    std::vector< std::string > logs; A value;

    public:

    LoggerMonad( const std::vector< std::string >& l, A v ) : logs( l ), value( v ) {}

    static LoggerMonad< A > unit( A val ) {

        return LoggerMonad< A >(std::vector< std::string >(), val);

    }

    LoggerMonad< A >& bind( std::function< LoggerMonad< A >(A) > func ) {

        LoggerMonad< A > tmp = func( value );

        value = tmp.value;

        logs.push_back( tmp.logs.at(0) );

        return *this;

    }

    void print() {

        std::cout << "value is: " << value << ". order of operations was: \n";

        for ( std::string& s : logs ) { std::cout << s << ' '; }

        std::cout << std::endl;

    }

};


int main() {

    std::function< LoggerMonad< int >( int ) > addFive = []( int x ) -> LoggerMonad< int > {

        return LoggerMonad< int >( std::vector< std::string >{ " addFive " }, x + 5 );

    };

    std::function< LoggerMonad< int >( int ) > multByFive = []( int x ) -> LoggerMonad< int > {

        return LoggerMonad< int >( std::vector< std::string >{ " multByFive " }, x * 5 );

    };

    LoggerMonad< int > x = LoggerMonad< int >::unit( 500 );

    x.bind( addFive ).bind( multByFive ).bind( multByFive );

    x.print();

    return 0;

}