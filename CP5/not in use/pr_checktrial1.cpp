#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector> 
#include <queue>

using namespace std;


class Graph
{
    private:
       
        unordered_map<string, double>::iterator itr; 
    public:
        unordered_map<int, string> mapofclasses;
        int next_course_num = 0;
        vector<string> txtVals;
        vector<string> depndCourses;
    

    void addEdge(vector<int> adj[], int s, int d)
    {
        adj[s].push_back(d);
        adj[d].push_back(s);
    }

    void printGraph(vector<int> adj[], int V) {
        for (int d = 0; d < V; ++d) {
            cout << "\n Vertex "
                 << d << ":";
        for (auto x : adj[d])
            cout << "-> " << x;
        printf("\n");
        }
    }

    void readInFile(string filename)
    {
        fstream myfile (filename);
        vector<string> commandSplit = {};
        string word; 
        
        size_t currentPosition; 

        file.open(myfile);
        if(myfile.is_open() )
        {
    
            while (myfile >> word)
            {
                    
            }
            currentPosition + 1);
                }

            }
        }
    }

    void insertValue()
    {
        
        unsigned int vecSize = txtVals.size();
        string graphval;
        int key;
        for(unsigned int n = 0; n < vecSize; n++)
        {
            key = n;
            string courseName = txtVals[n];
            mapofclasses.insert(make_pair( n, key))       
        }
    }

    //key is int and values are strings which are pulled
    void iteratethruGraph()
    {
        for (auto itr = mapofclasses.begin(); itr != mapofclasses.end(); itr++){
            cout << "\nAll Elements : \n";
            cout << itr->first << "  " <<  itr->second << endl;

        }
        
    }

    bool hasCycle(unordered_map<int, string> & graph)
    {
        int gs = graph.size();
        vector<bool> recursionStack(gs, false);
        vector<bool> visited(gs, false);
       

        for(auto& it : graph)
        {
            int vert = it.first;
        }
    }
    
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

bool hasCycle(unordered_map<int, vector<int>>& graph) 
{
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


};



int main(int argc, char* argv[])
{
    Graph studentSchedule;

    if (argc != 2)
    {
        cout << "format needed is './pr_check prereqs.txt'" << endl;
        return 1;
    }

    studentSchedule.readInFile(argv[1]);
    studentSchedule.insertValue();
    
    if(studentSchedule.hasCycle(unordered_map<int, string>& graph))
    {
        cout << "Not Viable" << endl;
        cout << "This course path requires course(s)"<< dependCourses << endl;


    }
     else {
        cout << "The graph does not contain a cycle. It is viable" << endl;
    }

   

}