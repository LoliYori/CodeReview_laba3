/*
 * Задание: Построение матрицы инцидентности из матрицы смежности
 *
 * Программа читает матрицу смежности из файла FileName1,
 * преобразует её в матрицу инцидентности и записывает результат
 * в файл FileName2.
 */

//#include "graph_utils.h"
//#include <iostream>
//
//int main() {
//    try {
//        auto result = readAdjacencyMatrix("FileName1.txt");
//        int n = result.first;
//        vector<vector<int>> adjMatrix = result.second;
//
//        auto incidenceMatrix = convertToIncidenceMatrix(n, adjMatrix);
//
//        int edgeCount = 0;
//        if (!incidenceMatrix.empty()) {
//            edgeCount = static_cast<int>(incidenceMatrix[0].size());
//        }
//
//        writeIncidenceMatrix("FileName2", incidenceMatrix, edgeCount);
//
//        cout << "Conversion completed successfully." << endl;
//    }
//    catch (const exception& e) {
//        cerr << "Error: " << e.what() << endl;
//        return 1;
//    }
//
//    return 0;
//}