/* Продолжение задания №1 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cctype>

namespace ExpressionTree {

    class Node {
    public:
        char value;
        Node* left;
        Node* right;

        Node(char val) : value(val), left(nullptr), right(nullptr) {}
    };

    class ExpressionTree {
    public:
        ExpressionTree(const std::string& expression);
        ~ExpressionTree();

        void evaluate(int x_value, const std::string& output_file);
        void transform();
        void printTree(const std::string& output_file);

    private:
        Node* root;

        Node* buildTree(const std::string& expression, int& index);
        int precedence(char op);
        int applyOp(int a, int b, char op);
        int evaluateTree(Node* node, int x_value);
        void printPrefix(Node* node, std::ofstream& file);
        void printPostfix(Node* node, std::ofstream& file);
        void printInfix(Node* node, std::ofstream& file);
        void deleteTree(Node* node);
        void transformTree(Node*& node);
    };

} // namespace ExpressionTree
