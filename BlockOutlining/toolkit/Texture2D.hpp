#pragma once

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <stbi/stb_image.h>



class Texture2D {
public:
    unsigned int ID = 0;
    int width = 0, height = 0, nrChannels = 0;

    Texture2D(std::string imgPath, GLint internalFormat, GLenum format, GLint sWrapMode, GLint tWrapMode, GLint minFilterMode, GLint magFilterMode);
    Texture2D(std::string imgPath, GLint internalFormat, GLenum format, GLint wrapMode, GLint filterMode) :
        Texture2D(imgPath, internalFormat, format, wrapMode, wrapMode, filterMode, filterMode) {}
    ~Texture2D();
    void use();
    void use(GLenum textureUnit);
    GLuint checkError(const char* context);
};

