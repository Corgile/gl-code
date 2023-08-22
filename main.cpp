#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	/* Initialize the library */
	if (!glfwInit()) {
		return -1;
	}

	/// tell GLFW what version of OpenGL is being used. v4.5 here.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	/// tell GLFW only use thr CORE profile so only modern functions are available
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// Create a windowed mode window and its OpenGL context
	GLFWwindow *window = glfwCreateWindow(640, 480, "你好世界", nullptr, nullptr);
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
	glViewport(0,0, 640, 480);
	/// give the rendering frame a initial color
	glClearColor(.07f, .13f, .17f, 1.f);
	/// clear bg color and assign a new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	/// swap buffer to update frame by frame.
	glfwSwapBuffers(window);
	/// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}