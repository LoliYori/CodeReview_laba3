#ifndef WORD_SHUFFLER_H
#define WORD_SHUFFLER_H

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

using namespace std;

/**
 * @brief Перемешивает буквы в слове до получения исходного слова
 * @param word Слово для перемешивания
 * @return Количество попыток до получения исходного слова
 * @throws invalid_argument если входная строка пуста
 */
int shuffleUntilOriginal(string& word);

#endif // WORD_SHUFFLER_H