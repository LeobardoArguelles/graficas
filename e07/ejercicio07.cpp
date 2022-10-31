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
#define THETA_DELTA 0.01f

struct glm_ptr {
	unsigned int VBO;
	int nData;
	GLfloat* vertices, *rotated_vertices;
	glm::vec3 theta;
};

struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};



void RenderText(Shader &s, std::string text, float x, float y, float scale,
glm::vec3 color, unsigned int VAO, unsigned int VBO, std::map<char, Character> Characters);
void rotate(glm_ptr* ptr, glm::mat3 matrix);
void mapChars(FT_Face face, std::map<char, Character> Characters);
void rotateX(glm_ptr* ptr);
void rotateY(glm_ptr* ptr);
void rotateZ(glm_ptr* ptr);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
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

	// USAR FREETYPE PARA TEXTO
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	std::map<char, Character> Characters;
	mapChars(face, Characters);

	// (FT_Face, width, height): width en 0 permite que es calcule automaticamente
	FT_Set_Pixel_Sizes(face, 0, 48);
	// CALLBACKS
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// SHADERS
	Shader shader("./shader.vs", "./shader.fs");
	Shader shaderNT("./shader_no_transform.vs", "./shader.fs");
	Shader shaderText("./shader_text.vs", "./text_shader.fs");

	// 8 vértices, 6 datos por cada uno (3 posición, 3 color)
	int nData = 8*6;
	GLfloat vertices[nData];
	GLfloat empty[nData];
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

				// Para tener los colores ya guardados en el vector de rotaciones
				empty[idx+3] = counter % 2;
				empty[idx+4] = (int)floor(counter/2) % 2;
				empty[idx+5] = (int)floor(counter/4) % 2;
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
	ptr->rotated_vertices = empty;
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
	GLfloat button_w = 0.4f;
	GLfloat sep = (2 - button_w*3)/4;
	GLfloat button_x = -1.0f + sep;
	GLfloat button_y = 0.85f;
	GLfloat button_h = 0.1f;
	GLfloat buttons_vertices[] = {
	// Botón 1
	button_x, button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top left
	button_x + button_w, button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top right
	button_x, button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot left
	button_x + button_w, button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot right

	// Botón 2
	button_x + button_w + sep, button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top left
	button_x + 2*button_w + sep, button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top right
	button_x + button_w + sep, button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot left
	button_x + 2*button_w + sep, button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot right

	// Botón 3
	button_x + 2*(button_w + sep), button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top left
	button_x + 3*button_w + 2*sep, button_y, 0.0f, 0.75f, 0.75f, 0.75f, // top right
	button_x + 2*(button_w + sep), button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot left
	button_x + 3*button_w + 2*sep, button_y - button_h, 0.0f, 0.75f, 0.75f, 0.75f, // bot right
	};

	unsigned int button_indices[] = {
	0, 1, 2, 1, 2, 3, // button 1
	4, 5, 6, 5, 6, 7, // button 2
	8, 9, 10, 9, 10, 11, // button 3
	};

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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(button_indices),
				button_indices, GL_STATIC_DRAW);

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
    gltSetText(text1, "Rotate X");
    gltSetText(text2, "Rotate Y");
    gltSetText(text3, "Rotate Z");
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

	// Crear matrices
	glm::vec3 theta = glm::vec3(0.0f, 0.0f, 0.0f);
	ptr->theta = theta;
	glm::mat4 Rx(1.0f);
	glm::mat4 Ry(1.0f);
	glm::mat4 Rz(1.0f);

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
		glDrawElements(GL_TRIANGLES, sizeof(button_indices)/sizeof(GLfloat),
					   GL_UNSIGNED_INT, 0);

		// Elimina la información de profundidad para dibujar el texto sobre
		// los botones.
		// Ver: https://stackoverflow.com/questions/5526704/how-do-i-keep-an-object-always-in-front-of-everything-else-in-opengl
		glClear(GL_DEPTH_BUFFER_BIT);
        gltBeginDraw();

		gltColor(1.0f, 1.0f, 1.0f, 1.0f);
		//                              x     y     scale
        gltDrawText2DAligned(text1, 115.0f, 70.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);

        gltDrawText2DAligned(text2, 300.0f, 70.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);

        gltDrawText2DAligned(text3, 480.0f, 70.0f, 1.0f,
                            GLT_CENTER, GLT_CENTER);
        gltEndDraw();

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
	GLfloat prevY = 0;
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
		ptr->rotated_vertices[idx] = dot(vec3(matrix[0][0], matrix[1][0], matrix[2][0]), vector);
		ptr->rotated_vertices[idx+1] = dot(vec3(matrix[0][1], matrix[1][1], matrix[2][1]), vector);
		ptr->rotated_vertices[idx+2] = dot(vec3(matrix[0][2], matrix[1][2], matrix[2][2]), vector);

	}
	// Configurar VBO
	glBindBuffer(GL_ARRAY_BUFFER, ptr->VBO);
	glBufferData(GL_ARRAY_BUFFER, ptr->nData*sizeof(GLfloat),
				ptr->rotated_vertices, GL_DYNAMIC_DRAW);
}

void rotateX(glm_ptr* ptr) {
	ptr->theta.x += THETA_DELTA;
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRX = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRX[1][1] = cos(ptr->theta.x);
	matrixRX[2][1] = -sin(ptr->theta.x);
	matrixRX[1][2] = sin(ptr->theta.x);
	matrixRX[2][2] = cos(ptr->theta.x);
	rotate(ptr, matrixRX);
}

void rotateY(glm_ptr* ptr) {
	ptr->theta.y += THETA_DELTA;
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRY = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRY[0][0] = cos(ptr->theta.y);
	matrixRY[2][0] = sin(ptr->theta.y);
	matrixRY[0][2] = -sin(ptr->theta.y);
	matrixRY[2][2] = cos(ptr->theta.y);
	rotate(ptr, matrixRY);
}

void rotateZ(glm_ptr* ptr) {
	ptr->theta.z += THETA_DELTA;
	// Crear matriz de rotación, iniciar con la identidad
	glm::mat3 matrixRZ = glm::mat3(1.0f);
	// Asignar elementos necesarios
	matrixRZ[0][0] = cos(ptr->theta.z);
	matrixRZ[1][0] = -sin(ptr->theta.z);
	matrixRZ[0][1] = sin(ptr->theta.z);
	matrixRZ[1][1] = cos(ptr->theta.z);
	rotate(ptr, matrixRZ);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	double xpos, ypos;
	// if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
	// 	glfwGetCursorPos(window, &xpos, &ypos);
	// 	data* d = (data*)glfwGetWindowUserPointer(window);
	// 	if (xpos < 600 && xpos > 500 && ypos < 100 && ypos > 0) {
	// 		if (d->divisions < MAX_DIVISIONS) {
	// 			increaseTriangle(d);
	// 			moveSquare(d, true);
	// 		}
	// 	}
	// 	else if (xpos > 0 && xpos < 100 && ypos < 100 && ypos > 0) {
	// 		if (d->divisions > MIN_DIVISIONS) {
	// 			decreaseTriangle(d);
	// 			moveSquare(d);
	// 		}
	// 	}
	// }
}

void mapChars(FT_Face face, std::map<char, Character> Characters) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // no byte-alignment restriction
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
}

void RenderText(Shader &s, std::string text, float x, float y, float scale,
glm::vec3 color, unsigned int VAO, unsigned int VBO, std::map<char, Character> Characters)
{
	// activate corresponding render state
	s.use();
	glUniform3f(glGetUniformLocation(s.ID, "textColor"),
	color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];
		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos, ypos + h, 0.0f, 0.0f },
			{ xpos, ypos, 0.0f, 1.0f },
			{ xpos + w, ypos, 1.0f, 1.0f },
			{ xpos, ypos + h, 0.0f, 0.0f },
			{ xpos + w, ypos, 1.0f, 1.0f },
			{ xpos + w, ypos + h, 1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// advance cursors for next glyph (advance is 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
