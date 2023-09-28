#include "shader.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/glew.h>
#include <vector>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderSource = R"(
		#version 430 core

		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;

        out vec4 v_Color;

		void main()
		{
			v_Color = a_Color;

			gl_Position = vec4(a_Position, 1.0);
		}
	)";

	std::string fragmentShaderSource = R"(
        #version 430 core

        out vec4 FragColor;

		in vec4 v_Color;

        void main()
        {
           FragColor = v_Color;
        }
    )";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    m_ProgramID = glCreateProgram();

    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if(m_ProgramID)
	    glDeleteProgram(m_ProgramID);
}

void Shader::Bind()
{
    if (!m_ProgramID)
        return;

	glUseProgram(m_ProgramID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}
