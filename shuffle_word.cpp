/* ������������ ���� �� ���������� � �������� ������ */

#include "shuffle_word.h"

using namespace std;

int ShuffleUntilMatch(const string& original) {
	if (original.empty()) {
		throw invalid_argument("����� �� ����� ���� ������");
	}

	string current = original;
	int count = 0;

	random_device rd;
	mt19937 generator(rd());

	do {
		// ���������� auto ��� ����������, ��������� ���: std::string::iterator
		auto first = current.begin(); 
		auto last = current.end();
		shuffle(first, last, generator);

		cout << current << endl;
		++count;
	} while (current != original);

	return count;
}
