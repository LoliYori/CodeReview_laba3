/* ����������� ������� �ExpressionTree */

//#include "expression_tree.h"
//
//using namespace std;
//
//int main() {
//	try {
//		const string input_file = "FN1";
//		const string output_file = "FN2";
//
//		string expression = ReadExpressionFromFile(input_file);
//		ExpressionTree tree = ExpressionTree::BuildFromInfix(expression);
//
//		int x_value;
//		cout << "������� �������� x: ";
//		cin >> x_value;
//
//		int result = tree.Evaluate(x_value);
//		WriteResultToFile(output_file, result, tree);
//
//		cout << "��������� ������� � ���� " << output_file << endl;
//	}
//	catch (const exception& e) {
//		cerr << "������: " << e.what() << endl;
//		return 1;
//	}
//
//	return 0;
//}
