//
// Created by brian on 8/22/23.
//

#ifndef PROGRAM_VERTEX_ARRAY_HPP
#define PROGRAM_VERTEX_ARRAY_HPP

#include <glad/glad.h>
#include <vertex_buffer.hpp>

class vertex_array {
public:
	/// a reference containers for the vertex array object(vao)
	GLuint m_vao_id{};

	vertex_array() {
		/// generate the vao and vbo with 1 object each
		glGenVertexArrays(1, &m_vao_id);//comes must before vbo init
	}

	void link_vbo(vertex_buffer &vbo, GLuint layout) {
		vbo.bind();

		/// configure the vertex attribute so that OpenGL knows how to read the vbo
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		/// enable the vertex attribute so that OpenGL knows how to use it
		glEnableVertexAttribArray(layout);
		vbo.unbind();
	}

	void link_attr(vertex_buffer &vbo, GLuint layout, GLint num_components, GLenum type, GLint stride, void *offset) {
		vbo.bind();
		///
		/// configure the vertex attribute so that OpenGL knows how to read the vbo
		glVertexAttribPointer(layout, num_components, type, GL_FALSE, stride, offset);
		/// enable the vertex attribute so that OpenGL knows how to use it
		glEnableVertexAttribArray(layout);
		vbo.unbind();
	}

	void bind() const {
		/// make the vao the current vertex array object by binding it
		glBindVertexArray(m_vao_id);
	}

	/// bind vbo to 0 so that we don't accidentally modify the vbo
	/// because the usage is GL_STATIC_DRAW
	void unbind() const {
		glBindVertexArray(0);
	}

	void delete_vao() {
		/// delete all objects that has been created.
		glDeleteVertexArrays(1, &m_vao_id);
	}

};


#endif //PROGRAM_VERTEX_ARRAY_HPP
