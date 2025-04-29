#include<iostream>
#include<GL/glut.h>
using namespace std;

int xa, ya, xb, yb, lineType;
int Round(float a)
{
    return (int)(a+0.5);
}

void ddaLine(int xa, int ya, int xb, int yb, int lineType)
{
    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;

    if(abs(dx) > abs(dy)) steps = abs(dx);
    else steps = abs(dy);
    
    float x, y, xinc, yinc;
    x = xa;
    y = ya;

    xinc = dx/(float) steps;
    yinc = dy/(float) steps;

    if(lineType == 4) glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2d(Round(x), Round(y));
    for(int k = 0; k<steps; k++)
    {
        if(lineType == 1)
        {
            x += xinc;
            y += yinc;
            glVertex2d(Round(x), Round(y));
        }
        else if(lineType == 2)
        {
            if(k%4 == 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x += xinc;
            y += yinc;
        }
        else if(lineType == 3)
        {
            if(k%4 != 0)
            {
                glVertex2d(Round(x), Round(y));
            }
            x += xinc;
            y += yinc;
        }
        else
        {
            x += xinc;
            y += yinc;
            glVertex2d(Round(x), Round(y));
        }
    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    y = 480 - y;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xa = x;
        ya = y;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        xb = x;
        yb = y;
        glColor3f(1, 0, 0);
        ddaLine(xa, ya, xb, yb, lineType);
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 1, 0);
    ddaLine(0, 240, 640, 240, 1);
    ddaLine(320, 0, 320, 480, 1);
    glFlush();
}

int main(int argc, char**argv)
{
    cout<<"Line Type (1. Simple, 2. Dotted, 3. Dashed, 4. Solid) = ";
    cin>>lineType;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,480);
    glutCreateWindow("DDA Line");
    glClearColor(0,0,0,0);
    glColor3f(1,0,0);
    gluOrtho2D(0,640 ,0,480);
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}