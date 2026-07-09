#ifndef PET_H
#define PET_H

#include <QString>
#include <QDate>
#include <QList>



class pet
{
public:
    int id;
    int owner_id;
    QString ad;
    QString tur;
    QString irk;
    QDate dogum_tarihi;

    static bool add(int owner_id, const QString &ad, const QString &tur, const QString &irk, const QDate &dogum_tarihi);
    static QList<pet> getAll();
    static QList<pet> getByOwner(int owner_id);
    static bool remove(int id);
    static bool update(int id, const QString &ad, const QString &tur, const QString &irk, const QDate &dogum_tarihi);
    static pet getById(int id);
};

#endif // PET_H