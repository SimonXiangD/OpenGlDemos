
#include <iostream>
#include "glfwWIndow.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using std::cout;
using std::endl;

int generateGLFWWindow()
{


    GLFWwindow* window = initGLFWWindow();
    if (window == nullptr) return -1;



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(.0, 1., .0, 1.);
        glClear(GL_COLOR_BUFFER_BIT);





        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* initGLFWWindow() {

    GLFWwindow* window;
    
    if (!glfwInit())
        return nullptr;

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW Window", NULL, NULL);
    if (!window)
    {
        cout << "window create falied!" << endl;
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}