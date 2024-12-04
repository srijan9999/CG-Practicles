#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> controlPoints; // Store control points
int curveType = 1;           // Default to Hermite
Point r1 = {100, 200};       // Tangent at P1 for Hermite
Point r4 = {-100, -200};     // Tangent at P4 for Hermite

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int binomialCoeff(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

Point hermitePoint(float t, Point p1, Point p4, Point r1, Point r4) {
    float h1 = 2 * t * t * t - 3 * t * t + 1;
    float h2 = -2 * t * t * t + 3 * t * t;
    float h3 = t * t * t - 2 * t * t + t;
    float h4 = t * t * t - t * t;

    Point p;
    p.x = h1 * p1.x + h2 * p4.x + h3 * r1.x + h4 * r4.x;
    p.y = h1 * p1.y + h2 * p4.y + h3 * r1.y + h4 * r4.y;
    return p;
}

Point bezierPoint(float t, const vector<Point>& controlPoints) {
    int n = controlPoints.size() - 1;
    Point p = {0, 0};

    for (int i = 0; i <= n; i++) {
        float coeff = binomialCoeff(n, i) * pow(1 - t, n - i) * pow(t, i);
        p.x += coeff * controlPoints[i].x;
        p.y += coeff * controlPoints[i].y;
    }
    return p;
}

void drawCurve() {
    glBegin(GL_LINE_STRIP);

    for (float t = 0; t <= 1; t += 0.01) {
        Point p;
        if (curveType == 1) {
            p = hermitePoint(t, controlPoints[0], controlPoints[1], r1, r4);
        } else {
            p = bezierPoint(t, controlPoints);
        }
        glVertex2f(p.x, p.y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 1);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (const auto& p : controlPoints) {
        glVertex2f(p.x, p.y);
    }
    glEnd();

    glColor3f(1, 0, 0);
    drawCurve();

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    cout << "Enter 1 for Hermite curve, 2 for Bezier curve: ";
    cin >> curveType;

    if (curveType == 1) {
        cout << "Enter P1 (x y): ";
        Point p1, p4;
        cin >> p1.x >> p1.y;
        cout << "Enter P4 (x y): ";
        cin >> p4.x >> p4.y;
        controlPoints = {p1, p4};
    } else if (curveType == 2) {
        int n;
        cout << "Enter number of control points: ";
        cin >> n;
        cout << "Enter control points (x y):" << endl;
        for (int i = 0; i < n; i++) {
            Point p;
            cin >> p.x >> p.y;
            controlPoints.push_back(p);
        }
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hermite / Bezier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
