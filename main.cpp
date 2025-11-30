

#define GLFW_INCLUDE_NONE
#include "helper/fileIo.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
void print(const char *message) { std::cout << message << std::endl; }
int main() {
  const char *vertexShaderSource = loadFileToHeap("./shaderSrc/main.vert");
  const char *fragmentShaderSource = loadFileToHeap("./shaderSrc/main.frag");
  glfwInit();
  std::cout << "GLFW initialized successfully" << std::endl;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  gladLoadGL();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  GLfloat vertexData[] = {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f,
                          0.0f,  0.0f,  1.0f, 0.0f};
  std::cout << "Vertex data defined" << std::endl;
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  print("vertex shader created");
  glShaderSource(vShader, 1, &vertexShaderSource, NULL);
  print("shader source set");
  glCompileShader(vShader);
  GLint success;
  // 1. Get the compilation status
  glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

  if (!success) { // If success is GL_FALSE (0)
    // 2. Compilation failed, retrieve and print the error log
    GLchar infoLog[512];
    glGetShaderInfoLog(vShader, 512, NULL, infoLog);

    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    // Don't forget to delete the shader object if you plan to exit or retry
    glDeleteShader(vShader);
    return -1;
  } else {
    std::cout << "Vertex shader compiled successfully" << std::endl;
  }
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fShader);
  glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);

  if (!success) { // If success is GL_FALSE (0)
    // 2. Compilation failed, retrieve and print the error log
    GLchar infoLog[512];
    glGetShaderInfoLog(fShader, 512, NULL, infoLog);

    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    // Don't forget to delete the shader object if you plan to exit or retry
    glDeleteShader(fShader);
    return -1;
  } else {
    std::cout << "Fragment shader compiled successfully" << std::endl;
  }

  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vShader);
  glAttachShader(shaderProgram, fShader);
  glLinkProgram(shaderProgram);

  // cleanup shaders as they are linked into program now and no longer necessary
  glDeleteShader(vShader);
  glDeleteShader(fShader);

  // shader has been created successfully
  GLuint VBO, VAO; // vertex buffer object
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
