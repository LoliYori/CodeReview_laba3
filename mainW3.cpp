/*
 Дано описание неориентированного графа в текстовом файле с именем FileName1. в виде матрицы смежности. 
 Первая строка файла содержит количество вершин графа (n), а следующие n строк содержат матрицу смежности (a), a[i][j]=0, если ребра между вершинами i и j не существует. 
 Построить матрицу инцидентности данного графа и вывести ее в файл с именем FileName2. 
 Для справки: матрица инцидентности (b) имеет размер n x m, m - число ребер графа, b[i][j]=1, если ребро j инцидентно вершине i, в противном случае b[i][j]=0. 
 Нумерацию ребер осуществлять в следующем порядке: сначала ребра, инцидентные вершине номер 1, потом ребра инцидентные вершине номер 2 и т.д. до вершины номер n.
 Ребра, инцидентные вершине с номером i перечислять в порядке возрастания номера второй вершины, инцидентной данному ребру. 
 При выводе в первой строке указать размер матрицы инцидентности: числа n и m, а в следующих n строках разместить матрицу инцидентности.
 */

#include "graph_w.h"

int main() {
    try {
        string input_filename = "FileName1.txt";
        string output_filename = "FileName2.txt";

        vector<vector<int>> adjacency_matrix;
        vector<vector<int>> incidence_matrix;

        LoadAdjacencyMatrix(input_filename, adjacency_matrix);
        GenerateIncidenceMatrix(adjacency_matrix, incidence_matrix);
        SaveIncidenceMatrix(output_filename, incidence_matrix);

        cout << "Матрица инцидентности успешно записана в файл: "
            << output_filename << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
