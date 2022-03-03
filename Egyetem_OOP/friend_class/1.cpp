#include "Decl.hpp"

void in_ch::kiir()
 {
  sps = {swim,cycle,depo,swim+cycle+depo,run,getSum()};
  cout << "\nLicence: " << lic;
  for(it = sps.begin(), j_it = jelek.begin();\
      it != sps.end(); it++, j_it++)
   {
    hpmp.clear(); s_hms(*it);
    cout << "\n" << *j_it << " "; 
    for(auto itb = hpmp.begin(); itb != hpmp.end(); itb++)
     {
      cout << *itb;
      if(itb != --hpmp.end()) cout << ":";
      else cout << " [h:m:s]";
     }
   }
  cout << "\nKategória: " << kat; 
 }

void in_gr_ch::kiir()
 {
  sps = {swim,cycle,depo,swim+cycle+depo,run,getSum()};
  cout << "\nLicence: " << lic;
  for(it = sps.begin(), j_it = jelek.begin();\
      it != sps.end(); it++, j_it++)
   {
    hpmp.clear(); s_hms(*it);
    cout << "\n" << *j_it << " "; 
    for(auto itb = hpmp.begin(); itb != hpmp.end(); itb++)
     {
      cout << *itb;
      if(itb != --hpmp.end()) cout << ":";
      else cout << " [h:m:s]";
     }
   }
  cout << "\nKategória: " << kat; 
  cout << "\nNem: " << nem;
 }

tri_race& tri_race::setSum(int ij)
 { sum=swim+cycle+run+depo-ij; return *this; }

 void mind1(tri_race& x_tri)
 { x_tri.kiir(); cout << "\n" << endl; }
