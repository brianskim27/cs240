#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

bool dfsUtil(unordered_map<int, vector<int>>& graph, int vertex, vector<bool>& visited, vector<bool>& recursionStack) {
    visited[vertex] = true;
    recursionStack[vertex] = true;

    for (int adjVertex : graph[vertex]) {
        if (!visited[adjVertex] && dfsUtil(graph, adjVertex, visited, recursionStack)) {
            return true;
        }
        else if (recursionStack[adjVertex]) {
            return true;
        }
    }

    recursionStack[vertex] = false;
    return false;
}

bool hasCycle(unordered_map<int, vector<int>>& graph) {
    int V = graph.size();
    vector<bool> visited(V, false);
    vector<bool> recursionStack(V, false);

    for (auto& it : graph) {
        int vertex = it.first;
        if (!visited[vertex]) {
            if (dfsUtil(graph, vertex, visited, recursionStack)) {
                return true;
            }
        }
    }

    return false;
}

bool hasPathTooLong(unordered_map<int, vector<int>>& graph, int start, int end, int maxLength) {
    queue<pair<int, int>> q;
    vector<bool> visited(graph.size(), false);
    q.push({start, 0});
    visited[start] = true;

    while (!q.empty()) {
        int vertex = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (vertex == end && distance > maxLength) {
            return true;
        }

        for (int adjVertex : graph[vertex]) {
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                q.push({adjVertex, distance + 1});
            }
        }
    }

    return false;
}

int main() {
    // Create a graph using an unordered map
    unordered_map<int, vector<int>> graph;
    graph[0] = {1, 4};
    graph[1] = {2, 3, 4};
    graph[2] = {3};
    graph[3] = {4};

    // Check for cycles in the graph using DFS
    if (hasCycle(graph)) {
        cout << "The graph contains a cycle." << endl;
    }
    else {
        cout << "The graph does not contain a cycle." << endl;
    }

    // Check for paths that are too long using BFS
    int start = 0;
    int end = 3;
    int maxLength = 2;
    if (hasPathTooLong(graph, start, end, maxLength)) {
        cout << "There is a path from vertex " << start << " to vertex " << end << " that is too long." << endl;
    }
    else {
        cout << "There is no path from vertex " << start << " to vertex " << end << " that is too long." << endl;
    }

    return 0;
}