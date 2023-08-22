#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/// 根据glew文档，要先创建opengl context才能调用glew API
	if (glewInit() not_eq GLEW_OK) {
		std::cout << "Error\n";
	}

	float positions[]{
			-1.f, -1.f,
			0.f, 1.f,
			1.f, -1.f
	};

	uint32_t buff;
	/// hey gl, generate me just 1 buffer and store it into buff
	glGenBuffers(1, &buff);
	/// and i am going to use the generated buffer like this:
	glBindBuffer(GL_ARRAY_BUFFER, buff);
	/// learn more from http://docs.gl
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		/// draw a triangle (black triangle)
		glDrawArrays(GL_TRIANGLES, 0, 3);// count: index point(x,y) count

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}