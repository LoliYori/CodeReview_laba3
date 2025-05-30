/* Перестановка букв до совпадения с исходным словом */

#include "shuffle_word.h"

using namespace std;

int ShuffleUntilMatch(const string& original) {
	if (original.empty()) {
		throw invalid_argument("Слово не может быть пустым");
	}

	string current = original;
	int count = 0;

	random_device rd;
	mt19937 generator(rd());

	do {
		// Используем auto для итераторов, ожидаемый тип: std::string::iterator
		auto first = current.begin(); 
		auto last = current.end();
		shuffle(first, last, generator);

		cout << current << endl;
		++count;
	} while (current != original);

	return count;
}
