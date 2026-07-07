#include "vet.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool vet::add(const QString &ad, const QString &uzmanlik)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Vet (ad, uzmanlik) VALUES (:ad, :uzmanlik)");
    query.bindValue(":ad", ad);
    query.bindValue(":uzmanlik", uzmanlik);
    if (!query.exec()) {
        qDebug() << "Veteriner eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<vet> vet::getAll()
{
    QList<vet> result;
    QSqlQuery query("SELECT id, ad, uzmanlik FROM Vet");
    while (query.next()) {
        vet v;
        v.id = query.value("id").toInt();
        v.ad = query.value("ad").toString();
        v.uzmanlik = query.value("uzmanlik").toString();
        result.append(v);
    }
    return result;
}

bool vet::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Vet WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Veteriner silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool vet::update(int id, const QString &ad, const QString &uzmanlik)
{
    QSqlQuery query;
    query.prepare("UPDATE Vet SET ad = :ad, uzmanlik = :uzmanlik WHERE id = :id");
    query.bindValue(":ad", ad);
    query.bindValue(":uzmanlik", uzmanlik);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Veteriner guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}