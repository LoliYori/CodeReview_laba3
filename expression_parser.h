/*
 * @file expression_parser.h
 * @brief ������������ ���� ��� ������� �������������� ���������
 *
 * �������: ���������� � �������������� ������ ��������������� ���������
 * ��������� �������� ��������: +, -, *, /, %, ^ (���������� � �������)
 * ��������: ����� ����� [1; 30] � ���������� x
 *
 * ���������:
 * 1. ��������� ������ ���������
 * 2. ��������� �������� ��� �������� x
 * 3. ������������� ������ (�������� A+x �� x+A)
 * 4. ������� ������ � ����������, ����������� � ��������� (� ����������� ��������) ������
 */

#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <cctype>

using namespace std;

/**
 * @enum TokenType
 * @brief ���� ������� ��� ������������ �������
 */
enum class TokenType {
    NUMBER,     ///< ����� �����
    VARIABLE,   ///< ���������� x
    OPERATOR,   ///< �������� (+,-,*,/,%,^)
    LEFT_PAREN, ///< ����� ������ '('
    RIGHT_PAREN,///< ������ ������ ')'
    END         ///< ����� ���������
};

/**
 * @struct Token
 * @brief ��������� ��� �������� ���������� � ������
 */
struct Token {
    TokenType type;  ///< ��� ������
    string value;    ///< �������� ������ (��� ����� � ����������)
    int pos;        ///< ������� � �������� ������

    /**
     * @brief ����������� ������
     * @param t ��� ������
     * @param v �������� ������
     * @param p ������� � ������
     */
    Token(TokenType t, const string& v, int p) : type(t), value(v), pos(p) {}
};

/**
 * @class ExprNode
 * @brief ����������� ������� ����� ��� ����� ������ ���������
 */
class ExprNode {
public:
    virtual ~ExprNode() = default;

    /**
     * @brief ���������� �������� ���������
     * @param x �������� ���������� x
     * @return ��������� ����������
     */
    virtual int evaluate(int x) const = 0;

    /**
     * @brief �������������� � ���������� �������
     * @return ������ � ���������� �����
     */
    virtual string toPrefix() const = 0;

    /**
     * @brief �������������� � ����������� �������
     * @return ������ � ����������� �����
     */
    virtual string toPostfix() const = 0;

    /**
     * @brief �������������� � ��������� ������� � ����������� ��������
     * @return ������ � ��������� �����
     */
    virtual string toInfix() const = 0;

    /**
     * @brief ��������, �������� �� ���� ����������
     * @return true ���� ���� ������������ ���������� x
     */
    virtual bool isVariable() const { return false; }

    /**
     * @brief �������������� ���������(������ A + x �� x + A)
     * @return ����� ��������� ����� ��������������
     */
    virtual shared_ptr<ExprNode> transform() = 0;
};

/**
 * @class ExpressionParser
 * @brief ����� ��� �������� � ������ � ��������������� �����������
 */
class ExpressionParser {
public:
    /**
     * @brief ����������� �������
     * @param expression ������ � ���������� ��� �������
     */
    ExpressionParser(const string& expression);

    /**
     * @brief ������ ��������� � ���������� ������
     * @throws runtime_error ��� �������������� �������
     */
    void parse();

    /**
     * @brief ���������� �������� ���������
     * @param x �������� ���������� x
     * @return ��������� ����������
     * @throws runtime_error ��� �������������� �������
     */
    int evaluate(int x) const;

    /**
     * @brief �������������� ������(������ A + x �� x + A)
     */
    void transform();

    /**
     * @brief ����� ����������� � ����
     * @param filename ��� ��������� �����
     * @param x �������� ���������� x ��� ����������
     * @throws runtime_error ��� ������� ������ � ����
     */
    void printResults(const string& filename, int x) const;

private:
    string expression;               ///< �������� ���������
    vector<Token> tokens;            ///< ������ �������
    size_t currentToken;             ///< ������� ������� � ������ �������
    shared_ptr<ExprNode> root;       ///< ������ ������ ���������

    /**
     * @brief ����������� ������(��������� �� ������)
     * @throws runtime_error ��� ����������� ������������ ��������
     */
    void tokenize();

    /**
     * @brief ������� ���������(������� + , -)
     * @return ���� ������ ���������
     */
    shared_ptr<ExprNode> parseExpression();

    /**
     * @brief ������� �����(�������*, / , %)
     * @return ���� ������ ���������
     */
    shared_ptr<ExprNode> parseTerm();

    /**
     * @brief ������� �������(�������^)
     * @return ���� ������ ���������
     */
    shared_ptr<ExprNode> parseFactor();

    /**
     * @brief ������� ��������� ���������(�����, ����������, ������)
     * @return ���� ������ ���������
     * @throws runtime_error ��� �������������� �������
     */
    shared_ptr<ExprNode> parsePrimary();

    /**
     * @brief ��������������� ����� ��� �������� �������� ��������
     * @param parser ����� ��� �������� ���������
     * @param ops ������ ���������� ����� ������
     * @return ���� ������ ���������
     */
    shared_ptr<ExprNode> parseBinaryOp(
        shared_ptr<ExprNode>(ExpressionParser::* parser)(),
        const vector<string>& ops
    );

    /**
     * @brief ��������� ���������� ������
     * @return �����
     */
    Token getNextToken();

    /**
     * @brief �������� ������������ �������� ������ ���������� ����
     * @param expected ��������� ��� ������
     * @param errorMsg ��������� �� ������
     * @throws runtime_error ���� ��� ������ �� ������������� ����������
     */
    void expect(TokenType expected, const string& errorMsg);

    /**
     * @brief �������� � ����������� ������ ��������� ����
     * @param type ��� ������ ��� ��������
     * @return true ���� ����� ������������� ����
     */
    bool match(TokenType type);

    /**
     * @brief �������� � ����������� ������ ������ �� �������� �����
     * @param types ������ ����� ��� ��������
     * @return true ���� ����� ������������� ������ �� �����
     */
    bool matchAny(const vector<TokenType>& types);
};

#endif // EXPRESSION_PARSER_H