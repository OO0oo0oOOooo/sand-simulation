#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <climits>
#include <list>

#include "Window.h"
#include "Input.h"
#include "Shader.h"
#include "MeshData.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO:
// - Rendering class
// - Grid Resolution
// - Grid class
// - Update loop

// - Chunks
// - each chunk has a grid map. 2D array of bytes, 0 air, 1 sand, 2 water, 3 stone, 4 dirt, 5 grass

// - tick and late tick
// - every tick, update the grid map
// - every late tick, render the new grid map if it has changed

struct TerrainData {
	unsigned char type;
};

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

unsigned int gridResolution = 16;
unsigned int tileSize = windowWidth / gridResolution;

unsigned int tilesX = windowWidth / tileSize;
unsigned int tilesY = windowHeight / tileSize;

std::vector<std::vector<TerrainData>> TerrainMap (tilesX, std::vector<TerrainData>(tilesY));

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

void testInput(Window window)
{
    if (Input::IsKeyPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
		std::cout << "LMB pressed" << std::endl;
	}

    if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        window.Close();
    }
}

int main(void)
{
    if (!glfwInit())
        return -1;

    // This might be copying the window object, but I'm not sure
    Window window(windowWidth, windowHeight, "Sand Simulation");
    GLFWwindow* glwindow = window.GetNativeWindow();

    GLenum err = glewInit();
    if (GLEW_OK != err)
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Input::SetupKeyInputs(glwindow);

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < tilesX; x++)
    {
        for (int y = 0; y < tilesY; y++)
        {
            TerrainMap[x][y].type = 1;

            if (TerrainMap[x][y].type == 1)
            {
                for (int i = 0; i < 4; i++)
                {
                    vertices.push_back({ glm::vec3(x, y, 0) * (float)tileSize + vertexPositions[i] * (float)tileSize, vertexColors[i] });
                }

                for (int i = 0; i < 6; i++)
                {
                    indices.push_back(meshTriangles[i] + vertices.size());
                }
            }
        }
    }

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) 12);
    glEnableVertexAttribArray(1);

    unsigned int indexBuffer;
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    Shader shader;

    glm::mat4 proj = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

    glm::mat4 VP = proj * view;

    shader.Bind();
    shader.SetUniformMat4f("u_ViewProjection", VP);
    shader.SetUniformMat4f("u_Transform", model);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glViewport(0, 0, windowWidth, windowHeight);
    while (!glfwWindowShouldClose(glwindow))
    {
        testInput(window);

        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(glwindow);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}