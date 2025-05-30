#include "expression_treeD.h"

// Проверка, является ли символ оператором
bool isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// Получение приоритета оператора
int getPriority(char op) {
	if (op == '^') return 4;
	if (op == '*' || op == '/' || op == '%') return 3;
	if (op == '+' || op == '-') return 2;
	return 0;
}

// Проверка, является ли подстрока числом
bool isNumber(const string& s) {
	if (s.empty()) return false;
	for (char c : s) {
		if (!isdigit(c)) return false;
	}
	return true;
}

// Преобразование выражения в постфиксную форму (ОПН)
vector<string> infixToPostfix(const string& expression) {
	vector<string> postfix;
	stack<char> operators;

	for (size_t i = 0; i < expression.size(); ) {
		if (isspace(expression[i])) {
			i++;
			continue;
		}

		if (expression[i] == '(') {
			operators.push(expression[i]);
			i++;
		}
		else if (expression[i] == ')') {
			while (!operators.empty() && operators.top() != '(') {
				postfix.push_back(string(1, operators.top()));
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
			i++;
		}
		else if (isOperator(expression[i])) {
			while (!operators.empty() && getPriority(operators.top()) >= getPriority(expression[i])) {
				postfix.push_back(string(1, operators.top()));
				operators.pop();
			}
			operators.push(expression[i]);
			i++;
		}
		else {
			// Обработка чисел и переменной x
			if (expression[i] == 'x') {
				postfix.push_back("x");
				i++;
			}
			else if (isdigit(expression[i])) {
				string num;
				while (i < expression.size() && isdigit(expression[i])) {
					num += expression[i];
					i++;
				}
				// Проверка на допустимый диапазон [1; 30]
				int value = stoi(num);
				if (value < 1 || value > 30) {
					throw invalid_argument("Operand value " + num + " is out of range [1; 30]");
				}
				postfix.push_back(num);
			}
			else {
				throw invalid_argument("Invalid character in expression: " + string(1, expression[i]));
			}
		}
	}

	while (!operators.empty()) {
		postfix.push_back(string(1, operators.top()));
		operators.pop();
	}

	return postfix;
}

// Построение дерева выражения из постфиксной формы
TreeNode* buildExpressionTree(const string& expression) {
	vector<string> postfix = infixToPostfix(expression);
	stack<TreeNode*> nodes;

	for (const string& token : postfix) {
		if (isOperator(token[0]) && token.size() == 1) {
			if (nodes.size() < 2) {
				throw invalid_argument("Invalid expression: not enough operands for operator " + token);
			}

			TreeNode* right = nodes.top();
			nodes.pop();
			TreeNode* left = nodes.top();
			nodes.pop();

			TreeNode* node = new TreeNode(NodeType::OPERATOR, 0, token[0]);
			node->left = left;
			node->right = right;
			nodes.push(node);
		}
		else if (token == "x") {
			TreeNode* node = new TreeNode(NodeType::VARIABLE, 0, '\0');
			nodes.push(node);
		}
		else if (isNumber(token)) {
			int value = stoi(token);
			TreeNode* node = new TreeNode(NodeType::OPERAND, value, '\0');
			nodes.push(node);
		}
		else {
			throw invalid_argument("Invalid token in expression: " + token);
		}
	}

	if (nodes.size() != 1) {
		throw invalid_argument("Invalid expression: too many operands or not enough operators");
	}

	return nodes.top();
}

// Вычисление значения выражения
int evaluateExpressionTree(TreeNode* root, int x) {
	if (root == nullptr) {
		throw invalid_argument("Tree is empty");
	}

	switch (root->type) {
	case NodeType::OPERAND:
		return root->value;
	case NodeType::VARIABLE:
		return x;
	case NodeType::OPERATOR: {
		int left = evaluateExpressionTree(root->left, x);
		int right = evaluateExpressionTree(root->right, x);

		switch (root->op) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/':
			if (right == 0) throw runtime_error("Division by zero");
			return left / right;
		case '%':
			if (right == 0) throw runtime_error("Modulo by zero");
			return left % right;
		case '^':
			if (right < 0) throw runtime_error("Negative exponent");
			return static_cast<int>(pow(left, right));
		default:
			throw invalid_argument("Unknown operator: " + string(1, root->op));
		}
	}
	default:
		throw invalid_argument("Unknown node type");
	}
}

// Преобразование дерева (замена A+x на x+A)
void transformTree(TreeNode* root) {
	if (root == nullptr) return;

	// Рекурсивно преобразуем поддеревья
	transformTree(root->left);
	transformTree(root->right);

	if (root->type == NodeType::OPERATOR && root->op == '+') {
		if (root->right->type == NodeType::VARIABLE) {
			// Меняем местами левое и правое поддерево
			TreeNode* temp = root->left;
			root->left = root->right;
			root->right = temp;
		}
	}
}

// Вывод дерева в префиксной форме
void printPrefix(TreeNode* root, ofstream& out) {
	if (root == nullptr) return;

	switch (root->type) {
	case NodeType::OPERAND:
		out << root->value << " ";
		break;
	case NodeType::VARIABLE:
		out << "x ";
		break;
	case NodeType::OPERATOR:
		out << root->op << " ";
		printPrefix(root->left, out);
		printPrefix(root->right, out);
		break;
	}
}

// Вывод дерева в постфиксной форме
void printPostfix(TreeNode* root, ofstream& out) {
	if (root == nullptr) return;

	printPostfix(root->left, out);
	printPostfix(root->right, out);

	switch (root->type) {
	case NodeType::OPERAND:
		out << root->value << " ";
		break;
	case NodeType::VARIABLE:
		out << "x ";
		break;
	case NodeType::OPERATOR:
		out << root->op << " ";
		break;
	}
}

// Вывод дерева в инфиксной форме с избыточными скобками
void printInfixWithBrackets(TreeNode* root, ofstream& out) {
	if (root == nullptr) return;

	if (root->type == NodeType::OPERAND) {
		out << root->value;
		return;
	}
	else if (root->type == NodeType::VARIABLE) {
		out << "x";
		return;
	}

	out << "(";
	printInfixWithBrackets(root->left, out);
	out << " " << root->op << " ";
	printInfixWithBrackets(root->right, out);
	out << ")";
}

// Удаление дерева
void deleteTree(TreeNode* root) {
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}