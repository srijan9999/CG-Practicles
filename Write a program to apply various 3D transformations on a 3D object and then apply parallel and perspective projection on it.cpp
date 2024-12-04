#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double PI = 3.14159265358979323846;

// Structure to represent a 3D point
struct Point3D {
    double x, y, z, w = 1; // Homogeneous coordinate w = 1 by default
};

// Function to display the object
void displayObject(const vector<Point3D>& object) {
    cout << "Object vertices:" << endl;
    for (const auto& point : object) {
        cout << "(" << point.x << ", " << point.y << ", " << point.z << ")" << endl;
    }
    cout << endl;
}

// Function to apply a transformation matrix to a 3D object
vector<Point3D> applyTransformation(const vector<Point3D>& object, const vector<vector<double>>& matrix) {
    vector<Point3D> transformedObject;

    for (const auto& point : object) {
        Point3D transformed;
        transformed.x = point.x * matrix[0][0] + point.y * matrix[0][1] + point.z * matrix[0][2] + point.w * matrix[0][3];
        transformed.y = point.x * matrix[1][0] + point.y * matrix[1][1] + point.z * matrix[1][2] + point.w * matrix[1][3];
        transformed.z = point.x * matrix[2][0] + point.y * matrix[2][1] + point.z * matrix[2][2] + point.w * matrix[2][3];
        transformed.w = point.x * matrix[3][0] + point.y * matrix[3][1] + point.z * matrix[3][2] + point.w * matrix[3][3];
        transformedObject.push_back(transformed);
    }

    return transformedObject;
}

// Function to create a translation matrix
vector<vector<double>> translationMatrix(double tx, double ty, double tz) {
    return {
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0,  1}
    };
}

// Function to create a scaling matrix
vector<vector<double>> scalingMatrix(double sx, double sy, double sz) {
    return {
        {sx, 0,  0,  0},
        {0,  sy, 0,  0},
        {0,  0,  sz, 0},
        {0,  0,  0,  1}
    };
}

// Function to create a rotation matrix about the X-axis
vector<vector<double>> rotationXMatrix(double angle) {
    double rad = angle * PI / 180.0;
    return {
        {1, 0,        0,         0},
        {0, cos(rad), -sin(rad), 0},
        {0, sin(rad), cos(rad),  0},
        {0, 0,        0,         1}
    };
}

// Function to create a rotation matrix about the Y-axis
vector<vector<double>> rotationYMatrix(double angle) {
    double rad = angle * PI / 180.0;
    return {
        {cos(rad),  0, sin(rad), 0},
        {0,         1, 0,        0},
        {-sin(rad), 0, cos(rad), 0},
        {0,         0, 0,        1}
    };
}

// Function to create a rotation matrix about the Z-axis
vector<vector<double>> rotationZMatrix(double angle) {
    double rad = angle * PI / 180.0;
    return {
        {cos(rad), -sin(rad), 0, 0},
        {sin(rad), cos(rad),  0, 0},
        {0,        0,         1, 0},
        {0,        0,         0, 1}
    };
}

// Function to create a parallel projection matrix
vector<vector<double>> parallelProjectionMatrix() {
    return {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 1}
    };
}

// Function to create a perspective projection matrix
vector<vector<double>> perspectiveProjectionMatrix(double d) {
    return {
        {1, 0, 0,  0},
        {0, 1, 0,  0},
        {0, 0, 1,  0},
        {0, 0, -1/d, 1}
    };
}

int main() {
    int n;
    vector<Point3D> object;

    // Input the object vertices
    cout << "Enter the number of vertices in the 3D object: ";
    cin >> n;
    cout << "Enter the vertices (x y z):" << endl;
    for (int i = 0; i < n; i++) {
        Point3D p;
        cin >> p.x >> p.y >> p.z;
        object.push_back(p);
    }

    displayObject(object);

    // Perform transformations
    while (true) {
        cout << "Choose an operation:" << endl;
        cout << "1. Translation" << endl;
        cout << "2. Scaling" << endl;
        cout << "3. Rotation (X-axis)" << endl;
        cout << "4. Rotation (Y-axis)" << endl;
        cout << "5. Rotation (Z-axis)" << endl;
        cout << "6. Parallel Projection" << endl;
        cout << "7. Perspective Projection" << endl;
        cout << "8. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 8) break;

        vector<vector<double>> transformation;
        switch (choice) {
            case 1: {
                double tx, ty, tz;
                cout << "Enter translation distances (tx ty tz): ";
                cin >> tx >> ty >> tz;
                transformation = translationMatrix(tx, ty, tz);
                break;
            }
            case 2: {
                double sx, sy, sz;
                cout << "Enter scaling factors (sx sy sz): ";
                cin >> sx >> sy >> sz;
                transformation = scalingMatrix(sx, sy, sz);
                break;
            }
            case 3: {
                double angle;
                cout << "Enter rotation angle (degrees): ";
                cin >> angle;
                transformation = rotationXMatrix(angle);
                break;
            }
            case 4: {
                double angle;
                cout << "Enter rotation angle (degrees): ";
                cin >> angle;
                transformation = rotationYMatrix(angle);
                break;
            }
            case 5: {
                double angle;
                cout << "Enter rotation angle (degrees): ";
                cin >> angle;
                transformation = rotationZMatrix(angle);
                break;
            }
            case 6:
                transformation = parallelProjectionMatrix();
                break;
            case 7: {
                double d;
                cout << "Enter distance of the viewer (d): ";
                cin >> d;
                transformation = perspectiveProjectionMatrix(d);
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
