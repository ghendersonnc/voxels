#include "Shader.h"
#include "Shader.h"
#include "Shader.h"
#include "Shader.h"
#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>

#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>

#include "Utility.h"

namespace Voxels
{
	Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		mShaderPaths[VertexShader] = std::move(vertexShaderPath);
		mShaderPaths[FragmentShader] = std::move(fragmentShaderPath);

		std::string vertexShaderData = Utility::loadIntoString(mShaderPaths[VertexShader]);
		std::string fragmentShaderData = Utility::loadIntoString(mShaderPaths[FragmentShader]);
		
		const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* shaderData = vertexShaderData.data();
		int length = static_cast<int>(vertexShaderData.size());
		glShaderSource(vertexShader, 1, &shaderData, &length);
		glCompileShader(vertexShader);
		_compileErrors(vertexShader);
	
		shaderData = fragmentShaderData.data();
		length = static_cast<int>(fragmentShaderData.size());
		glShaderSource(fragmentShader, 1, &shaderData, &length);
		glCompileShader(fragmentShader);
		_compileErrors(fragmentShader);

		mShaderId = glCreateProgram();

		glAttachShader(mShaderId, vertexShader);
		glAttachShader(mShaderId, fragmentShader);

		glLinkProgram(mShaderId);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

    void Shader::recompile()
    {
		glDeleteProgram(mShaderId);
		std::string vertexShaderData = Utility::loadIntoString(mShaderPaths[VertexShader]);
		std::string fragmentShaderData = Utility::loadIntoString(mShaderPaths[FragmentShader]);

		const unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* shaderData = vertexShaderData.data();
		int length = static_cast<int>(vertexShaderData.size());
		glShaderSource(vertexShader, 1, &shaderData, &length);
		glCompileShader(vertexShader);
		_compileErrors(vertexShader);

		shaderData = fragmentShaderData.data();
		length = static_cast<int>(fragmentShaderData.size());
		glShaderSource(fragmentShader, 1, &shaderData, &length);
		glCompileShader(fragmentShader);
		_compileErrors(fragmentShader);

		mShaderId = glCreateProgram();

		glAttachShader(mShaderId, vertexShader);
		glAttachShader(mShaderId, fragmentShader);
		glLinkProgram(mShaderId);

		int linked = 0;

		glGetProgramiv(mShaderId, GL_LINK_STATUS, &linked);
    }

    void Shader::use() const
    {
		glUseProgram(mShaderId);
    }

	void Shader::destroy() const
	{
		glDeleteProgram(mShaderId);
	}

    void Shader::sayhello()
    {
		std::cout << "hello\n";
    }

    void Shader::setUniform4f(const std::string& name, glm::vec4 vec) const
    {
		const int uniformLocation = glGetUniformLocation(mShaderId, name.data());
		glUniform4fv(uniformLocation, 1, value_ptr(vec));
    }

    void Shader::setUniform4i(const std::string& name, glm::ivec4 vec) const
    {
		const int uniformLocation = glGetUniformLocation(mShaderId, name.data());
		glUniform4iv(uniformLocation, 1, value_ptr(vec));
    }

    void Shader::setUniformMat4f(const std::string& name, glm::mat4 mat) const
    {
		const int uniformLocation = glGetUniformLocation(mShaderId, name.data());
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat));
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
		const int uniformLocation = glGetUniformLocation(mShaderId, name.data());
		glUniform1f(uniformLocation, value);
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void Shader::_compileErrors(const unsigned int& shader)
    {
		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE)
		{
			int logLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<char> errorLog(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, errorLog.data());

			std::cerr << errorLog.data() << '\n';
		}

    }
}
