#include "Logger.hpp"

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
   std::time_t rawTime;
   std::time(&rawTime);

   std::tm * time = std::localtime(&rawTime);
   QString hour = QString::number(time->tm_hour);
   QString min = QString::number(time->tm_min);
   QString sec = QString::number(time->tm_sec);
   QString day = QString::number(time->tm_mday);
   QString mon = QString::number(time->tm_mon + 1);
   QString year = QString::number(time->tm_year + 1900);

   QString dateString = hour + '_' + min + '_' + sec +
                        "__" + day + '_' + mon + '_' + year;

   return dateString;
}

Logger & Logger::getInstance()
{
   static Logger singleton;
   return singleton;
}

void Logger::log(QString const & logMessage)
{
   if (logFile.isOpen()) stream << logMessage << '\n';
   stream.flush();
}

bool Logger::createLog(QString const & desFolder)
{
   if (!logFile.isOpen())
   {
      dir = desFolder;
      logFile.setFileName(dir + "/log_" + getDateString() + ".log");

      // Jesli otworzy plik przypisuje mu strumien
      if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) stream.setDevice(&logFile);
   }

   return logFile.isOpen();
}

void Logger::destroyLog()
{
   logFile.close();
}
