#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>
#include <sstream>

typedef std::pair<std::string, size_t> NumOfWord; // The count of the word.
typedef std::vector<std::string> StringVector;
typedef std::unordered_map<std::string, size_t> UmapNumOfWord;
typedef std::vector<NumOfWord>  NumOfWordVector;

std::vector<std::string> words(const std::string& sentence) {

  StringVector wordVec;

  std::istringstream ss(sentence);

  std::string token;

  while( std::getline( ss, token, ' ') ) wordVec.push_back(token);

  return wordVec;
}

UmapNumOfWord count(StringVector v) { 

  // Every every word in the sentence gets a number, how many times it is in the sentence.

  UmapNumOfWord ret;

  for (auto i : v) {

    if (ret.find(i) == ret.end()) ret[i] = 1;

    else ret[i]++;

  }

  return ret;
}

//TODO: reverse() function
//TODO: sortVectorOfIntStringPairs() function

// Elvart kimenet:
// 3: very
// 2: this
// 2: string
// 1: short
// 1: is
// 1: a
// 1: one!

int main() {

  VectorOfIntStringPairs voisp = sortVectorOfIntStringPairs( reverse( count( words("this string is a very very very short string this one!"))));

  for (auto& v : voisp) {

    std::cout << v.first << ": " << v.second << std::endl;

  }

  return 0;
}
