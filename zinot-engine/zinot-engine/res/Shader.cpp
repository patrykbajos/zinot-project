//
// Created by patryk on 09.02.16.
//

#include <gl_core_3_3.hpp>
#include "Shader.hpp"

#include <QFile>
#include <memory>

#include <zinot-utils/Logger.hpp>
#include <zinot-utils/json/JsonReader.hpp>
#include <zinot-engine/dao/ShaderDescDao.hpp>

namespace Zinot
{

Shader::Shader()
{
   program = 0;
}

Shader::~Shader()
{
   if (program)
      gl::DeleteProgram(program);
}

GLenum Shader::loadFromFile(const QString & shdDescPath)
{
   ShaderDescDao shdDescDao;
   if (!JsonReader::loadFromJsonFile(shdDescPath, shdDescDao))
      return 0;

   program = gl::CreateProgram();
   if (!program)
      return gl::GetError();

   GLuint vs = loadShaderSrcFromFile(shdDescDao.getVsPath(), gl::VERTEX_SHADER);
   if (!vs)
      return gl::GetError();

   GLuint fs = loadShaderSrcFromFile(shdDescDao.getFsPath(), gl::FRAGMENT_SHADER);
   if (!fs)
      return gl::GetError();

   gl::AttachShader(program, vs);
   gl::AttachShader(program, fs);
   gl::LinkProgram(program);

   GLenum error = gl::GetError();
   if (error)
      return error;

   gl::DetachShader(program, vs);
   gl::DetachShader(program, fs);
   gl::DeleteShader(vs);
   gl::DeleteShader(fs);

   return gl::NO_ERROR_;
}

GLuint Shader::loadShaderSrcFromFile(const QString & path, GLenum type)
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
