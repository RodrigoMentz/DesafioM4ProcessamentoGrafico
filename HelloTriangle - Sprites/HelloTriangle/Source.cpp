#include <iostream>
#include <string>
#include <assert.h>
#include<stb_image.h>

using namespace std;

#include "Shader.h"
#include "Sprite.h"

GLuint loadTexture(string texturePath);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	srand((int)glfwGetTime());

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Desafio M4 -- Rodrigo Korte Mentz", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	GLuint texID = loadTexture("../../Textures/DesafioM4/background.png");
	GLuint texID2 = loadTexture("../../Textures/DesafioM4/arvore.png");
	GLuint texID3 = loadTexture("../../Textures/DesafioM4/araraazul.png");
	GLuint texID4 = loadTexture("../../Textures/DesafioM4/cachorro.png");
	GLuint texID5 = loadTexture("../../Textures/DesafioM4/vaca.png");

	Sprite background;
	background.setShader(&shader);
	background.inicializar(texID, glm::vec3(300.0, 300.0, 0.0), glm::vec3(1726.0/1.5, 968.0/1.5, 1.0));

	Sprite arvore;
	arvore.setShader(&shader);
	arvore.inicializar(texID2, glm::vec3(100.0, 300.0, 0.0), glm::vec3(800.0/2.0, 800.0/2.0, 1.0));

	Sprite arara;
	arara.setShader(&shader);
	arara.inicializar(texID3, glm::vec3(400.0, 400.0, 0.0), glm::vec3(920/6.0, 602.0/6.0, 1.0));

	Sprite cachorro;
	cachorro.setShader(&shader);
	cachorro.inicializar(texID4, glm::vec3(300.0, 170.0, 0.0), glm::vec3(360.0/4.0, 541.0/4.0, 1.0));

	Sprite vaca;
	vaca.setShader(&shader);
	vaca.inicializar(texID5, glm::vec3(550.0, 200.0, 0.0), glm::vec3(2250.0/10.0, 1769.0/10.0, 1.0));

	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	shader.setMat4("projection", glm::value_ptr(projection));
	
	shader.setInt("texBuffer", 0);

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		background.desenhar();
		arvore.desenhar();
		arara.desenhar();
		cachorro.desenhar();
		vaca.desenhar();

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

