#include <iostream>
#include <ostream>
#include <typeinfo>
#include "Decl.hpp"

void tri_race::kiir() const
 {
  cout << "\nLicence: " << lic << "\nÚ: " << swim << "\nB: " << cycle << "\nF: " << run \
       << "\nD: " << depo;
  cout << "\nCél idő: " << h << ":" << p << ":" << mp  << " [h:m:s]";
 }

 void in_ch::kiir() const
 {
  cout << "\nLicence: " << lic << "\nÚ: " << swim << "\nB: " << cycle << "\nD: " << depo \
       << "\nÚ+B+D: " << swim+cycle+depo << "\nF: " << run;
  cout << "\nCél idő: " << h << ":" << p << ":" << mp  << " [h:m:s]";
  cout << "\nKategória: " << kat;
 }
 
 void in_gr_ch::kiir() const
 {
  cout << "\nLicence: " << lic << "\nÚ: " << swim << "\nB: " << cycle << "\nD: " << depo \
       << "\nÚ+B+D: " << swim+cycle+depo << "\nF: " << run;
  cout << "\nCél idő: " << h << ":" << p << ":" << mp  << " [h:m:s]";
  cout << "\nKategória: " << kat;
  cout << "\nNem: " << nem;
 }

tri_race& tri_race::setSum(int ij)
 {
  sum=swim+cycle+run+depo-ij;
  h=sum/oRA; p=(sum%oRA)/pRC; mp=(sum%oRA)%pRC;
  return *this;
 }
 
//  void mind(tri_race& A_tri, tri_race& B_tri, tri_race& C_tri)
//  {
//   A_tri.kiir(); B_tri.kiir(); C_tri.kiir();
//   cout << "\n" << endl;
//  }
 
 void mind1(tri_race& x_tri)
 {
  x_tri.kiir();
  try {
     //   in_ch& rp = dynamic_cast<in_ch&>(x_tri);
     //   cout << "\nGyerek objektum vagyok: " << rp.getLic() << endl;
       in_ch& rp = dynamic_cast<in_gr_ch&>(x_tri);
       cout << "\nUnoka objektum vagyok: " << rp.getLic() << endl;
  } catch(bad_cast) {
       cout << "\nNem vagyok gyerek objektum!" << endl;
       cout << "\nNem vagyok unoka objektum!" << endl;
       try {
         in_ch& rp = dynamic_cast<in_gr_ch&>(x_tri);
         cout << "\n Gyerek objektum vagyok: " << rp.getLic() << endl;
       } catch (bad_cast) {
         cout << "\nNem vagyok gyerek objektum!" << endl;
         tri_race& rp = dynamic_cast<tri_race&>(x_tri);
         cout << "\nSzülő objektum vagyok: " << rp.getLic() << endl; 
       }
  }
  cout << "\n" << endl;
 } 
 
int main(void)
 {
  tri_race A_tri('A',1200,4200,2300,123), B_tri('B',1300,4300,2400,125),\
           C_tri('C',1400,4400,2400,130); /* Objektumok példányosítása, beállítása */
  A_tri.setSum(0); B_tri.setSum(0); C_tri.setSum(120);
  // mind(A_tri,B_tri,C_tri);
  in_ch D_tri('D',1450,4400,2400,130,5); D_tri.setSum(0);
  D_tri.kiir(); cout << "\n" << endl;
  /* D_tri.tri_race::kiir(); cout << "\n" << endl; Altalaban, ezt igy nem hasznaljuk, ez csak bemutatas */ 
  /* C_tri.in_ch::kiir(); */
  in_gr_ch E_tri('E',1450,4400,2300,120,4,'F'); E_tri.setSum(180);
  E_tri.kiir(); cout << "\n" << endl;
  mind1(A_tri); mind1(B_tri); mind1(C_tri);
  mind1(D_tri);
  mind1(E_tri);
  return 0;
}
