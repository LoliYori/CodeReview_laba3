#ifndef TEXT_SHUFFLER_H
#define TEXT_SHUFFLER_H

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

/**
 * @brief Заголовочный файл для функции перестановки букв в слове.
 */

 /**
  * Функция для перестановки букв в слове до тех пор, пока оно не совпадет с исходным.
  *
  * @param word Исходное слово.
  * @return Количество попыток перестановки.
  */
int ShuffleWordUntilMatch(const std::string& word);

#endif // TEXT_SHUFFLER_H
