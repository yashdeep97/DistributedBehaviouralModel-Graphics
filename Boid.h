#ifndef BOID_H
#define BOID_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GLFW/glfw3.h>

using namespace std;

class Boid
{
    public:
        float posX, posY;
        float velX, velY;
        float accX, accY;
        float r;
        float maxForce, maxSpeed;
        
    public:
        Boid(float x, float y){

            posX = x, posY = y;
            accX = 0.0, accY = 0.0;
            velX = (pow(-1, rand()%10)) * (rand() % 100);
            velY = (pow(-1, rand()%10)) * (rand() % 100);
                        
            r = 2.0;
            maxSpeed = 2.0;
            maxForce = 0.05;

        }

        void draw(){
            float vel = sqrt((velX * velX) + (velY * velY));
            float xDir = (velX / vel);
            float yDir = (velY / vel);
            glBegin(GL_TRIANGLES);
            glColor3f(1, 2, 3);
            glVertex3f(posX + xDir*15, posY + yDir*15, 0);
            glVertex3f(posX + yDir*5, posY - xDir*5, 0);
            glVertex3f(posX - yDir*5, posY + xDir*5, 0);
            glEnd();
        }

        void update(){
            velX += accX;
            velY += accY;

            float vel = sqrt((velX * velX) + (velY * velY));
            velX = (velX / vel) * maxSpeed;
            velY = (velY / vel) * maxSpeed;

            posX += velX;
            posY += velY;

            accX = 0;
            accY = 0;
            
        }

        void steer(float correctX, float correctY){
            float mag = sqrt((correctX * correctX) + (correctY * correctY));
            correctX = (correctX / mag) * maxSpeed;
            correctY = (correctY / mag) * maxSpeed;

            float steerX = correctX - velX;
            float steerY = correctY - velY;
            mag = sqrt((steerX * steerX) + (steerY * steerY));
            steerX = (steerX / mag) * maxForce;
            steerY = (steerX / mag) * maxForce;

            accX += steerX;
            accY += steerY;

        }

        void Avoidance(vector<Boid> flock){

        }

        void Cohesion(vector<Boid> flock){
            float sumX, sumY = 0.0f;
            float d, diffX, diffY;
            for(int i = 0; i < flock.size(); i++)
            {
                diffX = posX - flock[i].posX, diffY = posY - flock[i].posY;
                d = (diffX * diffX) + (diffY * diffY);
                if(d > 0){
                    sumX += flock[i].posX;
                    sumY += flock[i].posY;
                }
            }
            sumX /= (flock.size() - 1);
            sumY /= (flock.size() - 1);

            steer(sumX, sumY);
            
        }

        void Alignment(vector<Boid> flock){

        }

        void applyRules(vector<Boid> flock){
            Avoidance(flock);
            Cohesion(flock);
            Alignment(flock);
        }
        
        void run(vector<Boid> flock){
            applyRules(flock);
            update();
            draw();

        }        
};



#endif