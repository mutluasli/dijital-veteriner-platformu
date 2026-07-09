#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "owner.h"
#include "pet.h"
#include "vet.h"
#include "appointment.h"
#include "vaccine.h"
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<owner> owners = owner::getAll();
    for (const owner &o : owners) {
        ui->listWidgetSahipler->addItem(o.ad + " - " + o.telefon + " - " + o.email);
    }
    // Sahip combo box'ini doldur
    for (const owner &o : owners) {
        ui->comboBoxSahip->addItem(o.ad, o.id);
    }

    // Hayvan listesini doldur
    QList<pet> pets = pet::getAll();
    for (const pet &p : pets) {
        ui->listWidgetHayvanlar->addItem(p.ad + " (" + p.tur + ")");
    }
    // Randevu icin hayvan combo box'ini doldur
    QList<pet> allPets = pet::getAll();
    for (const pet &p : allPets) {
        ui->comboBoxHayvan->addItem(p.ad, p.id);
    }

    // Randevu listesini doldur
    QList<appointment> appointments = appointment::getAll();
    for (const appointment &a : appointments) {
        ui->listWidgetRandevu->addItem(
            a.tarih_saat.toString("dd.MM.yyyy hh:mm") + " - " + a.durum
            );
    }

    // Asi icin hayvan combo box'ini doldur
    QList<pet> petsForVaccine = pet::getAll();
    for (const pet &p : petsForVaccine) {
        ui->comboBoxAsiHayvan->addItem(p.ad, p.id);
    }

    // Asi listesini doldur
    refreshVaccineList();

    refreshReminders();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSahipEkle_clicked()
{
    QString ad = ui->lineEditAd->text();
    QString telefon = ui->lineEditTelefon->text();
    QString email = ui->lineEditEmail->text();

    if (ad.isEmpty()) {
        return;
    }

    owner::add(ad, telefon, email);

    ui->lineEditAd->clear();
    ui->lineEditTelefon->clear();
    ui->lineEditEmail->clear();

    ui->listWidgetSahipler->clear();
    QList<owner> owners = owner::getAll();
    for (const owner &o : owners) {
        ui->listWidgetSahipler->addItem(o.ad + " - " + o.telefon + " - " + o.email);
    }

}


void MainWindow::on_btnHayvanEkle_clicked()
{
    int ownerId = ui->comboBoxSahip->currentData().toInt();
    QString ad = ui->lineEditHayvanAdi->text();
    QString tur = ui->lineEditTur->text();
    QString irk = ui->lineEditIrk->text();
    QDate dogumTarihi = ui->dateEditDogum->date();

    if (ad.isEmpty() || ui->comboBoxSahip->count() == 0) {
        return;
    }

    pet::add(ownerId, ad, tur, irk, dogumTarihi);

    ui->lineEditHayvanAdi->clear();
    ui->lineEditTur->clear();
    ui->lineEditIrk->clear();

    ui->listWidgetHayvanlar->clear();
    QList<pet> pets = pet::getAll();
    for (const pet &p : pets) {
        ui->listWidgetHayvanlar->addItem(p.ad + " (" + p.tur + ")");
    }
}



    void MainWindow::on_btnRandevuEkle_clicked()
    {
        if (ui->comboBoxHayvan->count() == 0) {
            return;
        }

        int petId = ui->comboBoxHayvan->currentData().toInt();
        QDateTime tarihSaat = ui->dateTimeEditRandevu->dateTime();

        appointment::add(petId, 0, tarihSaat, "bekliyor");

        ui->listWidgetRandevu->clear();
        QList<appointment> appointments = appointment::getAll();
        for (const appointment &a : appointments) {
            ui->listWidgetRandevu->addItem(
                a.tarih_saat.toString("dd.MM.yyyy hh:mm") + " - " + a.durum
                );
        }
    }

    void MainWindow::on_btnAsiEkle_clicked()
    {
        if (ui->comboBoxAsiHayvan->count() == 0) {
            return;
        }

        int petId = ui->comboBoxAsiHayvan->currentData().toInt();
        QString asiAdi = ui->lineEditAsiAdi->text();
        QDate yapilisTarihi = ui->dateEditYapilis->date();
        QDate sonrakiTarih = ui->dateEditSonraki->date();

        if (asiAdi.isEmpty()) {
            return;
        }

        vaccine::add(petId, asiAdi, yapilisTarihi, sonrakiTarih);

        ui->lineEditAsiAdi->clear();

        refreshVaccineList();
    }

    void MainWindow::refreshVaccineList()
        {
            ui->listWidgetAsilar->clear();
            QList<vaccine> vaccines = vaccine::getAll();
            QDate today = QDate::currentDate();
            for (const vaccine &v : vaccines) {
                QString itemText = v.asi_adi + " - Sonraki: " + v.sonraki_tarih.toString("dd.MM.yyyy");
                QListWidgetItem *item = new QListWidgetItem(itemText);

                int daysLeft = today.daysTo(v.sonraki_tarih);
                if (daysLeft < 0) {
                    item->setForeground(Qt::red);
                    item->setText(itemText + " (GECIKTI!)");
                } else if (daysLeft <= 7) {
                    item->setForeground(QColor(255, 140, 0));
                    item->setText(itemText + " (YAKLASIYOR)");
                }
                ui->listWidgetAsilar->addItem(item);
            }
        }

        void MainWindow::refreshReminders()
        {
            ui->listWidgetHatirlatmalar->clear();
            QDate today = QDate::currentDate();

            QList<vaccine> vaccines = vaccine::getAll();
            for (const vaccine &v : vaccines) {
                int daysLeft = today.daysTo(v.sonraki_tarih);
                if (daysLeft > 7) {
                    continue;
                }

                pet ilgiliHayvan = pet::getById(v.pet_id);
                QString itemText = ilgiliHayvan.ad + " - " + v.asi_adi + " - " + v.sonraki_tarih.toString("dd.MM.yyyy");
                QListWidgetItem *item = new QListWidgetItem(itemText);

                if (daysLeft < 0) {
                    item->setForeground(Qt::red);
                    item->setText(itemText + " (GECIKTI!)");
                } else {
                    item->setForeground(QColor(255, 140, 0));
                    item->setText(itemText + " (YAKLASIYOR)");
                }

                ui->listWidgetHatirlatmalar->addItem(item);
            }

            if (ui->listWidgetHatirlatmalar->count() == 0) {
                ui->listWidgetHatirlatmalar->addItem("Su an icin bekleyen hatirlatma yok.");
            }
        }

    void MainWindow::on_btnAsiProgramiOlustur_clicked()
        {
            if (ui->comboBoxAsiHayvan->count() == 0) {
                return;
            }

            int petId = ui->comboBoxAsiHayvan->currentData().toInt();
            pet secilenHayvan = pet::getById(petId);
            QDate today = QDate::currentDate();

            int ayFarki = secilenHayvan.dogum_tarihi.daysTo(today) / 30;
            QString tur = secilenHayvan.tur.toLower();
            bool kedi = tur.contains("kedi");
            bool kopek = tur.contains("kopek") || tur.contains("köpek");

            if (ayFarki >= 84) {
                QMessageBox::information(this, "Bilgi", secilenHayvan.ad + " senior yasta, rutin asi programina ihtiyaci yok.");
                return;
            }

            bool yavru = ayFarki < 12;
            QList<QPair<QString, int>> program;

            if (kedi && yavru) {
                program = {{"Karma 1", 0}, {"Losemi 1", 10}, {"Karma 2", 10}, {"Losemi 2", 10}, {"Kuduz", 10}};
            } else if (kedi && !yavru) {
                program = {{"Karma", 0}, {"Losemi", 10}, {"Kuduz", 10}};
            } else if (kopek && yavru) {
                program = {{"Karma 1", 0}, {"Korona 1", 10}, {"Karma 2", 10}, {"Korona 2", 10},
                           {"Bronsin 1", 10}, {"Bronsin 2", 10}, {"Kuduz", 10}};
            } else if (kopek && !yavru) {
                program = {{"Karma", 0}, {"Kuduz", 10}};
            } else {
                QMessageBox::warning(this, "Uyari", "Bu tur icin asi protokolu tanimli degil.");
                return;
            }

            QDate tarih = today;
            for (int i = 0; i < program.size(); ++i) {
                tarih = tarih.addDays(program[i].second);
                QDate sonrakiDoz = (i + 1 < program.size()) ? tarih.addDays(program[i+1].second) : tarih.addYears(1);
                vaccine::add(petId, program[i].first, tarih, sonrakiDoz);
            }

            // Ic dis parazit ayrica, surekli tekrarlayan olarak eklenir (60 gunde bir)
            vaccine::add(petId, "Ic Dis Parazit", today, today.addDays(60));

            QMessageBox::information(this, "Basarili", secilenHayvan.ad + " icin asi programi olusturuldu.");
            refreshVaccineList();
        }
