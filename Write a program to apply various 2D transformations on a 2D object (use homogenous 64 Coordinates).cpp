#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

// Structure to represent a 2D point
struct Point {
    double x, y, w = 1; // Homogeneous coordinate w = 1 by default
};

// Function to display the vertices of the object
void displayObject(const vector<Point>& object) {
    cout << "Object vertices:" << endl;
    for (const auto& point : object) {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }
    cout << endl;
}

// Function to apply a transformation matrix to the object
vector<Point> applyTransformation(const vector<Point>& object, const vector<vector<double>>& matrix) {
    vector<Point> transformedObject;

    for (const auto& point : object) {
        Point transformed;
        transformed.x = point.x * matrix[0][0] + point.y * matrix[0][1] + point.w * matrix[0][2];
        transformed.y = point.x * matrix[1][0] + point.y * matrix[1][1] + point.w * matrix[1][2];
        transformed.w = point.x * matrix[2][0] + point.y * matrix[2][1] + point.w * matrix[2][2];
        transformedObject.push_back(transformed);
    }

    return transformedObject;
}

// Function to create a translation matrix
vector<vector<double>> translationMatrix(double tx, double ty) {
    return {
        {1, 0, tx},
        {0, 1, ty},
        {0, 0, 1}
    };
}

// Function to create a scaling matrix
vector<vector<double>> scalingMatrix(double sx, double sy) {
    return {
        {sx, 0,  0},
        {0,  sy, 0},
        {0,  0,  1}
    };
}

// Function to create a rotation matrix
vector<vector<double>> rotationMatrix(double angle) {
    double rad = angle * PI / 180.0; // Convert degrees to radians
    return {
        {cos(rad), -sin(rad), 0},
        {sin(rad), cos(rad),  0},
        {0,        0,         1}
    };
}

// Function to create a reflection matrix
vector<vector<double>> reflectionMatrix(char axis) {
    if (axis == 'x') {
        return {
            {1,  0,  0},
            {0, -1,  0},
            {0,  0,  1}
        };
    } else if (axis == 'y') {
        return {
            {-1, 0,  0},
            {0,  1,  0},
            {0,  0,  1}
        };
    } else {
        cerr << "Invalid axis. Using identity matrix." << endl;
        return {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };
    }
}

int main() {
    int n;
    vector<Point> object;

    // Input the object vertices
    cout << "Enter the number of vertices in the object: ";
    cin >> n;
    cout << "Enter the vertices (x y):" << endl;
    for (int i = 0; i < n; i++) {
        Point p;
        cin >> p.x >> p.y;
        object.push_back(p);
    }

    displayObject(object);

    // Perform transformations
    while (true) {
        cout << "Choose a transformation:" << endl;
        cout << "1. Translation" << endl;
        cout << "2. Scaling" << endl;
        cout << "3. Rotation" << endl;
        cout << "4. Reflection" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 5) break;

        vector<vector<double>> transformation;
        switch (choice) {
            case 1: {
                double tx, ty;
                cout << "Enter translation distances (tx ty): ";
                cin >> tx >> ty;
                transformation = translationMatrix(tx, ty);
                break;
            }
            case 2: {
                double sx, sy;
                cout << "Enter scaling factors (sx sy): ";
                cin >> sx >> sy;
                transformation = scalingMatrix(sx, sy);
                break;
            }
            case 3: {
                double angle;
                cout << "Enter rotation angle (degrees): ";
                cin >> angle;
                transformation = rotationMatrix(angle);
                break;
            }
            case 4: {
                char axis;
                cout << "Enter reflection axis (x or y): ";
                cin >> axis;
                transformation = reflectionMatrix(axis);
                break;
            }
            default:
                cout << "Invalid choice. Try again." << endl;
                continue;
        }

        object = applyTransformation(object, transformation);
        displayObject(object);
    }

    return 0;
}
