/* Продолжение задания №1 */

//#include "expression_treeM.h"
//
//int main() {
//    std::string input_file = "FN1.txt";
//    std::string output_file = "FN2.txt";
//    std::ifstream file(input_file);
//    if (!file.is_open()) {
//        std::cerr << "Could not open input file." << std::endl;
//        return 1;
//    }
//
//    std::string expression;
//    std::getline(file, expression);
//    file.close();
//
//    int x_value;
//    std::cout << "Enter the value of x: ";
//    std::cin >> x_value;
//
//    ExpressionTree::ExpressionTree tree(expression);
//    tree.evaluate(x_value, output_file);
//    tree.transform();
//    tree.printTree(output_file);
//
//    return 0;
//}
