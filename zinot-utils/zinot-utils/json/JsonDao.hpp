//
// Created by patryk on 10.01.17.
//

#ifndef ZINOT_PROJECT_JSONDAO_HPP
#define ZINOT_PROJECT_JSONDAO_HPP

#include <QJsonDocument>

class JsonDao
{
public:
   virtual bool loadFromJsonDoc(const QJsonDocument & jsonDoc) = 0;
};


#endif //ZINOT_PROJECT_JSONDAO_HPP
