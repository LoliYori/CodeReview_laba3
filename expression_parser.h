/*
 * @file expression_parser.h
 * @brief Заголовочный файл для парсера арифметических выражений
 *
 * Задание: Построение и преобразование дерева арифметического выражения
 * Выражение содержит операции: +, -, *, /, %, ^ (возведение в степень)
 * Операнды: целые числа [1; 30] и переменная x
 *
 * Требуется:
 * 1. Построить дерево выражения
 * 2. Вычислить значение при заданном x
 * 3. Преобразовать дерево (заменить A+x на x+A)
 * 4. Вывести дерево в префиксной, постфиксной и инфиксной (с избыточными скобками) формах
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
 * @brief Типы токенов для лексического анализа
 */
enum class TokenType {
    NUMBER,     ///< Целое число
    VARIABLE,   ///< Переменная x
    OPERATOR,   ///< Оператор (+,-,*,/,%,^)
    LEFT_PAREN, ///< Левая скобка '('
    RIGHT_PAREN,///< Правая скобка ')'
    END         ///< Конец выражения
};

/**
 * @struct Token
 * @brief Структура для хранения информации о токене
 */
struct Token {
    TokenType type;  ///< Тип токена
    string value;    ///< Значение токена (для чисел и операторов)
    int pos;        ///< Позиция в исходной строке

    /**
     * @brief Конструктор токена
     * @param t Тип токена
     * @param v Значение токена
     * @param p Позиция в строке
     */
    Token(TokenType t, const string& v, int p) : type(t), value(v), pos(p) {}
};

/**
 * @class ExprNode
 * @brief Абстрактный базовый класс для узлов дерева выражения
 */
class ExprNode {
public:
    virtual ~ExprNode() = default;

    /**
     * @brief Вычисление значения выражения
     * @param x Значение переменной x
     * @return Результат вычисления
     */
    virtual int evaluate(int x) const = 0;

    /**
     * @brief Преобразование в префиксную нотацию
     * @return Строка в префиксной форме
     */
    virtual string toPrefix() const = 0;

    /**
     * @brief Преобразование в постфиксную нотацию
     * @return Строка в постфиксной форме
     */
    virtual string toPostfix() const = 0;

    /**
     * @brief Преобразование в инфиксную нотацию с избыточными скобками
     * @return Строка в инфиксной форме
     */
    virtual string toInfix() const = 0;

    /**
     * @brief Проверка, является ли узел переменной
     * @return true если узел представляет переменную x
     */
    virtual bool isVariable() const { return false; }

    /**
     * @brief Преобразование поддерева(замена A + x на x + A)
     * @return Новое поддерево после преобразования
     */
    virtual shared_ptr<ExprNode> transform() = 0;
};

/**
 * @class ExpressionParser
 * @brief Класс для парсинга и работы с арифметическими выражениями
 */
class ExpressionParser {
public:
    /**
     * @brief Конструктор парсера
     * @param expression Строка с выражением для разбора
     */
    ExpressionParser(const string& expression);

    /**
     * @brief Разбор выражения и построение дерева
     * @throws runtime_error при синтаксических ошибках
     */
    void parse();

    /**
     * @brief Вычисление значения выражения
     * @param x Значение переменной x
     * @return Результат вычисления
     * @throws runtime_error при арифметических ошибках
     */
    int evaluate(int x) const;

    /**
     * @brief Преобразование дерева(замена A + x на x + A)
     */
    void transform();

    /**
     * @brief Вывод результатов в файл
     * @param filename Имя выходного файла
     * @param x Значение переменной x для вычисления
     * @throws runtime_error при ошибках записи в файл
     */
    void printResults(const string& filename, int x) const;

private:
    string expression;               ///< Исходное выражение
    vector<Token> tokens;            ///< Список токенов
    size_t currentToken;             ///< Текущая позиция в списке токенов
    shared_ptr<ExprNode> root;       ///< Корень дерева выражения

    /**
     * @brief Лексический анализ(разбиение на токены)
     * @throws runtime_error при обнаружении недопустимых символов
     */
    void tokenize();

    /**
     * @brief Парсинг выражения(уровень + , -)
     * @return Узел дерева выражения
     */
    shared_ptr<ExprNode> parseExpression();

    /**
     * @brief Парсинг терма(уровень*, / , %)
     * @return Узел дерева выражения
     */
    shared_ptr<ExprNode> parseTerm();

    /**
     * @brief Парсинг фактора(уровень^)
     * @return Узел дерева выражения
     */
    shared_ptr<ExprNode> parseFactor();

    /**
     * @brief Парсинг первичных выражений(числа, переменные, скобки)
     * @return Узел дерева выражения
     * @throws runtime_error при синтаксических ошибках
     */
    shared_ptr<ExprNode> parsePrimary();

    /**
     * @brief Вспомогательный метод для парсинга бинарных операций
     * @param parser Метод для парсинга операндов
     * @param ops Список операторов этого уровня
     * @return Узел дерева выражения
     */
    shared_ptr<ExprNode> parseBinaryOp(
        shared_ptr<ExprNode>(ExpressionParser::* parser)(),
        const vector<string>& ops
    );

    /**
     * @brief Получение следующего токена
     * @return Токен
     */
    Token getNextToken();

    /**
     * @brief Проверка соответствия текущего токена ожидаемому типу
     * @param expected Ожидаемый тип токена
     * @param errorMsg Сообщение об ошибке
     * @throws runtime_error если тип токена не соответствует ожидаемому
     */
    void expect(TokenType expected, const string& errorMsg);

    /**
     * @brief Проверка и потребление токена заданного типа
     * @param type Тип токена для проверки
     * @return true если токен соответствует типу
     */
    bool match(TokenType type);

    /**
     * @brief Проверка и потребление токена одного из заданных типов
     * @param types Список типов для проверки
     * @return true если токен соответствует одному из типов
     */
    bool matchAny(const vector<TokenType>& types);
};

#endif // EXPRESSION_PARSER_H