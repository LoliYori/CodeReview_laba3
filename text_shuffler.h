#ifndef TEXT_SHUFFLER_H
#define TEXT_SHUFFLER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

/**
 * @brief ������������ ���� ��� ������� ������������ ���� � �����.
 */

 /**
  * ������� ��� ������������ ���� � ����� �� ��� ���, ���� ��� �� �������� � ��������.
  *
  * @param word �������� �����.
  * @return ���������� ������� ������������.
  */
int ShuffleWordUntilMatch(const std::string& word);

#endif // TEXT_SHUFFLER_H
