#include "expression_treeD.h"

//int main() {
//	try {
//		// Чтение входных данных
//		ifstream fin("FN1.txt");
//		ofstream fout("FN2.txt");
//
//		if (!fin.is_open()) {
//			throw runtime_error("Cannot open input file FN1.txt");
//		}
//		if (!fout.is_open()) {
//			throw runtime_error("Cannot open output file FN2.txt");
//		}
//
//		string expression;
//		int x;
//
//		getline(fin, expression);
//		fin >> x;
//		fin.close();
//
//		// Построение дерева выражения
//		TreeNode* root = buildExpressionTree(expression);
//
//		// Вычисление значения выражения
//		int result = evaluateExpressionTree(root, x);
//		fout << "Result: " << result << endl << endl;
//
//		// Преобразование дерева
//		transformTree(root);
//
//		// Вывод преобразованного дерева
//		fout << "Prefix notation: ";
//		printPrefix(root, fout);
//		fout << endl << endl;
//
//		fout << "Postfix notation: ";
//		printPostfix(root, fout);
//		fout << endl << endl;
//
//		fout << "Infix notation with brackets: ";
//		printInfixWithBrackets(root, fout);
//		fout << endl;
//
//		// Освобождение памяти
//		deleteTree(root);
//		fout.close();
//	}
//	catch (const exception& e) {
//		cerr << "Error: " << e.what() << endl;
//		return 1;
//	}
//
//	return 0;
//}