#include "../../../include/AndroidOpenGLShader.h"
#include "../../../include/AndroidUtil.h"

AndroidOpenGLShader::AndroidOpenGLShader(android_app* app, const std::string & path, bool pathFromAssets,
                                         GLenum shaderType) : Shader(path),
                                                              app(app),
                                                              pathFromAssets(pathFromAssets),
                                                              shaderType(shaderType) {
}

AndroidOpenGLShader::~AndroidOpenGLShader() {
}

void AndroidOpenGLShader::deleteShader() {
    glDeleteShader(shader);
}

long AndroidOpenGLShader::getShader() {
    return shader;
}

std::string AndroidOpenGLShader::readShaderSource() {
    std::string result;
    if(!pathFromAssets) {
        Util::loadFile(path, result);
    } else {
        AndroidUtil::loadFileFromAssets(app, path, result);
    }
    return result;
}

bool AndroidOpenGLShader::compileShader(const std::string & shaderSource) {
    shader = glCreateShader(shaderType);
    const char * shaderSourceCStr = shaderSource.c_str();
    glShaderSource(shader, 1, &shaderSourceCStr, NULL);
    glCompileShader(shader);
    GLint compilationOK = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationOK);
    if(compilationOK != GL_TRUE) {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> logContainer(logLength);
        glGetShaderInfoLog(shader, logLength, NULL, logContainer.data());
        std::string information(begin(logContainer), end(logContainer));
        std::cerr << "*** Compilation of shaderType (GLenum:" << shaderType << ") path:" << path
                  << ", information" << information << "shader source:" << shaderSource
                  << std::endl;
        deleteShader();
        return false;
    }
    return true;
}