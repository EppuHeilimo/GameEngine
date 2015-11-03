#include <glew\GL\glew.h>
#include <string>
#include <glm\glm.hpp>

#pragma once
class ShaderProgram
{
public:
	ShaderProgram(std::string vertexFile, std::string fragmentFile);
	ShaderProgram(std::string vertexFile, std::string geometryFile, int i);
	ShaderProgram(std::string vertexFile, std::string fragmentFile, std::string geometryFile);
	~ShaderProgram();
	void loadBoolean();
	void loadMatrix(int, glm::mat4&);
	void loadFloat(int location, float value);
	void loadInt(int location, int value);
	void loadVector3f(int, glm::vec3&);
	void loadVector4f(int, glm::vec4&);
	void loadVector2f(int location, glm::vec2 &vector);
	void start();
	void stop();
	void bindAttribute(int attribute, std::string variableName);
protected:
	int getProgramID(){ return programID; }
	virtual void getAllUniformLocations() = 0;
	virtual void bindAttributes() = 0;
	int getUniformLocation(std::string uniformName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
private:
	static int loadShader(const std::string& file, int type);
	int programID;
	int vertexShaderID;
	int fragmentShaderID;
	int geometryShaderID;
	

};

