#include <iostream>
using namespace std;

// Region codes for the endpoints
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Function to compute region code for a point (x, y)
int computeCode(double x, double y, double xmin, double ymin, double xmax, double ymax) {
    int code = INSIDE;

    if (x < xmin)       // To the left of the rectangle
        code |= LEFT;
    else if (x > xmax)  // To the right of the rectangle
        code |= RIGHT;
    if (y < ymin)       // Below the rectangle
        code |= BOTTOM;
    else if (y > ymax)  // Above the rectangle
        code |= TOP;

    return code;
}

// Cohen-Sutherland line clipping algorithm
void cohenSutherlandClip(double x1, double y1, double x2, double y2,
                         double xmin, double ymin, double xmax, double ymax) {
    int code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
    int code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
    bool accept = false;

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            // Both endpoints lie within the rectangle
            accept = true;
            break;
        } else if (code1 & code2) {
            // Both endpoints are outside the rectangle in the same region
            break;
        } else {
            // Some segment of the line is inside the rectangle
            int code_out;
            double x, y;

            // At least one endpoint is outside the rectangle
            code_out = code1 ? code1 : code2;

            // Find intersection point
            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            // Replace the outside point with the intersection point
            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1, xmin, ymin, xmax, ymax);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2, xmin, ymin, xmax, ymax);
            }
        }
    }

    if (accept) {
        cout << "Line accepted from (" << x1 << ", " << y1 << ") to ("
             << x2 << ", " << y2 << ")" << endl;
    } else {
        cout << "Line rejected." << endl;
    }
}

int main() {
    double x1, y1, x2, y2;
    double xmin, ymin, xmax, ymax;

    // Input the rectangle coordinates
    cout << "Enter the coordinates of the clipping rectangle (xmin, ymin, xmax, ymax): ";
    cin >> xmin >> ymin >> xmax >> ymax;

    // Input the line coordinates
    cout << "Enter the coordinates of the line endpoints (x1, y1, x2, y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    // Perform line clipping
    cohenSutherlandClip(x1, y1, x2, y2, xmin, ymin, xmax, ymax);

    return 0;
}
