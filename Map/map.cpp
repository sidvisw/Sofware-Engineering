#include <bits/stdc++.h>

// Libraries included for reading the map.osm XML file
#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace std;

// Declaring PI to use it in calculations for crowfly distance
const double PI = acos(-1);

/*
Ultiliy function for searching the node in the unordered map of nodes
Parameters - unordered map of nodes, node ID to be found
Returns the node element having same ID in the map, node with no ID if node not found
*/
pair<string, pair<string, pair<double, double>>> findNode(unordered_map<string, pair<string, pair<double, double>>> &nodes, const string &ID)
{
    if (nodes.count(ID))
    {
        return make_pair(ID, nodes[ID]);
    }
    return make_pair("", make_pair("", make_pair(-1, -1)));
}

/*
Ultility function for searching a way in the unordered map of ways
Parameters - unordered map of ways, way ID to be found
Returns the way element having same ID in the map, way with no ID if way not found
*/
pair<string, pair<string, vector<string>>> findWay(unordered_map<string, pair<string, vector<string>>> &ways, string &ID)
{
    if (ways.count(ID))
    {
        return make_pair(ID, ways[ID]);
    }
    vector<string> temp;
    return make_pair("", make_pair("", temp));
}

/*
Ultility function to calculate crowfly distance between two given nodes
Parameters - two node elements between whom crowfly distance is to be found
Returns the crowfly distance between the two given nodes
*/
double crowFlyDist(pair<string, pair<string, pair<double, double>>> node1, pair<string, pair<string, pair<double, double>>> node2)
{
    return (6371.0072 * acos(cos(PI / 180 * (90 - node1.second.second.first)) * cos(PI / 180 * (90 - node2.second.second.first)) + sin(PI / 180 * (90 - node1.second.second.first)) * sin(PI / 180 * (90 - node2.second.second.first)) * cos(PI / 180 * (node1.second.second.second - node2.second.second.second))));
}

// driver function
int main()
{
    // initialising reader for reading map.osm XML file
    ptree reader;
    read_xml("map.osm", reader);
    // unordered map to store the node and way elements
    unordered_map<string, pair<string, pair<double, double>>> nodes;
    unordered_map<string, pair<string, vector<string>>> ways;
    // Reading XML file through BOOST_FOREACH loop
    BOOST_FOREACH (ptree::value_type &child, reader.get_child("osm"))
    {
        if (child.first == "node")
        {
            string name;
            BOOST_FOREACH (ptree::value_type &child_of_child, child.second)
            {
                if (child_of_child.first == "tag" && child_of_child.second.get<string>("<xmlattr>.k") == "name")
                {
                    name = child_of_child.second.get<string>("<xmlattr>.v");
                }
            }
            nodes[child.second.get<string>("<xmlattr>.id")] = make_pair(name, make_pair(child.second.get<double>("<xmlattr>.lat"), child.second.get<double>("<xmlattr>.lon")));
        }
        if (child.first == "way")
        {
            string name;
            vector<string> temp;
            BOOST_FOREACH (ptree::value_type &child_of_child, child.second)
            {
                if (child_of_child.first == "tag" && child_of_child.second.get<string>("<xmlattr>.k") == "name")
                {
                    name = child_of_child.second.get<string>("<xmlattr>.v");
                }
                if (child_of_child.first == "nd")
                {
                    temp.push_back(child_of_child.second.get<string>("<xmlattr>.ref"));
                }
            }
            ways[child.second.get<string>("<xmlattr>.id")] = make_pair(name, temp);
        }
    }

    // unordered map of unordered map to store the graph in the form of adjacency list
    unordered_map<string, unordered_map<string, pair<double, string>>> graph;

    // loop to initialise the graph with the use of nodes and ways
    for (auto x : ways)
    {
        for (auto it = x.second.second.begin(); it != x.second.second.end() - 1; it++)
        {
            double dist = crowFlyDist(findNode(nodes, *it), findNode(nodes, *(it + 1)));
            if (!(graph.count(*it) && graph[*it].count(*(it + 1)) && graph[*it][*(it + 1)].first <= dist))
            {
                graph[*it][*(it + 1)] = make_pair(dist, x.first);
                graph[*(it + 1)][*it] = make_pair(dist, x.first);
            }
        }
    }

    int input;
    // do-while loop to interface a menu based text interface
    do
    {
        // clear the output screen
        system("clear");
        // print the menu on output console
        cout << "Welcome to our Kharagpur Map!!!" << endl;
        cout << "All Distances given are in km..." << endl;
        cout << "Choose your choice..." << endl;
        cout << "1. Print number of nodes.\n2. Print number of ways.\n3. Search for a node or a way.\n4. Find k-closest nodes to a given node.\n5. Find shortest path between two nodes.\n6. Exit.\nEnter your choice : ";
        cin >> input;
        getchar();
        string str, str2;
        int k;
        pair<string, pair<string, pair<double, double>>> nodeElement;
        pair<string, pair<string, vector<string>>> wayElement;
        switch (input)
        {
        case 1:
            // printing the total number of nodes
            cout << "The total number of nodes are : " << nodes.size() << endl;
            cout << "Press enter to continue...";
            getchar();
            break;
        case 2:
            // printing the total number of ways
            cout << "The total number of ways are : " << ways.size() << endl;
            cout << "Press enter to continue...";
            getchar();
            break;
        case 3:
            // searching the nodes with the help of substring
            cout << "Enter the searching string : ";
            getline(cin, str);
            k = 1;
            cout << "The nodes pertaining to your query are as follows..." << endl;
            printf("%10s\t%10s\t%70s\t%10s\t%10s\n", "Sl.No.", "Node ID", "Node Name", "Latitude", "Longitude");
            for (auto x : nodes)
            {
                // using find function to check whether a given string is a substring of node name or not
                if (x.second.first.find(str) != string::npos)
                {
                    printf("%10d\t%10s\t%70s\t%10lf\t%10lf\n", k, (char *)x.first.c_str(), (char *)x.second.first.c_str(), x.second.second.first, x.second.second.second);
                    k++;
                }
            }
            cout << "Press enter to continue...";
            getchar();
            break;
        case 4:
            // finding k-nearest nodes
            cout << "Enter the Node ID for which you want to find the K-nearest nodes : ";
            cin >> str;
            nodeElement = findNode(nodes, str);
            if (nodeElement.first == "")
            {
                cout << "Wrong ID!!" << endl;
            }
            else
            {
                cout << "Enter the value of K : ";
                cin >> k;
                // using priority queue for eaisier implementation to find k-nearest neighbours
                priority_queue<pair<double, pair<string, pair<string, pair<double, double>>>>, vector<pair<double, pair<string, pair<string, pair<double, double>>>>>, greater<pair<double, pair<string, pair<string, pair<double, double>>>>>> pq;
                for (auto x : nodes)
                {
                    if (nodeElement.first != x.first)
                        pq.push(make_pair(crowFlyDist(nodeElement, x), x));
                }
                // printing the k-nearest neighbours in a tabular format
                cout << "The K-nearest neighbours to the given node are as follows..." << endl;
                printf("%10s\t%10s\t%70s\t%10s\t%10s\t%20s\n", "Sl.No.", "Node ID", "Node Name", "Latitude", "Longitude", "CrowFly Distance");
                for (int i = 0; i < k; i++)
                {
                    printf("%10d\t%10s\t%70s\t%10lf\t%10lf\t%20lf\n", i + 1, (char *)pq.top().second.first.c_str(), (pq.top().second.second.first.length()) ? (char *)pq.top().second.second.first.c_str() : "NA", pq.top().second.second.second.first, pq.top().second.second.second.second, pq.top().first);
                    pq.pop();
                }
            }
            cout << "Press enter to continue...";
            getchar();
            getchar();
            break;
        case 5:
            // dijkstra algorithm to find the shortest path between any two given nodes
            cout << "Enter the ID of Source : ";
            cin >> str;
            if (findNode(nodes, str).first == "")
            {
                cout << "Wrong ID!!" << endl;
            }
            else
            {
                cout << "Enter the ID of Destination : ";
                cin >> str2;
                if (findNode(nodes, str2).first == "")
                {
                    cout << "Wrong ID!!" << endl;
                }
                else
                {
                    // unordered map distances to store the current shortest path from source to the vertex ID provided as key
                    unordered_map<string, double> distances;
                    // unordered map touch to store the ID of vertex that is used as an intermediate to reach the vertex ID provided as key
                    unordered_map<string, string> touch;
                    // initialising touch vertices to source
                    // initialising distances as infinity
                    for (auto x : nodes)
                    {
                        touch[x.first] = str;
                        if (x.first == str)
                        {
                            distances[x.first] = 0;
                        }
                        else
                        {
                            distances[x.first] = DBL_MAX;
                        }
                    }
                    // priority queue to extract the minimum way length in O(log n)
                    priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
                    pq.push(make_pair(distances[str], str));
                    // computing the distances and touch unordered map using dijkstra algorithm
                    while (!pq.empty())
                    {
                        auto minNode = pq.top();
                        pq.pop();
                        for (auto x : graph[minNode.second])
                        {
                            if (distances[x.first] > distances[minNode.second] + graph[minNode.second][x.first].first)
                            {
                                touch[x.first] = minNode.second;
                                distances[x.first] = distances[minNode.second] + graph[minNode.second][x.first].first;
                                pq.push(make_pair(distances[x.first], x.first));
                            }
                        }
                    }
                    // if vertex distance is still infinity then output path not found
                    if (distances[str2] == DBL_MAX)
                    {
                        cout << "No path found!!" << endl;
                    }
                    else
                    {
                        // using stack data structure for storing the path and printing them in an order
                        stack<string> stk;
                        stk.push(str2);
                        while (stk.top() != str)
                        {
                            stk.push(touch[stk.top()]);
                        }
                        cout << "Path found....." << endl
                             << "Follow below mentioned steps to reach the destination..." << endl;
                        string id;
                        id = stk.top();
                        stk.pop();
                        k = 1;
                        // printing the path along with distances and way ID to be used
                        while (!stk.empty())
                        {
                            auto node = findNode(nodes, id);
                            cout << "Step " << k++ << " : "
                                 << "ID : " << id << " Name : " << ((node.second.first.length() == 0) ? "NA" : node.second.first) << " -> to -> ";
                            node = findNode(nodes, stk.top());
                            wayElement = findWay(ways, graph[id][stk.top()].second);
                            cout << "ID : " << stk.top() << " Name : " << ((node.second.first.length() == 0) ? "NA" : node.second.first) << " via Way ID : " << wayElement.first << " Name : " << ((wayElement.second.first.length() == 0) ? "NA" : wayElement.second.first) << " Distance : " << graph[id][stk.top()].first << endl;
                            id = stk.top();
                            stk.pop();
                        }
                        // print the total distance
                        cout << "Total Distance : " << distances[str2] << endl;
                    }
                }
            }
            cout << "Press enter to continue...";
            getchar();
            getchar();
            break;
        case 6:
            break;
        default:
            cout << "Wrong Choice!!" << endl;
            cout << "Press enter to continue...";
            getchar();
            getchar();
        }
    } while (input != 6);

    return 0;
}