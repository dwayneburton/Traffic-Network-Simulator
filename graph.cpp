// Including the necessary header file
#include <iostream>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <queue>
#include <iomanip>
#include <functional>

// Graph destructor that clears all stored edges
Graph::~Graph() {
    map.clear();
}

// Inserts an edge between nodes a and b with given distance and speed
void Graph::insert(int a, int b, double d, double s) {
    // If edge does not exist, initialize traffic to 1
    if (map.find(a) == map.end() || map[a].find(b) == map[a].end()) {
        map[a][b].distance = d;
        map[a][b].speed = s;
        map[a][b].traffic = 1;
    } else {
        map[a][b].distance = d;
        map[a][b].speed = s;
    }

    // Insert reciprocal edge for undirected graph
    if (map.find(b) == map.end() || map[b].find(a) == map[b].end()) {
        map[b][a].distance = d;
        map[b][a].speed = s;
        map[b][a].traffic = 1;
    } else {
        map[b][a].distance = d;
        map[b][a].speed = s;
    }
}

// Loads edges from a file and inserts them into the graph
void Graph::load(std::string &filename) {
    std::ifstream file(filename);
    std::string input;
    int a, b;
    double d, s;
    while (std::getline(file, input)) {
        std::istringstream iss(input);
        iss >> a >> b >> d >> s;
        insert(a, b, d, s);
    }
}

// Updates traffic factor on an edge if it exists
bool Graph::traffic(int a, int b, double A) {
    if (map.find(a) == map.end() || map[a].find(b) == map[a].end()) {
        return 0;
    } else {
        map[a][b].traffic = A;
        map[b][a].traffic = A;
        return 1;
    }
}

// Loads and applies multiple traffic updates from a file
bool Graph::update(std::string &filename) {
    std::ifstream file(filename);
    std::string input;
    int a, b;
    double A;
    bool updated = false;
    while (std::getline(file, input)) {
        std::istringstream iss(input);
        iss >> a >> b >> A;
        if (traffic(a, b, A)) {
            updated = true;
        }
    }
    return updated;
}

// Prints all neighbor nodes directly connected to node a
void Graph::print(int a) {
    if (map.find(a) == map.end()) {
        std::cout << "failure" << std::endl;
    } else {
        for (auto &p: map[a]) {
            std::cout << p.first << " ";
        }
        std::cout << std::endl;
    }
}

// Deletes node a and all edges connected to it
bool Graph::erase(int a) {
    if (map.find(a) == map.end()) {
        return 0;
    }
    for (auto &p: map[a]) {
        map[p.first].erase(a);
    }
    map.erase(a);
    return 1;
}

// Computes and prints the shortest-time path from a to b using Dijkstra’s algorithm
bool Graph::path(int a, int b) {
    if (map.find(a) == map.end() || map.find(b) == map.end()) {
        return 0;
    }

    std::unordered_map<int, double> distance;
    std::unordered_map<int, int> visited;

    // Priority queue with custom comparator for time-based distances
    std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> pq([&distance](int left, int right) {return std::max(distance[left], distance[right]) == distance[left];});

    // Initialize all nodes with infinite distance
    for (auto &p: map) {
        distance[p.first] = std::numeric_limits<double>::infinity();
        visited[p.first] = -1;
    }

    // Set starting node distance to 0
    distance[a] = 0;
    pq.push(a);

    // Dijkstra’s main loop
    while (!pq.empty()) {
        if (pq.top() == b) {
            break;
        }

        for (auto &p: map[pq.top()]) {
            double time = p.second.distance / (p.second.speed * p.second.traffic);
            if (distance[pq.top()] + time < distance[p.first]) {
                distance[p.first] = distance[pq.top()] + time;
                visited[p.first] = pq.top();
                pq.push(p.first);
            }
        }
        pq.pop();
    }

    // If no path exists
    if (distance[b] == std::numeric_limits<double>::infinity()) {
        return 0;
    }

    // Backtrack to construct path
    std::vector<int> path;
    while (b != -1) {
        path.push_back(b);
        b = visited[b];
    }

    // Print path in reverse order
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << " ";
    }
    return 1;
}

// Computes and returns the shortest travel time from a to b using Dijkstra’s algorithm
double Graph::lowest(int a, int b) {
    if (map.find(a) == map.end() || map.find(b) == map.end()) {
        return 0; 
    }

    std::unordered_map<int, double> distance;

    // Priority queue with custom comparator for time-based distances
    std::priority_queue<int, std::vector<int>, std::function<bool(int, int)>> pq([&distance](int left, int right) {return std::max(distance[left], distance[right]) == distance[left];});

    // Initialize all nodes with infinite distance
    for (auto &p: map) {
        distance[p.first] = std::numeric_limits<double>::infinity();
    }

    // Set starting node distance to 0
    distance[a] = 0;
    pq.push(a);

    // Dijkstra’s main loop
    while (!pq.empty()) {
        if (pq.top() == b) {
            break;
        }

        for (auto &p: map[pq.top()]) {
            double time = p.second.distance / (p.second.speed*p.second.traffic);
            if (distance[pq.top()] + time < distance[p.first]) {
                distance[p.first] = distance[pq.top()] + time;
                pq.push(p.first);
            }
        }
        pq.pop();
    }

    // Format output precision to 3 decimal places
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(3);

    // Return 0 if no path exists; otherwise, return shortest time
    if (distance[b] == std::numeric_limits<double>::infinity()) {
        return 0;
    } else {
        return distance[b];
    }
}