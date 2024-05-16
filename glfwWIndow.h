#pragma once

#ifndef GLFWWINDOW_H
#define GLFWWINSOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <bits/stdc++.h>
#include <learnopengl/shader_m.h>

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int generateGLFWWindow();
GLFWwindow* initGLFWWindow();

#endif // !GLFWWINDOW_H
