// Including the necessary header file
#include <unordered_map>

// Structure to represent edge data between two nodes
struct data {
    double distance;
    double speed;
    double traffic;
};

// Graph class definition
class Graph {
    private:
    std::unordered_map<int, std::unordered_map<int, data>> map; // Adjacency list representation of the graph

    public:
    ~Graph();                                       // Destructor that clears the graph
    void insert(int a, int b, double d, double s);  // Inserts or updates an edge between nodes a and b
    void load(std::string &filename);               // Loads multiple edges from a file
    bool traffic(int a, int b, double A);           // Updates traffic factor on an edge
    bool update(std::string &filename);             // Updates traffic factors for multiple edges from a file
    void print(int a);                              // Prints all neighbors of node a
    bool erase(int a);                              // Deletes a node and all its edges
    bool path(int a, int b);                        // Prints the shortest-time path from a to b
    double lowest(int a, int b);                    // Returns the shortest travel time from a to b
};