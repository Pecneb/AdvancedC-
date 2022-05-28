#include <iostream>
#include <string>

using namespace std;

auto query( const string& conn ) {
  
  return [ &conn ]( const string& sess ) -> auto {
  
    return [ &conn, &sess ]( const string& qdata ) -> auto {
    
      return string( conn + "/" + sess + ": " + qdata );
    
    };
  
  };

}

int main() {
  
  string lconnection( "LocalConnection" );

  auto remoteQuery = query( "RemoteConnection" );

  string sessionA( "SessionA" );

  auto remoteQuerySessionB = remoteQuery( "SessionB" );

  cout << query( lconnection )( sessionA )( "SELECT * FROM 1" ) << '\n';

  cout << remoteQuery( sessionA )( "SELECT * FROM user" ) << '\n';

  cout << remoteQuerySessionB( "SELECT password FROM admin" ) << '\n';

  return 0;

}
