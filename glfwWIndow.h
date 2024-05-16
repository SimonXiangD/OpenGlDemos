#pragma once

#ifndef GLFWWINDOW_H
#define GLFWWINSOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int generateGLFWWindow();
GLFWwindow* initGLFWWindow();

#endif // !GLFWWINDOW_H
