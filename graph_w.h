/*
 * Продолжение задания 3
 *
 * @file graph_w.h
 * @brief Заголовочный файл для обработки графов: считывание матрицы смежности и построение матрицы инцидентности.
 */

#ifndef GRAPH_W_H
#define GRAPH_W_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Считывает матрицу смежности из файла.
 *
 * @param input_filename Имя входного файла.
 * @param adjacency_matrix Ссылка на матрицу смежности.
 * @throws runtime_error При ошибке чтения или некорректных данных.
 */
void LoadAdjacencyMatrix(const string& input_filename,
    vector<vector<int>>& adjacency_matrix);

/**
 * @brief Строит матрицу инцидентности по матрице смежности.
 *
 * @param adjacency_matrix Матрица смежности.
 * @param incidence_matrix Ссылка на результат — матрицу инцидентности.
 */
void GenerateIncidenceMatrix(const vector<vector<int>>& adjacency_matrix,
    vector<vector<int>>& incidence_matrix);

/**
 * @brief Сохраняет матрицу инцидентности в файл.
 *
 * @param output_filename Имя выходного файла.
 * @param incidence_matrix Матрица инцидентности.
 */
void SaveIncidenceMatrix(const string& output_filename,
    const vector<vector<int>>& incidence_matrix);

#endif  // GRAPH_W_H
