#include <math.h>

using namespace std;

vector<int> hpmp(3);
vector<int>::iterator ke; /* elemek címzése */

/* komparátor/predikátum (összehasonlító/tulajdonság hozzárendelő) függvény */
bool hasonlit(int i, int j) { return i>j; } 
bool szuro (int i) { 
    int n = i;
    if (n < 0) n *= (-1); 
    return ((n%2)==1); 
}
bool szuro2 (int i) { return ((i%2)==0 && i!=0); }