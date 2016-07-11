//
// Created by patryk on 05.02.16.
//

#include <gl_core_3_3.hpp>
#include "Shader.hpp"

#include <QFile>
#include <memory>
#include <zinot-utils/Logger.hpp>

namespace Zinot
{

GLenum Zinot::Shader::loadFromFile(GLuint type)
{
   shader = gl::CreateShader(type);

   if (!shader)
      return gl::FALSE_;

   QString fileName = getName();
   QFile file(fileName);
   file.open(QIODevice::ReadOnly);
   QByteArray shdData = file.readAll();
   const GLchar * shdSrcPtr = shdData.data();
   file.close();

   gl::ShaderSource(shader, 1, &shdSrcPtr, NULL);
   gl::CompileShader(shader);

   GLint compilationStatus = gl::FALSE_;
   gl::GetShaderiv(shader, gl::COMPILE_STATUS, &compilationStatus);

   if (!compilationStatus)
   {
      // Pobiera dlugosc logu i zajmuje miejsce
      GLint logLen;
      gl::GetShaderiv(shader, gl::INFO_LOG_LENGTH, &logLen);
      std::unique_ptr<GLchar> log(new GLchar[logLen]);

      // Pobiera log
      GLint lenRet = 0;
      gl::GetShaderInfoLog(shader, logLen, &lenRet, log.get());

      // Logguje do pliku
      Logger & logFile = Logger::getInstance();
      logFile.log("ERROR: Shader compilation error at shader: \"" + fileName + "\"\n" +
                  QString::fromUtf8(log.get(), lenRet) + "\n");

      gl::DeleteShader(shader);
      shader = 0;

      return gl::FALSE_;
   }

   return gl::TRUE_;
}
} // namespace Zinot
