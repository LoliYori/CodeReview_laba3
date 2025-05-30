/* ������������ ���� �� ���������� � �������� ������ */

#include "shuffle_w.h"

int ShuffleUntilMatchW(const string& original) {
	if (original.empty()) {
		cerr << "������: ����� �� ����� ���� ������." << endl;
		return -1;
	}

	string current = original;
	int count = 0;

	random_device rd;
	mt19937 generator(rd());

	do {
		// ���������� auto ��� ����������, ��������� ���: std::string::iterator
		auto first = current.begin();  // std::string::iterator
		auto last = current.end();    // std::string::iterator
		shuffle(first, last, generator);

		cout << current << endl;
		++count;
	} while (current != original);

	return count;
}

