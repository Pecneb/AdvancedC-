#include <iostream>
#include <chrono>
#include <string>
#include <functional>

using namespace std;

/* Jobb oldali referencia ertelme, lenyege peldaval. 
 * A move() jobb oldali referenciat csinal a beadott valtozobol,
 * igy ezzel azt jelzi a forditonak, hogy arra a valtozonak
 * a memoriateruletere mar nem lesz szukseg es elveheti a masik valtozo */

void swap1(string& a, string& b) {
  /* csere move() fuggveny nelkul */
  string temp{ a };
  a = b;
  b = temp;
}

void swap2(string& a, string& b) {
  /* swap move()-val, ez a fv. azt teszi lehetove, 
   * hogy b-t temp-be nem kell atmasolnia a gepnek,
   * hanem csak atveszi a memoria teruletet */
  string temp{ move(b) };
  b = move(a);
  a = move(temp);
}

void printTest(string& a, string& b) {
  cout << a << "\t" << b << "\n";
}

int main() {
  string a{"Nice Cock!"};
  string b{"Thank you very much!"};
  string words[] = {a,b};
  size_t wordCount = 2;
  printTest(a, b);
  swap1(a, b);
  printTest(a, b);
  swap2(a,b);
  printTest(a, b);
  return 0;
}
