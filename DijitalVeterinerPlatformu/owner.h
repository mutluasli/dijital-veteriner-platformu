#ifndef OWNER_H
#define OWNER_H
#include "owner.h"
#include <QString>

class owner
{
public:
    int id;
    QString ad;
    QString telefon;
    QString email;

    static bool add(const QString &ad,const QString &telefon,const QString &email);
    static QList<owner> getAll();
    static bool remove (int id);
    static bool update(int id, const QString &ad,const QString &telefon,const QString &email);
};

#endif // OWNER_H
