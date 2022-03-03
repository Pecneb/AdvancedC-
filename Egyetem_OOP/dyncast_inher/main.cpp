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
 
int main(void)
 {
  in_ch A_tri('A',1200,4200,2300,123,1), B_tri('B',1300,4300,2400,125,2),\
           C_tri('C',1400,4400,2400,130,3); /* Objektumok példányosítása, beállítása */
  A_tri.setSum(0); B_tri.setSum(0); C_tri.setSum(120);
  in_ch D_tri('D',1450,4400,2400,130,5); D_tri.setSum(0);
  in_gr_ch E_tri('E',1450,4400,2300,120,4,'F'); E_tri.setSum(180);
  mind1(A_tri); mind1(B_tri); mind1(C_tri);
  mind1(D_tri);
  mind1(E_tri);
  return 0;
}