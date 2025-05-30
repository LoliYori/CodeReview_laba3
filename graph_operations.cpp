/*
 * Продолжение задания №GraphIncidenceMatrix
 */

#include "graph_operations.h"

void LoadAdjacencyMatrix(const string& input_filename, vector<vector<int>>& adjacency_matrix) {
	ifstream file(input_filename);
	if (!file.is_open()) {
		throw runtime_error("Не удалось открыть файл: " + input_filename);
	}

	int vertex_count;
	file >> vertex_count;

	if (vertex_count <= 0) {
		throw runtime_error("Количество вершин должно быть положительным.");
	}

	adjacency_matrix.resize(vertex_count, vector<int>(vertex_count));
	for (int i = 0; i < vertex_count; ++i) {
		for (int j = 0; j < vertex_count; ++j) {
			if (!(file >> adjacency_matrix[i][j])) {
				throw runtime_error("Ошибка при чтении матрицы смежности.");
			}
			if (adjacency_matrix[i][j] != 0 && adjacency_matrix[i][j] != 1) {
				throw runtime_error("Матрица смежности должна содержать только 0 или 1.");
			}
		}
	}
}

void GenerateIncidenceMatrix(const vector<vector<int>>& adjacency_matrix, vector<vector<int>>& incidence_matrix) {
	int vertex_count = static_cast<int>(adjacency_matrix.size());

	vector<pair<int, int>> edges;
	vector<vector<bool>> visited(vertex_count, vector<bool>(vertex_count, false));

	for (int i = 0; i < vertex_count; ++i) {
		for (int j = 0; j < vertex_count; ++j) {
			if (adjacency_matrix[i][j] == 1 && !visited[i][j]) {
				if (i != j) {
					edges.emplace_back(i, j);
					visited[i][j] = true;
					visited[j][i] = true;
				}
			}
		}
	}

	int edge_count = static_cast<int>(edges.size());
	incidence_matrix.assign(vertex_count, vector<int>(edge_count, 0));

	for (int edge_index = 0; edge_index < edge_count; ++edge_index) {
		int from = edges[edge_index].first;
		int to = edges[edge_index].second;
		incidence_matrix[from][edge_index] = 1;
		incidence_matrix[to][edge_index] = 1;
	}
}


void SaveIncidenceMatrix(const string& output_filename, const vector<vector<int>>& incidence_matrix) {
	ofstream file(output_filename);
	if (!file.is_open()) {
		throw runtime_error("Не удалось открыть файл: " + output_filename);
	}

	int vertex_count = static_cast<int>(incidence_matrix.size());
	int edge_count = vertex_count > 0 ? static_cast<int>(incidence_matrix[0].size()) : 0;

	file << vertex_count << " " << edge_count << "\n";

	for (int i = 0; i < vertex_count; ++i) {
		// auto: ожидаемый тип — int
		for (auto val : incidence_matrix[i]) {
			file << val << " ";
		}
		file << "\n";
	}
}
