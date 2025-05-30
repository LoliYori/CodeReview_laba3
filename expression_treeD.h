/*
 * Задание: Построение и преобразование дерева арифметического выражения
 * Вычисление значения выражения при заданном x
 * Преобразование поддеревьев вида A+x в x+A
 * Вывод дерева в префиксной, постфиксной и инфиксной формах с избыточными скобками
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <stdexcept>
#include <cmath>

using namespace std;

// Типы узлов дерева
enum class NodeType {
	OPERAND,
	VARIABLE,
	OPERATOR
};

// Структура узла дерева
struct TreeNode {
	NodeType type;
	int value; // Для операндов
	char op;   // Для операторов
	TreeNode* left;
	TreeNode* right;

	TreeNode(NodeType t, int v, char o) : type(t), value(v), op(o), left(nullptr), right(nullptr) {}
};

// Основные функции
TreeNode* buildExpressionTree(const string& expression);
int evaluateExpressionTree(TreeNode* root, int x);
void transformTree(TreeNode* root);
void printPrefix(TreeNode* root, ofstream& out);
void printPostfix(TreeNode* root, ofstream& out);
void printInfixWithBrackets(TreeNode* root, ofstream& out);
void deleteTree(TreeNode* root);