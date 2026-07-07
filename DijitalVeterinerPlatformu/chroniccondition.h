#ifndef CHRONICCONDITION_H
#define CHRONICCONDITION_H

#include <QString>
#include <QList>

class chroniccondition
{
public:
    int id;
    int pet_id;
    QString hastalik_adi;
    QString notlar;
    QString kontrol_sikligi;

    static bool add(int pet_id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi);
    static QList<chroniccondition> getAll();
    static QList<chroniccondition> getByPet(int pet_id);
    static bool remove(int id);
    static bool update(int id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi);
};

#endif // CHRONICCONDITION_H