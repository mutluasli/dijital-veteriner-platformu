#ifndef CHRONICCONDITION_H
#define CHRONICCONDITION_H

#include <QString>
#include <QDate>
#include <QList>

class chroniccondition
{
public:
    int id;
    int pet_id;
    QString hastalik_adi;
    QString notlar;
    QString kontrol_sikligi;
    QDate son_kontrol_tarihi;

    static bool add(int pet_id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi, const QDate &son_kontrol_tarihi);
    static QList<chroniccondition> getAll();
    static QList<chroniccondition> getByPet(int pet_id);
    static bool remove(int id);
    static bool update(int id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi, const QDate &son_kontrol_tarihi);
};

#endif // CHRONICCONDITION_H