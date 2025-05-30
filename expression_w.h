/* Продолжение задания 2 */
#ifndef EXPRESSION_W_H
#define EXPRESSION_W_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Структура узла дерева выражения
 * value - значение (число или оператор)
 * left - левое поддерево
 * right - правое поддерево
 */
struct TreeNode {
	string value;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;

	explicit TreeNode(const string& val);
};

/**
 * @brief Класс ExpressionTree строит дерево из инфиксной записи
 */
class ExpressionTree {
public:
	/**
	 * @brief Построить дерево из инфиксного выражения
	 * @param infix строка с выражением
	 * @return экземпляр ExpressionTree
	 */
	static ExpressionTree BuildFromInfix(const string& infix);

	/**
	 * @brief Вычислить значение выражения при заданном x
	 * @param x значение переменной x
	 * @return результат вычисления
	 */
	int Evaluate(int x);

	/**
	 * @brief Нормализовать выражение (упростить дерево)
	 */
	void Normalize();

	/**
	 * @brief Получить корень дерева
	 * @return shared_ptr на корень
	 */
	shared_ptr<TreeNode> GetRoot();

	/**
	 * @brief Вывести дерево в инфиксной форме
	 * @param os поток вывода
	 * @param node узел дерева
	 */
	void PrintInfix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief Вывести дерево в префиксной форме
	 * @param os поток вывода
	 * @param node узел дерева
	 */
	void PrintPrefix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief Вывести дерево в постфиксной форме
	 * @param os поток вывода
	 * @param node узел дерева
	 */
	void PrintPostfix(ostream& os, shared_ptr<TreeNode> node);

private:
	shared_ptr<TreeNode> root;

	static int EvaluateNode(shared_ptr<TreeNode> node, int x);
	static void NormalizeNode(shared_ptr<TreeNode>& node);
};

/**
 * @brief Считывает выражение из файла
 * @param filename имя файла
 * @return строка с выражением
 */
string ReadExpressionFromFile(const string& filename);

/**
 * @brief Записывает результат и дерево выражения в файл
 * @param filename имя файла
 * @param result результат вычисления
 * @param tree объект дерева выражения
 */
void WriteResultToFile(const string& filename, int result, ExpressionTree& tree);

#endif  // EXPRESSION_TREE_H
