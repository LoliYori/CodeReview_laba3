/**
 * @file graph_utils.h
 * @brief Функции для работы с графами
 *
 * Задание: Построение матрицы инцидентности из матрицы смежности
 *
 * Функции для чтения матрицы смежности из файла, преобразования в матрицу инцидентности
 * и записи результата в файл.
 */

#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <utility>

using namespace std;

/**
 * @brief Читает матрицу смежности из файла
 * @param filename Имя файла для чтения
 * @return Пару: количество вершин и матрица смежности
 * @throw invalid_argument Если файл не может быть открыт или данные некорректны
 */
pair<int, vector<vector<int>>> readAdjacencyMatrix(const string& filename);

/**
 * @brief Преобразует матрицу смежности в матрицу инцидентности
 * @param n Количество вершин
 * @param adjMatrix Матрица смежности
 * @return Матрицу инцидентности
 */
vector<vector<int>> convertToIncidenceMatrix(int n, const vector<vector<int>>& adjMatrix);

/**
 * @brief Записывает матрицу инцидентности в файл
 * @param filename Имя файла для записи
 * @param incidenceMatrix Матрица инцидентности
 * @param edgeCount Количество рёбер
 * @throw invalid_argument Если файл не может быть открыт
 */
void writeIncidenceMatrix(const string& filename, const vector<vector<int>>& incidenceMatrix, int edgeCount);

#endif // GRAPH_UTILS_H