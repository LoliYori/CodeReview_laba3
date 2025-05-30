#include "expression_parser.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    try {
        // Чтение входного файла
        ifstream in("FN1.txt");
        if (!in) {
            cerr << "Cannot open input file FN1.txt" << endl;
            return 1;
        }

        string expression;
        getline(in, expression);
        in.close();

        // Удаление начальных/конечных пробелов
        expression.erase(0, expression.find_first_not_of(" \t\n\r\f\v"));
        expression.erase(expression.find_last_not_of(" \t\n\r\f\v") + 1);

        if (expression.empty()) {
            cerr << "Error: Empty expression in FN1.txt" << endl;
            return 1;
        }

        cout << "Parsing expression: " << expression << endl;

        // Чтение значения x
        int x;
        cout << "Enter value for x: ";
        if (!(cin >> x)) {
            cerr << "Invalid input for x" << endl;
            return 1;
        }

        // Парсинг и вычисление выражения
        ExpressionParser parser(expression);
        parser.parse();

        cout << "Evaluation result: " << parser.evaluate(x) << endl;

        // Преобразование дерева
        parser.transform();

        // Вывод результатов
        parser.printResults("FN2.txt", x);

        cout << "Results successfully written to FN2.txt" << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}