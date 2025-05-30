/* Перестановка букв до совпадения с исходным словом */

#include "shuffle_w.h"

int ShuffleUntilMatchW(const string& original) {
	if (original.empty()) {
		cerr << "Ошибка: Слово не может быть пустым." << endl;
		return -1;
	}

	string current = original;
	int count = 0;

	random_device rd;
	mt19937 generator(rd());

	do {
		// Используем auto для итераторов, ожидаемый тип: std::string::iterator
		auto first = current.begin();  // std::string::iterator
		auto last = current.end();    // std::string::iterator
		shuffle(first, last, generator);

		cout << current << endl;
		++count;
	} while (current != original);

	return count;
}

