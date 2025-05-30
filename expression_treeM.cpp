/* Продолжение задания №1 */

#include "expression_treeM.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <cctype>

namespace ExpressionTree {

    ExpressionTree::ExpressionTree(const std::string& expression) {
        int index = 0;
        root = buildTree(expression, index);
    }

    ExpressionTree::~ExpressionTree() {
        deleteTree(root);
    }

    void ExpressionTree::evaluate(int x_value, const std::string& output_file) {
        std::ofstream file(output_file);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open output file.");
        }

        int result = evaluateTree(root, x_value);
        file << result << std::endl;
    }

    int ExpressionTree::evaluateTree(Node* node, int x_value) {
        if (!node) return 0;
        if (std::isdigit(node->value)) return node->value - '0';
        if (node->value == 'x') return x_value;

        int left_val = evaluateTree(node->left, x_value);
        int right_val = evaluateTree(node->right, x_value);
        return applyOp(left_val, right_val, node->value);
    }

    void ExpressionTree::transform() {
        transformTree(root);
    }

    void ExpressionTree::printTree(const std::string& output_file) {
        std::ofstream file(output_file, std::ios_base::app);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open output file.");
        }

        file << "Prefix: ";
        printPrefix(root, file);
        file << "\nPostfix: ";
        printPostfix(root, file);
        file << "\nInfix: ";
        printInfix(root, file);
        file << std::endl;
    }

    Node* ExpressionTree::buildTree(const std::string& expression, int& index) {
        if (index >= expression.size()) return nullptr;

        std::stack<Node*> stack;
        while (index < expression.size()) {
            if (expression[index] == ' ') {
                index++;
                continue;
            }

            if (std::isdigit(expression[index]) || expression[index] == 'x') {
                stack.push(new Node(expression[index++]));
            }
            else {
                Node* node = new Node(expression[index]);
                node->right = stack.top();
                stack.pop();
                node->left = stack.top();
                stack.pop();
                stack.push(node);
                index++;
            }
        }

        return stack.top();
    }

    int ExpressionTree::precedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '%') return 2;
        if (op == '^') return 3;
        return 0;
    }

    int ExpressionTree::applyOp(int a, int b, char op) {
        switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero.");
            return a / b;
        case '%':
            if (b == 0) throw std::runtime_error("Modulo by zero.");
            return a % b;
        case '^': return static_cast<int>(std::pow(a, b));
        default: throw std::runtime_error("Invalid operator.");
        }
    }

    void ExpressionTree::printPrefix(Node* node, std::ofstream& file) {
        if (!node) return;
        file << node->value;
        printPrefix(node->left, file);
        printPrefix(node->right, file);
    }

    void ExpressionTree::printPostfix(Node* node, std::ofstream& file) {
        if (!node) return;
        printPostfix(node->left, file);
        printPostfix(node->right, file);
        file << node->value;
    }

    void ExpressionTree::printInfix(Node* node, std::ofstream& file) {
        if (!node) return;
        if (std::isdigit(node->value) || node->value == 'x') {
            file << node->value;
            return;
        }
        file << "(";
        printInfix(node->left, file);
        file << node->value;
        printInfix(node->right, file);
        file << ")";
    }

    void ExpressionTree::deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void ExpressionTree::transformTree(Node*& node) {
        if (!node || !node->left || !node->right) return;

        transformTree(node->left);
        transformTree(node->right);

        if (node->value == '+' && node->right->value == 'x') {
            Node* temp = node->left;
            node->left = node->right;
            node->right = temp;
        }
    }

} // namespace ExpressionTree
