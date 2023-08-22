//
// Created by brian on 8/22/23.
//

#ifndef PROGRAM_TEXTURE_HPP
#define PROGRAM_TEXTURE_HPP

#include <glad/glad.h>
#include <stb/std_image.h>
#include <shader.hpp>

class texture {
public:
	GLuint m_texture_id;
	GLenum type;
	GLuint unit;

	texture(const char *const image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
		// Assigns the type of the texture ot the texture object
		type = texType;
		// Stores the width, height, and the number of color channels of the image
		int widthImg, heightImg, numColCh;
		// Flips the image so it appears right side up
		stbi_set_flip_vertically_on_load(true);
		// Reads the image from a file and stores it in bytes
		unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

		// Generates an OpenGL texture object
		glGenTextures(1, &m_texture_id);
		// Assigns the texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(texType, m_texture_id);

		// Configures the type of algorithm that is used to make the image smaller or bigger
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
		// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
		// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

		// Assigns the image to the OpenGL Texture object
		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
		// Generates MipMaps
		glGenerateMipmap(texType);

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(texType, 0);
	}

	void tex_uni(shader &_shader, const char *const uniform, GLint _unit) {
		// Gets the location of the uniform
		GLint texUni = glGetUniformLocation(_shader.m_program_id, uniform);
		// Shader needs to be activated before changing the value of a uniform
		_shader.activate();
		// Sets the value of the uniform
		glUniform1i(texUni, _unit);
	}

	void bind() {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(type, m_texture_id);
	}

	void unbind() {
		glBindTexture(type, 0);
	}

	void delete_texture() {
		glDeleteTextures(1, &m_texture_id);
	}

};


#endif //PROGRAM_TEXTURE_HPP
