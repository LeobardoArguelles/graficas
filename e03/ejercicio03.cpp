#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <shader.hpp>

#include <glm/glm.hpp>
using namespace glm;

int main() {
	// DECLARACIÓN DE VARIABLES
	int N = 5000;

	// Initialise GLFW
	if ( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open window and create its OpenGL context
	GLFWwindow* window;

	window = glfwCreateWindow(1366, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	vec2 vertices [] = {
	vertices[0] = vec2(-0.5, -0.5),
	vertices[1] = vec2(0.5, -0.5),
	vertices[2] = vec2(0, 0.5)
	};

	vec2 points[N];

	vec2 u = vec2(vertices[0] + vertices[1]);
	vec2 v = vec2(vertices[0] + vertices[2]);
	vec2 p = vec2((u + v)*vec2(0.5, 0.5));

	points[0] = p;

	GLfloat g_vertex_buffer_data[N*3];
	GLfloat g_color_buffer_data[N*3];

	float color[3] = {0};
	float stride = 1.0/(N/255.0);
	std::cout << stride << std::endl;
	unsigned int turn = 0;

	// Inicializar una seed random
	srand(time(NULL));
	for(int i = 1; i < N; i++) {

		int j = rand() % 3;

		// Elegir un nuevo punto al azar
		vec2 new_point = points[i-1] + vertices[j];
		new_point = new_point * vec2(0.5, 0.5);
		points[i] = new_point;
		g_vertex_buffer_data[(i-1)*3] = new_point[0];
		g_vertex_buffer_data[(i-1)*3+1] = new_point[1];
		g_vertex_buffer_data[(i-1)*3+2] = 0.0;

		g_color_buffer_data[(i-1)*3] = color[0];
		g_color_buffer_data[(i-1)*3+1] = color[1];
		g_color_buffer_data[(i-1)*3+2] = color[2];

		if (turn == 0) {
			color[0] += stride;
			if (color[0] > 1) {
				color[0] = 0;
				turn = 1;
			}
		}
		else if (turn == 1) {
			color[1] += stride;
			if (color[1] > 1) {
				color[1] = 0;
				turn = 2;
			}
		}
		else {
			color[2] += stride;
			if (color[2] > 1) {
				color[2] = 0;
				turn = 0;
			}
		}
	}

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
		glDrawArrays(GL_POINTS, 0, N);

		// Cambiar buffers entre el que está trabajando, y el que muestra el
		// resultado final. Evita parpadeos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
	return 0;
}
