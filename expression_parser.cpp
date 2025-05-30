#include "expression_parser.h"
#include <algorithm>
#include <cctype>

// Вспомогательные классы узлов
class NumberNode : public ExprNode {
    int value;
public:
    NumberNode(int val) : value(val) {}
    int evaluate(int) const override { return value; }
    string toPrefix() const override { return to_string(value); }
    string toPostfix() const override { return to_string(value); }
    string toInfix() const override { return to_string(value); }
    shared_ptr<ExprNode> transform() override { return make_shared<NumberNode>(value); }
};

class VariableNode : public ExprNode {
public:
    int evaluate(int x) const override { return x; }
    string toPrefix() const override { return "x"; }
    string toPostfix() const override { return "x"; }
    string toInfix() const override { return "x"; }
    bool isVariable() const override { return true; }
    shared_ptr<ExprNode> transform() override { return make_shared<VariableNode>(); }
};

class BinaryOpNode : public ExprNode {
    string op;
    shared_ptr<ExprNode> left;
    shared_ptr<ExprNode> right;
public:
    BinaryOpNode(const string& op, shared_ptr<ExprNode> l, shared_ptr<ExprNode> r)
        : op(op), left(l), right(r) {
    }

    int evaluate(int x) const override {
        int l = left->evaluate(x);
        int r = right->evaluate(x);

        if (op == "+") return l + r;
        if (op == "-") return l - r;
        if (op == "*") return l * r;
        if (op == "/") {
            if (r == 0) throw runtime_error("Division by zero");
            return l / r;
        }
        if (op == "%") {
            if (r == 0) throw runtime_error("Modulo by zero");
            return l % r;
        }
        if (op == "^") {
            if (r < 0) throw runtime_error("Negative exponent");
            int result = 1;
            for (int i = 0; i < r; ++i) result *= l;
            return result;
        }
        throw runtime_error("Unknown operator: " + op);
    }

    string toPrefix() const override {
        return op + " " + left->toPrefix() + " " + right->toPrefix();
    }

    string toPostfix() const override {
        return left->toPostfix() + " " + right->toPostfix() + " " + op;
    }

    string toInfix() const override {
        return "(" + left->toInfix() + " " + op + " " + right->toInfix() + ")";
    }

    shared_ptr<ExprNode> transform() override {
        auto newLeft = left->transform();
        auto newRight = right->transform();

        if (op == "+" && !newLeft->isVariable() && newRight->isVariable()) {
            return make_shared<BinaryOpNode>(op, newRight, newLeft);
        }

        return make_shared<BinaryOpNode>(op, newLeft, newRight);
    }
};

// Реализация методов ExpressionParser
void ExpressionParser::tokenize() {
    tokens.clear();
    for (size_t i = 0; i < expression.size(); ) {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (expression[i] == '(') {
            tokens.emplace_back(TokenType::LEFT_PAREN, "(", static_cast<int>(i));
            i++;
            continue;
        }

        if (expression[i] == ')') {
            tokens.emplace_back(TokenType::RIGHT_PAREN, ")", static_cast<int>(i));
            i++;
            continue;
        }

        if (string("+-*/%^").find(expression[i]) != string::npos) {
            tokens.emplace_back(TokenType::OPERATOR, string(1, expression[i]), static_cast<int>(i));
            i++;
            continue;
        }

        if (expression[i] == 'x' || expression[i] == 'X') {
            tokens.emplace_back(TokenType::VARIABLE, "x", static_cast<int>(i));
            i++;
            continue;
        }

        if (isdigit(expression[i])) {
            size_t start = i;
            while (i < expression.size() && isdigit(expression[i])) i++;
            string numStr = expression.substr(start, i - start);
            int num = stoi(numStr);
            if (num < 1 || num > 30) {
                throw runtime_error("Number out of range [1;30] at position " + to_string(start));
            }
            tokens.emplace_back(TokenType::NUMBER, numStr, static_cast<int>(start));
            continue;
        }

        throw runtime_error("Unexpected character '" + string(1, expression[i]) + "' at position " + to_string(i));
    }
    tokens.emplace_back(TokenType::END, "", static_cast<int>(expression.size()));
}

Token ExpressionParser::getNextToken() {
    if (currentToken >= tokens.size()) {
        return Token(TokenType::END, "", static_cast<int>(expression.size()));
    }
    return tokens[currentToken++];
}

void ExpressionParser::expect(TokenType expected, const string& errorMsg) {
    if (currentToken >= tokens.size() || tokens[currentToken].type != expected) {
        throw runtime_error(errorMsg + " at position " + to_string(currentToken < tokens.size() ? tokens[currentToken].pos : static_cast<int>(expression.size())));
    }
    currentToken++;
}

bool ExpressionParser::match(TokenType type) {
    if (currentToken < tokens.size() && tokens[currentToken].type == type) {
        currentToken++;
        return true;
    }
    return false;
}

shared_ptr<ExprNode> ExpressionParser::parsePrimary() {
    Token token = getNextToken();

    switch (token.type) {
    case TokenType::NUMBER:
        return make_shared<NumberNode>(stoi(token.value));
    case TokenType::VARIABLE:
        return make_shared<VariableNode>();
    case TokenType::LEFT_PAREN: {
        auto expr = parseExpression();
        expect(TokenType::RIGHT_PAREN, "Expected ')'");
        return expr;
    }
    default:
        throw runtime_error("Unexpected token '" + token.value + "' at position " + to_string(token.pos));
    }
}

shared_ptr<ExprNode> ExpressionParser::parseFactor() {
    auto left = parsePrimary();

    while (match(TokenType::OPERATOR) && tokens[currentToken - 1].value == "^") {
        auto right = parseFactor();
        left = make_shared<BinaryOpNode>("^", left, right);
    }

    return left;
}

shared_ptr<ExprNode> ExpressionParser::parseTerm() {
    auto left = parseFactor();

    while (currentToken < tokens.size() && tokens[currentToken].type == TokenType::OPERATOR) {
        string op = tokens[currentToken].value;
        if (op == "*" || op == "/" || op == "%") {
            currentToken++;
            auto right = parseFactor();
            left = make_shared<BinaryOpNode>(op, left, right);
        }
        else {
            break;
        }
    }

    return left;
}

shared_ptr<ExprNode> ExpressionParser::parseExpression() {
    auto left = parseTerm();

    while (currentToken < tokens.size() && tokens[currentToken].type == TokenType::OPERATOR) {
        string op = tokens[currentToken].value;
        if (op == "+" || op == "-") {
            currentToken++;
            auto right = parseTerm();
            left = make_shared<BinaryOpNode>(op, left, right);
        }
        else {
            break;
        }
    }

    return left;
}

void ExpressionParser::parse() {
    tokenize();
    currentToken = 0;
    root = parseExpression();
    if (currentToken < tokens.size() && tokens[currentToken].type != TokenType::END) {
        throw runtime_error("Unexpected token '" + tokens[currentToken].value + "' at position " + to_string(tokens[currentToken].pos));
    }
}

int ExpressionParser::evaluate(int x) const {
    if (!root) throw runtime_error("Expression not parsed");
    return root->evaluate(x);
}

void ExpressionParser::transform() {
    if (!root) throw runtime_error("Expression not parsed");
    root = root->transform();
}

void ExpressionParser::printResults(const string& filename, int x) const {
    ofstream out(filename);
    if (!out) throw runtime_error("Cannot open output file");

    out << "Original expression: " << expression << endl;
    out << "Evaluated with x=" << x << ": " << evaluate(x) << endl;
    out << "Prefix form: " << root->toPrefix() << endl;
    out << "Postfix form: " << root->toPostfix() << endl;
    out << "Infix form with brackets: " << root->toInfix() << endl;
}