#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <GLFW/glfw3.h>
#include "Boid.h"
// #include "Flock.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow *window);
// void setupFlock(Flock);
void drawPoint(int x, int y);

int main(void)
{
    GLFWwindow* window;
    srand(time(NULL));
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (window == NULL)
    {
		cout<<"Failed to create window"<<endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // New coordinate system
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode( GL_MODELVIEW );

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Boid b(300.5, 400.6);
    // Flock flock;
    // setupFlock(flock);
    // flock.getSize();

    vector<Boid> flock;
    for(int i = 0; i < 100; i++)
    {
        flock.push_back(Boid((float)SCREEN_WIDTH/2, (float)SCREEN_WIDTH/2));
    }
    cout<<flock.size()<<endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
     
        for(int i = 0; i < flock.size(); i++)
        {
            flock[i].run(flock);
        }
        
        
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

		// handle escape key press
        processInput(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// Re-adjust Viewport size when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// cout<<height<<" "<<width<<endl;
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawPoint(int x, int y){
    int point[] = { x, y };
    glEnableClientState( GL_VERTEX_ARRAY ); //enable drawing vertex array
    // glPointSize(40.0);
    glVertexPointer( 2, GL_INT, 0, point );
    glDrawArrays( GL_POINTS, 0, 1);
    glDisableClientState( GL_VERTEX_ARRAY );
}

// void setupFlock(Flock flock){
    
//     for(int i = 0; i < 100; i++)
//     {
//         Boid b(SCREEN_WIDTH/2, SCREEN_WIDTH/2);
//         flock.addBoid(b);
//     }
    
// }