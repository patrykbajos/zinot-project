#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

#include <QFile>
#include <QTextStream>

// Singleton
class Logger
{
private:
   Logger();
   ~Logger();

protected:
   QFile logFile;
   QTextStream stream;

   QString getDateString();
public:
   static Logger & getInstance();

   bool createLog(QString const & outPath);

   void destroyLog();

   void log(QString const & logMessage);
};

#endif /* LOGGER_H_ */
