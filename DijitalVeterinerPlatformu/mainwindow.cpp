#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "owner.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<owner> owners = owner::getAll();
    for (const owner &o : owners) {
        ui->listWidgetSahipler->addItem(o.ad + " - " + o.telefon + " - " + o.email);
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

