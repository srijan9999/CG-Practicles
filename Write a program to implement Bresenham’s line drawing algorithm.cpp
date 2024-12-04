#include <iostream>
#include <vector>
using namespace std;

// Function to implement Bresenham's Line Drawing Algorithm
vector<pair<int, int>> bresenhamLine(int x1, int y1, int x2, int y2) {
    vector<pair<int, int>> points;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        points.push_back({x1, y1}); // Add current point to the result

        if (x1 == x2 && y1 == y2) {
            break; // Exit loop when the endpoint is reached
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return points;
}

int main() {
    int x1, y1, x2, y2;

    // Input start and end points
    cout << "Enter the start point (x1, y1): ";
    cin >> x1 >> y1;
    cout << "Enter the end point (x2, y2): ";
    cin >> x2 >> y2;

    // Get the line points
    vector<pair<int, int>> linePoints = bresenhamLine(x1, y1, x2, y2);

    // Print the line points
    cout << "The points on the line are:" << endl;
    for (auto point : linePoints) {
        cout << "(" << point.first << ", " << point.second << ")" << endl;
    }

    return 0;
}
