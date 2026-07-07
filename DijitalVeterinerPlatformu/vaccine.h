#ifndef VACCINE_H
#define VACCINE_H

#include <QString>
#include <QDate>
#include <QList>

class vaccine
{
public:
    int id;
    int pet_id;
    QString asi_adi;
    QDate yapilis_tarihi;
    QDate sonraki_tarih;

    static bool add(int pet_id, const QString &asi_adi, const QDate &yapilis_tarihi, const QDate &sonraki_tarih);
    static QList<vaccine> getAll();
    static QList<vaccine> getByPet(int pet_id);
    static bool remove(int id);
    static bool update(int id, const QString &asi_adi, const QDate &yapilis_tarihi, const QDate &sonraki_tarih);
};

#endif // VACCINE_H