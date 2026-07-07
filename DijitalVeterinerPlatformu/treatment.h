#ifndef TREATMENT_H
#define TREATMENT_H

#include <QString>
#include <QDate>
#include <QList>

class treatment
{
public:
    int id;
    int pet_id;
    QString tani;
    QString ilac;
    QDate baslangic_tarihi;
    QDate bitis_tarihi;

    static bool add(int pet_id, const QString &tani, const QString &ilac, const QDate &baslangic_tarihi, const QDate &bitis_tarihi);
    static QList<treatment> getAll();
    static QList<treatment> getByPet(int pet_id);
    static bool remove(int id);
    static bool update(int id, const QString &tani, const QString &ilac, const QDate &baslangic_tarihi, const QDate &bitis_tarihi);
};

#endif // TREATMENT_H