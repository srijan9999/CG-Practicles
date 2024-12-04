#include <iostream>
#include <vector>
using namespace std;

// A structure to represent a point
struct Point {
    double x, y;
};

// Function to compute the intersection point of two lines
Point computeIntersection(Point p1, Point p2, Point clip1, Point clip2) {
    double a1 = p2.y - p1.y;
    double b1 = p1.x - p2.x;
    double c1 = a1 * p1.x + b1 * p1.y;

    double a2 = clip2.y - clip1.y;
    double b2 = clip1.x - clip2.x;
    double c2 = a2 * clip1.x + b2 * clip1.y;

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        // Lines are parallel, return an arbitrary point
        return {0, 0};
    }

    double x = (b2 * c1 - b1 * c2) / determinant;
    double y = (a1 * c2 - a2 * c1) / determinant;

    return {x, y};
}

// Function to check if a point is inside the clipping edge
bool isInside(Point test, Point clip1, Point clip2) {
    return (clip2.x - clip1.x) * (test.y - clip1.y) - 
           (clip2.y - clip1.y) * (test.x - clip1.x) >= 0;
}

// Function to clip a polygon against a single edge of the clipping region
vector<Point> clipPolygon(vector<Point> polygon, Point clip1, Point clip2) {
    vector<Point> newPolygon;

    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        Point current = polygon[i];
        Point prev = polygon[(i - 1 + n) % n];

        bool currInside = isInside(current, clip1, clip2);
        bool prevInside = isInside(prev, clip1, clip2);

        if (currInside && prevInside) {
            // Both points are inside, add the current point
            newPolygon.push_back(current);
        } else if (currInside && !prevInside) {
            // Current point is inside, previous is outside, add intersection and current
            newPolygon.push_back(computeIntersection(prev, current, clip1, clip2));
            newPolygon.push_back(current);
        } else if (!currInside && prevInside) {
            // Current point is outside, previous is inside, add intersection
            newPolygon.push_back(computeIntersection(prev, current, clip1, clip2));
        }
    }

    return newPolygon;
}

// Function to perform the Sutherland-Hodgman polygon clipping
vector<Point> sutherlandHodgman(vector<Point> polygon, vector<Point> clipRegion) {
    vector<Point> clippedPolygon = polygon;

    int m = clipRegion.size();
    for (int i = 0; i < m; i++) {
        Point clip1 = clipRegion[i];
        Point clip2 = clipRegion[(i + 1) % m];
        clippedPolygon = clipPolygon(clippedPolygon, clip1, clip2);
    }

    return clippedPolygon;
}

int main() {
    int n, m;

    // Input the polygon vertices
    cout << "Enter the number of vertices in the polygon: ";
    cin >> n;
    vector<Point> polygon(n);
    cout << "Enter the vertices of the polygon (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> polygon[i].x >> polygon[i].y;
    }

    // Input the clipping region vertices
    cout << "Enter the number of vertices in the clipping region: ";
    cin >> m;
    vector<Point> clipRegion(m);
    cout << "Enter the vertices of the clipping region (x y):" << endl;
    for (int i = 0; i < m; i++) {
        cin >> clipRegion[i].x >> clipRegion[i].y;
    }

    // Perform the clipping
    vector<Point> clippedPolygon = sutherlandHodgman(polygon, clipRegion);

    // Output the clipped polygon
    cout << "The vertices of the clipped polygon are:" << endl;
    for (const auto& point : clippedPolygon) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    return 0;
}
