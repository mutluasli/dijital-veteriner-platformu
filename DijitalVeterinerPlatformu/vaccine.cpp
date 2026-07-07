#include "vaccine.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool vaccine::add(int pet_id, const QString &asi_adi, const QDate &yapilis_tarihi, const QDate &sonraki_tarih)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Vaccine (pet_id, asi_adi, yapilis_tarihi, sonraki_tarih) VALUES (:pet_id, :asi_adi, :yapilis_tarihi, :sonraki_tarih)");
    query.bindValue(":pet_id", pet_id);
    query.bindValue(":asi_adi", asi_adi);
    query.bindValue(":yapilis_tarihi", yapilis_tarihi);
    query.bindValue(":sonraki_tarih", sonraki_tarih);
    if (!query.exec()) {
        qDebug() << "Asi eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<vaccine> vaccine::getAll()
{
    QList<vaccine> result;
    QSqlQuery query("SELECT id, pet_id, asi_adi, yapilis_tarihi, sonraki_tarih FROM Vaccine");
    while (query.next()) {
        vaccine v;
        v.id = query.value("id").toInt();
        v.pet_id = query.value("pet_id").toInt();
        v.asi_adi = query.value("asi_adi").toString();
        v.yapilis_tarihi = query.value("yapilis_tarihi").toDate();
        v.sonraki_tarih = query.value("sonraki_tarih").toDate();
        result.append(v);
    }
    return result;
}

QList<vaccine> vaccine::getByPet(int pet_id)
{
    QList<vaccine> result;
    QSqlQuery query;
    query.prepare("SELECT id, pet_id, asi_adi, yapilis_tarihi, sonraki_tarih FROM Vaccine WHERE pet_id = :pet_id");
    query.bindValue(":pet_id", pet_id);
    query.exec();
    while (query.next()) {
        vaccine v;
        v.id = query.value("id").toInt();
        v.pet_id = query.value("pet_id").toInt();
        v.asi_adi = query.value("asi_adi").toString();
        v.yapilis_tarihi = query.value("yapilis_tarihi").toDate();
        v.sonraki_tarih = query.value("sonraki_tarih").toDate();
        result.append(v);
    }
    return result;
}

bool vaccine::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Vaccine WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Asi silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool vaccine::update(int id, const QString &asi_adi, const QDate &yapilis_tarihi, const QDate &sonraki_tarih)
{
    QSqlQuery query;
    query.prepare("UPDATE Vaccine SET asi_adi = :asi_adi, yapilis_tarihi = :yapilis_tarihi, sonraki_tarih = :sonraki_tarih WHERE id = :id");
    query.bindValue(":asi_adi", asi_adi);
    query.bindValue(":yapilis_tarihi", yapilis_tarihi);
    query.bindValue(":sonraki_tarih", sonraki_tarih);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Asi guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}