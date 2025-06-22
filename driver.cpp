// Including the necessary header files
#include <iostream>
#include <string>
#include "graph.h"
#include <sstream>
#include <iomanip>

int main(){ 
    // Variable initializations and declarations
    std::string input, command, parameter;
    int a, b;
    double d, s, A;
    Graph graph;
    
    // Loop that runs until the user enters the "exit" command
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        iss >> command;

        // Inserts an edge between nodes a and b with a given distance and speed
        if (command == "insert") {
            iss >> a >> b >> d >> s;
            graph.insert(a, b, d, s);
            std::cout << "success" << std::endl;

        // Loads a graph from a file with multiple edge insertions
        } else if (command == "load") {
            iss >> parameter;
            graph.load(parameter);
            std::cout << "success" << std::endl;

        // Updates the traffic factor on an edge between nodes a and b
        } else if (command == "traffic") {
            iss >> a >> b >> A;
            if (graph.traffic(a, b, A)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        
        // Updates traffic factors for multiple edges using values from a file
        } else if (command == "update") {
            iss >> parameter;
            if (graph.update(parameter)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }

        // Prints all neighbors of a given node
        } else if (command == "print") {
            iss >> a;
            graph.print(a);
        
        // Deletes a node and all its associated edges from the graph
        } else if (command == "delete") {
            iss >> a;
            if (graph.erase(a)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        
        // Prints the shortest-time path between nodes a and b
        } else if (command == "path") {
            iss >> a >> b;
            if (graph.path(a, b)) {
                std::cout << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        
        // Computes and prints the shortest travel time between nodes a and b
        } else if (command == "lowest") {
            iss >> a >> b;
            double lowest = graph.lowest(a, b);
            if (lowest) {
                std::cout << lowest << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
            
        // Ends the program given the "exit" command
        } else if (command == "exit") {
            break;
        }
    }
}