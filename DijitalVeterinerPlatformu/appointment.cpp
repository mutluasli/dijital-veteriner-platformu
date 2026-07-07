#include "appointment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool appointment::add(int pet_id, int vet_id, const QDateTime &tarih_saat, const QString &durum)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Appointment (pet_id, vet_id, tarih_saat, durum) VALUES (:pet_id, :vet_id, :tarih_saat, :durum)");
    query.bindValue(":pet_id", pet_id);
    query.bindValue(":vet_id", vet_id);
    query.bindValue(":tarih_saat", tarih_saat);
    query.bindValue(":durum", durum);
    if (!query.exec()) {
        qDebug() << "Randevu eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<appointment> appointment::getAll()
{
    QList<appointment> result;
    QSqlQuery query("SELECT id, pet_id, vet_id, tarih_saat, durum FROM Appointment");
    while (query.next()) {
        appointment a;
        a.id = query.value("id").toInt();
        a.pet_id = query.value("pet_id").toInt();
        a.vet_id = query.value("vet_id").toInt();
        a.tarih_saat = query.value("tarih_saat").toDateTime();
        a.durum = query.value("durum").toString();
        result.append(a);
    }
    return result;
}

QList<appointment> appointment::getByPet(int pet_id)
{
    QList<appointment> result;
    QSqlQuery query;
    query.prepare("SELECT id, pet_id, vet_id, tarih_saat, durum FROM Appointment WHERE pet_id = :pet_id");
    query.bindValue(":pet_id", pet_id);
    query.exec();
    while (query.next()) {
        appointment a;
        a.id = query.value("id").toInt();
        a.pet_id = query.value("pet_id").toInt();
        a.vet_id = query.value("vet_id").toInt();
        a.tarih_saat = query.value("tarih_saat").toDateTime();
        a.durum = query.value("durum").toString();
        result.append(a);
    }
    return result;
}

bool appointment::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Appointment WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Randevu silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool appointment::update(int id, const QDateTime &tarih_saat, const QString &durum)
{
    QSqlQuery query;
    query.prepare("UPDATE Appointment SET tarih_saat = :tarih_saat, durum = :durum WHERE id = :id");
    query.bindValue(":tarih_saat", tarih_saat);
    query.bindValue(":durum", durum);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Randevu guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}