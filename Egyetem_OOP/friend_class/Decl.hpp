#pragma once
#include <iostream>
#include <vector>

using namespace std;

class barat;

class tri_race /* szülő */
 {
   protected:
    char lic;
    int swim, cycle, run, depo;
   private:
    int sum;
   public:
    tri_race() { lic='-'; swim=0; cycle=0; run=0; depo=0; }  
    tri_race(char lc, int sw, int cyc, int rn, int dp) 
     { lic=lc; swim=sw; cycle=cyc; run=rn; depo=dp;
      cout << "\nA paraméteres objektum létrejött"; } 
   virtual void kiir() =0; 
   int getSum() const { return sum; }
	 tri_race& setSum(int ij);
   virtual ~tri_race() { cout << "\nTöröltem a szülő osztályt!"; }
	 tri_race(const tri_race&) = delete;
   tri_race& operator=(const tri_race&) = delete;
   friend class barat;
	};

class h_m_s  /* átszámoló */
 {
  protected:
  vector<int> hpmp;
  vector<int> sps;
  vector<string> jelek = {"Ú:","B:","D:","Ú+B+D:","F:","Cél idő:"};
  vector<int>::iterator it;
  vector<string>::iterator j_it;
  const int oRA, pRC;
  h_m_s() : oRA(3600),pRC(60) { }
  void s_hms(int s)
   { hpmp.push_back(s/oRA); hpmp.push_back((s%oRA)/pRC);
     hpmp.push_back((s%oRA)%pRC); }
  ~h_m_s() { cout << "\nTöröltem az átszámoló osztályt!"; }
 };

class in_ch : public tri_race, protected h_m_s    /* gyerek */
 {
  protected:
   int kat;
  public:
   in_ch() : tri_race() { kat=0; }
   in_ch(char lc, int sw, int cyc, int rn, int dp, int kt) : \
          tri_race(lc, sw, cyc, rn, dp) { kat=kt; }
   void kiir();
   ~in_ch() { cout << "\nTöröltem a gyerek-objektum saját adatait!"; }
   friend class barat;
 };
 
class barat  /* barát osztály */
 {
  public:
   barat() { }
  void olvas(in_ch& X_Tri)
   { 
    cout << "\nLicence: " << X_Tri.lic << "\nKategória: " << X_Tri.kat << "\n";
    //cout << "Cél idő: " << X_Tri.sum << "\n";
    //X_Tri.lic='Z'; X_Tri.kat=10; //X_Tri.sum=10000;
    //cout << "\nLicence: " << X_Tri.lic << "\nKategória: " << X_Tri.kat << "\n";
    //cout << "Cél idő: " << X_Tri.sum << "\n";
   }
  ~barat() { cout << "\nTöröltem a barát osztályt!"; }
 };

class in_gr_ch : public in_ch  /* unoka */
 {
  private:
   char nem;
  public:
   in_gr_ch() : in_ch(), nem('N') {  }
   in_gr_ch(char lc, int sw, int cyc, int rn, int dp, int kt, char nm)\
             : in_ch(lc, sw, cyc, rn, dp, kt), nem(nm) {  }
   void kiir();
   ~in_gr_ch() { cout << "\nTöröltem az unoka-objektum saját adatait!"; }
 };

void mind1(tri_race& x_tri);