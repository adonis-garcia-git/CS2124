/*
  words.cpp
  Sec A
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Word {
    string name;
    vector<int> positions;
};

size_t findWord(const vector<Word>& words, const string& name) {
    for (size_t index = 0; index < words.size(); ++index) {
	if (words[index].name == name) {
	    return index;
	}
    }
    return words.size();
}


int main() {

    ifstream textStream("jabberwocky");
    if (!textStream) {
	cerr << "failed to open jabberwocky\n";
	exit(1);
    }

    vector<Word> words;

    string name;
    int pos = 0;

    while (textStream >> name) {
	// find out if we have already seen name
	size_t index = findWord(words, name);

	// if we haven't, then add another Word object onto words
	if (index == words.size()) {
	    Word aWord;
	    aWord.name = name;
	    aWord.positions.push_back(pos);
	    words.push_back(aWord);

	}

	// else, we have seen it, add the position onto that Word object
	else {
	    words[index].positions.push_back(pos);
	}
	++pos;
    }
    textStream.close();
}
