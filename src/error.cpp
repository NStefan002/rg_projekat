#include <rg/error.hpp>

void clearAllOpenGlErrors()
{
    while (glGetError() != GL_NO_ERROR)
        ;
}

const char *openGLErrorToString(GLenum error)
{
    switch (error)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    }
    ASSERT(false, "Invalid error code.");
    return "THIS_SHOULD_NEVER_HAPPEN";
}

bool wasPreviousOpenGLCallSuccessful(const char *file, int line, const char *call)
{
    bool success = true;
    GLenum err;
    while ((err = glGetError()))
    {
        LOG(openGLErrorToString(err));
        success = false;
    }

    return success;
}
