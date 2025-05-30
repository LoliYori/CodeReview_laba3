/*
 * «адача: ѕерестановка букв в слове
 * ѕрограмма принимает слово, случайно переставл€ет буквы до тех пор,
 * пока не получитс€ исходное слово, подсчитывает количество попыток
 */

#include "word_shuffler.h"

int shuffleUntilOriginal(string& word) {
    if (word.empty()) {
        throw invalid_argument("Input word cannot be empty");
    }

    string original = word;
    string shuffled = word;
    int attempts = 0;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);

    cout << word << endl;

    do {
        shuffle(shuffled.begin(), shuffled.end(), generator);
        cout << shuffled << endl;
        attempts++;
    } while (shuffled != original);

    return attempts;
}