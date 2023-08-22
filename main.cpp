#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <valarray>

/// vertex shader source
const char *const vertexShaderSource = R"""(
#version 450 core
layout (location = 0) in vec3 aPos;
void main() {
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)""";
/// fragment shader source
const char *const fragmentShaderSource = R"""(
#version 450 core
out vec4 FragColor;
void main() {
  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
}
)""";

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

	/// vertices coordinates
	GLfloat vertices[] = {
			-.5f, -.5f * float(sqrt(3)) / 3, .0f,
			.5f, -.5f * float(sqrt(3)) / 3, .0f,
			.0f, .5f * float(sqrt(3)) * 2 / 3, .0f
	};

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

	/// create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	/// attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	/// compile the vertex shader into machine code
	glCompileShader(vertexShader);

	/// create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	/// attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	/// compile the fragment shader into machine code
	glCompileShader(fragmentShader);

	/// create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	/// attach the vertex and fragment shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	/// link all shaders together into the shader program
	glLinkProgram(shaderProgram);

	/// delete
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/// create reference containers for the vertex array object and vertex buffer object
	GLuint vao, vbo;
	/// generate the vao and vbo with 1 object each
	glGenVertexArrays(1, &vao);//must before vbo init.
	glGenBuffers(1, &vbo);

	/// make the vao the current vertex array object by binding it
	glBindVertexArray(vao);

	/// bind thr vbo specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	/// introduce the vertices into the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/// configure the vertex attribute so that OpenGL knows how to read the vbo
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	/// enable the vertex attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	/// bind vao and vbo to 0 so that we don't accidentally modify the vao and vbo
	/// because the usage is GL_STATIC_DRAW
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/// give the rendering frame a initial color
	glClearColor(.07f, .13f, .17f, 1.f);
	/// clear bg color and assign a new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	/// swap buffer to update frame by frame.
	glfwSwapBuffers(window);
	/// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		glClearColor(.07f, .13f, .17f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		/// tell OpenGL which program is currently being used
		glUseProgram(shaderProgram);
		/// bind the vao so OpenGL knows to use it
		glBindVertexArray(vao);
		/// draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}

	/// delete all objects that has been created.
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}