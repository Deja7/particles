#include "shader.h"
#include <vector>
#define DIR "shaders/"
Shader::Shader(string vertexPath, string fragmentPath){
	string vCode, fCode;
	fstream vFile, fFile;
	stringstream vStream, fStream;

	vFile.open(DIR + vertexPath);
	vStream << vFile.rdbuf();
	vFile.close();
	vCode = vStream.str();
	const char* vcCode = vCode.c_str();
	
	fFile.open(DIR + fragmentPath);
	fStream << fFile.rdbuf();
	fFile.close();
	fCode = fStream.str();
	const char* fcCode = fCode.c_str();

	unsigned int vertex, fragment;
	int success;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vcCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) { 
		std::cout << "Vertex shader compilation error\n"; 
		GLint logLength;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
		glGetShaderInfoLog(vertex, logLength, nullptr, log.data());

		std::cerr << "B³¹d kompilacji shadera:\n" << log.data() << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fcCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) std::cout << "Fragment shader compilation error\n";

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) std::cout << "Shader program linking error\n";
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const string& name, bool value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setGLuint64(const string& name, GLuint64 value){
	glUniformHandleui64ARB(glGetUniformLocation(ID, name.c_str()), value);
	//cout << value << "\n";
	//glProgramUniformHandleui64ARB(ID, 0, value);
}

void Shader::setFloat(const string& name, float value) {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const string& name, glm::mat4 value){
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec3(const string& name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value));
}


ComputeShader::ComputeShader(string computePath){
	string cCode;
	fstream cFile;
	stringstream cStream;

	cFile.open(DIR + computePath);
	cStream << cFile.rdbuf();
	cFile.close();
	cCode = cStream.str();
	const char* ccCode = cCode.c_str();

	GLuint compute;
	int success;

	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &ccCode, NULL);
	glCompileShader(compute);
	glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "Compute shader compilation error\n";
		GLint logLength;
		glGetShaderiv(compute, GL_INFO_LOG_LENGTH, &logLength);

		std::vector<GLchar> log(logLength);
		glGetShaderInfoLog(compute, logLength, nullptr, log.data());

		std::cerr << "B³¹d kompilacji shadera:\n" << log.data() << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, compute);
	glLinkProgram(ID);

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) std::cout << "Shader program linking error\n";

	glDeleteShader(compute);
}