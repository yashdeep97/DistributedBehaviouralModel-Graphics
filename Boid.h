#ifndef BOID_H
#define BOID_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GLFW/glfw3.h>
#include "Obstacle.h"

using namespace std;

#define XMin 0
#define YMin 0
#define XMax 1000
#define YMax 1000

class Boid
{
    public:
        float posX, posY;
        float velX, velY;
        // float r;
        float maxForce, maxVelocity, minVelocity;
        
    public:
        Boid(float x, float y){

            posX = x, posY = y;
            velX = (pow(-1, rand()%10)) * (rand() % 100);
            velY = (pow(-1, rand()%10)) * (rand() % 100);
            velX /= 50;
            velY /= 50;
            maxVelocity = 5.0;
            minVelocity = 0.1;
            maxForce = 0.05;

        }

        void draw(){
            float vel = sqrt((velX * velX) + (velY * velY));
            float xDir = (velX / vel);
            float yDir = (velY / vel);
            glBegin(GL_TRIANGLES);
            glColor3f(1, 1, 1);
            glVertex3f(posX + xDir*15, posY + yDir*15, 0);
            glVertex3f(posX + yDir*5, posY - xDir*5, 0);
            glVertex3f(posX - yDir*5, posY + xDir*5, 0);
            glEnd();
        }

        void update(){

            posX += velX;
            posY += velY;
        }

        void Avoidance(vector<Boid> flock){
            float sumX, sumY = 0.0f;
            float d, diffX, diffY;
            for(int i = 0; i < flock.size(); i++)
            {
                diffX = posX - flock[i].posX, diffY = posY - flock[i].posY;
                d = sqrt((diffX * diffX) + (diffY * diffY));
                if(d < 20.0 && d > 0.0){
                    sumX -= (flock[i].posX - posX)/(d);
                    sumY -= (flock[i].posY - posY)/(d);
                }
            }

            velX += sumX/2;
            velY += sumY/2;
        }

        void avoidObstacles(vector<Obstacle> obstacles){
            float sumX, sumY = 0.0f;
            float d, diffX, diffY;
            for(int i = 0; i < obstacles.size(); i++)
            {
                diffX = obstacles[i].posX - posX, diffY = obstacles[i].posY - posY;
                d = sqrt((diffX * diffX) + (diffY * diffY));
                float dot = velX*diffX + velY*diffY;
                if(dot == (-1) * d){

                } else if(d < 100.0 && dot > 0.5){                    
                    sumX += (velX - diffX)/(d);
                    sumY += (velY - diffY)/(d);
                } else if(d < 100.0 && dot < 0){                    
                    sumX -= (velX - diffX)/(d*5);
                    sumY -= (velY - diffY)/(d*5);
                }
            }
            float mag = (velX * velX) + (velY * velY);
            velX += (sumX/10) * mag;
            velY += (sumY/10) * mag;
        }

        void Cohesion(vector<Boid> flock){
            float sumX, sumY = 0.0f;
            for(int i = 0; i < flock.size(); i++)
            {
                if(posX != flock[i].posX && posY != flock[i].posY){
                    sumX += flock[i].posX;
                    sumY += flock[i].posY;
                }
            }
            sumX /= (flock.size() - 1);
            sumY /= (flock.size() - 1);

            velX += (sumX - posX)/20000;
            velY += (sumY - posY)/20000;
        }

        void Alignment(vector<Boid> flock){
            float sumVelX, sumVelY = 0.0f;
            for(int i = 0; i < flock.size(); i++)
            {
                if(posX != flock[i].posX && posY != flock[i].posY){
                    sumVelX += flock[i].velX;
                    sumVelY += flock[i].velY;
                }
            }
            sumVelX /= (flock.size() - 1);
            sumVelY /= (flock.size() - 1);

            velX += (sumVelX - velX)/20.0;
            velY += (sumVelY - velY)/20.0;
        }

        void applyRules(vector<Boid> flock, vector<Obstacle> obstacles){
            Avoidance(flock);
            Cohesion(flock);
            Alignment(flock);
            avoidObstacles(obstacles);
        }

        void limitVelocity(){
            float vel = sqrt((velX * velX) + (velY * velY));
            if (vel > maxVelocity) {
                velX = (velX / vel) * maxVelocity;
                velY = (velY / vel) * maxVelocity;
            }

            if (vel < minVelocity) {
                velX = (velX / vel) * minVelocity;
                velY = (velY / vel) * minVelocity;
            }
            
            
        }

        void boundPosition(){
            
            if ( posX < XMin ) {
                posX = XMax;
            } else if ( posX > XMax ) {
                posX = XMin;
            }
            if ( posY < YMin ) {
                posY = YMax;
            } else if ( posY > YMax ) {
                posY = YMin;
            }
            
        }
        
        void run(vector<Boid> flock, vector<Obstacle> obstacles){
            applyRules(flock, obstacles);
            limitVelocity();
            boundPosition();
            update();
            draw();

        }        
};



#endif