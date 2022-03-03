#include "Decl.hpp"

int main(void)
 {
  in_ch A_tri('A',1200,4200,2300,123,1), B_tri('B',1300,4300,2400,125,2),\
           C_tri('C',1400,4400,2400,130,3); 
  A_tri.setSum(0); B_tri.setSum(0); C_tri.setSum(120);
  in_ch D_tri('D',1450,4400,2400,130,5); D_tri.setSum(0);
  in_gr_ch E_tri('E',1450,4400,2300,120,4,'F'); E_tri.setSum(180);
  mind1(A_tri); mind1(B_tri); mind1(C_tri); mind1(D_tri); mind1(E_tri);
  barat b;
  b.olvas(A_tri);
  return 0;
}