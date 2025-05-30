/* Продолжение задания №1 */

#include "incidence_matrix.h"

void BuildIncidenceMatrix(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Не удалось открыть файл " + inputFileName);
    }

    int n;
    inputFile >> n;
    if (n <= 0) {
        throw std::invalid_argument("Количество вершин должно быть положительным числом");
    }

    std::vector<std::vector<int>> adjacencyMatrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> adjacencyMatrix[i][j];
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                throw std::invalid_argument("Матрица смежности должна содержать только 0 и 1");
            }
        }
    }

    int m = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                ++m;
            }
        }
    }

    std::vector<std::vector<int>> incidenceMatrix(n, std::vector<int>(m, 0));
    int edgeIndex = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjacencyMatrix[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                ++edgeIndex;
            }
        }
    }

    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open()) {
        throw std::invalid_argument("Не удалось открыть файл " + outputFileName);
    }

    outputFile << n << " " << m << std::endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            outputFile << incidenceMatrix[i][j] << " ";
        }
        outputFile << std::endl;
    }
}
