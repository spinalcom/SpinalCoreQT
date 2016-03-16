#ifndef CONFIG_H
#define CONFIG_H

#include <QtCore/QString>

class config
{
public:
    config();

    QString fileName;
    QString IP;
    QString port;
    QString data_container;

    void read_config();

};

#endif // CONFIG_H
