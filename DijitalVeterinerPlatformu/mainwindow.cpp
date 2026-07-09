#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "owner.h"
#include "pet.h"
#include "appointment.h"

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


