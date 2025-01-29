#include "Texture2D.hpp"


Texture2D::Texture2D(std::string imgPath, GLint internalFormat, GLenum format, GLint sWrapMode, GLint tWrapMode, GLint minFilterMode, GLint magFilterMode) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

        checkError("Texture Creation11");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);

    unsigned char* data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    checkError("Texture Creation");
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::use() {
    glBindTexture(GL_TEXTURE_2D, ID);
    checkError("Binding Texture");
}

void Texture2D::use(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    use();
}

GLuint Texture2D::checkError(const char* context)
{
    GLuint err = glGetError();
    if (err > 0) {
        std::cout << "0x" << std::hex << err << " glGetError() in " << context
            << std::endl << std::dec;
    }
    return err;
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}