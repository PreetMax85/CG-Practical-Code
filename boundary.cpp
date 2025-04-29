#include <GL/glut.h>
#include <iostream> // Used for potential debug output (optional)
using namespace std;

// Define colors (RGB: 0.0 to 1.0)
float boundaryColor[3] = {1.0f, 0.0f, 0.0f}; // Red boundary
float fillColor[3] = {0.0f, 0.0f, 1.0f};   // Blue fill

// --- Helper Function to Compare Colors 
bool colorsMatch(float c1[3], float c2[3]) {
    return c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2];
}

// --- Boundary Fill Algorithm (4-connected recursive) ---
void boundaryFill4(int x, int y, float* fillCol, float* boundaryCol) {
    float currentPixelColor[3];

    // Read the color of the current pixel
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentPixelColor);

    // Check if the current pixel is NOT the boundary color and NOT the fill color
    if (!colorsMatch(currentPixelColor, boundaryCol) && !colorsMatch(currentPixelColor, fillCol))
    {
        // Set the pixel to the fill color
        glColor3fv(fillCol);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush(); // Flush drawing commands to make the pixel visible immediately

        // Recursively call for neighbors (4-connected)
        boundaryFill4(x + 1, y, fillCol, boundaryCol);
        boundaryFill4(x - 1, y, fillCol, boundaryCol);
        boundaryFill4(x, y + 1, fillCol, boundaryCol);
        boundaryFill4(x, y - 1, fillCol, boundaryCol);
    }
}

// --- Display Callback ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a simple polygon (rectangle) with the boundary color
    glColor3fv(boundaryColor);
    glLineWidth(2.0); // Make boundary thicker
    glBegin(GL_LINE_LOOP);
        glVertex2i(100, 100);
        glVertex2i(200, 100);
        glVertex2i(200, 200);
        glVertex2i(100, 200);
    glEnd();

    glFlush(); // Ensure the polygon is drawn before potential filling
}

// --- Mouse Click Callback ---
void mouse(int button, int state, int x, int y) {
    // Start fill on left mouse button down click
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert window coordinates (top-left origin) to OpenGL coordinates (bottom-left origin)
        int openglX = x;
        int openglY = 500 - y;

        cout << "Starting fill at: (" << openglX << ", " << openglY << ")" << endl; // Debug output
        boundaryFill4(openglX, openglY, fillColor, boundaryColor);
    }
}

// --- Initialization ---
void init() {
    // Set the background color
    glClearColor(1, 1, 1, 1);

    // Set up the projection matrix for 2D viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 500); // Match pixel coordinates
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview mode
}

// --- Main Function ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);                        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single buffering and RGB color
    glutInitWindowSize(600, 500); // Set window size
    glutInitWindowPosition(100, 100);           // Set window position
    glutCreateWindow("Boundary Fill Algorithm (Click Inside Polygon)"); // Create window

    init(); // Perform initialization tasks

    glutDisplayFunc(display); // Register display callback
    glutMouseFunc(mouse);     // Register mouse callback

    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;
} 



