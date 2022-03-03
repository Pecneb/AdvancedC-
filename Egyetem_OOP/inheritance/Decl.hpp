using namespace std;

class tri_race /* szülő osztály deklarációja */
 {
   protected:
    char lic;
    int swim, cycle, run, depo, h, p, mp;
   private:
    int sum;
    const int oRA, pRC;
   public:
    tri_race() : oRA(3600), pRC(60) /* Alapértelmezett konstruktor */
      { lic='-'; swim=0; cycle=0; run=0; depo=0; }  
    tri_race(char lc, int sw, int cyc, int rn, int dp) : oRA(3600), pRC(60) /* Alapérték beállító konstruktor */
     { 
      lic=lc; swim=sw; cycle=cyc; run=rn; depo=dp;
      cout << "\nA paraméteres objektum létrejött";
     } 
    char getLic() {return lic;}
   virtual void kiir() const ; 
	 tri_race& setSum(int ij);
   virtual ~tri_race()
    { cout << "\nTöröltem a szülő objektumot!"; }
    tri_race(const tri_race&) = delete;
    tri_race& operator=(const tri_race&) = delete;
 };
	
class in_ch : public tri_race /* származtatott gyerek osztály deklarációja */
 {
   protected:
    int kat;
   public:
    in_ch() : tri_race() { kat=0; }
    in_ch(char lc, int sw, int cyc, int rn, int dp, int kt) : tri_race(lc, sw, cyc, rn, dp) { kat=kt; }
    void kiir() const ;
    ~in_ch()
    { cout << "\nTöröltem a gyerek-objektum saját adatait!"; }
    in_ch(const in_ch&) = delete;
    in_ch& operator=(const in_ch&) = delete;
 };
 
 class in_gr_ch : public in_ch /* származtatott unoka osztály deklarációja */
 {
   private:
    char nem;
   public:
    in_gr_ch() : in_ch(), nem('N') {  }
    in_gr_ch(char lc, int sw, int cyc, int rn, int dp, int kt, char nm) : \
           in_ch(lc, sw, cyc, rn, dp, kt), nem(nm) {  }
    void kiir() const ;
    ~in_gr_ch()
    { cout << "\nTöröltem az unoka-objektum saját adatait!"; }
    in_gr_ch(const in_gr_ch&) = delete;
    in_gr_ch& operator=(const in_gr_ch&) = delete;
 }; 
