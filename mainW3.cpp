/*
 ���� �������� ������������������ ����� � ��������� ����� � ������ FileName1. � ���� ������� ���������. 
 ������ ������ ����� �������� ���������� ������ ����� (n), � ��������� n ����� �������� ������� ��������� (a), a[i][j]=0, ���� ����� ����� ��������� i � j �� ����������. 
 ��������� ������� ������������� ������� ����� � ������� �� � ���� � ������ FileName2. 
 ��� �������: ������� ������������� (b) ����� ������ n x m, m - ����� ����� �����, b[i][j]=1, ���� ����� j ���������� ������� i, � ��������� ������ b[i][j]=0. 
 ��������� ����� ������������ � ��������� �������: ������� �����, ����������� ������� ����� 1, ����� ����� ����������� ������� ����� 2 � �.�. �� ������� ����� n.
 �����, ����������� ������� � ������� i ����������� � ������� ����������� ������ ������ �������, ����������� ������� �����. 
 ��� ������ � ������ ������ ������� ������ ������� �������������: ����� n � m, � � ��������� n ������� ���������� ������� �������������.
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

        cout << "������� ������������� ������� �������� � ����: "
            << output_filename << endl;
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
        return 1;
    }

    return 0;
}
