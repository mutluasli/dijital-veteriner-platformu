#include "treatment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool treatment::add(int pet_id, const QString &tani, const QString &ilac, const QDate &baslangic_tarihi, const QDate &bitis_tarihi)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Treatment (pet_id, tani, ilac, baslangic_tarihi, bitis_tarihi) VALUES (:pet_id, :tani, :ilac, :baslangic_tarihi, :bitis_tarihi)");
    query.bindValue(":pet_id", pet_id);
    query.bindValue(":tani", tani);
    query.bindValue(":ilac", ilac);
    query.bindValue(":baslangic_tarihi", baslangic_tarihi);
    query.bindValue(":bitis_tarihi", bitis_tarihi);
    if (!query.exec()) {
        qDebug() << "Tedavi eklenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<treatment> treatment::getAll()
{
    QList<treatment> result;
    QSqlQuery query("SELECT id, pet_id, tani, ilac, baslangic_tarihi, bitis_tarihi FROM Treatment");
    while (query.next()) {
        treatment t;
        t.id = query.value("id").toInt();
        t.pet_id = query.value("pet_id").toInt();
        t.tani = query.value("tani").toString();
        t.ilac = query.value("ilac").toString();
        t.baslangic_tarihi = query.value("baslangic_tarihi").toDate();
        t.bitis_tarihi = query.value("bitis_tarihi").toDate();
        result.append(t);
    }
    return result;
}

QList<treatment> treatment::getByPet(int pet_id)
{
    QList<treatment> result;
    QSqlQuery query;
    query.prepare("SELECT id, pet_id, tani, ilac, baslangic_tarihi, bitis_tarihi FROM Treatment WHERE pet_id = :pet_id");
    query.bindValue(":pet_id", pet_id);
    query.exec();
    while (query.next()) {
        treatment t;
        t.id = query.value("id").toInt();
        t.pet_id = query.value("pet_id").toInt();
        t.tani = query.value("tani").toString();
        t.ilac = query.value("ilac").toString();
        t.baslangic_tarihi = query.value("baslangic_tarihi").toDate();
        t.bitis_tarihi = query.value("bitis_tarihi").toDate();
        result.append(t);
    }
    return result;
}

bool treatment::remove(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Treatment WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Tedavi silinemedi:" << query.lastError().text();
        return false;
    }
    return true;
}

bool treatment::update(int id, const QString &tani, const QString &ilac, const QDate &baslangic_tarihi, const QDate &bitis_tarihi)
{
    QSqlQuery query;
    query.prepare("UPDATE Treatment SET tani = :tani, ilac = :ilac, baslangic_tarihi = :baslangic_tarihi, bitis_tarihi = :bitis_tarihi WHERE id = :id");
    query.bindValue(":tani", tani);
    query.bindValue(":ilac", ilac);
    query.bindValue(":baslangic_tarihi", baslangic_tarihi);
    query.bindValue(":bitis_tarihi", bitis_tarihi);
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Tedavi guncellenemedi:" << query.lastError().text();
        return false;
    }
    return true;
}