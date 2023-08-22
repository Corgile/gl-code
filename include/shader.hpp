//
// Created by brian on 8/22/23.
//

#ifndef PROGRAM_SHADER_HPP
#define PROGRAM_SHADER_HPP

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class shader {
public:
	GLuint m_shader_program;

	shader(const char *const _vertex_file, const char *const _fragment_file) {
		std::string vertex_code = get_file_content(_vertex_file);
		std::string fragment_code = get_file_content(_fragment_file);

		const char* vertex_source = vertex_code.c_str();
		const char* fragment_source = fragment_code.c_str();

		/// create vertex shader object and get its reference
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		/// attach vertex shader source to the vertex shader object
		glShaderSource(vertexShader, 1, &vertex_source, nullptr);
		/// compile the vertex shader into machine code
		glCompileShader(vertexShader);

		/// create fragment shader object and get its reference
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		/// attach fragment shader source to the fragment shader object
		glShaderSource(fragmentShader, 1, &fragment_source, nullptr);
		/// compile the fragment shader into machine code
		glCompileShader(fragmentShader);

		/// create shader program object and get its reference
		m_shader_program = glCreateProgram();
		/// attach the vertex and fragment shaders to shader program
		glAttachShader(m_shader_program, vertexShader);
		glAttachShader(m_shader_program, fragmentShader);
		/// link all shaders together into the shader program
		glLinkProgram(m_shader_program);

		/// delete
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	/// activate shader program
	void activate() const {
		/// tell OpenGL which program is currently being used
		glUseProgram(m_shader_program);
	}

	/// deactivate shader program
	void deactivate() const {
		glDeleteProgram(m_shader_program);
	}

	static std::string get_file_content(const std::string &filename) {
		std::ifstream in(filename, std::ios::binary);
		if (not in) throw errno;
		std::string content;
		in.seekg(0, std::ios::end);
		content.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&content[0], content.size());
		in.close();
		return content;
	}

};


#endif //PROGRAM_SHADER_HPP
