/* void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON)
            drawType = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            drawType = 2;
        else if (button == GLUT_MIDDLE_BUTTON)
            drawType = 3;
            
        glutPostRedisplay();
    }
} */


#include <GL/glut.h>

// Global variables
int drawType = 0;  // 0: None, 1: Simple, 2: Concentric, 3: Pattern

// Plot eight symmetric points for the circle
void plotPoint(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc - x);
}

// Bresenham's circle algorithm
void circle(int xc, int yc, int r) {
    int a, x = 0, y = r, p = 3 - 2*r;
    
    glBegin(GL_POINTS);
    plotPoint(xc, yc, x, y);
    
    while (x <= y) {
        a = p < 0 ? p+= 4*x++ + 6 : p += 4*(x++ - y--) + 10;
        plotPoint(xc, yc, x, y);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw red axes
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(-300, 0); glVertex2i(300, 0);  // X-axis
    glVertex2i(0, -300); glVertex2i(0, 300);  // Y-axis
    glEnd();
    
    // Draw circles based on drawType
    if (drawType > 0) {
        glColor3f(0, 1, 1);
        glPointSize(2);
        
        switch (drawType) {
            case 1:  // Simple Circle
                circle(0, 0, 100);
                break;
            case 2:  // Concentric Circles
                circle(0, 0, 50);
                circle(0, 0, 200);
                break;
            case 3: {  // Pattern of circles
                int r = 70;
                circle(0, 0, r);
                circle(r, 0, r);
                circle(-r, 0, r);
                circle(0, -r, r);
                circle(0, r, r);
                break;
            }
        }
    }
    
    glutSwapBuffers();
}

void keyboard(unsigned char button, int x, int y) {
        if (button == 's')
            drawType = 1;
        else if (button == 'c')
            drawType = 2;
        else if (button == 'p')
            drawType = 3;    
        glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham Circle");
    
    // Initialize
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}