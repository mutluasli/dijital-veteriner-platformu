#include "owner.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool owner::add(const QString &ad, const QString &telefon, const QString &email)
{
    QSqlQuery query;
    query.prepare("INSERT INTO owner (ad, telefon, email) VALUES (:ad, :telefon, :email)");
    query.bindValue(":ad", ad);
    query.bindValue(":telefon", telefon);
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Sahip eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<owner> owner::getAll()
{
    QList<owner> result;
    QSqlQuery query("SELECT id, ad, telefon, email FROM owner");

    while (query.next()) {
        owner o;
        o.id = query.value("id").toInt();
        o.ad = query.value("ad").toString();
        o.telefon = query.value("telefon").toString();
        o.email = query.value("email").toString();
        result.append(o);
    }
    return result;
}

bool owner::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM owner WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Sahip silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool owner::update(int id, const QString &ad, const QString &telefon, const QString &email)
{
    QSqlQuery query;
    query.prepare("UPDATE owner SET ad = :ad, telefon = :telefon, email = :email WHERE id = :id");
    query.bindValue(":ad", ad);
    query.bindValue(":telefon", telefon);
    query.bindValue(":email", email);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Sahip guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}