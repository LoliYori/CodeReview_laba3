/*
 * ����������� ������� 3
 *
 * @file graph_w.h
 * @brief ������������ ���� ��� ��������� ������: ���������� ������� ��������� � ���������� ������� �������������.
 */

#ifndef GRAPH_W_H
#define GRAPH_W_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief ��������� ������� ��������� �� �����.
 *
 * @param input_filename ��� �������� �����.
 * @param adjacency_matrix ������ �� ������� ���������.
 * @throws runtime_error ��� ������ ������ ��� ������������ ������.
 */
void LoadAdjacencyMatrix(const string& input_filename,
    vector<vector<int>>& adjacency_matrix);

/**
 * @brief ������ ������� ������������� �� ������� ���������.
 *
 * @param adjacency_matrix ������� ���������.
 * @param incidence_matrix ������ �� ��������� � ������� �������������.
 */
void GenerateIncidenceMatrix(const vector<vector<int>>& adjacency_matrix,
    vector<vector<int>>& incidence_matrix);

/**
 * @brief ��������� ������� ������������� � ����.
 *
 * @param output_filename ��� ��������� �����.
 * @param incidence_matrix ������� �������������.
 */
void SaveIncidenceMatrix(const string& output_filename,
    const vector<vector<int>>& incidence_matrix);

#endif  // GRAPH_W_H
