#pragma once

#ifndef GLFWWINDOW_H
#define GLFWWINSOW_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <bits/stdc++.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

using namespace std;




int generateGLFWWindow();
GLFWwindow* initGLFWWindow();


template<class T>
void show(vector<T> v);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif // !GLFWWINDOW_H
