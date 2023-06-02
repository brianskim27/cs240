// #include <bits/stdc++.h>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <unordered_map>
// #include <vector>
// #include <queue>

// using namespace std;

// class Graph
// {
// private:
//     unordered_map<string, double>::iterator itr;

// public:
//     unordered_map<int, string> mapofclasses;
//     int next_course_num = 0;
//     vector<string> txtVals;

//     // void addEdge(vector<int> adj[], int s, int d)
//     // {
//     //     adj[s].push_back(d);
//     //     adj[d].push_back(s);
//     // }

//     void readInFile(string filename)
//     {
//         fstream myfile(filename);
//         vector<string> commandSplit = {};
//         string word;
//         string line;
//         int n = 0;

//         size_t currentPosition;

//         // file.open(myfile);
//         if (myfile.is_open())
//         {

//             getline(cin, line);
//             while ((currentPosition = line.find(" ")) != string::npos)
//             {
//                 commandSplit.push_back(line.substr(0, currentPosition));
//                 line.erase(0, currentPosition + 1);
//                 string ser = line;

//                 // std::find function call
//                 it = std::find(mapofclasses.begin(), mapofclasses.end(), ser);
//                 if (it != mapofclasses.end())
//                 {
//                     // code continues if found
//                     continue;
//                 }
//                 else
//                     mapofclasses.insert(make_pair(n, line));
//             }
//         }
//         myfile.close();
//     }

//     // key is int and values are strings which are pulled
//     void iteratethruGraph()
//     {
//         for (auto itr = mapofclasses.begin(); itr != mapofclasses.end(); itr++)
//         {
//             cout << "\nAll Elements : \n";
//             cout << itr->first << "  " << itr->second << endl;
//         }
//     }

//     bool dfsUtil(unordered_map<int, vector<int>> &graph, int vert, vector<bool> &visited, vector<bool> &recursionStack)
//     {
//         visited[vert] = true;
//         recursionStack[vert] = true;

//         for (int adjVertex : graph[vert])
//         {
//             if (!visited[adjVertex] && dfsUtil(graph, adjVertex, visited, recursionStack))
//             {
//                 return true;
//             }
//             else if (recursionStack[adjVertex])
//             {
//                 return true;
//             }
//         }

//         recursionStack[vert] = false;
//         return false;
//     }

//     bool hasCycle(unordered_map<int, vector<int>> &graph)
//     {
//         int V = graph.size();
//         vector<bool> visited(V, false);
//         vector<bool> recursionStack(V, false);

//         for (auto &it : graph)
//         {
//             int vertex = it.first;
//             if (!visited[vertex])
//             {
//                 if (dfsUtil(graph, vertex, visited, recursionStack))
//                 {
//                     return true;
//                 }
//             }
//         }

//         return false;
//     }
// };

// int main(int argc, char *argv[])
// {
//     Graph studentSchedule;

//     if (argc != 2)
//     {
//         cout << "format needed is './pr_check prereqs.txt'" << endl;
//         return 1;
//     }

//     studentSchedule.readInFile(argv[1]);
//     studentSchedule.hasCycle();

//     if (studentSchedule.hasCycle())
//     {
//         cout << "Not Viable" << endl;
//         cout << "This course path requires course(s)" << dependCourses << endl;
//     }
//     else
//     {
//         cout << "The graph does not contain a cycle. It is viable" << endl;
//     }
// }
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph
{
public:
    unordered_map<int, std::string> mapofclasses;
    int next_course_num = 0;
    vector<std::string> txtVals;

    void readInFile(std::string filename)
    {
        ifstream myfile(filename);
        string line;
        size_t n = 0;

        if (!myfile.is_open()) {
            cerr << "Unable to open file " << filename << std::endl;
            return;
        }

        while (std::getline(myfile, line))
        {
            std::istringstream iss(line);
            std::string class_name;
            iss >> class_name;
            txtVals.push_back(class_name);

            if (mapofclasses.find(n) == mapofclasses.end())
            {
                mapofclasses.insert(std::make_pair(n, class_name));
                n++;
            }
        }

        myfile.close();
    }

    void iteratethruGraph()
    {
        for (auto it = mapofclasses.begin(); it != mapofclasses.end(); it++)
        {
            std::cout << "\nAll Elements : \n";
            std::cout << it->first << "  " << it->second << std::endl;
        }
    }

    bool dfsUtil(std::unordered_map<int, std::vector<int>> &graph, int vert, std::vector<bool> &visited, std::vector<bool> &recursionStack)
    {
        visited[vert] = true;
        recursionStack[vert] = true;

        for (int adjVertex : graph[vert])
        {
            if (!visited[adjVertex] && dfsUtil(graph, adjVertex, visited, recursionStack))
            {
                return true;
            }
            else if (recursionStack[adjVertex])
            {
                return true;
            }
        }

        recursionStack[vert] = false;
        return false;
    }

    bool hasCycle(std::unordered_map<int, std::vector<int>> &graph)
    {
        int V = graph.size();
        std::vector<bool> visited(V, false);
        std::vector<bool> recursionStack(V, false);

        for (auto &it : graph)
        {
            int vertex = it.first;
            if (!visited[vertex])
            {
                if (dfsUtil(graph, vertex, visited, recursionStack))

    studentSchedule.readInFile(argv[1]);
    studentSchedule.iteratethruGraph();
    return 0;
}
   
