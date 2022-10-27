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
#define STARTING_DIVISIONS 0
#define MIN_DIVISIONS 0
#define MAX_DIVISIONS 6

struct data {
	int divisions;
	vec3 a, b, c, d;
	float* vertices;
	float* slider_vertices;
	int* idx_slider_modify; // Indices que deben ser incrementados/decrementados, en orden
	float space;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int VBOs;
	int nVertices;
	int nVertices_slider;
};

int getNVertices(int divisions);
void divideTetra(vec3 a, vec3 b, vec3 c, vec3 d, int count, GLfloat vertices[],
				int start, int Ndivisions);
void tetra(vec3 a, vec3 b, vec3 c, vec3 d, GLfloat vertices[], int start);
void triangle(vec3 a, vec3 b, vec3 c, GLfloat vertices[], int start, vec3 fColor);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void decreaseTriangle(data* d);
void increaseTriangle(data* d);
void changeTriangle(data* d, int delta);
void moveSquare(data* d, bool left=false);

int main(int argc, char **argv) {
	// Declaración de variables
	int nVertices = 0;
	int divisions = STARTING_DIVISIONS;
	data *d = new data;

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

	// Shader myShader("./shader.vs", "./shader.fs");

	// TRIÁNGULO DE SERPINSKI
	nVertices = getNVertices(divisions);
	// nVertices = 54*4;
	float vertices[nVertices];

	// VALORES INICIALES
	vec3 a = vec3(-1.0f,  -1.0f, -1.0f);
	vec3 b = vec3(1.0f,  -1.0f, -1.0f);
	vec3 c = vec3(0.0f,   1.0f, -1.0f);
	vec3 de = vec3(0.0f,  0.0f, 1.0f);

	divideTetra(a, b, c, de, divisions, vertices, 0, divisions);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	d->a = a;
	d->b = b;
	d->c = c;
	d->d = de;
	d->divisions = divisions;
	d->vertices = vertices;
	d->VAO = VAO;
	d->VBO = VBO;
	d->nVertices = nVertices;
	glfwSetWindowUserPointer(window, d);
	

	// primero hay que hacer bind, para que tengan efecto las operaciones
	glBindVertexArray(VAO);

	// configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

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

	// SLIDER

	Shader shader_3d("./shader_3d.vs", "./shader.fs");
	Shader slider_shader("./shader_2d.vs", "./shader.fs");
	float sliderHeight = 0.008;
	float sliderL = -0.85;
	float sliderR = -1*sliderL;
	float sliderT = 0.85;
	float sliderB = sliderT - sliderHeight;

	float squareWidth = 0.025;
	float squareHeight = 0.1;
	float squareL = -squareWidth;
	float squareR = squareWidth;
	float squareT = sliderT + squareHeight/2;
	float squareB = sliderB - squareHeight/2;

	float lArrowX = sliderL + squareWidth;
	float lArrowY = sliderT - sliderHeight/2;

	float space = ((2*-1*lArrowX)-squareWidth)/MAX_DIVISIONS;
	float markerL = lArrowX + space;
	float markerR = markerL + squareWidth;

	float slider_vertices[] = {
		//x         y      z    R     G    B
		sliderL,  sliderT, 0.0f, 0.0f, 0.0f, 0.0f,
		sliderL,  sliderB, 0.0f, 0.0f, 0.0f, 0.0f,
	    sliderR,  sliderT, 0.0f, 0.0f, 0.0f, 0.0f,
		sliderR,  sliderB, 0.0f, 0.0f, 0.0f, 0.0f,

		markerL,  squareT, 0.0f, 0.0f, 0.0f, 0.0f,
		markerL,  squareB, 0.0f, 0.0f, 0.0f, 0.0f,
	    markerR,  squareT, 0.0f, 0.0f, 0.0f, 0.0f,
		markerR,  squareB, 0.0f, 0.0f, 0.0f, 0.0f,

		// Left arrow
		lArrowX, squareT, 0.0f, 0.0f, 0.0f, 0.0f,
		lArrowX, squareB, 0.0f, 0.0f, 0.0f, 0.0f,
		sliderL, lArrowY, 0.0f, 0.0f, 0.0f, 0.0f,

		// Right arrow
		-lArrowX, squareT, 0.0f, 0.0f, 0.0f, 0.0f,
		-lArrowX, squareB, 0.0f, 0.0f, 0.0f, 0.0f,
		sliderR, lArrowY, 0.0f, 0.0f, 0.0f, 0.0f
	};

	d->nVertices_slider = sizeof(slider_vertices)/sizeof(float);
	d->slider_vertices = slider_vertices;
	int idx_to_modify[] = {24, 30, 36, 42};
	d->idx_slider_modify = idx_to_modify;
	d->space = space;

	unsigned int slider_indices[] = {
	0, 1, 2, // Bar first half
	3, 1, 2, // Bar second half
	4, 5, 6, // Bar first half
	7, 5, 6, // Bar second half
	8, 9, 10, // Left Arrow
	11, 12, 13 // Right Arrow
	};

	unsigned int VAOs, VBOs, EBOs;
	glGenVertexArrays(1, &VAOs);
	glGenBuffers(1, &VBOs);
	glGenBuffers(1, &EBOs);

	d->VBOs = VBOs;
	glBindVertexArray(VAOs);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(slider_vertices),
				 slider_vertices, GL_DYNAMIC_DRAW);
	// POSICIÓN
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// COLOR
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// configurar EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(slider_indices),
				 slider_indices, GL_DYNAMIC_DRAW);

	// CALLBACKS
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glPointSize(2);

	// Activar 3D
	glm::mat4 model         = glm::mat4(1.0f); // inicializar con matriz identidad
	glm::mat4 view          = glm::mat4(1.0f);
	glm::mat4 projection    = glm::mat4(1.0f);

	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / (float)W_HEIGHT, 0.1f, 100.0f);

	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(shader_3d.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(shader_3d.ID, "view");

	model = glm::rotate(model, glm::radians(5.5f), glm::vec3(1.0f, 0.0f, 0.0f));
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_3d.use();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		shader_3d.setMat4("projection", projection);

		// Triangle
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, d->nVertices);

		// Slider
		// slider_shader.use();
		slider_shader.use();
		glBindVertexArray(VAOs);
		glDrawElements(GL_TRIANGLES, sizeof(slider_indices)/sizeof(float),
					   GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void divideTetra(vec3 a, vec3 b, vec3 c, vec3 d, int count, GLfloat vertices[],
int start, int Ndivisions)  {
	if (count == 0)
	{
		tetra(a, b, c, d, vertices, start);
	}
	else
	{
		vec3 divisor = vec3(0.5, 0.5, 0.5);
		vec3 ab = (a + b) * divisor;
		vec3 ad = (a + d) * divisor;
		vec3 ac = (a + c) * divisor;

		vec3 bc = (b + c) * divisor;
		vec3 bd = (b + d) * divisor;
		vec3 dc = (d + c) * divisor;

		--count;
		int Nvertices = getNVertices(Ndivisions);
		int division = Nvertices / 4;
		int nextNdivisions = Ndivisions - 1;

		divideTetra(a, ab, ac, ad, count, vertices, start, nextNdivisions);
		divideTetra(ac, bc, c, dc, count, vertices, start + division, nextNdivisions);
		divideTetra(ab, b, bc, bd, count, vertices, start + 2*division, nextNdivisions);
		divideTetra(ad, bd, dc, d, count, vertices, start + 3*division, nextNdivisions);
	}
}

void tetra(vec3 a, vec3 b, vec3 c, vec3 d, GLfloat vertices[], int start) {
	triangle(a, c, d, vertices, start, vec3(1, 0, 0));
	triangle(a, b, d, vertices, start+18, vec3(0, 1, 0));
	triangle(b, c, d, vertices, start+36, vec3(0, 0, 1));
}

void triangle(vec3 a, vec3 b, vec3 c, GLfloat vertices[], int start, vec3 fColor) {
	vertices[start] = a.x;
	vertices[start+1] = a.y;
	vertices[start+2] = a.z;
	vertices[start+3] = fColor.x;
	vertices[start+4] = fColor.y;
	vertices[start+5] = fColor.z;

	vertices[start+6] = b.x;
	vertices[start+7] = b.y;
	vertices[start+8] = b.z;
	vertices[start+9] = fColor.x;
	vertices[start+10] = fColor.y;
	vertices[start+11] = fColor.z;

	vertices[start+12] = c.x;
	vertices[start+13] = c.y;
	vertices[start+14] = c.z;
	vertices[start+15] = fColor.x;
	vertices[start+16] = fColor.y;
	vertices[start+17] = fColor.z;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xpos, ypos;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwGetCursorPos(window, &xpos, &ypos);
		data* d = (data*)glfwGetWindowUserPointer(window);
		if (xpos < 600 && xpos > 500 && ypos < 100 && ypos > 0) {
			if (d->divisions < MAX_DIVISIONS) {
				increaseTriangle(d);
				moveSquare(d, true);
			}
		}
		else if (xpos > 0 && xpos < 100 && ypos < 100 && ypos > 0) {
			if (d->divisions > MIN_DIVISIONS) {
				decreaseTriangle(d);
				moveSquare(d);
			}
		}
	}
}

void changeTriangle(data* d, int delta) {
	d->divisions = d->divisions + delta;
	d->nVertices = getNVertices(d->divisions);
	float *vertices = new float[d->nVertices];
	d->nVertices = getNVertices(d->divisions);
	d->vertices = vertices;
	divideTetra(d->a, d->b, d->c, d->d, d->divisions, d->vertices, 0, d->divisions);

	// configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, d->VBO);
	//                             vvvvvvvvvvvvvvvvvvvvvvvv ¡El puntero no conoce el tamaño del array!
	glBufferData(GL_ARRAY_BUFFER, d->nVertices*sizeof(float), d->vertices, GL_DYNAMIC_DRAW);
}

void increaseTriangle(data* d) {
	changeTriangle(d, 1);
}

void decreaseTriangle(data* d) {
	changeTriangle(d, -1);
}

void moveSquare(data* d, bool left) {
	if (left) {
		// 4 es la cantidad de índices en <idx_slider_modify>
		for(int i = 0; i < 4; i++)
			d->slider_vertices[d->idx_slider_modify[i]]+=d->space;
	}
	else {
		for(int i = 0; i < 4; i++)
			d->slider_vertices[d->idx_slider_modify[i]]-=d->space;
	}
	glBindBuffer(GL_ARRAY_BUFFER, d->VBOs);
	glBufferData(GL_ARRAY_BUFFER, d->nVertices_slider*sizeof(float),
				 d->slider_vertices, GL_DYNAMIC_DRAW);
}

int getNVertices(int divisions)
{
	// if (!divisions) //divisions = 0
	// 	return (int)pow(2.0, 1)*27;
	return (int)pow(2.0, 1+(2*divisions))*27;
}
