#ifndef FLOCK_H
#define FLOCK_H

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#include "Boid.h"

using namespace std;

class Flock
{
    private:
        vector<Boid> boids;
        
    public:
        Flock(){
            boids.resize(100);
        }

        void addBoid(Boid b){
            boids.push_back(b);
        }

        void getSize(){
            cout<<boids.size()<<endl;
        }
        
        void run(){
            
            for(int i = 0; i < boids.size(); i++)
            {
                boids[i].run();
            }
            
        }        
};



#endif