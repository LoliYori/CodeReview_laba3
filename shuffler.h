/**
 * @file shuffler.h
 * @brief Заголовочный файл для функций перемешивания букв в слове
 */

#ifndef SHUFFLER_H
#define SHUFFLER_H

#include <string>

 /**
  * @brief Перемешивает буквы в слове случайным образом
  * @param word Слово для перемешивания
  * @return Перемешанное слово
  * @throws std::invalid_argument Если входная строка пуста
  */
std::string shuffleLetters(const std::string& word);

/**
 * @brief Выполняет перемешивание слова до совпадения с оригиналом
 * @param originalWord Исходное слово
 * @return Количество попыток до совпадения
 * @throws std::invalid_argument Если входная строка пуста
 */
int shuffleUntilMatch(const std::string& originalWord);

#endif // SHUFFLER_H