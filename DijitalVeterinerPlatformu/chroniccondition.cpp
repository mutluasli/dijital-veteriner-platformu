#include "chroniccondition.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool chroniccondition::add(int pet_id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi, const QDate &son_kontrol_tarihi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ChronicCondition (pet_id, hastalik_adi, notlar, kontrol_sikligi, son_kontrol_tarihi) VALUES (:pet_id, :hastalik_adi, :notlar, :kontrol_sikligi, :son_kontrol_tarihi)");
    query.bindValue(":pet_id", pet_id);
    query.bindValue(":hastalik_adi", hastalik_adi);
    query.bindValue(":notlar", notlar);
    query.bindValue(":kontrol_sikligi", kontrol_sikligi);
    query.bindValue(":son_kontrol_tarihi", son_kontrol_tarihi);
    if (!query.exec()) {
        qDebug() << "Kronik durum eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<chroniccondition> chroniccondition::getAll()
{
    QList<chroniccondition> result;
    QSqlQuery query("SELECT id, pet_id, hastalik_adi, notlar, kontrol_sikligi, son_kontrol_tarihi FROM ChronicCondition");
    while (query.next()) {
        chroniccondition c;
        c.id = query.value("id").toInt();
        c.pet_id = query.value("pet_id").toInt();
        c.hastalik_adi = query.value("hastalik_adi").toString();
        c.notlar = query.value("notlar").toString();
        c.kontrol_sikligi = query.value("kontrol_sikligi").toString();
        c.son_kontrol_tarihi = query.value("son_kontrol_tarihi").toDate();
        result.append(c);
    }
    return result;
}

QList<chroniccondition> chroniccondition::getByPet(int pet_id)
{
    QList<chroniccondition> result;
    QSqlQuery query;
    query.prepare("SELECT id, pet_id, hastalik_adi, notlar, kontrol_sikligi, son_kontrol_tarihi FROM ChronicCondition WHERE pet_id = :pet_id");
    query.bindValue(":pet_id", pet_id);
    query.exec();
    while (query.next()) {
        chroniccondition c;
        c.id = query.value("id").toInt();
        c.pet_id = query.value("pet_id").toInt();
        c.hastalik_adi = query.value("hastalik_adi").toString();
        c.notlar = query.value("notlar").toString();
        c.kontrol_sikligi = query.value("kontrol_sikligi").toString();
        c.son_kontrol_tarihi = query.value("son_kontrol_tarihi").toDate();
        result.append(c);
    }
    return result;
}

bool chroniccondition::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ChronicCondition WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Kronik durum silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool chroniccondition::update(int id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi, const QDate &son_kontrol_tarihi)
{
    QSqlQuery query;
    query.prepare("UPDATE ChronicCondition SET hastalik_adi = :hastalik_adi, notlar = :notlar, kontrol_sikligi = :kontrol_sikligi, son_kontrol_tarihi = :son_kontrol_tarihi WHERE id = :id");
    query.bindValue(":hastalik_adi", hastalik_adi);
    query.bindValue(":notlar", notlar);
    query.bindValue(":kontrol_sikligi", kontrol_sikligi);
    query.bindValue(":son_kontrol_tarihi", son_kontrol_tarihi);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Kronik durum guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}