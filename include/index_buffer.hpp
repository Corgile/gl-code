//
// Created by brian on 8/22/23.
//

#ifndef PROGRAM_INDEX_BUFFER_HPP
#define PROGRAM_INDEX_BUFFER_HPP

#include <glad/glad.h>

class index_buffer {
public:
	GLuint m_ibo_id{};

	index_buffer(GLuint *indices, GLsizeiptr size) {
		glGenBuffers(1, &m_ibo_id);
		/// bind the vbo specifying it's a GL_ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);
		/// introduce the vertices into the vbo
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo_id);
	}

	void unbind() const { // NOLINT(*-convert-member-functions-to-static)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void delete_ibo() {
		glDeleteBuffers(1, &m_ibo_id);
	}
};


#endif //PROGRAM_INDEX_BUFFER_HPP
