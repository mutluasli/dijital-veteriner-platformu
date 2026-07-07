#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>

bool DataBase::initialize()
{
    // Veritabanı dosyasının nereye kaydedileceğini belirle
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QString dbPath = path + "/veteriner.db";

    // SQLite bağlantısını aç
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Veritabani acilamadi:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS Owner ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "ad TEXT NOT NULL, "
               "telefon TEXT, "
               "email TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Pet ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "owner_id INTEGER NOT NULL, "
               "ad TEXT NOT NULL, "
               "tur TEXT, "
               "irk TEXT, "
               "dogum_tarihi DATE, "
               "FOREIGN KEY (owner_id) REFERENCES Owner(id))");

    query.exec("CREATE TABLE IF NOT EXISTS Vet ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "ad TEXT NOT NULL, "
               "uzmanlik TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS Appointment ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "pet_id INTEGER NOT NULL, "
               "vet_id INTEGER NOT NULL, "
               "tarih_saat DATETIME NOT NULL, "
               "durum TEXT DEFAULT 'bekliyor', "
               "FOREIGN KEY (pet_id) REFERENCES Pet(id), "
               "FOREIGN KEY (vet_id) REFERENCES Vet(id))");

    query.exec("CREATE TABLE IF NOT EXISTS Vaccine ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "pet_id INTEGER NOT NULL, "
               "asi_adi TEXT NOT NULL, "
               "yapilis_tarihi DATE NOT NULL, "
               "sonraki_tarih DATE, "
               "FOREIGN KEY (pet_id) REFERENCES Pet(id))");

    query.exec("CREATE TABLE IF NOT EXISTS Treatment ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "pet_id INTEGER NOT NULL, "
               "tani TEXT, "
               "ilac TEXT, "
               "baslangic_tarihi DATE, "
               "bitis_tarihi DATE, "
               "FOREIGN KEY (pet_id) REFERENCES Pet(id))");

    query.exec("CREATE TABLE IF NOT EXISTS ChronicCondition ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "pet_id INTEGER NOT NULL, "
               "hastalik_adi TEXT NOT NULL, "
               "notlar TEXT, "
               "kontrol_sikligi TEXT, "
               "FOREIGN KEY (pet_id) REFERENCES Pet(id))");

    qDebug() << "Veritabani hazir:" << dbPath;
    return true;
}


