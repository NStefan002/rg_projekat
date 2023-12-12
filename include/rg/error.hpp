#ifndef ERROR_H
#define ERROR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define LOG(msg) std::cerr << msg << "\n[" << __FILE__ << ", " << __func__ << ", " << __LINE__ << "]" << std::endl;

#define ASSERT(cond, msg)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(cond))                                                                                                   \
        {                                                                                                              \
            LOG(msg);                                                                                                  \
            __builtin_trap();                                                                                          \
            glfwTerminate();                                                                                           \
        }                                                                                                              \
    } while (0)

#define GLCALL(x)                                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        clearAllOpenGlErrors();                                                                                        \
        x;                                                                                                             \
        ASSERT(wasPreviousOpenGLCallSuccessful());                                                                     \
    } while (0)

void clearAllOpenGlErrors();

const char *openGLErrorToString(GLenum error);

bool wasPreviousOpenGLCallSuccessful(const char *file, int line, const char *call);

#endif // !ERROR_H
