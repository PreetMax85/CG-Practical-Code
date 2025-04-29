#include <GL/glut.h>

int oldx, oldy, newx, newy;         
int type = 1;                       
bool have_points = false;           

void dda(int x1, int y1, int x2, int y2, int type) {
    float step, x = x1, y = y1, Xin, Yin;   
    int dx = x2 - x1, dy = y2 - y1;        
    step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy); 
    Xin = dx / step;                        
    Yin = dy / step;                        
    glPointSize(type == 4 ? 10.0f : 1.0f);  
    glBegin(GL_POINTS);                     
    glVertex2i((int)x, (int)y);           
    int j = 0;                             
    for (int k = 1; k <= step; k++) {       
        x += Xin;                          
        y += Yin;                           
        if (type == 1 || type == 4)         
            glVertex2i((int)x, (int)y);
        else if (type == 2 && j % 4 == 0)   
            glVertex2i((int)x, (int)y);
        else if (type == 3 && j < 5)        
            glVertex2i((int)x, (int)y);
        j = (j + 1) % 10;                   // Update counter, reset at 10 for dashed pattern
    }
    glEnd();                               
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);           
    glColor3f(1.0, 0.0, 0.0);             
    dda(-350, 0, 350, 0, 1);             
    dda(0, 350, 0, -350, 1);             
    if (have_points) {                    
        glColor3f(0.0, 0.0, 1.0);         
        dda(oldx, oldy, newx, newy, type); 
    }
    glFlush();                              
}

void init() {
    glClearColor(1, 1, 1, 1);     
    glMatrixMode(GL_PROJECTION);           
    glLoadIdentity();                      
    gluOrtho2D(-350, 350, -350, 350);      
}

int cnt = 0;                               
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) { 
        int xi = x - 350, yi = 350 - y;     // Convert screen coords to logical coords
        cnt = (cnt + 1) % 2;                // Toggle between 0 and 1 for first/second point
        if (cnt == 1) {                     // First click
            oldx = xi; oldy = yi;           // Set start point
        } else {                            // Second click
            newx = xi; newy = yi;           // Set end point
            have_points = true;             // Enable line drawing
            glutPostRedisplay();           
        }
        glPointSize(5.0f);                  // Set point size for clicked points
        glColor3f(0.0, 1.0, 0.0);          // Set color to green for points
        glBegin(GL_POINTS);                 // Start drawing a point
        glVertex2i(xi, yi);                 // Plot the clicked point
        glEnd();                            // Finish drawing
        glFlush();                          // Show the point immediately
    }
}

void menu(int a) {
    type = a;                              
    if (have_points) glutPostRedisplay();  
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);                 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    glutInitWindowSize(700, 700);         
    glutInitWindowPosition(50, 50);         
    glutCreateWindow("Line Drawing");       
    init();                                
    glutDisplayFunc(display);               
    glutMouseFunc(mouse);                   
    glutCreateMenu(menu);                  
    glutAddMenuEntry("DDA_SIMPLE", 1);      
    glutAddMenuEntry("DDA_DOTTED", 2);      
    glutAddMenuEntry("DDA_DASHED", 3);     
    glutAddMenuEntry("DDA_SOLID", 4);       
    glutAttachMenu(GLUT_RIGHT_BUTTON);      
    glutMainLoop();                         
    return 0;                              
} 




