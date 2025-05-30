/*
 * �������: ���������� � �������������� ������ ��������������� ���������
 * ���������� �������� ��������� ��� �������� x
 * �������������� ����������� ���� A+x � x+A
 * ����� ������ � ����������, ����������� � ��������� ������ � ����������� ��������
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

// ���� ����� ������
enum class NodeType {
	OPERAND,
	VARIABLE,
	OPERATOR
};

// ��������� ���� ������
struct TreeNode {
	NodeType type;
	int value; // ��� ���������
	char op;   // ��� ����������
	TreeNode* left;
	TreeNode* right;

	TreeNode(NodeType t, int v, char o) : type(t), value(v), op(o), left(nullptr), right(nullptr) {}
};

// �������� �������
TreeNode* buildExpressionTree(const string& expression);
int evaluateExpressionTree(TreeNode* root, int x);
void transformTree(TreeNode* root);
void printPrefix(TreeNode* root, ofstream& out);
void printPostfix(TreeNode* root, ofstream& out);
void printInfixWithBrackets(TreeNode* root, ofstream& out);
void deleteTree(TreeNode* root);