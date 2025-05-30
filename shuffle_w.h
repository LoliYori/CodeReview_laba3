#ifndef SHUFFLE_W_H
#define SHUFFLE_W_H

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
int ShuffleUntilMatchW(const string& original);

#endif // SHUFFLE_W_H
