#include "Logger.hpp"

#include <QDate>

Logger::Logger()
{ }

Logger::~Logger()
{
   if (logFile.isOpen())
   {
      logFile.close();
   }
}

QString Logger::getDateString()
{
   QDateTime dateTime = QDateTime::currentDateTime();
   return dateTime.toString("dd.MM.yyyy hh:mm:ss");
}

Logger & Logger::getInstance()
{
   static Logger singleton;
   return singleton;
}

void Logger::log(QString const & logMessage)
{
   if (logFile.isOpen())
   {
      stream << logMessage << '\n';
      stream.flush();
   }
}

bool Logger::createLog(QString const & outPath)
{
   if (!logFile.isOpen())
   {
      logFile.setFileName(outPath);

      if (logFile.open(QIODevice::WriteOnly | QIODevice::Append))
      {
         stream.setDevice(&logFile);
         stream << "\n[====== STARTING LOG ======]\n";
         stream << "[ DATE: " << getDateString() << "]\n\n";
         stream.flush();
      }
   }

   return logFile.isOpen();
}

void Logger::destroyLog()
{
   logFile.close();
}
