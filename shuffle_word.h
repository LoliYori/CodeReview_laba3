#ifndef SHUFFLE_WORD_H
#define SHUFFLE_WORD_H

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

using namespace std;

/**
 * @brief ������������ ����� ����� � ��������� ������� �� ���������� � ����������.
 * @param original �����, ������� ����� ����������.
 * @return ���������� ������� �� ����������.
 * @throws invalid_argument ���� ����� ������.
 */
int ShuffleUntilMatch(const string& original);

#endif // SHUFFLE_WORD_H
