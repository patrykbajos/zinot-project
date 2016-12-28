//
// Created by patryk on 09.02.16.
//

#include <gl_core_3_3.hpp>

#include "GpuProgram.hpp"

#include <QFile>
#include <zinot-utils/Logger.hpp>
#include <memory>

namespace Zinot
{

GpuProgram::GpuProgram()
{
   vs = 0;
   fs = 0;
   program = 0;
}

GpuProgram::~GpuProgram()
{
   if (program)
      gl::DeleteProgram(program);
   if (vs)
      gl::DeleteShader(vs);
   if (fs)
      gl::DeleteShader(fs);
}

GLenum GpuProgram::loadFromFiles(const QString & vsPath, const QString & fsPath)
{
   program = gl::CreateProgram();
   if (!program)
      return gl::GetError();

   vs = loadShaderFromFile(vsPath, gl::VERTEX_SHADER);
   if (!vs)
      return gl::GetError();

   fs = loadShaderFromFile(fsPath, gl::FRAGMENT_SHADER);
   if (!fs)
      return gl::GetError();

   gl::AttachShader(program, vs);
   gl::AttachShader(program, fs);
   gl::LinkProgram(program);

   return gl::GetError();
}

GLuint GpuProgram::loadShaderFromFile(const QString & path, GLenum type)
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
      shader = 0;

      return 0;
   }

   return shader;
}

}
