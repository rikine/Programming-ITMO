#include "GL/freeglut.h"
#include <array>
#include "cube.h"
#include <exception>

constexpr auto CUBE_SIZE = 12;
constexpr auto TIMER = 15;
Cube cube;

// colors
//                            (up,     down,     front,     back,     left,     right)
std::array<uint, 6> sides = {0xFFFFFF, 0xFFFF00, 0x00FF00, 0x0000FF, 0xFF8000, 0xFF0000};

//start position
int xCam = 0, yCam = 0, zCam = 0;

// move on z
double zCube = -35.0;

//angel of movement
int angel = 10;

bool automated = false;

//solution
std::vector<uchar> p;

void automate();

uint edge(const uchar c)
{
    if (c == 'F')
        return 2;
    else if (c == 'w')
        return 3;
    else if (c == 'r')
        return 5;
    else if (c == 'L')
        return 4;
    else if (c == 'u')
        return 1;
    else if (c == 'D')
        return 0;
    return 10;
}

void display()
{
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glTranslated(0, 0, zCube);
    glRotatef(xCam, 1, 0, 0);
    glRotatef(yCam, 0, 1, 0);
    glTranslated(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
    cube.draw();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w / h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init()
{
    glClearColor(0.07, 0.07, 0.07, 0.0);
    glEnable(GL_DEPTH_TEST);

    cube.set_size(CUBE_SIZE);
    cube.set_def_col(sides);
    cube.clear();

    cube.input();
    cube.check_invariants();
}

void specialKeys(int key, int, int)
{
    if (key == GLUT_KEY_DOWN)
    {
        xCam += 3;
        if (xCam >= 360)
            xCam -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_UP)
    {
        xCam -= 3;
        if (xCam < 0)
            xCam += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_RIGHT)
    {
        yCam += 3;
        if (yCam >= 360)
            yCam -= 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_LEFT)
    {
        yCam -= 3;
        if (yCam < 0)
            yCam += 360;
        glutPostRedisplay();
    }

    if (key == GLUT_KEY_F1)
    {
        cube.clear();
        glutPostRedisplay();
    }
}

void keys(uchar key, int, int)
{
    if (cube.get_current() == -1 && key == 's')
    {
        cube.solver();
        p = cube.solution();
    }

    if (cube.get_current() == -1 && key >= '0' && key < '6')
    {
        cube.Rotate(key - '0', angel);
        display();
    }

    if (key == 'a')
    {
        automated = automated ? false : true;
    }

    if (cube.get_current() == -1 && key == 'z')
    {
        automate();
    }
}

void timer(int)
{
    glutTimerFunc(TIMER, timer, 0);
    if (automated)
    {
        if (cube.get_current() == -1)
            automate();
        else
            cube.Rotate(cube.get_current(), angel);
    }
    else
        cube.Rotate(cube.get_current(), angel);
    display();
}

void automate()
{
    if (!p.empty())
    {
        if (cube.get_current() == -1)
        {
            cube.Rotate(edge(p.back()), angel);
            p.pop_back();
        }
    }
    else
        automated = false;
    display();
}

int main(int argc, const char *argv[])
{
    glutInit(&argc, const_cast<char **>(argv));
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 720);
    glutInitWindowPosition(20, 20);
    glutCreateWindow("Rubic'x Cube");
    try
    {
        init();
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keys);
        glutTimerFunc(TIMER, timer, 0);
        glutSpecialFunc(specialKeys);
        glutMainLoop();
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}