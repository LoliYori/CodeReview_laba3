/*
 * Ввести с клавиатуры любое слово. Используя генерацию случайных чисел, переставить
 * буквы этого слова в случайном порядке. Делать это до тех пор, пока полученное слово не совпадёт
 * с начальным словом. Выводить слово после каждой перестановки и посчитать общее количество
 * выведенных слов (не считая исходного). Пример выполнения программы:
 * Введите слово: корова
 * воакро
 * вокроа
 * ароовк
 * краоов
 * крваоо
 * оокавр
 * ооквра
 * вкраоо
 * корова
 * 9 попыток
 */

//#include "shuffle_word.h"
//
//using namespace std;
//
//int main2() {
//	string word;
//	cout << "Enter a word: ";
//	cin >> word;
//
//	if (word.empty()) {
//		cerr << "Error: Empty word entered." << endl;
//		return 1;
//	}
//
//	try {
//		int attempts = ShuffleUntilMatch(word);
//		cout << attempts << " try" << endl;
//	}
//	catch (const invalid_argument& e) {
//		cerr << "Error: " << e.what() << endl;
//		return 1;
//	}
//
//	return 0;
//}
