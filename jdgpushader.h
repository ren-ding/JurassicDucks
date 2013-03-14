/**
 *
 *  @file jdgpushader.h
 *
 *  @brief The head file of jdgpushader.cpp
 *
 *  @author Ren DING
 *  @date 30/09/12.
 *
 */


#ifndef __JDGPUSHADERH__
#define __JDGPUSHADERH__

#include "glheaders.h"
#include "headers.h"

typedef GLuint	GPUShader;
typedef GLuint	GPUProgram;

extern "C" {
    // Compile from string source. Returns shader object
    // ready for program, or fails if there is an error.
    // kind should be GL_VERTEX_SHADER/GL_FRAGMENT_SHADER
    GPUShader GpuCompileShader(int kind, const char *source);

    // The same, but read source code from a file
    GPUShader GpuLoadShader(int kind, QString fileName);

    // Create a program object ready for use
    GPUProgram GpuNewProgram(GPUShader vertex, GPUShader fragment);

    // Link and validate program. Useful for DIY pogram creation
    void GpuCheckProgram(GPUProgram program);

    // Install program and shaders into OpenGL. Pass 0 to disable GPU
    void GpuUseProgram(GPUProgram program);

    // Return most recently installed program
    GPUProgram GpuGetProgram();

    // Get handle to shader variable
    GLint GpuGetUniform(GPUProgram program, QString name);
    GLint GpuGetAttribute(GPUProgram program, QString name);
}

#endif // __JDGPUSHADERH__
