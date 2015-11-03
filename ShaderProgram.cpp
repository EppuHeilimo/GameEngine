#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>


ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile)
{
	programID = glCreateProgram();
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	
	CheckShaderError(vertexShaderID, GL_COMPILE_STATUS, false, "vertexShader failed to compile!");

	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	CheckShaderError(fragmentShaderID, GL_COMPILE_STATUS, false, "fragmentShader failed to compile!");


	glAttachShader(programID, vertexShaderID);

	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	CheckShaderError(programID, GL_LINK_STATUS, true, "Shaderprogram failed to link!");
	glValidateProgram(programID);
	CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Shaderprogram failed to validate!");


}

ShaderProgram::ShaderProgram(std::string vertexFile, std::string geometryFile, int i)
{
	programID = glCreateProgram();
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);

	CheckShaderError(vertexShaderID, GL_COMPILE_STATUS, false, "vertexShader failed to compile!");

	geometryShaderID = loadShader(geometryFile, GL_GEOMETRY_SHADER);

	CheckShaderError(geometryShaderID, GL_COMPILE_STATUS, false, "geometryShader failed to compile!");


	glAttachShader(programID, vertexShaderID);

	glAttachShader(programID, geometryShaderID);

	/*
	glLinkProgram(programID);
	CheckShaderError(programID, GL_LINK_STATUS, true, "Shaderprogram failed to link!");
	glValidateProgram(programID);
	CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Shaderprogram failed to validate!");
	*/

}

ShaderProgram::ShaderProgram(std::string vertexFile, std::string fragmentFile, std::string geometryFile)
{
	programID = glCreateProgram();
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);

	CheckShaderError(vertexShaderID, GL_COMPILE_STATUS, false, "vertexShader failed to compile!");

	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	CheckShaderError(fragmentShaderID, GL_COMPILE_STATUS, false, "fragmentShader failed to compile!");

	geometryShaderID = loadShader(geometryFile, GL_GEOMETRY_SHADER);

	CheckShaderError(geometryShaderID, GL_COMPILE_STATUS, false, "geometryShader failed to compile!");

	glAttachShader(programID, vertexShaderID);

	glAttachShader(programID, geometryShaderID);

	glAttachShader(programID, fragmentShaderID);

	

	glLinkProgram(programID);
	CheckShaderError(programID, GL_LINK_STATUS, true, "Shaderprogram failed to link!");
	glValidateProgram(programID);
	CheckShaderError(programID, GL_VALIDATE_STATUS, true, "Shaderprogram failed to validate!");


}



ShaderProgram::~ShaderProgram()
{
	stop(); //Make sure program is stopped
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

int ShaderProgram::getUniformLocation(std::string uniformName){
	const GLchar* name = uniformName.c_str();
	return glGetUniformLocation(programID, name);

}

void ShaderProgram::loadBoolean(){

}
void ShaderProgram::loadMatrix(int location, glm::mat4 &matrix){
	
	glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&matrix);
}
void ShaderProgram::loadFloat(int location, float value){
	glUniform1f(location, value);
}
void ShaderProgram::loadInt(int location, int value){
	glUniform1i(location, value);
}
void ShaderProgram::loadVector3f(int location, glm::vec3 &vector){
	glUniform3f(location, vector.x, vector.y, vector.z);
}
void ShaderProgram::loadVector4f(int location, glm::vec4 &vector){
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}
void ShaderProgram::loadVector2f(int location, glm::vec2 &vector){
	glUniform2f(location, vector.x, vector.y);
}
void ShaderProgram::start(){
	glUseProgram(programID);
}
void ShaderProgram::stop(){
	glUseProgram(0);
}

void ShaderProgram::bindAttribute(int attribute, std::string variableName){
	const GLchar* name = variableName.c_str();
	glBindAttribLocation(programID, attribute, name);
}

int ShaderProgram::loadShader(const std::string& fileName, int type){
	std::ifstream file;
	
	file.open((fileName).c_str());
	std::string output;
	std::string line;

	if (file.is_open()){
		while (file.good()){
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: ";
	}
	int shaderID = glCreateShader(type);
	const GLchar* p[1];
	p[0] = output.c_str();
	GLint lengths[1];
	lengths[0] = output.length();
	glShaderSource(shaderID, 1, p, lengths);
	glCompileShader(shaderID);
	return shaderID;
}

void ShaderProgram::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
