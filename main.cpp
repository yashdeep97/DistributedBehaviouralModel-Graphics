#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <GLFW/glfw3.h>
#include "Boid.h"
#include "Obstacle.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

vector<Boid> flock;
vector<Obstacle> obstacles;
int flag = 0;

int main(void)
{
    GLFWwindow* window;
    srand(time(NULL));
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flock Simulation", NULL, NULL);
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

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(int i = 0; i < flock.size(); i++)
        {
            flock[i].run(flock, obstacles);
        }
        for(int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i].add();
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        flock.push_back(Boid((float)xpos, abs((float)ypos - SCREEN_HEIGHT)));
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        obstacles.push_back(Obstacle((float)xpos, abs((float)ypos - SCREEN_HEIGHT)));
    }    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_S && action == GLFW_PRESS && flag == 0){
        for(int i = 0; i < 200; i++)
        {
            flock.push_back(Boid((float)SCREEN_WIDTH/2, (float)SCREEN_WIDTH/2));
        }
        cout<<"Hello!"<<endl;
        flag = 1;
    }
}
