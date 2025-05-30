/* Продолжение задания №Перестановка букв слова */

#include "text_shuffler.h"

int ShuffleWordUntilMatch(const std::string& word) {
    if (word.empty()) {
        throw std::invalid_argument("Ошибка: введено пустое слово.");
    }

    std::string shuffledWord = word;
    int attempts = 0;
    std::srand(std::time(0));

    do {
        std::random_shuffle(shuffledWord.begin(), shuffledWord.end());
        std::cout << shuffledWord << std::endl;
        attempts++;
    } while (shuffledWord != word);

    return attempts;
}
