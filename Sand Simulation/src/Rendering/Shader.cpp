#include "shader.h"

#include <iostream>

Shader::Shader(std::string fileName)
{
    /*
    const char* vertexShaderSource = R"(
	#version 430 core

	layout (location = 0) in vec3 a_Position;
	layout (location = 1) in vec4 a_Color;

    uniform mat4 u_ViewProjection;
    uniform mat4 u_Transform;

    out vec3 v_Position;
    out vec4 v_Color;

	void main()
	{
		v_Position = a_Position;
		v_Color = a_Color;
		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	}
    )";

    const char* fragmentShaderSource = R"(
    #version 430 core
       
    uniform vec4 u_Color;

    out vec4 FragColor;

    in vec3 v_Position;
    in vec4 v_Color;

    void main()
    {
        FragColor = v_Color;
    }
    )";
    */

    std::pair<std::string, std::string> str = ReadFile("src/Shaders/" + fileName + ".glsl");

    const char* vertexShaderSource = str.first.c_str();
    const char* fragmentShaderSource = str.second.c_str();

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

std::pair<std::string, std::string> Shader::ReadFile(std::string filePath)
{
    std::ifstream file(filePath);
    std::stringstream vertexShader, fragmentShader;
    std::string line;

    bool isVertexShader = false;
    bool isFragmentShader = false;

    if(!file.is_open())
        std::cerr << "Error opening shader file: " << filePath << std::endl;

    while (std::getline(file, line))
    {
        if (line == "#Vertex Shader")
        {
            isVertexShader = true;
            isFragmentShader = false;
            continue;
        }
        else if(line == "#Fragment Shader")
        {
            isVertexShader = false;
            isFragmentShader = true;
            continue;
        }

        if (isVertexShader)
        {
            vertexShader << line << "\n";
        }
        else if (isFragmentShader)
        {
            fragmentShader << line << "\n";
        }
    }

    file.close();
    return std::make_pair(vertexShader.str(), fragmentShader.str());
}

void Shader::SetUniform1f(const char* name, float value)
{
    glUniform1f(glGetUniformLocation(m_ProgramID, name), value);
}

void Shader::SetUniform2f(const char* name, glm::vec2 value)
{
	glUniform2f(glGetUniformLocation(m_ProgramID, name), value.x, value.y);
}

void Shader::SetUniform3f(const char* name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z);
}

void Shader::SetUniform4f(const char* name, glm::vec4 value)
{
	glUniform4f(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform1i(const char* name, int value)
{
    glUniform1i(glGetUniformLocation(m_ProgramID, name), value);
}

void Shader::SetUniform2i(const char* name, glm::ivec2 value)
{
    glUniform2i(glGetUniformLocation(m_ProgramID, name), value.x, value.y);
}

void Shader::SetUniform3i(const char* name, glm::ivec3 value)
{
	glUniform3i(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z);
}

void Shader::SetUniform4i(const char* name, glm::ivec4 value)
{
	glUniform4i(glGetUniformLocation(m_ProgramID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetUniformMat2f(const char* name, const glm::mat2& matrix)
{
    glUniformMatrix2fv(glGetUniformLocation(m_ProgramID, name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformMat3f(const char* name, const glm::mat3& matrix)
{
    glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniformMat4f(const char* name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name), 1, GL_FALSE, &matrix[0][0]);
}
