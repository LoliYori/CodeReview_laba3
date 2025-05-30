#ifndef SHUFFLE_WORD_H
#define SHUFFLE_WORD_H

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>

using namespace std;

/**
 * @brief Перемешивает буквы слова в случайном порядке до совпадения с оригиналом.
 * @param original Слово, которое будет перемешано.
 * @return Количество попыток до совпадения.
 * @throws invalid_argument если слово пустое.
 */
int ShuffleUntilMatch(const string& original);

#endif // SHUFFLE_WORD_H
