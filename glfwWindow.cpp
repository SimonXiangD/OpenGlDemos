
#include "glfwWIndow.h"
#include "generateGeo.h"


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const unsigned int CUBE_NUM = 10;

using std::cout;
using std::endl;
using std::vector;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int generateGLFWWindow()
{

    srand(time(NULL));
    GLFWwindow* window = initGLFWWindow();
    if (window == nullptr) return -1;

    vector<float> vertices = vec2tovec1(getCube2d());
    //show(vertices);

    for(int i = 0; i < 0; i++)
    translate(vertices);

    vector<glm::vec3> cubes;
    for (int i = 0; i < CUBE_NUM; i++) {
        cubes.push_back(glm::vec3(random_float(-10, 10), random_float(-10, 10), random_float(-10, 10)));
    }

    cout << vertices.size() << endl;

    glEnable(GL_DEPTH_TEST);

    GLuint triangleVbo, triangleVao;
    glGenBuffers(1, &triangleVbo);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &triangleVao);
    glBindVertexArray(triangleVao);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    Shader rainbowShader("shader/simplest.vs", "shader/posColor.fs");

    double lastTime = glfwGetTime();


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

       /* double curTime = glfwGetTime();
        if (curTime - lastTime <= 0.5) {
            continue;
        }
        lastTime = curTime;*/

        glClearColor(.0, 1., .0, 1.);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);


        rainbowShader.use();
        glBindVertexArray(triangleVao);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5, 1.0, 0.2));
        //model = glm::translate(model, glm::vec3(0.8, 0.8, 0.8));


        rainbowShader.setMat4("view", view);
        rainbowShader.setMat4("projection", projection);
        rainbowShader.setMat4("model", model);

        for (unsigned int i = 0; i < CUBE_NUM; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubes[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            model = glm::scale(model, cubes[i]);
            rainbowShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glDrawArrays(GL_TRIANGLES, 0, vertices.size());


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &triangleVbo);
    glDeleteBuffers(1, &triangleVao);
    glfwTerminate();
    return 0;
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

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

template<class T>
void show(vector<T> v) {
    for (auto t : v) cout << t << endl;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}