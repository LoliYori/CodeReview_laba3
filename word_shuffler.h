#ifndef WORD_SHUFFLER_H
#define WORD_SHUFFLER_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

using namespace std;

/**
 * @brief ������������ ����� � ����� �� ��������� ��������� �����
 * @param word ����� ��� �������������
 * @return ���������� ������� �� ��������� ��������� �����
 * @throws invalid_argument ���� ������� ������ �����
 */
int shuffleUntilOriginal(string& word);

#endif // WORD_SHUFFLER_H