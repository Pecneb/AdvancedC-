#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <sstream>

typedef std::pair<size_t, std::string> IntStringPairs; /* count x word */
typedef std::vector<std::string> StringVector;
typedef std::unordered_map<std::string, size_t> UmapIntStringPairs; /* word x count */
typedef std::vector<IntStringPairs> VectorOfIntStringPairs; /* Vector storing IntStringPairs pairs (pair<size_t, std::string) */

std::vector<std::string> words(const std::string& sentence) {
	
	/* Waits a sentence or some string as input.
	 * It splits the sentence at spaces and
	 * produce a vector of words */

	StringVector wordVec;

	std::istringstream ss(sentence);

	std::string token; // a single word from the sentence

	while( std::getline( ss, token, ' ') ) wordVec.push_back(token);

	return wordVec;
}

UmapIntStringPairs count(StringVector v) { 

	/* Waits a vector of words as input.
	 * It counts how many times a word
	 * appears in the sentence and
	 * produces an unordered_map
	 * with pairs<string, size_t>. */

	UmapIntStringPairs ret;

	for (auto word : v) {

		/* if word not found in map, initialize a <key, value> pair with key = word, value = 1 */
		
		if (ret.find(word) == ret.end()) ret[word] = 1; 

		/* if word is found, increment the value by 1 */

		else ret[word]++;

	}

	return ret;
}

VectorOfIntStringPairs reverse(UmapIntStringPairs um) {

    /* Swap the key, value of unordered_map<std::string, size_t> um
     * and put them in a vector<pair<size_t, std::string>> */

	VectorOfIntStringPairs ret;

	for (auto k : um) {

        IntStringPairs p = std::make_pair(k.second, k.first);
        ret.push_back(p);

    }

    return ret;
}

VectorOfIntStringPairs sortVectorOfIntStringPairs(VectorOfIntStringPairs&& v) {

    /* Sorts the input vector<pair<size_t, std::string>> based on key to descending order. */

    VectorOfIntStringPairs ret(std::move(v));

    std::sort(ret.begin(), ret.end(), [](IntStringPairs paira, IntStringPairs pairb) -> bool { return paira.first > pairb.first; });

    return ret;
} 

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
