#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <valarray>
#include <index_buffer.hpp>
#include <shader.hpp>
#include <vertex_buffer.hpp>
#include <vertex_array.hpp>

/// vertices coordinates
GLfloat vertices[]{
		//@formatter:off          COORDINATES                               /           RGB COLORS          //
		 -.5f,      -.5f * float(sqrt(3)) / 3,     0.0f,  .8f,  .3f,   .02f,
		 0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f,  .8f, .3f,  .02f,
		0.0f,     .5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.f, .6f,  .32f,
		-.5f / 2, 0.5f * float(sqrt(3)) / 6,    0.0f, .9f, .45f, .17f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6,    0.0f, .9f, .45f, .17f,
		0.0f,     -.5f * float(sqrt(3)) / 3.0f, 0.0f, .8f, .3f,  .02f
		//@formatter:on
};
/// index buffer
GLuint indices[]{
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
};


int main() {
	/// Initialize the library
	if (!glfwInit()) {
		return -1;
	}

	/// tell GLFW what version of OpenGL is being used. v4.5 here.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	/// tell GLFW only use thr CORE profile so only modern functions are available
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/// Create a windowed mode window and its OpenGL context
	GLFWwindow *window = glfwCreateWindow(640, 640, "你好世界", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}

	/// introduce the window to the current context
	glfwMakeContextCurrent(window);

	/// tell glad to load needed configs for OpenGL
	gladLoadGL();
	/// tell opengl which area of of our window is to be rendered
	glViewport(0, 0, 640, 640);

	shader shader_program("/home/brian/Projects/gl-code/shader-source/triangles.vert",
												"/home/brian/Projects/gl-code/shader-source/triangle.frag");
	/// generate vertex array object and bind it
	vertex_array vao;
	vao.bind();
	/// generate vertex buffer object and link it to vertices
	vertex_buffer vbo(vertices, sizeof(vertices));
	/// generate element buffer object and link it to indices
	index_buffer ibo(indices, sizeof(indices));
	ibo.bind();
	/// link vbo to vao
	//vao.link_vbo(vbo, 0);
	vao.link_attr(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), nullptr);
	vao.link_attr(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	/// unbind all to prevent accidentally modifying them
	vao.unbind();
	vbo.unbind();
	ibo.unbind();

	GLint uniId = glGetUniformLocation(shader_program.m_program_id, "scale");

	/// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		/// give the rendering frame a initial color
		glClearColor(.07f, .13f, .17f, 1.f);
		/// clear bg color and assign a new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		shader_program.activate();
		glUniform1f(uniId, 1.5f);
		/// bind the vao so OpenGL knows to use it
		vao.bind();
		/// draw the 4-triangle
		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
		/// swap buffer to update frame by frame.
		glfwSwapBuffers(window);
		/// Poll for and process events
		glfwPollEvents();
	}

	vao.delete_vao();
	vbo.delete_vbo();
	ibo.delete_ibo();
	shader_program.deactivate();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}