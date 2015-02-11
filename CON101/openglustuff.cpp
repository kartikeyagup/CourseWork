#include <GL/glut.h>

float rx = 0;
float ry = 0;
float rz = 0;
void display()
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 10.0);//1.5, 20.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
    glTranslatef( 0, 0, -3 );

    glColor3f (1.0, 1.0, 1.0);
    glScalef (1.0, 2.0, 1.0);
    glRotatef( -rx, 1, 0, 0 );
    glRotatef( -ry, 0, 1, 0 );
    glRotatef( -rz, 0, 0, 1 );
    glutWireCube (1.0);

    glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
    if( key == 'x' ) rx += 5;
    if( key == 'y' ) ry += 5;
    if( key == 'z' ) rz += 5;
}

void timer( int extra )
{
    // run display() every 16ms or so
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

int main(int argc, char** argv)
{   
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize (500, 500); 
    glutCreateWindow(argv[0]);

    glShadeModel (GL_FLAT);

    glutDisplayFunc(display); 
    glutKeyboardFunc( keyboard );
    glutTimerFunc( 0, timer, 0 );
    glutMainLoop();
    return 0;
}