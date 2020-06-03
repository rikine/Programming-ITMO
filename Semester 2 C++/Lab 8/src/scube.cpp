#include "scube.h"

void small_cube::rotateZ() noexcept
{
    uint tmp = color[5];
    color[5] = color[3];
    color[3] = color[4];
    color[4] = color[2];
    color[2] = tmp;
}

void small_cube::rotateY() noexcept
{
    uint tmp = color[2];
    color[2] = color[1];
    color[1] = color[3];
    color[3] = color[0];
    color[0] = tmp;
}

void small_cube::rotateX() noexcept
{
    uint tmp = color[0];
    color[0] = color[4];
    color[4] = color[1];
    color[1] = color[5];
    color[5] = tmp;
}

void small_cube::set_color(size_t i, const uchar color_)
{
    if (i > 5)
        throw MyException("Wrong color index");
    uint temp = 0;
    switch (color_)
    {
    case 'w':
        temp = 0xFFFFFF;
        break;
    case 'r':
        temp = 0xFF0000;
        break;
    case 'o':
        temp = 0xFF8000;
        break;
    case 'b':
        temp = 0x0000FF;
        break;
    case 'g':
        temp = 0x00FF00;
        break;
    case 'y':
        temp = 0xFFFF00;
        break;
    default:
        throw MyException("Wrong color input");
    }
    this->color[i] = temp;
}

uchar small_cube::get_color(size_t i)
{
    if (i > 5)
        throw MyException("Wrong color index");

    switch (color[i])
    {
    case 0xFFFFFF:
        return 'w';
    case 0xFF0000:
        return 'r';
    case 0xFF8000:
        return 'o';
    case 0x0000FF:
        return 'b';
    case 0x00FF00:
        return 'g';
    case 0xFFFF00:
        return 'y';
    default:
        throw MyException("Wrong color");
    }
}

uchar *small_cube::at(int i) noexcept
{
    _color[0] = color[i] >> 16;
    _color[1] = color[i] >> 8;
    _color[2] = color[i];

    return _color.begin();
}

void small_cube::draw()
{
    glPushMatrix();
    glBegin(GL_QUADS);

    // верх
    glColor3ubv(at(0));
    glVertex3f(size, size, size);
    glVertex3f(0, size, size);
    glVertex3f(0, 0, size);
    glVertex3f(size, 0, size);

    // низ
    glColor3ubv(at(1));
    glVertex3f(size, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, size, 0);
    glVertex3f(size, size, 0);

    // спереди
    glColor3ubv(at(2));
    glVertex3f(size, 0, size);
    glVertex3f(0, 0, size);
    glVertex3f(0, 0, 0);
    glVertex3f(size, 0, 0);

    // сзади
    glColor3ubv(at(3));
    glVertex3f(size, size, 0);
    glVertex3f(0, size, 0);
    glVertex3f(0, size, size);
    glVertex3f(size, size, size);

    // слева
    glColor3ubv(at(4));
    glVertex3f(0, size, size);
    glVertex3f(0, size, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, size);

    // справа
    glColor3ubv(at(5));
    glVertex3f(size, size, 0);
    glVertex3f(size, size, size);
    glVertex3f(size, 0, size);
    glVertex3f(size, 0, 0);

    glEnd();
    glPopMatrix();
}

void small_cube::draw(double x, double y, double z)
{
    glPushMatrix();
    glTranslated(x, y, z);
    draw();
    glPopMatrix();
}

void small_cube::set_color(size_t i, const uint color_)
{
    if (i > 5)
        throw MyException("Wrong color");
    this->color[i] = color_;
}