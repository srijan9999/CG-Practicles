#include <iostream>
#include <vector>
using namespace std;

// Function to plot the points for 8-way symmetry
void plotCirclePoints(int xc, int yc, int x, int y, vector<pair<int, int>> &points) {
    points.push_back({xc + x, yc + y});
    points.push_back({xc - x, yc + y});
    points.push_back({xc + x, yc - y});
    points.push_back({xc - x, yc - y});
    points.push_back({xc + y, yc + x});
    points.push_back({xc - y, yc + x});
    points.push_back({xc + y, yc - x});
    points.push_back({xc - y, yc - x});
}

// Function to implement the Midpoint Circle Drawing Algorithm
vector<pair<int, int>> midpointCircle(int xc, int yc, int r) {
    vector<pair<int, int>> points;

    int x = 0, y = r;
    int p = 1 - r; // Initial decision parameter

    plotCirclePoints(xc, yc, x, y, points);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * x - 2 * y + 1;
        }
        plotCirclePoints(xc, yc, x, y, points);
    }

    return points;
}

int main() {
    int xc, yc, r;

    // Input center and radius
    cout << "Enter the center of the circle (xc, yc): ";
    cin >> xc >> yc;
    cout << "Enter the radius of the circle: ";
    cin >> r;

    // Generate the circle points
    vector<pair<int, int>> circlePoints = midpointCircle(xc, yc, r);

    // Print the circle points
    cout << "The points on the circle are:" << endl;
    for (auto point : circlePoints) {
        cout << "(" << point.first << ", " << point.second << ")" << endl;
    }

    return 0;
}
