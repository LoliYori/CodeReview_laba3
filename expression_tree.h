/* Продолжение задания №ExpressionTree */

#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

/**
 * @brief Структура узла дерева выражения
 */
struct TreeNode {
	string value;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;

	explicit TreeNode(const string& val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief Класс ExpressionTree строит дерево из инфиксной записи
 */
class ExpressionTree {
public:
	/**
	 * @brief Построить дерево из инфиксного выражения
	 */
	static ExpressionTree BuildFromInfix(const string& infix);

	/**
	 * @brief Вычислить значение выражения при заданном x
	 */
	int Evaluate(int x);

	/**
	 * @brief Нормализовать выражение
	 */
	void Normalize();

	/**
	 * @brief Получить корень дерева
	 */
	shared_ptr<TreeNode> GetRoot() {
		return root;
	}

	/**
	 * @brief Вывести дерево в инфиксной форме
	 */
	void PrintInfix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief Вывести дерево в префиксной форме
	 */
	void PrintPrefix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief Вывести дерево в постфиксной форме
	 */
	void PrintPostfix(ostream& os, shared_ptr<TreeNode> node);

private:
	shared_ptr<TreeNode> root;

	static int EvaluateNode(shared_ptr<TreeNode> node, int x);
	static void NormalizeNode(shared_ptr<TreeNode>& node);
};

string ReadExpressionFromFile(const string& filename);
void WriteResultToFile(const string& filename, int result, ExpressionTree& tree);

#endif // EXPRESSION_TREE_H
