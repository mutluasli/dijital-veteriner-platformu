#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QString>
#include <QDateTime>
#include <QList>

class appointment
{
public:
    int id;
    int pet_id;
    int vet_id;
    QDateTime tarih_saat;
    QString durum;

    static bool add(int pet_id, int vet_id, const QDateTime &tarih_saat, const QString &durum);
    static QList<appointment> getAll();
    static QList<appointment> getByPet(int pet_id);
    static bool remove(int id);
    static bool update(int id, const QDateTime &tarih_saat, const QString &durum);
};

#endif // APPOINTMENT_H