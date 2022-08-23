#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, pair<vector<int>, int>> routes;
// split function to split string as per given delimiter and storing in an array
vector<int> split(string line)
{
    vector<int> lis;
    int i = 0;
    int j = 0;
    while (1)
    {
        if (line[j] == ' ')
        {
            int tem = stoi(line.substr(i, j));
            lis.push_back(tem);
            i = j + 1;
        }

        j = j + 1;

        if (line[j] == '\0')
        {
            int tem = stoi(line.substr(i, j - 1));
            lis.push_back(tem);
            break;
        }
    }
    return (lis);
}

//print a given vector
void PrintVector(vector<int> tem)
{
    for (int i = 0; i < tem.size(); i++)
    {
        cout << tem[i] << " ";
    }
    cout << endl;
}

//print the graph
void PrintGraph(map<int, vector<vector<int>>> graph)
{
    for (auto &item : graph)
    {
        cout << item.first << endl;
        for (int i = 0; i < item.second.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << item.second[i][j] << " ";
            }
            cout << endl;
        }
    }
}

void GetPaths(int node, int nodes, map<int, pair<int, int>> dist)
{
    int cur = 0;
    int parent;

    pair<int, int> p;
    while (cur < nodes)
    {

        if (cur != node)
        {
            p = make_pair(node, cur);
            routes[p].first.push_back(cur);
            parent = dist[cur].second;
            while (parent != node)
            {
                routes[p].first.push_back(parent);
                parent = dist[parent].second;
            }
            routes[p].first.push_back(parent);
        }
        cur++;
    }
}

int main()
{

    // your code goes here
    int nodes, edges;
    vector<int> tem;
    std::map<int, vector<vector<int>>> graph; // graph declaration
                                              // heap declaration
    map<pair<int, int>, vector<int>> edge;
    map<int, vector<vector<int>>> forward;
    map<int, vector<int>> pointer;
    map<int, vector<vector<int>>> forward2;

    map<int, vector<vector<int>>> connections;
    string line = "1 2 3 4";
    ifstream fin;
    fin.open("file.txt");
    //cout << line << endl;

    getline(fin, line);
    tem = split(line);
    //PrintVector(tem);
    nodes = tem[0];
    edges = tem[1];
    getline(fin, line);

    while (fin)
    {

        tem = split(line);
        //PrintVector(tem);
        graph[tem[0]].push_back({tem[1], tem[2], tem[3]});
        graph[tem[1]].push_back({tem[0], tem[2], tem[3]});
        if (tem[3] == 1)
        {
            edge[make_pair(tem[0], tem[1])] = {0, 0, 24};
            edge[make_pair(tem[1], tem[0])] = {0, 0, 24};
        }
        else if (tem[3] == 3)
        {
            edge[make_pair(tem[0], tem[1])] = {0, 0, 672};
            edge[make_pair(tem[1], tem[0])] = {0, 0, 672};
        }
        getline(fin, line);
    }

    fin.close();
    //PrintGraph(graph);
    int source = 0;

    while (source < nodes)
    {

        int count = 1;
        map<int, pair<int, int>> dist; // stores shortest path from source and parent nodes
        std::priority_queue<pair<int, int>> heap;

        for (int i = 0; i < nodes; i++)
        {
            dist[i].first = 100000; // initialising every node distance as infinite
            dist[i].second = 0;     // initialilly all parent nodes are zeros
        }

        dist[source].first = 0;
        dist[source].second = 0;
        int cur = source;
        int dis = 0;
        while (count <= nodes) // traverse the loop n times
        {
            count++;
            for (int i = 0; i < graph[cur].size(); i++)
            {
                int t2 = graph[cur][i][0];
                int t1 = dis + graph[cur][i][1];
                if (t1 < dist[t2].first)
                {
                    dist[t2].first = t1;                               // relaxing the distance
                    dist[t2].second = cur;                             // updating the parent node
                    heap.push(make_pair((-1) * t1, graph[cur][i][0])); // pushing distances + node numbers into the heap
                }
            }

            pair<int, int> top = heap.top(); // return the topmost node
            heap.pop();                      // extracting the minimum node
            cur = top.second;                // updating the smallest distance node which needs to be traversed next
            dis = (-1) * top.first;          // distance from source to current node that needs to be traversed
        }

        int c = 0;
        /*
        for (auto &ele : dist)
        {
            cout << c << " " << ele.second.first << " " << ele.second.second << endl; // node number, shortest distance from source, parent node
            c++;
        }
        */

        int node = source;

        GetPaths(node, nodes, dist);
        //cout << routes[{0, 6}].first[0];
        //cout << "Source: " << node << endl;
        for (int i = 0; i < nodes; i++)
        {
            if (node != i)
            {
                int len = routes[{node, i}].first.size();

                // cout << i << ":" << endl;
                reverse(routes[{node, i}].first.begin(), routes[{node, i}].first.end());
                routes[{node, i}].second = dist[i].first;
                //cout << node << " " << i << " " << routes[{node, i}].second;
                //cout << endl;
            }
        }

        source++;
    }
    /*
    cout << "hello" << endl;
    int z = nodes - 1;
    for (; z >= 1; z--)
    {
        for (int v = z - 1; v >= 0; v--)
        {
            copy(routes[{v, z}].first.begin(), routes[{v, z}].first.end(), routes[{z, v}].first.begin());

            routes[{z, v}].second = routes[{v, z}].second;
        }
    }
    cout << "hello" << endl;
*/
    /*
    for (auto &item : routes)
    {

        for (int i = 0; i < item.second.size(); i++)
        {
            routes[{item.first, tem[1]}]
        }
    }
    */

    fin.open("file2.txt");
    //cout << line << endl;
    getline(fin, line);
    int con = stoi(line);
    int tem2 = 8;
    int round = 0;

    getline(fin, line);
    while (tem2)
    {
        cout << "connection" << round << endl;
        tem2 = tem2 - 1;
        //for every connection

        tem = split(line);
        vector<int> tem5;

        vector<int> tem3;
        map<int, vector<vector<int>>> tem4;
        map<int, vector<vector<int>>>::iterator itr;
        tem3 = routes[{tem[0], tem[1]}].first;
        int flag = 0;
        //cout << tem3.size() << endl;
        int st = tem[0];
        int ed = tem[1];
        for (int k = 0; k < tem3.size() - 1; k++)
        {

            //cout << "k  k+1 " << tem3[k] << " " << tem3[k + 1] << endl;
            tem5.push_back(edge[{tem3[k], tem3[k + 1]}][0]);

            if (edge[{tem3[k], tem3[k + 1]}][0] + tem[2] <= edge[{tem3[k], tem3[k + 1]}][2])
            {
                tem4[tem3[k]].push_back({-1, -1, tem3[k + 1], edge[{tem3[k], tem3[k + 1]}][0]});

                tem4[tem3[k + 1]].push_back({tem3[k], edge[{tem3[k], tem3[k + 1]}][0], -1, -1});

                edge[{tem3[k], tem3[k + 1]}][0] = edge[{tem3[k], tem3[k + 1]}][0] + tem[2];
                edge[{tem3[k + 1], tem3[k]}][0] = edge[{tem3[k + 1], tem3[k]}][0] + tem[2];
            }
            else
            {

                flag = 1;
            }
        }

        //cout << "hello0" << endl;

        if (flag == 0)
        {

            for (int k = 0; k < tem3.size() - 1; k++)
            {
                if (tem3[k] == st)
                {
                    pointer[tem3[k]].push_back(0);
                }
                else
                {
                    pointer[tem3[k]].push_back(1);
                }

                if (tem3[k + 1] == ed)
                {
                    pointer[tem3[k + 1]].push_back(0);
                }
                else
                {
                    pointer[tem3[k + 1]].push_back(1);
                }
            }

            int k1;
            vector<vector<int>> k2;
            //cout << "hello1" << endl;
            cout << "round" << round << endl;
            connections[round].push_back({round, tem[0], tem[1], tem[2]});
            connections[round].push_back(routes[{tem[0], tem[1]}].first);
            connections[round].push_back(tem5);
            connections[round].push_back({routes[{tem[0], tem[1]}].second});
            for (itr = tem4.begin(); itr != tem4.end(); itr++)
            {
                k1 = itr->first;
                k2 = itr->second;
                //cout << "hello2" << endl;

                for (int i = 0; i < k2.size(); i++)
                {
                    //cout << "hello3" << endl;
                    forward[k1].push_back(k2[i]);
                    //cout << k2[i][0] << "hello" << k2[i][1] << " hello" << k2[i][2] << " hello" << k2[i][3] << endl;
                }
            }
            for (auto &ele : edge)
            {
                edge[{ele.first.first, ele.first.second}][1] = edge[{ele.first.first, ele.first.second}][0];
                edge[{ele.first.second, ele.first.first}][1] = edge[{ele.first.second, ele.first.first}][0];
            }
        }

        else
        {

            for (auto &ele : edge)
            {
                edge[{ele.first.first, ele.first.second}][0] = edge[{ele.first.first, ele.first.second}][1];
                edge[{ele.first.second, ele.first.first}][1] = edge[{ele.first.second, ele.first.first}][0];
            }
        }

        getline(fin, line);
        round++;
    }

    int k1;
    vector<vector<int>> k2;
    map<int, vector<vector<int>>>::iterator itr;
    map<int, vector<vector<int>>>::iterator itr2;
    //cout << "hello" << endl;
    map<int, vector<int>>::iterator itr3;
    vector<int> k3;
    /*
    for (itr3 = pointer.begin(); itr3 != pointer.end(); itr3++)
    {
        k3 = itr3->second;
        cout << itr3->first << ":" << endl;
        for (int i = 0; i < k3.size(); i++)
        {
            cout << k3[i] << " ";
        }
        cout << endl;
    }
    
    for (itr = forward.begin(); itr != forward.end(); itr++)
    {
        k1 = itr->first;
        k2 = itr->second;
        cout << k1 << ":" << endl;
        for (int i = 0; i < k2.size(); i++)
        {
            cout << k2[i][0] << " " << k2[i][1] << " " << k2[i][2] << " " << k2[i][3] << endl;
        }
    }
    */

    for (itr = forward.begin(); itr != forward.end(); itr++)
    {
        k1 = itr->first;
        k2 = itr->second;
        vector<int> x;
        vector<int> y;
        // cout << k1 << ":" << endl;
        for (int i = 0; i < k2.size(); i++)
        {
            if (pointer[k1][i] == 1)
            {
                x = k2[i];
                y = k2[i + 1];
                forward2[k1].push_back({k2[i][0] + k2[i + 1][0] + 1, k2[i][1] + k2[i + 1][1] + 1, k2[i][2] + k2[i + 1][2] + 1, k2[i][3] + k2[i + 1][3] + 1});
                i = i + 1;
            }
            else
            {
                forward2[k1].push_back(k2[i]);
            }
        }
    }
    /*
    for (itr = forward2.begin(); itr != forward2.end(); itr++)
    {
        k1 = itr->first;
        k2 = itr->second;
        cout << k1 << ":" << endl;
        for (int i = 0; i < k2.size(); i++)
        {
            cout << k2[i][0] << " " << k2[i][1] << " " << k2[i][2] << " " << k2[i][3] << endl;
        }
    }

    

    for (itr = connections.begin(); itr != connections.end(); itr++)
    {
        k1 = itr->first;
        cout << k1 << ":" << endl;
        k2 = itr->second;

        for (int i = 0; i < k2.size(); i++)
        {
            for (int j = 0; j < k2[i].size(); j++)
            {
                cout << k2[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    */

    ofstream fout;
    int node = 0;
    fout.open("routing.txt");
    while (node < nodes)
    {
        string line2;

        line2 = "Routing table for node  " + to_string(node);
        fout << line2 << endl;
        line2 = "";
        line2 = line2 + "Destination Node                                                  ";
        line2 = line2 + "Path (from Source to Dest)                                        ";
        line2 = line2 + "End-to-end Path Delay";
        fout << line2 << endl;

        while (fout)
        {
            line2 = "";
            line2 = line2 + to_string(node) + "                                                                        ";
            line2 = line2 + "{" + to_string(node) + "}" + "                                                             ";
            line2 = line2 + to_string(0);
            fout << line2 << endl;
            for (int k = 0; k < nodes; k++)
            {
                line2 = "";
                if (k != node)
                {
                    line2 = line2 + to_string(k) + "                                                                        ";
                    string temp = "{";
                    vector<int> temp2;
                    temp2 = routes[{node, k}].first;
                    for (int i = 0; i < temp2.size(); i++)
                    {
                        temp = temp + to_string(temp2[i]);
                        if (i != temp2.size() - 1)
                        {
                            temp = temp + ",";
                        }
                    }
                    temp = temp + "}                                                         ";
                    line2 = line2 + temp;
                    line2 = line2 + to_string(routes[{node, k}].second);
                    fout << line2 << endl;
                }
            }
            break;
        }
        node++;
        line2 = "\n\n\n";
        fout << line2;
    }
    fout.close();

    fout.open("forwarding.txt");

    node = 0;

    for (itr = forward2.begin(); itr != forward2.end(); itr++)
    {
        k1 = itr->first;
        k2 = itr->second;
        string line2;
        line2 = "Forwarding Table for Node  " + to_string(k1);

        fout << line2 << endl;
        line2 = "";
        line2 = line2 + "Node ID of Incoming Port                       ";
        line2 = line2 + "Starting Slot Number                            ";
        line2 = line2 + "Node ID of Outgoing Port                        ";
        line2 = line2 + "Starting Slot Number";
        fout << line2 << endl;
        for (int i = 0; i < k2.size(); i++)
        {

            cout << k2[i][0] << " " << k2[i][1] << " " << k2[i][2] << " " << k2[i][3] << endl;
            line2 = "";
            int y1 = k2[i][0];
            if (y1 == -1)
            {
                line2 = line2 + "-                                                   ";
            }
            else
            {
                line2 = line2 + to_string(y1) + "                                                    ";
            }
            int y2 = k2[i][1];
            if (y2 == -1)
            {
                line2 = line2 + "-                                                   ";
            }
            else
            {
                line2 = line2 + to_string(y2) + "                                                    ";
            }
            int y3 = k2[i][2];
            if (y3 == -1)
            {
                line2 = line2 + "-                                                   ";
            }
            else
            {
                line2 = line2 + to_string(y3) + "                                                   ";
            }
            int y4 = k2[i][3];
            if (y4 == -1)
            {
                line2 = line2 + "-                                                   ";
            }
            else
            {
                line2 = line2 + to_string(y4) + "                                                   ";
            }

            fout << line2 << endl;
        }

        line2 = "\n\n\n";
        fout << line2;
    }

    fout.close();

    fout.open("connections.txt");
    node = 0;
    string line2;
    line2 = "Connections  ";
    fout << line2 << endl;
    line2 = "";
    line2 = line2 + "Connection ID       ";
    line2 = line2 + "Source ID           ";
    line2 = line2 + "Destination ID            ";
    line2 = line2 + "Slots               ";
    line2 = line2 + "Path                      ";
    line2 = line2 + "Starting Slot Number List              ";
    line2 = line2 + "PathCost";
    fout << line2 << endl;
    for (itr = connections.begin(); itr != connections.end(); itr++)
    {
        k1 = itr->first;
        k2 = itr->second;

        line2 = "";
        for (int j = 0; j < k2[0].size(); j++)
        {

            line2 = line2 + to_string(k2[0][j]) + "                     ";
        }

        line2 = line2 + "{";
        for (int j = 0; j < k2[1].size(); j++)
        {

            line2 = line2 + to_string(k2[1][j]);
            if (j != k2[1].size() - 1)
            {
                line2 = line2 + ",";
            }
        }
        line2 = line2 + "}                        ";

        line2 = line2 + "{";
        for (int j = 0; j < k2[2].size(); j++)
        {

            line2 = line2 + to_string(k2[2][j]);
            if (j != k2[2].size() - 1)
            {
                line2 = line2 + ",";
            }
        }
        line2 = line2 + "-}                             ";

        line2 = line2 + to_string(k2[3][0]);

        fout << line2 << endl;
    }

    fout.close();
    fin.close();

    return 0;
}
