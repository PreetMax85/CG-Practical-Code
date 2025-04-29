#include <iostream>
#include <GL/glut.h>
using namespace std;

int xa, ya, xb, yb, lineType;

void bresenhamLine(int xa, int ya, int xb, int yb, int lineType)
{
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int xStep = (xb > xa) ? 1 : -1;
    int yStep = (yb > ya) ? 1 : -1;

    int x = xa;
    int y = ya;

    if(lineType == 4) glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    
    if (dx >= dy)
    {
        int p = 2 * dy - dx;
        int twoDy = 2 * dy;
        int twoDyDx = 2 * (dy - dx);

        for (int i = 0; i < dx; i++)
        {
            x += xStep;
            if (p < 0)
                p += twoDy;
            else
            {
                y += yStep;
                p += twoDyDx;
            }

            if (lineType == 1) // Simple
            {
                glVertex2d(x, y);
            }
            else if (lineType == 2) // Dotted
            {
                if (i % 4 == 0)
                    glVertex2d(x, y);
            }
            else if (lineType == 3) // Dashed
            {
                if (i % 8 != 0)
                    glVertex2d(x, y);
            }
            else if (lineType == 4) // Solid
            {
                glVertex2d(x, y);
            }
        }
    }
    else
    {
        int p = 2 * dx - dy;
        int twoDx = 2 * dx;
        int twoDxDy = 2 * (dx - dy);

        for (int i = 0; i < dy; i++)
        {
            y += yStep;
            if (p < 0)
                p += twoDx;
            else
            {
                x += xStep;
                p += twoDxDy;
            }

            if (lineType == 1) // Simple
            {
                glVertex2d(x, y);
            }
            else if (lineType == 2) // Dotted
            {
                if (i % 4 == 0)
                    glVertex2d(x, y);
            }
            else if (lineType == 3) // Dashed
            {
                if (i % 8 != 0)
                    glVertex2d(x, y);
            }
            else if (lineType == 4) // Solid
            {
                glVertex2d(x, y);
            }
        }
    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = 480 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xa = x;
        ya = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xb = x;
        yb = y;
        glColor3f(1, 0, 0);
        bresenhamLine(xa, ya, xb, yb, lineType);
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    bresenhamLine(0, 240, 640, 240, 1);
    bresenhamLine(320, 0, 320, 480, 1);
}

int main(int argc, char **argv)
{
    cout << "Enter Line Type (1. Simple 2. Dotted 3. Dashed 4. Solid): ";
    cin >> lineType;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line");
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 0, 0);
    gluOrtho2D(0, 640, 0, 480);
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}