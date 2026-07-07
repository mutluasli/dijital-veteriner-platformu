#ifndef VET_H
#define VET_H

#include <QString>
#include <QList>

class vet
{
public:
    int id;
    QString ad;
    QString uzmanlik;

    static bool add(const QString &ad, const QString &uzmanlik);
    static QList<vet> getAll();
    static bool remove(int id);
    static bool update(int id, const QString &ad, const QString &uzmanlik);
};

#endif // VET_H