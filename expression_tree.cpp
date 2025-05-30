#include "expression_tree.h"

bool IsOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

int GetPrecedence(char op) {
	switch (op) {
	case '+': case '-': return 1;
	case '*': case '/': case '%': return 2;
	case '^': return 3;
	default: return 0;
	}
}

bool IsRightAssociative(char op) {
	return op == '^';
}

bool IsVariable(const string& token) {
	return token == "x";
}

bool IsNumber(const string& token) {
	return all_of(token.begin(), token.end(), ::isdigit);
}

int ApplyOperator(char op, int lhs, int rhs) {
	switch (op) {
	case '+': return lhs + rhs;
	case '-': return lhs - rhs;
	case '*': return lhs * rhs;
	case '/':
		if (rhs == 0) throw runtime_error("Деление на ноль.");
		return lhs / rhs;
	case '%':
		if (rhs == 0) throw runtime_error("Остаток от деления на ноль.");
		return lhs % rhs;
	case '^': {
		int result = 1;
		for (int i = 0; i < rhs; ++i) result *= lhs;
		return result;
	}
	default:
		throw runtime_error("Неизвестный оператор.");
	}
}

vector<string> Tokenize(const string& expr) {
	vector<string> tokens;
	string current;
	for (char ch : expr) {
		if (isdigit(ch)) {
			current += ch;
		}
		else if (isalpha(ch)) {
			if (!current.empty()) {
				tokens.push_back(current);
				current.clear();
			}
			tokens.emplace_back(1, ch);
		}
		else {
			if (!current.empty()) {
				tokens.push_back(current);
				current.clear();
			}
			if (!isspace(ch)) {
				tokens.emplace_back(1, ch);
			}
		}
	}
	if (!current.empty()) {
		tokens.push_back(current);
	}
	return tokens;
}

vector<string> ToPostfix(const vector<string>& tokens) {
	vector<string> output;
	stack<string> op_stack;

	for (const string& token : tokens) {
		if (IsNumber(token) || IsVariable(token)) {
			output.push_back(token);
		}
		else if (token == "(") {
			op_stack.push(token);
		}
		else if (token == ")") {
			while (!op_stack.empty() && op_stack.top() != "(") {
				output.push_back(op_stack.top());
				op_stack.pop();
			}
			if (!op_stack.empty()) op_stack.pop();
		}
		else if (IsOperator(token[0])) {
			while (!op_stack.empty()) {
				char top = op_stack.top()[0];
				if (IsOperator(top) &&
					((!IsRightAssociative(token[0]) && GetPrecedence(token[0]) <= GetPrecedence(top)) ||
						(IsRightAssociative(token[0]) && GetPrecedence(token[0]) < GetPrecedence(top)))) {
					output.push_back(op_stack.top());
					op_stack.pop();
				}
				else break;
			}
			op_stack.push(token);
		}
	}
	while (!op_stack.empty()) {
		output.push_back(op_stack.top());
		op_stack.pop();
	}
	return output;
}

shared_ptr<TreeNode> BuildTreeFromPostfix(const vector<string>& postfix) {
	stack<shared_ptr<TreeNode>> st;

	for (const string& token : postfix) {
		if (IsNumber(token) || IsVariable(token)) {
			st.push(make_shared<TreeNode>(token));
		}
		else if (IsOperator(token[0])) {
			if (st.size() < 2) throw runtime_error("Некорректное выражение.");
			auto right = st.top(); st.pop();
			auto left = st.top(); st.pop();
			auto node = make_shared<TreeNode>(token);
			node->left = left;
			node->right = right;
			st.push(node);
		}
	}
	if (st.size() != 1) throw runtime_error("Ошибка построения дерева.");
	return st.top();
}

ExpressionTree ExpressionTree::BuildFromInfix(const string& infix) {
	vector<string> tokens = Tokenize(infix);
	vector<string> postfix = ToPostfix(tokens);
	ExpressionTree tree;
	tree.root = BuildTreeFromPostfix(postfix);
	tree.Normalize();
	return tree;
}

int ExpressionTree::EvaluateNode(shared_ptr<TreeNode> node, int x) {
	if (!node) throw runtime_error("Пустой узел дерева.");

	if (IsNumber(node->value)) return stoi(node->value);
	if (IsVariable(node->value)) return x;

	int left = EvaluateNode(node->left, x);
	int right = EvaluateNode(node->right, x);
	return ApplyOperator(node->value[0], left, right);
}

int ExpressionTree::Evaluate(int x) {
	return EvaluateNode(root, x);
}

void ExpressionTree::NormalizeNode(shared_ptr<TreeNode>& node) {
	if (!node || !IsOperator(node->value[0])) return;

	NormalizeNode(node->left);
	NormalizeNode(node->right);

	if (node->value == "+" && node->left && node->right) {
		bool left_is_x = IsVariable(node->left->value);
		bool right_is_x = IsVariable(node->right->value);

		if (left_is_x && !right_is_x) {
			swap(node->left, node->right);
		}
	}
}

void ExpressionTree::Normalize() {
	NormalizeNode(root);
}

void ExpressionTree::PrintInfix(ostream& os, shared_ptr<TreeNode> node) {
	if (!node) return;
	bool need_parens = IsOperator(node->value[0]);
	if (need_parens) os << "(";
	PrintInfix(os, node->left);
	os << node->value;
	PrintInfix(os, node->right);
	if (need_parens) os << ")";
}

void ExpressionTree::PrintPrefix(ostream& os, shared_ptr<TreeNode> node) {
	if (!node) return;
	os << node->value << " ";
	PrintPrefix(os, node->left);
	PrintPrefix(os, node->right);
}

void ExpressionTree::PrintPostfix(ostream& os, shared_ptr<TreeNode> node) {
	if (!node) return;
	PrintPostfix(os, node->left);
	PrintPostfix(os, node->right);
	os << node->value << " ";
}

void WriteResultToFile(const string& filename, int result, ExpressionTree& tree) {
	ofstream out(filename);
	out.imbue(locale::classic());
	if (!out) throw runtime_error("Невозможно открыть файл для записи.");

	out << "Результат вычисления: " << result << endl;

	out << "Префиксная форма: ";
	tree.PrintPrefix(out, tree.GetRoot());
	out << endl;

	out << "Постфиксная форма: ";
	tree.PrintPostfix(out, tree.GetRoot());
	out << endl;

	out << "Инфиксная форма с избыточными скобками: ";
	tree.PrintInfix(out, tree.GetRoot());
	out << endl;
}

string ReadExpressionFromFile(const string& filename) {
	ifstream in(filename);
	in.imbue(locale::classic());
	if (!in) throw runtime_error("Невозможно открыть файл для чтения.");

	string expression;
	getline(in, expression);
	if (expression.empty()) throw runtime_error("Файл пуст или содержит некорректные данные.");
	return expression;
}
