#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to represent a point
struct Point {
    int x, y;
};

// Structure to represent an edge
struct Edge {
    int yMax;
    float x;
    float slopeInv; // Inverse slope (1/m)
};

// Function to sort edges by x-coordinate
bool compareByX(const Edge& e1, const Edge& e2) {
    return e1.x < e2.x;
}

// Function to build the edge table
vector<vector<Edge>> buildEdgeTable(vector<Point>& polygon) {
    int n = polygon.size();
    vector<vector<Edge>> edgeTable(500); // Assuming max screen height of 500

    for (int i = 0; i < n; i++) {
        Point p1 = polygon[i];
        Point p2 = polygon[(i + 1) % n]; // Next vertex (wrapping around)

        if (p1.y == p2.y) continue; // Ignore horizontal edges

        // Ensure p1 is the lower point
        if (p1.y > p2.y) swap(p1, p2);

        Edge edge;
        edge.yMax = p2.y;
        edge.x = p1.x;
        edge.slopeInv = (float)(p2.x - p1.x) / (p2.y - p1.y);

        edgeTable[p1.y].push_back(edge);
    }

    return edgeTable;
}

// Function to fill the polygon using Scan-Line algorithm
void scanLineFill(vector<Point>& polygon) {
    auto edgeTable = buildEdgeTable(polygon);

    vector<Edge> activeEdgeTable;

    int y = 0;
    while (y < edgeTable.size()) {
        // Add edges from the edge table to the active edge table
        for (const auto& edge : edgeTable[y]) {
            activeEdgeTable.push_back(edge);
        }

        // Remove edges whose yMax equals the current scan line
        activeEdgeTable.erase(
            remove_if(activeEdgeTable.begin(), activeEdgeTable.end(),
                      [y](Edge& e) { return e.yMax == y; }),
            activeEdgeTable.end());

        // Sort the active edge table by x-coordinate
        sort(activeEdgeTable.begin(), activeEdgeTable.end(), compareByX);

        // Fill pixels between pairs of intersections
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
            if (i + 1 < activeEdgeTable.size()) {
                int xStart = (int)activeEdgeTable[i].x;
                int xEnd = (int)activeEdgeTable[i + 1].x;

                for (int x = xStart; x < xEnd; x++) {
                    cout << "Filling pixel (" << x << ", " << y << ")" << endl;
                }
            }
        }

        // Update x-coordinates in the active edge table
        for (auto& edge : activeEdgeTable) {
            edge.x += edge.slopeInv;
        }

        y++;
    }
}

int main() {
    int n;

    // Input the polygon vertices
    cout << "Enter the number of vertices in the polygon: ";
    cin >> n;

    vector<Point> polygon(n);
    cout << "Enter the vertices of the polygon (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    // Perform scan-line polygon filling
    cout << "Filling the polygon..." << endl;
    scanLineFill(polygon);

    return 0;
}
