#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <myshader.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

// Definir constantes
#define W_HEIGHT 600
#define W_WIDTH 600

void processInput(GLFWwindow *window);
void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d, GLfloat vertices[], unsigned int indices[],
unsigned int start);

int main(int argc, char **argv) {
	// START BOILERPLATE
	glewExperimental = GL_TRUE;
	if (!glfwInit()) {
		printf("failed to initialize GLFW.\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Ejercicio 5", nullptr, nullptr);
	int* test = new int;

	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit()) {
		printf("failed to initialize OpenGL\n");
		return -1;
	}

	// END BOILERPLATE

	Shader shader("./shader.vs", "./shader.fs");

	// 8 vértices, 6 datos por cada uno (3 posición, 3 color)
	int nData = 8*6;
	GLfloat vertices[nData];
	for (int i = 0; i < 2; i++) {
		float x = 0, y = 0, z = 0;
		x = (i & 1) ? -0.5 : 0.5;
		for (int j = 0; j < 2; j++) {
			y = (j & 1) ? -0.5 : 0.5;
			for (int k = 0; k < 2; k++) {
				z = (k & 1) ? -0.5 : 0.5;
				int idx = i*24 + j*12 + k*6;
				vertices[idx] = x;
				vertices[idx+1] = y;
				vertices[idx+2] = z;
				vertices[idx+3] = abs(x);
				vertices[idx+4] = abs(y);
				vertices[idx+5] = abs(y);
			}
		}
	}

	// 6 caras, 2 triángulos c/u, 3 puntos por triángulo
	int nIndices = 6*2*3;
	unsigned int indices[nIndices];

	// Definir las caras
	// Los puntos a, b, c, d, deben formar la cara en el orden de las
	// manecillas del reloj
	quad(2, 0, 1, 3, vertices, indices, 0);
	quad(2, 6, 7, 3, vertices, indices, 6);
	quad(0, 4, 5, 1, vertices, indices, 12);
	quad(6, 4, 0, 2, vertices, indices, 18);
	quad(7, 5, 1, 3, vertices, indices, 24);
	quad(6, 4, 5, 7, vertices, indices, 30);

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// primero hay que hacer bind, para que tengan efecto las operaciones
	glBindVertexArray(VAO);

	// configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// indicar a OpenGL cómo interpretar los datos mandados
	glVertexAttribPointer(
		0, // Índice a ser modificado
		3, // Cantidad de componentes por vértice (debe ser 1, 2, 3, ó 4)
		GL_FLOAT, // Tipo de dato
		GL_FALSE, // ¿Normalizar?
		6*sizeof(float), // Stride
		(void*)0 // Offset del primer elemento
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, // Índice a ser modificado
		3, // Cantidad de componentes por vértice (debe ser 1, 2, 3, ó 4)
		GL_FLOAT, // Tipo de dato
		GL_FALSE, // ¿Normalizar?
		6*sizeof(float), // Stride
		(void*)(3*sizeof(float)) // Offset del primer elemento
	);
	glEnableVertexAttribArray(1);

	// configurar EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
				 indices, GL_STATIC_DRAW);

	// Activar 3D
	glm::mat4 model         = glm::mat4(1.0f); // inicializar con matriz identidad
	glm::mat4 view          = glm::mat4(1.0f);
	glm::mat4 projection    = glm::mat4(1.0f);

	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / (float)W_HEIGHT, 0.1f, 100.0f);

	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(shader.ID, "view");

	for (auto x : vertices) {
		std::cout << x << std::endl;
	};

	for (auto x : indices) {
		std::cout << x << std::endl;
	};

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
	model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		shader.setMat4("projection", projection);

		// Triangle
		glBindVertexArray(VAO);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(GL_TRIANGLES, nIndices,
					   GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/* a, b, c, d, son los puntos que delimitan una cara del cuadrado
 * Vértices es un array donde se llenará la información */
void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d, GLfloat vertices[], unsigned int indices[],
unsigned int start) {
	// Los puntos a, b, c, d, deben formar la cara en el orden de las
	// manecillas del reloj
	indices[start] = a;
	indices[start+1] = b;
	indices[start+2] = c;
	indices[start+3] = a;
	indices[start+4] = c;
	indices[start+5] = d;
}
