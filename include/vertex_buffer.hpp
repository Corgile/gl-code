//
// Created by brian on 8/22/23.
//

#ifndef PROGRAM_VERTEX_BUFFER_HPP
#define PROGRAM_VERTEX_BUFFER_HPP

#include <glad/glad.h>

class vertex_buffer {
public:
	/// a reference containers for the vertex buffer object(vbo)
	GLuint m_vbo_id{};

	vertex_buffer(GLfloat *vertices, GLsizeiptr size) {
		glGenBuffers(1, &m_vbo_id);
		/// bind the vbo specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
		/// introduce the vertices into the vbo
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
	}

	/// bind vbo to 0 so that we don't accidentally modify the vbo
	/// because the usage is GL_STATIC_DRAW
	void unbind() const { // NOLINT(*-convert-member-functions-to-static)
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void delete_vbo() {
		glDeleteBuffers(1, &m_vbo_id);
	}
};


#endif //PROGRAM_VERTEX_BUFFER_HPP
