//
// Created by patryk on 09.02.16.
//

#include <gl_core_3_3.hpp>

#include "Shader.hpp"

#include <QFile>
#include <zinot-utils/Logger.hpp>
#include <memory>

namespace Zinot
{

Shader::Shader()
{
   vs = 0;
   fs = 0;
   program = 0;
}

Shader::~Shader()
{
   if (program)
      gl::DeleteProgram(program);
   if (vs)
      gl::DeleteShader(vs);
   if (fs)
      gl::DeleteShader(fs);
}

GLenum Shader::loadFromFile(const QString & shaderPath)
{
   QString vsPath, fsPath;

   program = gl::CreateProgram();
   if (!program)
      return gl::GetError();

   GLuint vs = loadShaderFromFile(vsPath, gl::VERTEX_SHADER);
   if (!vs)
      return gl::GetError();

   GLuint fs = loadShaderFromFile(fsPath, gl::FRAGMENT_SHADER);
   if (!fs)
      return gl::GetError();

   gl::AttachShader(program, vs);
   gl::AttachShader(program, fs);
   gl::LinkProgram(program);

   return gl::GetError();
}

GLuint Shader::loadShaderFromFile(const QString & path, GLenum type)
{
   GLuint shader = 0;
   shader = gl::CreateShader(type);

   if (!shader)
      return 0;

   QFile file(path);
   file.open(QIODevice::ReadOnly);
   QByteArray shdData = file.readAll();
   file.close();

   const GLchar * shdSrcPtr = shdData.data();
   gl::ShaderSource(shader, 1, &shdSrcPtr, NULL);
   gl::CompileShader(shader);

   GLint compilationStatus = gl::FALSE_;
   gl::GetShaderiv(shader, gl::COMPILE_STATUS, &compilationStatus);

   if (!compilationStatus)
   {
      // Pobiera dlugosc logu i zajmuje miejsce
      GLint logLen;
      gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &logLen);
      std::unique_ptr<GLchar> logMessage(new GLchar[logLen]);

      // Pobiera log
      GLint lenRet = 0;
      gl::GetShaderInfoLog(shader, logLen, &lenRet, logMessage.get());

      // Logguje do pliku
      Logger & log = Logger::getInstance();
      log.log("[ERROR]: Shader compilation error at shader: \"" + path + "\"\n" +
              QString::fromUtf8(logMessage.get(), lenRet) + "\n");

      gl::DeleteShader(shader);
      return 0;
   }

   return shader;
}

}
