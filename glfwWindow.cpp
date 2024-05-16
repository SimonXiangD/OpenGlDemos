
#include "glfwWIndow.h"
#include "generateGeo.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using std::cout;
using std::endl;
using std::vector;

template<class T>
void show(vector<T> v) {
    for (auto t : v) cout << t << endl;
}

int generateGLFWWindow()
{

    srand(time(NULL));
    GLFWwindow* window = initGLFWWindow();
    if (window == nullptr) return -1;

    vector<float> vertices = vec2tovec1(getTraingle2d());
    show(vertices);

    GLuint triangleVbo, triangleVao;
    glGenBuffers(1, &triangleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &triangleVao);
    glBindVertexArray(triangleVao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);


    Shader rainbowShader("shader/simplest.vs", "shader/posColor.fs");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(.0, 1., .0, 1.);
        glClear(GL_COLOR_BUFFER_BIT);


        rainbowShader.use();
        glBindVertexArray(triangleVao);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());


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