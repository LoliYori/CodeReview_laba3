/**
 * @file graph_utils.h
 * @brief ������� ��� ������ � �������
 *
 * �������: ���������� ������� ������������� �� ������� ���������
 *
 * ������� ��� ������ ������� ��������� �� �����, �������������� � ������� �������������
 * � ������ ���������� � ����.
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
 * @brief ������ ������� ��������� �� �����
 * @param filename ��� ����� ��� ������
 * @return ����: ���������� ������ � ������� ���������
 * @throw invalid_argument ���� ���� �� ����� ���� ������ ��� ������ �����������
 */
pair<int, vector<vector<int>>> readAdjacencyMatrix(const string& filename);

/**
 * @brief ����������� ������� ��������� � ������� �������������
 * @param n ���������� ������
 * @param adjMatrix ������� ���������
 * @return ������� �������������
 */
vector<vector<int>> convertToIncidenceMatrix(int n, const vector<vector<int>>& adjMatrix);

/**
 * @brief ���������� ������� ������������� � ����
 * @param filename ��� ����� ��� ������
 * @param incidenceMatrix ������� �������������
 * @param edgeCount ���������� ����
 * @throw invalid_argument ���� ���� �� ����� ���� ������
 */
void writeIncidenceMatrix(const string& filename, const vector<vector<int>>& incidenceMatrix, int edgeCount);

#endif // GRAPH_UTILS_H