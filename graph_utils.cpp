#include "graph_utils.h"

pair<int, vector<vector<int>>> readAdjacencyMatrix(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw invalid_argument("Cannot open file: " + filename);
    }

    int n;
    file >> n;
    if (n <= 0) {
        throw invalid_argument("Invalid number of vertices: " + to_string(n));
    }

    vector<vector<int>> adjMatrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!(file >> adjMatrix[i][j])) {
                throw invalid_argument("Invalid matrix data in file: " + filename);
            }
        }
    }

    return make_pair(n, adjMatrix);
}

vector<vector<int>> convertToIncidenceMatrix(int n, const vector<vector<int>>& adjMatrix) {
    // Создаём список рёбер в нужном порядке
    vector<pair<int, int>> edges;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (adjMatrix[i][j] != 0 && !visited[i][j] && i != j) {
                edges.emplace_back(i, j);
                visited[i][j] = visited[j][i] = true;
            }
        }
    }

    int m = static_cast<int>(edges.size());
    vector<vector<int>> incidenceMatrix(n, vector<int>(m, 0));

    for (int idx = 0; idx < m; ++idx) {
        int u = edges[idx].first;
        int v = edges[idx].second;
        incidenceMatrix[u][idx] = 1;
        incidenceMatrix[v][idx] = 1;
    }

    return incidenceMatrix;
}


void writeIncidenceMatrix(const string& filename, const vector<vector<int>>& incidenceMatrix, int edgeCount) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw invalid_argument("Cannot open file for writing: " + filename);
    }

    int n = static_cast<int>(incidenceMatrix.size());
    file << n << " " << edgeCount << "\n";

    for (const auto& row : incidenceMatrix) {
        for (int val : row) {
            file << val << " ";
        }
        file << "\n";
    }
}