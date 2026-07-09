#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "owner.h"
#include "pet.h"
#include "appointment.h"
#include "vaccine.h"
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

    // Asi listesini doldur (hatirlatma renkleriyle)
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
