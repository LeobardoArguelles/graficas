#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/glut.h>

#include <GLFW/glfw3.h>

#include <shader.hpp>

#include <glm/glm.hpp>
using namespace glm;

void divideTriangle(vec3 a, vec3 b, vec3 c, int count, GLfloat vertices[], GLfloat color[],
					int start, int Ndivisions);
void triangle(vec3 a, vec3 b, vec3 c, GLfloat vertices[], GLfloat color[], int start);

void processInput(GLFWwindow *window);

int main() {
	// DECLARACIÓN DE VARIABLES
	int Ndivisions = 5;

	glewExperimental = GL_TRUE;

	// Initialise GLFW
	if ( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open window and create its OpenGL context
	GLFWwindow* window;

	window = glfwCreateWindow(1366, 768, "Ejercicio 4", NULL, NULL);
	if( !window ) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}


	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	int Nvertices = (int)pow(3.0, Ndivisions+1)*3;
	// El 12*3 es para agregar un slider, requiero 12 vertices
	GLfloat g_vertex_buffer_data[Nvertices + 12*3];
	GLfloat g_color_buffer_data[Nvertices];

	vec3 a = vec3(-0.5, -0.5, 0.0);
	vec3 b = vec3(0.5, -0.5, 0.0);
	vec3 c = vec3(0.0, 0.5, 0.0);
	divideTriangle(a, b, c, Ndivisions, g_vertex_buffer_data, g_color_buffer_data, 0, Ndivisions);

	// Agregar el slider
	g_vertex_buffer_data[Nvertices] = -0.35;
	g_vertex_buffer_data[Nvertices+1] = 0.75;
	g_vertex_buffer_data[Nvertices+2] = 0.0;

	g_vertex_buffer_data[Nvertices+3] = 0.35;
	g_vertex_buffer_data[Nvertices+4] = 0.75;
	g_vertex_buffer_data[Nvertices+5] = 0.0;

	g_vertex_buffer_data[Nvertices+6] = -0.35;
	g_vertex_buffer_data[Nvertices+7] = 0.74;
	g_vertex_buffer_data[Nvertices+8] = 0.0;

	g_vertex_buffer_data[Nvertices+9] = -0.35;
	g_vertex_buffer_data[Nvertices+10] = 0.74;
	g_vertex_buffer_data[Nvertices+11] = 0.0;

	g_vertex_buffer_data[Nvertices+12] = 0.35;
	g_vertex_buffer_data[Nvertices+13] = 0.75;
	g_vertex_buffer_data[Nvertices+14] = 0.0;

	g_vertex_buffer_data[Nvertices+15] = 0.35;
	g_vertex_buffer_data[Nvertices+16] = 0.74;
	g_vertex_buffer_data[Nvertices+17] = 0.0;

	g_vertex_buffer_data[Nvertices+18] = -0.02;
	g_vertex_buffer_data[Nvertices+19] = 0.79;
	g_vertex_buffer_data[Nvertices+20] = 0.0;

	g_vertex_buffer_data[Nvertices+21] = 0.02;
	g_vertex_buffer_data[Nvertices+22] = 0.79;
	g_vertex_buffer_data[Nvertices+23] = 0.0;

	g_vertex_buffer_data[Nvertices+24] = 0.02;
	g_vertex_buffer_data[Nvertices+25] = 0.70;
	g_vertex_buffer_data[Nvertices+26] = 0.0;

	g_vertex_buffer_data[Nvertices+27] = 0.02;
	g_vertex_buffer_data[Nvertices+28] = 0.70;
	g_vertex_buffer_data[Nvertices+29] = 0.0;

	g_vertex_buffer_data[Nvertices+30] = -0.02;
	g_vertex_buffer_data[Nvertices+31] = 0.79;
	g_vertex_buffer_data[Nvertices+32] = 0.0;

	g_vertex_buffer_data[Nvertices+33] = -0.02;
	g_vertex_buffer_data[Nvertices+34] = 0.70;
	g_vertex_buffer_data[Nvertices+35] = 0.0;

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// Esto le indica a OpenGL cómo procesar los datos recibidos
	glVertexAttribPointer(
		0, // Posicion
		3, // Tamaño
		GL_FLOAT, // Tipo de dato
		GL_FALSE, // ¿Normalizar?
		3*sizeof(float), // Stride
		(void*)0 // Offset del primer elemento
	);

	// Hay que habilitar el atributo, 0 es posición
	glEnableVertexAttribArray(0);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glVertexAttribPointer(
		1, // 1: Color
		3, // Tamaño
		GL_FLOAT, // Tipo de dato
		GL_FALSE, // ¿Normalizar?
		3*sizeof(float), // Stride
		(void*)0 //Offset del primer elemento
	);

	// Hay que habilitar el atributo, 1 es color
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader",
									"SimpleFragmentShader.fragmentshader");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glPointSize(2);
	do {
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(programID);

		// Ya solo usamos el VAO, en vez de los VBO
		glBindVertexArray(VAO);

		// N es la cantidad de puntos a usar para dibujar
		glDrawArrays(GL_TRIANGLES, 0, Nvertices+36);

		// Cambiar buffers entre el que está trabajando, y el que muestra el
		// resultado final. Evita parpadeos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
	return 0;
}

void divideTriangle(vec3 a, vec3 b, vec3 c, int count, GLfloat vertices[], GLfloat color[],
int start, int Ndivisions) {
	if (count == 0)
	{
		triangle(a, b, c, vertices, color, start);
	}
	else
	{
		vec3 divisor = vec3(0.5, 0.5, 0.5);
		vec3 ab = (a + b) * divisor;
		vec3 ac = (a + c) * divisor;
		vec3 bc = (b + c) * divisor;

		--count;
		int Nvertices = pow(3.0, Ndivisions+1)*3;
		int division = Nvertices / 3;
		int nextNdivisions = Ndivisions - 1;

		std::cout << "Start: " << start << std::endl;
		std::cout << "Start + division: " << start + division << std::endl;
		std::cout << "Start + 2*division: " << start + 2*division << std::endl << std::endl;

		divideTriangle(a, ab, ac, count, vertices, color, start, nextNdivisions);
		divideTriangle(c, ac, bc, count, vertices, color, start + division, nextNdivisions);
		divideTriangle(b, bc, ab, count, vertices, color, start + 2*division, nextNdivisions);
	}
}

void triangle(vec3 a, vec3 b, vec3 c, GLfloat vertices[], GLfloat color[], int start) {

	vertices[start] = a.x;
	vertices[start+1] = a.y;
	vertices[start+2] = a.z;

	vertices[start+3] = b.x;
	vertices[start+4] = b.y;
	vertices[start+5] = b.z;

	vertices[start+6] = c.x;
	vertices[start+7] = c.y;
	vertices[start+8] = c.z;

	color[start] = 0.13;
	color[start+1] = 0.68;
	color[start+2] = 0.45;

	color[start+3] = 0.13;
	color[start+4] = 0.68;
	color[start+5] = 0.45;

	color[start+6] = 0.13;
	color[start+7] = 0.68;
	color[start+8] = 0.45;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
