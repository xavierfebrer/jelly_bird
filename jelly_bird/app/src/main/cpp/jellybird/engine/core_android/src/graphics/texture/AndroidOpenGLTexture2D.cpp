#include "../../../include/AndroidOpenGLTexture2D.h"
#include "../../../include/AndroidUtil.h"

AndroidOpenGLTexture2D::AndroidOpenGLTexture2D(android_app* app, const std::string & path, bool pathFromAssets,
                                               GLint location, GLint tMinFilter, GLint tMaxFilter,
                                               GLint tWrapS, GLint tWrapT, GLint level, GLenum type,
                                               bool flipOnLoad) : Texture2D(path),
                                                                  app(app),
                                                                  pathFromAssets(pathFromAssets),
                                                                  location(location),
                                                                  tWrapS(tWrapS), tWrapT(tWrapT),
                                                                  tMinFilter(tMinFilter),
                                                                  tMaxFilter(tMaxFilter),
                                                                  level(level), type(type),
                                                                  flipOnLoad(flipOnLoad) {
}

AndroidOpenGLTexture2D::~AndroidOpenGLTexture2D() {
    unLoad();
}

bool AndroidOpenGLTexture2D::load() {
    if(!loaded) {
        glGenTextures(1, &id);
        if(!pathFromAssets){
            Util::util_stbi_set_flip_vertically_on_load(flipOnLoad);
            data = Util::util_stbi_load(std::string(path).c_str(), &size.x, &size.y, &nrChannels, 0);
        } else {
            data = AndroidUtil::loadImageFromAssets(app, std::string(path).c_str(), &size.x, &size.y, &nrChannels, 0, flipOnLoad);
        }
        GLenum format;
        if(nrChannels == 1) {
            format = GL_RED;
        } else if(nrChannels == 3) {
            format = GL_RGB;
        } else if(nrChannels == 4) {
            format = GL_RGBA;
        } else {
            std::cout << "Unknown format with nrChannels: " << nrChannels << std::endl;
            Util::util_stbi_image_free(data);
            return loaded;
        }
        if(data) {
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, level, format, size.x, size.y, 0, format, type, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tWrapS);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrapT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tMinFilter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tMaxFilter);
            Util::util_stbi_image_free(data);
        } else {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            Util::util_stbi_image_free(data);
            return loaded;
        }
        loaded = true;
    }
    return loaded;
}

bool AndroidOpenGLTexture2D::unLoad() {
    if(loaded) {
        glDeleteTextures(1, &id);
        loaded = false;
    }
    return !loaded;
}

void AndroidOpenGLTexture2D::activeBind() {
    glActiveTexture(GL_TEXTURE0 + location);
    glBindTexture(GL_TEXTURE_2D, id);
}
