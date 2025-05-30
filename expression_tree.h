/* ����������� ������� �ExpressionTree */

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
 * @brief ��������� ���� ������ ���������
 */
struct TreeNode {
	string value;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;

	explicit TreeNode(const string& val) : value(val), left(nullptr), right(nullptr) {}
};

/**
 * @brief ����� ExpressionTree ������ ������ �� ��������� ������
 */
class ExpressionTree {
public:
	/**
	 * @brief ��������� ������ �� ���������� ���������
	 */
	static ExpressionTree BuildFromInfix(const string& infix);

	/**
	 * @brief ��������� �������� ��������� ��� �������� x
	 */
	int Evaluate(int x);

	/**
	 * @brief ������������� ���������
	 */
	void Normalize();

	/**
	 * @brief �������� ������ ������
	 */
	shared_ptr<TreeNode> GetRoot() {
		return root;
	}

	/**
	 * @brief ������� ������ � ��������� �����
	 */
	void PrintInfix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief ������� ������ � ���������� �����
	 */
	void PrintPrefix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief ������� ������ � ����������� �����
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
