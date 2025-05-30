/* ����������� ������� 2 */
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
 * @brief ��������� ���� ������ ���������
 * value - �������� (����� ��� ��������)
 * left - ����� ���������
 * right - ������ ���������
 */
struct TreeNode {
	string value;
	shared_ptr<TreeNode> left;
	shared_ptr<TreeNode> right;

	explicit TreeNode(const string& val);
};

/**
 * @brief ����� ExpressionTree ������ ������ �� ��������� ������
 */
class ExpressionTree {
public:
	/**
	 * @brief ��������� ������ �� ���������� ���������
	 * @param infix ������ � ����������
	 * @return ��������� ExpressionTree
	 */
	static ExpressionTree BuildFromInfix(const string& infix);

	/**
	 * @brief ��������� �������� ��������� ��� �������� x
	 * @param x �������� ���������� x
	 * @return ��������� ����������
	 */
	int Evaluate(int x);

	/**
	 * @brief ������������� ��������� (��������� ������)
	 */
	void Normalize();

	/**
	 * @brief �������� ������ ������
	 * @return shared_ptr �� ������
	 */
	shared_ptr<TreeNode> GetRoot();

	/**
	 * @brief ������� ������ � ��������� �����
	 * @param os ����� ������
	 * @param node ���� ������
	 */
	void PrintInfix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief ������� ������ � ���������� �����
	 * @param os ����� ������
	 * @param node ���� ������
	 */
	void PrintPrefix(ostream& os, shared_ptr<TreeNode> node);

	/**
	 * @brief ������� ������ � ����������� �����
	 * @param os ����� ������
	 * @param node ���� ������
	 */
	void PrintPostfix(ostream& os, shared_ptr<TreeNode> node);

private:
	shared_ptr<TreeNode> root;

	static int EvaluateNode(shared_ptr<TreeNode> node, int x);
	static void NormalizeNode(shared_ptr<TreeNode>& node);
};

/**
 * @brief ��������� ��������� �� �����
 * @param filename ��� �����
 * @return ������ � ����������
 */
string ReadExpressionFromFile(const string& filename);

/**
 * @brief ���������� ��������� � ������ ��������� � ����
 * @param filename ��� �����
 * @param result ��������� ����������
 * @param tree ������ ������ ���������
 */
void WriteResultToFile(const string& filename, int result, ExpressionTree& tree);

#endif  // EXPRESSION_TREE_H
