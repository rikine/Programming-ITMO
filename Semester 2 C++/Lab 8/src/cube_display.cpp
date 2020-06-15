#include "cube.h"

void Cube::draw() //просто блять нахуй рисует кубик
{
    for (auto &c : ok)
        for (auto &c1 : c)
            for (auto &c2 : c1)
                c2 = true;

    if (current != -1)
    {
        glPushMatrix();
        int i, j, k;

        if (current == 0 || current == 1)
        {
            k = (current & 1) * 2;
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    ok[i][j][k] = false;

            glTranslated(size / 2, size / 2, 0);
            glRotatef(rotate[current], 0, 0, 1); // ПРОСТО КРУЧУ ЕПТА
            glTranslated(-size / 2, -size / 2, 0);
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    parts[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k); //ПРОСТО РИСУЮ ТО ЧТО ПОКРУТИЛ
        }
        else if (current == 2 || current == 3)
        {
            j = (current & 1) * 2;
            for (i = 0; i < 3; i++)
                for (k = 0; k < 3; k++)
                    ok[i][j][k] = false;

            glTranslated(size / 2, 0, size / 2);
            glRotatef(rotate[current], 0, 1, 0);
            glTranslated(-size / 2, 0, -size / 2);
            for (i = 0; i < 3; i++)
                for (k = 0; k < 3; k++)
                    parts[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
        }
        else if (current == 4 || current == 5)
        {
            i = (current & 1) * 2;
            for (j = 0; j < 3; j++)
                for (k = 0; k < 3; k++)
                    ok[i][j][k] = false;

            glTranslated(0, size / 2, size / 2);
            glRotatef(rotate[current], 1, 0, 0);
            glTranslated(0, -size / 2, -size / 2);
            for (j = 0; j < 3; j++)
                for (k = 0; k < 3; k++)
                    parts[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
        }
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                if (ok[i][j][k])
                    parts[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
}

void Cube::rot90(int idx, int sign)
{
    int i, j, k;
    if (sign == -1)
   
        if (idx == 0 || idx == 1)
        {
            //down, up
            k = (idx & 1) * 2;
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    tmp[j][2 - i] = parts[i][j][k];
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)
                    tmp[i][j].rotateZ(), parts[i][j][k] = tmp[i][j];
        }
        else if (idx == 2 || idx == 3)
        {
            //left, right
            j = (idx & 1) * 2;
            for (i = 0; i < 3; i++)
                for (k = 0; k < 3; k++)
                    tmp[k][2 - i] = parts[i][j][k];
            for (i = 0; i < 3; i++)
                for (k = 0; k < 3; k++)
                    tmp[i][k].rotateX(), parts[i][j][k] = tmp[i][k];
        }
        else if (idx == 4 || idx == 5)
        {
            // front, back
            i = (idx & 1) * 2;
            for (j = 0; j < 3; j++)
                for (k = 0; k < 3; k++)
                    tmp[k][2 - j] = parts[i][j][k];
            for (j = 0; j < 3; j++)
                for (k = 0; k < 3; k++)
                    tmp[j][k].rotateY(), parts[i][j][k] = tmp[j][k];
        }
    
}

void Cube::Rotate(int idx, int angle) //3Д поворот
{
    if (current == -1 || current == idx)//если поворачивается текущая грань или не поворач
    {
        if (idx == -1)
            return;

        rotate[idx] += angle;

        if (rotate[idx] % 90 != 0)
        {
            current = idx;
        }
        else
        {
            if (current == 2 || current == 3)
                rot90(idx, 1);
            else
                rot90(idx, -1);
            rotate[idx] = 0;
            current = -1;
        }
    }
}
