/* Продолжение задания №1 */

#ifndef INCIDENCE_MATRIX_H
#define INCIDENCE_MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * Функция для построения матрицы инцидентности графа.
 *
 * @param inputFileName Имя входного файла, содержащего матрицу смежности.
 * @param outputFileName Имя выходного файла, в который будет записана матрица инцидентности.
 * @throw std::invalid_argument Если входные данные некорректны.
 */
void BuildIncidenceMatrix(const std::string& inputFileName, const std::string& outputFileName);

#endif // INCIDENCE_MATRIX_H
