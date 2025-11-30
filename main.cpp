#include <glad/glad.h>
#include <iostream>

#include <GLFW/glfw3.h>
int main() {
  const char *vertexShaderSource = R"(
#version 330 core

layout(location = 0) in vec3 aPos;      // vertex position
layout(location = 1) in vec3 aColor;    // vertex color (optional)

out vec3 vColor; // pass to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
  )";
  const char *fragmentShaderSource = R"(

#version 330 core

in vec3 vColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor, 1.0);
}
  )";
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLfloat vertexData[] = {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
                          0.0f,  0.0f,  1.0f, 0.0f};
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vShader);

  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fShader);

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vShader);
  glAttachShader(shaderProgram, fShader);
  glLinkProgram(shaderProgram);

  // cleanup shaders as they are linked into program now and no longer necessary
  glDeleteShader(vShader);
  glDeleteShader(fShader);

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glViewport(0, 0, 800, 600);
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
