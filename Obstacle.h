#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GLFW/glfw3.h>

using namespace std;

class Obstacle
{
    public:
        float posX, posY;

    public:
        Obstacle(float x, float y){
            posX = x, posY = y;
        }

        void draw(){
            glBegin(GL_QUADS);
            glColor3f(1, 0, 0);
            glVertex3f(posX + 10, posY + 10, 0);
            glVertex3f(posX + 10, posY - 10, 0);
            glVertex3f(posX - 10, posY - 10, 0);
            glVertex3f(posX - 10, posY + 10, 0);
            glEnd();
        }
        
        void add(){
            draw();
        }        
};

#endif