/**
 * @file shuffler.h
 * @brief ������������ ���� ��� ������� ������������� ���� � �����
 */

#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <string>

 /**
  * @brief ������������ ����� � ����� ��������� �������
  * @param word ����� ��� �������������
  * @return ������������ �����
  * @throws std::invalid_argument ���� ������� ������ �����
  */
std::string shuffleLetters(const std::string& word);

/**
 * @brief ��������� ������������� ����� �� ���������� � ����������
 * @param originalWord �������� �����
 * @return ���������� ������� �� ����������
 * @throws std::invalid_argument ���� ������� ������ �����
 */
int shuffleUntilMatch(const std::string& originalWord);

#endif // SHUFFLER_H