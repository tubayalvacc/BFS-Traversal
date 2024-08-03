#include <iostream>
#include <queue>
#include <map>
#include <vector>

// Define the Node structure
struct Node {
    char value;             // Value stored in the node (e.g., 'A', 'B', etc.)
    std::vector<Node*> neighbors;  // Adjacency list to store pointers to adjacent nodes
    bool isVisited;         // Flag to check if the node has been visited during BFS
};

// Global map to store nodes with their value as the key
std::map<char, Node*> nodeMap;

// Function to create the graph
void createGraph() {
    char nodeValue;

    // Prompt user to enter nodes
    std::cout << "Enter nodes in the graph (press 'x' to stop): ";
    while (std::cin >> nodeValue && nodeValue != 'x') {
        // Check if the node already exists in the map
        if (nodeMap.find(nodeValue) == nodeMap.end()) {
            // Create a new node and add it to the map
            Node* newNode = new Node{nodeValue, {}, false};
            nodeMap[nodeValue] = newNode;
        }
    }

    // Create edges (links) between nodes
    for (auto& pair : nodeMap) {
        Node* currentNode = pair.second;  // Get the current node
        char neighborValue;

        // Prompt user to enter adjacent nodes for the current node
        std::cout << "Enter the links for node " << currentNode->value << " (press 'x' to stop): ";
        while (std::cin >> neighborValue && neighborValue != 'x') {
            // Check if the neighbor node exists in the map
            if (nodeMap.find(neighborValue) != nodeMap.end()) {
                // Add the neighbor node to the current node's adjacency list
                currentNode->neighbors.push_back(nodeMap[neighborValue]);
            }
        }
    }
}

// Function to perform BFS traversal
void bfs(Node* startNode) {
    if (startNode == nullptr) return; // Check if the starting node is null

    std::queue<Node*> nodeQueue;  // Queue to manage the BFS traversal
    startNode->isVisited = true;  // Mark the starting node as visited
    nodeQueue.push(startNode);    // Add the starting node to the queue

    // Perform BFS traversal
    while (!nodeQueue.empty()) {
        Node* currentNode = nodeQueue.front();  // Get the node from the front of the queue
        nodeQueue.pop();  // Remove the node from the queue
        std::cout << currentNode->value << " ";  // Print the node's value

        // Traverse all neighbors of the current node
        for (Node* neighbor : currentNode->neighbors) {
            // Check if the neighbor node has not been visited
            if (!neighbor->isVisited) {
                neighbor->isVisited = true;  // Mark the neighbor node as visited
                nodeQueue.push(neighbor);  // Add the neighbor node to the queue
            }
        }
    }
    std::cout << std::endl;  // Print a newline at the end of BFS traversal
}

int main() {
    createGraph();  // Create the graph based on user input

    std::cout << "BFS traversal of the graph is: ";
    if (!nodeMap.empty()) {
        bfs(nodeMap.begin()->second);  // Start BFS from the first node in the map
    }

    // Clean up dynamically allocated nodes
    for (auto& pair : nodeMap) {
        delete pair.second;  // Delete each node to free memory
    }

    return 0;  // Return 0 to indicate successful completion
}
