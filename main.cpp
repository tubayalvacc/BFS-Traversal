#include <iostream>
#include <queue>  // For std::queue used in BFS
#include <map>    // For std::map to store nodes for quick access
#include <vector> // For std::vector used in adjacency list

// Define the Node structure
struct Node {
    char data;           // Data stored in the node (e.g., 'A', 'B', etc.)
    std::vector<Node*> adj;  // Adjacency list to store pointers to adjacent nodes
    bool visited;       // Flag to check if the node has been visited during BFS
};

// Global map to store nodes with their data as the key
std::map<char, Node*> nodes;

// Function to create the graph
void createGraph() {
    char nodeData;

    // Prompt user to enter nodes
    std::cout << "Enter nodes in the graph (press 'x' to stop): ";
    while (std::cin >> nodeData && nodeData != 'x') {
        // Check if node already exists
        if (nodes.find(nodeData) == nodes.end()) {
            // Create a new node and add it to the map
            Node* newNode = new Node{nodeData, {}, false};
            nodes[nodeData] = newNode;
        }
    }

    // Create edges between nodes
    for (auto& pair : nodes) {
        Node* currentNode = pair.second;  // Get the current node
        char adjData;

        // Prompt user to enter adjacent nodes for the current node
        std::cout << "Enter the links for node " << currentNode->data << " (press 'x' to stop): ";
        while (std::cin >> adjData && adjData != 'x') {
            // Check if adjacent node exists
            if (nodes.find(adjData) != nodes.end()) {
                // Add the adjacent node to the current node's adjacency list
                currentNode->adj.push_back(nodes[adjData]);
            }
        }
    }
}

// Function to perform BFS traversal
void bfs(Node* startNode) {
    if (startNode == nullptr) return; // Check if the starting node is null

    std::queue<Node*> q;  // Queue to manage the BFS traversal
    startNode->visited = true;  // Mark the starting node as visited
    q.push(startNode);  // Add the starting node to the queue

    // Perform BFS traversal
    while (!q.empty()) {
        Node* node = q.front();  // Get the node from the front of the queue
        q.pop();  // Remove the node from the queue
        std::cout << node->data << " ";  // Print the node's data

        // Traverse all adjacent nodes
        for (Node* adjNode : node->adj) {
            // Check if the adjacent node has not been visited
            if (!adjNode->visited) {
                adjNode->visited = true;  // Mark the adjacent node as visited
                q.push(adjNode);  // Add the adjacent node to the queue
            }
        }
    }
    std::cout << std::endl;  // Print a newline at the end of BFS traversal
}

int main() {
    createGraph();  // Create the graph based on user input

    std::cout << "BFS traversal of the graph is: ";
    if (!nodes.empty()) {
        bfs(nodes.begin()->second);  // Start BFS from the first node in the map
    }

    // Clean up dynamically allocated nodes
    for (auto& pair : nodes) {
        delete pair.second;  // Delete each node to free memory
    }

    return 0;  // Return 0 to indicate successful completion
}
