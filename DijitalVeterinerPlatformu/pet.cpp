#include "pet.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool pet::add(int owner_id, const QString &ad, const QString &tur, const QString &irk, const QDate &dogum_tarihi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Pet (owner_id, ad, tur, irk, dogum_tarihi) VALUES (:owner_id, :ad, :tur, :irk, :dogum_tarihi)");
    query.bindValue(":owner_id", owner_id);
    query.bindValue(":ad", ad);
    query.bindValue(":tur", tur);
    query.bindValue(":irk", irk);
    query.bindValue(":dogum_tarihi", dogum_tarihi);

    if (!query.exec()) {
        qDebug() << "Hayvan eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<pet> pet::getAll()
{
    QList<pet> result;
    QSqlQuery query("SELECT id, owner_id, ad, tur, irk, dogum_tarihi FROM Pet");
    while (query.next()) {
        pet p;
        p.id = query.value("id").toInt();
        p.owner_id = query.value("owner_id").toInt();
        p.ad = query.value("ad").toString();
        p.tur = query.value("tur").toString();
        p.irk = query.value("irk").toString();
        p.dogum_tarihi = query.value("dogum_tarihi").toDate();
        result.append(p);
    }
    return result;
}

QList<pet> pet::getByOwner(int owner_id)
{
    QList<pet> result;
    QSqlQuery query;
    query.prepare("SELECT id, owner_id, ad, tur, irk, dogum_tarihi FROM Pet WHERE owner_id = :owner_id");
    query.bindValue(":owner_id", owner_id);
    query.exec();
    while (query.next()) {
        pet p;
        p.id = query.value("id").toInt();
        p.owner_id = query.value("owner_id").toInt();
        p.ad = query.value("ad").toString();
        p.tur = query.value("tur").toString();
        p.irk = query.value("irk").toString();
        p.dogum_tarihi = query.value("dogum_tarihi").toDate();
        result.append(p);
    }
    return result;
}

bool pet::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Pet WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Hayvan silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool pet::update(int id, const QString &ad, const QString &tur, const QString &irk, const QDate &dogum_tarihi)
{
    QSqlQuery query;
    query.prepare("UPDATE Pet SET ad = :ad, tur = :tur, irk = :irk, dogum_tarihi = :dogum_tarihi WHERE id = :id");
    query.bindValue(":ad", ad);
    query.bindValue(":tur", tur);
    query.bindValue(":irk", irk);
    query.bindValue(":dogum_tarihi", dogum_tarihi);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Hayvan guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}