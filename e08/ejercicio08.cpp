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
#include <map>

// Texto
#define GLT_IMPLEMENTATION
#include "gltext.h"
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace glm;

// Definir constantes
#define W_HEIGHT 600
#define W_WIDTH 600
#define THETA_DELTA 0.05f
#define TRANSLATE_DELTA 0.01f
#define SCALE_DELTA 0.05f

// Vector booleano que detecta si un boton está siendo presionado,
// para rotar el cubo en el loop principal
bool rotate_button_clicked[] = {false, false, false};

struct button_group {
	bool xplus = false;
	bool xminus = false;
	bool yplus = false;
	bool yminus = false;
	bool zplus = false;
	bool zminus = false;
};

button_group rotate_btns;
button_group translate_btns;
button_group scale_btns;

struct glm_ptr {
	unsigned int VBO;
	int nData;
	GLfloat* vertices;
};

struct Point {
	GLfloat x, y;
};

struct Button {
    Point top_left, bot_right;
};

void rotate(glm_ptr* ptr, glm::mat3 matrix);
void rotateX(glm_ptr* ptr, int direction);
void rotateY(glm_ptr* ptr, int direction);
void rotateZ(glm_ptr* ptr, int direction);

void translate(glm_ptr* ptr, float x, float y, float z);
void translateX(glm_ptr* ptr, int direction);
void translateY(glm_ptr* ptr, int direction);
void translateZ(glm_ptr* ptr, int direction);

void scale(glm_ptr* ptr, float x, float y, float z);
void scaleX(glm_ptr* ptr, int direction);
void scaleY(glm_ptr* ptr, int direction);
void scaleZ(glm_ptr* ptr, int direction);

void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void quad(unsigned int a, unsigned int b, unsigned int c, unsigned int d, GLfloat vertices[], unsigned int indices[],
unsigned int start);
void generateButton(GLfloat* vertices, unsigned int* indices, int start_v,
int start_idx, Point top_left, GLfloat width, GLfloat height, unsigned int start_point);
void generateButtons(GLfloat* vertices, unsigned int* indices);

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

	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Ejercicio 7", nullptr, nullptr);

	if (!window) {
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (glewInit()) {
		printf("failed to initialize OpenGL\n");
		return -1;
	}

	// Hay que activarlo DESPUÉS de tener el contexto de la ventana
	glEnable(GL_DEPTH_TEST);
	// Blend para poder darle color al texto
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// END BOILERPLATE

	// CALLBACKS
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// SHADERS
	Shader shader("./shader.vs", "./shader.fs");
	Shader shaderNT("./shader_no_transform.vs", "./shader.fs");

	// 8 vértices, 6 datos por cada uno (3 posición, 3 color)
	int nData = 8*6;
	GLfloat vertices[nData];
	int counter = 0;
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
				// Asignar color de acuerdo al número de vértice
				// Ej: 1 = 001, 5 = 101, 7 = 111
				vertices[idx+3] = counter % 2;
				vertices[idx+4] = (int)floor(counter/2) % 2;
				vertices[idx+5] = (int)floor(counter/4) % 2;

				counter++;
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

	// Usar puntero global para poder modificar los datos
	glm_ptr *ptr = new glm_ptr;
	ptr->VBO = VBO;
	ptr->nData = nData;
	ptr->vertices = vertices;
	glfwSetWindowUserPointer(window, ptr);

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

	// configurar EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
				 indices, GL_DYNAMIC_DRAW);

	// BOTONES


	// 3 menus, 6 botones por menu, 4 vertices por boton, 6 datos por vértice
	unsigned int nVertices = 6*3*4*6;
	nIndices = 3*6*6;
	GLfloat buttons_vertices[nVertices];
	unsigned int buttons_indices[nIndices];

	generateButtons(buttons_vertices, buttons_indices);

	unsigned int VAOb, VBOb, EBOb;
	glGenVertexArrays(1, &VAOb);
	glGenBuffers(1, &VBOb);
	glGenBuffers(1, &EBOb);

	glBindVertexArray(VAOb);

	glBindBuffer(GL_ARRAY_BUFFER, VBOb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buttons_vertices), buttons_vertices,
				GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOb);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(buttons_indices),
				buttons_indices, GL_STATIC_DRAW);

	// TEXTO
	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return EXIT_FAILURE;
    }
	GLTtext *text1 = gltCreateText();
	GLTtext *text2 = gltCreateText();
	GLTtext *text3 = gltCreateText();
	GLTtext *text4 = gltCreateText();
	GLTtext *text5 = gltCreateText();
	GLTtext *text6 = gltCreateText();
    gltSetText(text1, "-     X     +");
    gltSetText(text2, "-     Y     +");
    gltSetText(text3, "-     Z     +");
    gltSetText(text4, "Rotar");
    gltSetText(text5, "Trasladar");
    gltSetText(text6, "Escalar");
	unsigned int VAOT, VBOT;
	glGenVertexArrays(1, &VAOT);
	glGenBuffers(1, &VBOT);

	glBindVertexArray(VAOT);
	glBindBuffer(GL_ARRAY_BUFFER, VBOT);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6*4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Activar 3D
	glm::mat4 model         = glm::mat4(1.0f); // inicializar con matriz identidad
	glm::mat4 view          = glm::mat4(1.0f);
	glm::mat4 projection    = glm::mat4(1.0f);

	view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	projection = glm::perspective(glm::radians(45.0f), 800.0f / (float)W_HEIGHT, 0.1f, 100.0f);
	// retrieve the matrix uniform locations
	unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
	unsigned int viewLoc  = glGetUniformLocation(shader.ID, "view");

	float x = 0;
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.use();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		shader.setMat4("projection", projection);

		// Triangle
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, nIndices,
					   GL_UNSIGNED_INT, 0);

		// Buttons
		shaderNT.use();
		glBindVertexArray(VAOb);
		glDrawElements(GL_TRIANGLES, sizeof(buttons_indices)/sizeof(unsigned int),
					   GL_UNSIGNED_INT, 0);

		// Elimina la información de profundidad para dibujar el texto sobre
		// los botones.
		// Ver: https://stackoverflow.com/questions/5526704/how-do-i-keep-an-object-always-in-front-of-everything-else-in-opengl
		glClear(GL_DEPTH_BUFFER_BIT);
        gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
        gltDrawText2DAligned(text4, 125.0f, 30.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text5, 300.0f, 30.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text6, 470.0f, 30.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
		//                              x     y     scale
        gltDrawText2DAligned(text1, 125.0f, 60.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text1, 300.0f, 60.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text1, 470.0f, 60.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);

        gltDrawText2DAligned(text2, 125.0f, 120.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text2, 300.0f, 120.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text2, 470.0f, 120.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);

        gltDrawText2DAligned(text3, 125.0f, 180.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text3, 300.0f, 180.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltDrawText2DAligned(text3, 470.0f, 180.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltEndDraw();

		// Rotar
		if (rotate_btns.xplus)
			rotateX(ptr, 1);
		else if (rotate_btns.xminus)
			rotateX(ptr, -1);
		else if (rotate_btns.yplus)
			rotateY(ptr, 1);
		else if (rotate_btns.yminus)
			rotateY(ptr, -1);
		else if (rotate_btns.zplus)
			rotateZ(ptr, 1);
		else if (rotate_btns.zminus)
			rotateZ(ptr, -1);
		// Trasladar
		else if (translate_btns.xplus)
			translateX(ptr, 1);
		else if (translate_btns.xminus)
			translateX(ptr, -1);
		else if (translate_btns.yplus)
			translateY(ptr, 1);
		else if (translate_btns.yminus)
			translateY(ptr, -1);
		else if (translate_btns.zplus)
			translateZ(ptr, 1);
		else if (translate_btns.zminus)
			translateZ(ptr, -1);
		// Escalar
		else if (scale_btns.xplus)
			scaleX(ptr, 1);
		else if (scale_btns.xminus)
			scaleX(ptr, -1);
		else if (scale_btns.yplus)
			scaleY(ptr, 1);
		else if (scale_btns.yminus)
			scaleY(ptr, -1);
		else if (scale_btns.zplus)
			scaleZ(ptr, 1);
		else if (scale_btns.zminus)
			scaleZ(ptr, -1);
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

void rotate(glm_ptr* ptr, glm::mat3 matrix) {
	// ptr->theta.x += 0.1f;
	bool positions = true;
	GLfloat x = 0, y = 0, z = 0;
	for (int idx = 0; idx < ptr->nData; idx++) {
		if (positions) {
			// Obtener primero todos los componentes
			positions = false;
			x = ptr->vertices[idx];
			y = ptr->vertices[idx+1];
			z = ptr->vertices[idx+2];
		}
		else {
			positions = true;
			idx += 4;
			continue;
		}
		// Aplicar la transformación
		glm::vec3 vector = vec3(x, y, z);
		ptr->vertices[idx] = dot(vec3(matrix[0][0], matrix[1][0], matrix[2][0]), vector);
		ptr->vertices[idx+1] = dot(vec3(matrix[0][1], matrix[1][1], matrix[2][1]), vector);
		ptr->vertices[idx+2] = dot(vec3(matrix[0][2], matrix[1][2], matrix[2][2]), vector);

	}
	// Configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, ptr->VBO);
	glBufferData(GL_ARRAY_BUFFER, ptr->nData*sizeof(GLfloat),
				ptr->vertices, GL_DYNAMIC_DRAW);
}

void rotateX(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRX = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRX[1][1] = cos(THETA_DELTA*direction);
	matrixRX[2][1] = -sin(THETA_DELTA*direction);
	matrixRX[1][2] = sin(THETA_DELTA*direction);
	matrixRX[2][2] = cos(THETA_DELTA*direction);
	rotate(ptr, matrixRX);
}

void rotateY(glm_ptr* ptr, int direction) {
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRY = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRY[0][0] = cos(THETA_DELTA*direction);
	matrixRY[2][0] = sin(THETA_DELTA*direction);
	matrixRY[0][2] = -sin(THETA_DELTA*direction);
	matrixRY[2][2] = cos(THETA_DELTA*direction);
	rotate(ptr, matrixRY);
}

void rotateZ(glm_ptr* ptr, int direction) {
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRZ = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRZ[0][0] = cos(THETA_DELTA*direction);
	matrixRZ[1][0] = -sin(THETA_DELTA*direction);
	matrixRZ[0][1] = sin(THETA_DELTA*direction);
	matrixRZ[1][1] = cos(THETA_DELTA*direction);
	rotate(ptr, matrixRZ);
}

void translate(glm_ptr* ptr, float x, float y, float z) {
	// ptr->theta.x += 0.1f;
	bool positions = true;
	GLfloat Vx = 0, Vy = 0, Vz = 0;
	// Crear la matriz con el desplazamiento adecuado.
	// Ver 8.14 del libro learnopengl
	glm::mat4 matrixTranslation = glm::mat4(1.0f);
	matrixTranslation[3][0] = x;
	matrixTranslation[3][1] = y;
	matrixTranslation[3][2] = z;
	for (int idx = 0; idx < ptr->nData; idx++) {
		if (positions) {
			// Obtener primero todos los componentes
			positions = false;
			Vx = ptr->vertices[idx];
			Vy = ptr->vertices[idx+1];
			Vz = ptr->vertices[idx+2];
		}
		else {
			positions = true;
			idx += 4;
			continue;
		}
		// Aplicar la transformación
		glm::vec4 vector = vec4(Vx, Vy, Vz, 1);
		ptr->vertices[idx] = dot(vec4(matrixTranslation[0][0], matrixTranslation[1][0], matrixTranslation[2][0], matrixTranslation[3][0]), vector);
		ptr->vertices[idx+1] = dot(vec4(matrixTranslation[0][1], matrixTranslation[1][1], matrixTranslation[2][1], matrixTranslation[3][1]), vector);
		ptr->vertices[idx+2] = dot(vec4(matrixTranslation[0][2], matrixTranslation[1][2], matrixTranslation[2][2], matrixTranslation[3][2]), vector);

	}
	// Configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, ptr->VBO);
	glBufferData(GL_ARRAY_BUFFER, ptr->nData*sizeof(GLfloat),
				ptr->vertices, GL_DYNAMIC_DRAW);
}

void translateX(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	translate(ptr, TRANSLATE_DELTA*direction, 0, 0);
}

void translateY(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	translate(ptr, 0, TRANSLATE_DELTA*direction, 0);
}

void translateZ(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	translate(ptr, 0, 0, TRANSLATE_DELTA*direction);
}

void scale(glm_ptr* ptr, float x, float y, float z) {
	// ptr->theta.x += 0.1f;
	bool positions = true;
	GLfloat Vx = 0, Vy = 0, Vz = 0;
	// Crear la matriz con el desplazamiento adecuado.
	// Ver 8.14 del libro learnopengl
	glm::mat4 matrixTranslation = glm::mat4(1.0f);
	matrixTranslation[0][0] = x;
	matrixTranslation[1][1] = y;
	matrixTranslation[2][2] = z;
	for (int idx = 0; idx < ptr->nData; idx++) {
		if (positions) {
			// Obtener primero todos los componentes
			positions = false;
			Vx = ptr->vertices[idx];
			Vy = ptr->vertices[idx+1];
			Vz = ptr->vertices[idx+2];
		}
		else {
			positions = true;
			idx += 4;
			continue;
		}
		// Aplicar la transformación
		glm::vec4 vector = vec4(Vx, Vy, Vz, 1);
		ptr->vertices[idx] = dot(vec4(matrixTranslation[0][0], matrixTranslation[1][0], matrixTranslation[2][0], matrixTranslation[3][0]), vector);
		ptr->vertices[idx+1] = dot(vec4(matrixTranslation[0][1], matrixTranslation[1][1], matrixTranslation[2][1], matrixTranslation[3][1]), vector);
		ptr->vertices[idx+2] = dot(vec4(matrixTranslation[0][2], matrixTranslation[1][2], matrixTranslation[2][2], matrixTranslation[3][2]), vector);

	}
	// Configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, ptr->VBO);
	glBufferData(GL_ARRAY_BUFFER, ptr->nData*sizeof(GLfloat),
				ptr->vertices, GL_DYNAMIC_DRAW);
}

void scaleX(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	std::cout << 1+SCALE_DELTA*direction << std::endl;
	scale(ptr, 1+SCALE_DELTA*direction, 1, 1);
}

void scaleY(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	scale(ptr, 1, 1+SCALE_DELTA*direction, 1);
}

void scaleZ(glm_ptr* ptr, int direction) {
	// Direction debe ser -1 ó 1
	scale(ptr, 1, 1, 1+SCALE_DELTA*direction);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xpos, ypos;
	glm_ptr *ptr = (glm_ptr*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos << " " << ypos << std::endl;
		if (ypos >= 45 && ypos <= 75) {
			if (xpos >= 80 && xpos <= 115 )
				rotate_btns.xminus = true;
			else if (xpos >= 140 && xpos <= 170 )
				rotate_btns.xplus = true;
			else if (xpos >= 250 && xpos <= 285 )
				translate_btns.xminus = true;
			else if (xpos >= 315 && xpos <= 345 )
				translate_btns.xplus = true;
			else if (xpos >= 425 && xpos <= 455 )
				scale_btns.xminus = true;
			else if (xpos >= 485 && xpos <= 515 )
				scale_btns.xplus = true;
		}
		else if (ypos >= 100 && ypos <= 130) {
			if (xpos >= 80 && xpos <= 115 )
				rotate_btns.yminus = true;
			else if (xpos >= 140 && xpos <= 170 )
				rotate_btns.yplus = true;
			else if (xpos >= 250 && xpos <= 285 )
				translate_btns.yminus = true;
			else if (xpos >= 315 && xpos <= 345 )
				translate_btns.yplus = true;
			else if (xpos >= 425 && xpos <= 455 )
				scale_btns.yminus = true;
			else if (xpos >= 485 && xpos <= 515 )
				scale_btns.yplus = true;
		}
		else if (ypos >= 160 && ypos <= 200) {
			if (xpos >= 80 && xpos <= 115 )
				rotate_btns.zminus = true;
			else if (xpos >= 140 && xpos <= 170 )
				rotate_btns.zplus = true;
			else if (xpos >= 250 && xpos <= 285 )
				translate_btns.zminus = true;
			else if (xpos >= 315 && xpos <= 345 )
				translate_btns.zplus = true;
			else if (xpos >= 425 && xpos <= 455 )
				scale_btns.zminus = true;
			else if (xpos >= 485 && xpos <= 515 )
				scale_btns.zplus = true;
		}
	} else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		rotate_btns.xminus = false;
		rotate_btns.xplus = false;
		rotate_btns.yminus = false;
		rotate_btns.yplus = false;
		rotate_btns.zminus = false;
		rotate_btns.zplus = false;

		scale_btns.xminus = false;
		scale_btns.xplus = false;
		scale_btns.yminus = false;
		scale_btns.yplus = false;
		scale_btns.zminus = false;
		scale_btns.zplus = false;

		translate_btns.xminus = false;
		translate_btns.xplus = false;
		translate_btns.yminus = false;
		translate_btns.yplus = false;
		translate_btns.zminus = false;
		translate_btns.zplus = false;
	}
}

void generateButtons(GLfloat* vertices, unsigned int* indices) {
	// Definir variables
	GLfloat button_w = 0.1f;
	GLfloat space = 0.1f;
	GLfloat vspace = 0.1f;
	GLfloat sep = (2 - (button_w*2 + space)*3)/4;
	GLfloat button_h = 0.1f;
	GLfloat startx = -1.0f + sep;
	GLfloat starty = 0.85f;
	unsigned int groups = 3;

	// Hacer 1 grupo a la vez (Rotacion, traslacion, escalamiento)
	for(int i = 0; i < 3; i++) {
		GLfloat top_left_x = startx;
		GLfloat top_left_y = starty - i*(button_h + vspace);
		for (int j = 0; j < 6; j++) {
			unsigned int start_v = j*24 + i*144;
			unsigned int start_idx = j*6 + i*36;
			unsigned int start_point = j*4 + i*24;
			if (j > 0)
				top_left_x += j%2 == 1 > 0 ? button_w + space : button_w + sep;
			Point top_left = {top_left_x, top_left_y};
			generateButton(vertices, indices, start_v, start_idx, top_left, button_w, button_h, start_point);
		}
	}
}

void generateButton(GLfloat* vertices, unsigned int* indices, int start_v,
int start_idx, Point top_left, GLfloat width, GLfloat height, unsigned int start_point) {
	// Se necesitan 4 puntos, 6 datos por punto
	// TOP LEFT
	vertices[start_v] = top_left.x;
	vertices[start_v+1] = top_left.y;
	vertices[start_v+2] = 0.0f;
	vertices[start_v+3] = 0.75f;
	vertices[start_v+4] = 0.75f;
	vertices[start_v+5] = 0.75f;

	// TOP RIGHT
	vertices[start_v+6] = top_left.x + width;
	vertices[start_v+7] = top_left.y;
	vertices[start_v+8] = 0.0f;
	vertices[start_v+9] = 0.75f;
	vertices[start_v+10] = 0.75f;
	vertices[start_v+11] = 0.75f;

	// BOT LEFT
	vertices[start_v+12] = top_left.x;
	vertices[start_v+13] = top_left.y - height;
	vertices[start_v+14] = 0.0f;
	vertices[start_v+15] = 0.75f;
	vertices[start_v+16] = 0.75f;
	vertices[start_v+17] = 0.75f;

	// BOT RIGHT
	vertices[start_v+18] = top_left.x + width;
	vertices[start_v+19] = top_left.y - height;
	vertices[start_v+20] = 0.0f;
	vertices[start_v+21] = 0.75f;
	vertices[start_v+22] = 0.75f;
	vertices[start_v+23] = 0.75f;

	indices[start_idx] = start_point;
	indices[start_idx+1] = start_point + 1;
	indices[start_idx+2] = start_point + 2;
	indices[start_idx+3] = start_point + 1;
	indices[start_idx+4] = start_point + 2;
	indices[start_idx+5] = start_point + 3;
}
