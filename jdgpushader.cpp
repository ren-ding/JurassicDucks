/**
 *
 *  @file jdgpushader.cpp
 *
 *  @brief The class is for gpu shader loading,
 *  program are based on Mr.Hugh Fisher's gpu loader (C version), ANU
 *
 *  @author Ren DING
 *  @date 30/09/12.
 *
 */

#include "jdgpushader.h"
#include "jdUtility.h"

static GPUProgram currentProgram;

// Compile from string source. Returns shader object
// ready for program, or fails if there is an error.
// kind should be GL_VERTEX_SHADER/GL_FRAGMENT_SHADER
GPUShader GpuCompileShader(int kind,const char *source)
{
    GLuint	    shader;
    const GLchar * src[1];
    GLint		ok;
    char		buf[512];
    char        msg[1024];
    GLsizei     len;

    // Shader itself.
    shader = glCreateShader(kind);
    jdUtility::CheckGL("glCreateShader");
    // And only one source string per shader
    src[0] = source;
    glShaderSource(shader, 1, src, NULL);
    jdUtility::CheckGL("glShaderSource");

    // Now compile and report any errors
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (! ok) {
        glGetShaderInfoLog(shader, sizeof(buf), &len, (GLchar *)buf);
        buf[len] = 0;
        if (kind == GL_VERTEX_SHADER)
            sprintf(msg, "Error in vertex shader:%s", buf);
        else if (kind == GL_FRAGMENT_SHADER)
            sprintf(msg, "Error in fragment shader:%s", buf);
        //char* to QString
        QString qmsg = QString::fromUtf8((const char*)msg);
        qWarning() << qmsg;
    }
    //Compiled OK doesn't mean perfect: might still fail link
    //ith fragment shader when final program is created

    return shader;
}

//
// The same, but read source code from a file
//
GPUShader GpuLoadShader(int kind, QString fileName)
{
    GPUShader result;
    char *    source;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        qWarning() << "Cannot read file";

    QTextStream stream ( &file );
    QString qSource = stream.readAll();
    file.close();

    // QString to char*
    QByteArray ba = qSource.toUtf8();
    source = ba.data();

    // And build shader
    result = GpuCompileShader(kind, source);    

    return result;
}

//
// Create a program object ready for use
//
GPUProgram GpuNewProgram(GPUShader vertex, GPUShader fragment)
{
    GPUProgram	prog;

    //Sanity check
    if (vertex == 0 && fragment == 0)
        qWarning() << "GpuNewProgram without any shaders!";

    prog = glCreateProgram();
    //Actually no difference between shader types when attaching
    if (vertex)
        glAttachShader(prog, vertex);
    if (fragment)
        glAttachShader(prog, fragment);

    //And make sure they play nice with each other
    GpuCheckProgram(prog);

    return prog;
}

//
//  Link and validate program. Useful for DIY pogram creation
//
void GpuCheckProgram(GPUProgram program)
{
    GLint		ok;
    char		buf[512];
    GLsizei	    len;

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (! ok) {
        glGetProgramInfoLog(program, sizeof(buf), &len, (GLchar *)buf);
        buf[len] = 0;
        qWarning() << "Error linking GPU program";
    }
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &ok);
    if (! ok) {
        glGetProgramInfoLog(program, sizeof(buf), &len, (GLchar *)buf);
        buf[len] = 0;
        qWarning() << "Validation error for GPU program:" + QString(buf);
    }
}

//
//  Install program and shaders into OpenGL. Pass 0 to disable GPU
//
void GpuUseProgram(GPUProgram program)
{
    glUseProgram(program);
    currentProgram = program;

    if (program != 0)
        jdUtility::CheckGL("glUseProgram");
}

//
// Return most recently installed program
//
GPUProgram GpuGetProgram()
{
    return currentProgram;
}

//
// Get handle to shader variable
//
GLint GpuGetUniform(GPUProgram program, QString name)
{
    GLint   h;

    //QString to char*
    QByteArray ba = name.toUtf8();
    const char* cname = ba.constData();

    h = glGetUniformLocation(program, cname);
    if (h < 0)
        qWarning() << "Cannot get location of " + name + "in shader";
    return h;
}

//
// get attribute
//
GLint GpuGetAttribute(GPUProgram program, QString name)
{
    GLint   h;
    //QString to char*
    QByteArray ba = name.toUtf8();
    const char* cname = ba.constData();

    h = glGetAttribLocation(program, cname);
    if (h < 0)
        qWarning() << "Cannot get location of attribute " + name + "in shader";
    return h;
}
