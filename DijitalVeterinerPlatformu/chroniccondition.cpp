#include "chroniccondition.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool chroniccondition::add(int pet_id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ChronicCondition (pet_id, hastalik_adi, notlar, kontrol_sikligi) VALUES (:pet_id, :hastalik_adi, :notlar, :kontrol_sikligi)");
    query.bindValue(":pet_id", pet_id);
    query.bindValue(":hastalik_adi", hastalik_adi);
    query.bindValue(":notlar", notlar);
    query.bindValue(":kontrol_sikligi", kontrol_sikligi);
    if (!query.exec()) {
        qDebug() << "Kronik durum eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<chroniccondition> chroniccondition::getAll()
{
    QList<chroniccondition> result;
    QSqlQuery query("SELECT id, pet_id, hastalik_adi, notlar, kontrol_sikligi FROM ChronicCondition");
    while (query.next()) {
        chroniccondition c;
        c.id = query.value("id").toInt();
        c.pet_id = query.value("pet_id").toInt();
        c.hastalik_adi = query.value("hastalik_adi").toString();
        c.notlar = query.value("notlar").toString();
        c.kontrol_sikligi = query.value("kontrol_sikligi").toString();
        result.append(c);
    }
    return result;
}

QList<chroniccondition> chroniccondition::getByPet(int pet_id)
{
    QList<chroniccondition> result;
    QSqlQuery query;
    query.prepare("SELECT id, pet_id, hastalik_adi, notlar, kontrol_sikligi FROM ChronicCondition WHERE pet_id = :pet_id");
    query.bindValue(":pet_id", pet_id);
    query.exec();
    while (query.next()) {
        chroniccondition c;
        c.id = query.value("id").toInt();
        c.pet_id = query.value("pet_id").toInt();
        c.hastalik_adi = query.value("hastalik_adi").toString();
        c.notlar = query.value("notlar").toString();
        c.kontrol_sikligi = query.value("kontrol_sikligi").toString();
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

bool chroniccondition::update(int id, const QString &hastalik_adi, const QString &notlar, const QString &kontrol_sikligi)
{
    QSqlQuery query;
    query.prepare("UPDATE ChronicCondition SET hastalik_adi = :hastalik_adi, notlar = :notlar, kontrol_sikligi = :kontrol_sikligi WHERE id = :id");
    query.bindValue(":hastalik_adi", hastalik_adi);
    query.bindValue(":notlar", notlar);
    query.bindValue(":kontrol_sikligi", kontrol_sikligi);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Kronik durum guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}