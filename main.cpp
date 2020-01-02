#include <iostream>
using namespace std;
#include "vgl.h"
#include "LoadShaders.h"
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;
//--------------------------------------------------------------------
//
// init
//
void
init( void )
{
static const GLfloat vertices[NumVertices][2] =
{
{ -0.90f, -0.90f }, // Triangle 1
{ 0.85f, -0.90f },
{ -0.90f, 0.85f },
{ 0.90f, -0.85f }, // Triangle 2
{ 0.90f, 0.90f },
{ -0.85f, 0.90f }
};
glCreateBuffers(NumBuffers, Buffers);
glNamedBufferStorage(Buffers[ArrayBuffer], sizeof (vertices),
vertices, 0);
ShaderInfo shaders[] = {
{ GL_VERTEX_SHADER, "../shaders/triangles.vert" },
{ GL_FRAGMENT_SHADER, "../shaders/triangles.frag" },
{ GL_NONE, NULL }
};
GLuint program = LoadShaders(shaders);
glUseProgram(program);
glGenVertexArrays(NumVAOs, VAOs);
glBindVertexArray(VAOs[Triangles]);
glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
glVertexAttribPointer(vPosition, 2, GL_FLOAT,
GL_FALSE, 0, BUFFER_OFFSET(0));
glEnableVertexAttribArray(vPosition);
}
//--------------------------------------------------------------------
//
// display
//
void
display( void )
{
static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
glClearBufferfv(GL_COLOR, 0, black);
glBindVertexArray(VAOs[Triangles]);
glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}
//--------------------------------------------------------------------
//
// main
//
int
main( int argc, char ** argv)
{
glfwInit();
GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles" , NULL,
NULL);
glfwMakeContextCurrent(window);
gl3wInit();
init();
while (!glfwWindowShouldClose(window))
{
display();
glfwSwapBuffers(window);
glfwPollEvents();
}
glfwDestroyWindow(window);
glfwTerminate();
}