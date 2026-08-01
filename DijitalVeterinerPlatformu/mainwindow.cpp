#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "owner.h"
#include "pet.h"
#include "vet.h"
#include "appointment.h"
#include "vaccine.h"
#include <QMessageBox>
#include <QDate>
#include "treatment.h"
#include "chroniccondition.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QList<owner> owners = owner::getAll();
    for (const owner &o : owners) {
        QListWidgetItem *item = new QListWidgetItem(o.ad + " - " + o.telefon + " - " + o.email);
        item->setData(Qt::UserRole, o.id);
       ui->listWidgetSahipler->addItem(item);
    }

    // Sahip combo box'ini doldur
    for (const owner &o : owners) {
        ui->comboBoxSahip->addItem(o.ad, o.id);
    }


    // Hayvan listesini doldur
    QList<pet> pets = pet::getAll();
    for (const pet &p : pets) {
        QListWidgetItem *item = new QListWidgetItem(petFullLabel(p) + " - Tur: " + p.tur + " - Dogum: " + p.dogum_tarihi.toString("dd.MM.yyyy"));
        item->setData(Qt::UserRole, p.id);
        ui->listWidgetHayvanlar->addItem(item);
    }

    // Randevu icin hayvan combo box'ini doldur
    QList<pet> allPets = pet::getAll();
    for (const pet &p : allPets) {
    ui->comboBoxHayvan->addItem(petComboLabel(p), p.id);
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
        ui->comboBoxAsiHayvan->addItem(petComboLabel(p), p.id);
    }

    // Asi listesini doldur
    refreshVaccineList();

    refreshReminders();

    // Tedavi icin hayvan combo box'ini doldur
    QList<pet> petsForTreatment = pet::getAll();
    for (const pet &p : petsForTreatment) {
        ui->comboBoxTedaviHayvan->addItem(petComboLabel(p), p.id);
    }

    // Tedavi listesini doldur
    QList<treatment> treatments = treatment::getAll();
    for (const treatment &t : treatments) {
        ui->listWidgetTedaviler->addItem(t.tani + " - " + t.ilac + " (" + t.baslangic_tarihi.toString("dd.MM.yyyy") + " - " + t.bitis_tarihi.toString("dd.MM.yyyy") + ")");
    }
    // Kronik durum icin hayvan combo box'ini doldur
    QList<pet> petsForChronic = pet::getAll();
    for (const pet &p : petsForChronic) {
       ui->comboBoxKronikHayvan->addItem(petComboLabel(p), p.id);
    }

    refreshChronicList();

    // Beslenme icin hayvan combo box'ini doldur
    QList<pet> petsForNutrition = pet::getAll();
    for (const pet &p : petsForNutrition) {
        ui->comboBoxBeslenmeHayvan->addItem(petComboLabel(p), p.id);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::petComboLabel(const pet &p)
{
    owner sahibi = owner::getById(p.owner_id);
    return p.ad + " (" + sahibi.ad + ")";
}

QString MainWindow::petFullLabel(const pet &p)
{
    owner sahibi = owner::getById(p.owner_id);
    return p.ad + " - Sahip: " + sahibi.ad + " - Irk: " + p.irk;
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
        QListWidgetItem *item = new QListWidgetItem(o.ad + " - " + o.telefon + " - " + o.email);
        item->setData(Qt::UserRole, o.id);
        ui->listWidgetSahipler->addItem(item);
    }

    // Sahip combo box'ini de guncelle
    ui->comboBoxSahip->clear();
    for (const owner &o : owners) {
        ui->comboBoxSahip->addItem(o.ad, o.id);
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
        owner sahibi = owner::getById(p.owner_id);
        QString satir = p.ad + " - Sahip: " + sahibi.ad + " - Tür: " + p.tur + " - Irk: " + p.irk + " - Doğum: " + p.dogum_tarihi.toString("dd.MM.yyyy");
        QListWidgetItem *item = new QListWidgetItem(satir);
        item->setData(Qt::UserRole, p.id);
        ui->listWidgetHayvanlar->addItem(item);
    }
    ui->listWidgetHayvanlar->setCurrentItem(nullptr);

    ui->comboBoxHayvan->clear();
    ui->comboBoxAsiHayvan->clear();
    ui->comboBoxTedaviHayvan->clear();
    ui->comboBoxKronikHayvan->clear();
    ui->comboBoxBeslenmeHayvan->clear();
    for (const pet &p : pets) {
       ui->comboBoxHayvan->addItem(petComboLabel(p), p.id);
        ui->comboBoxAsiHayvan->addItem(p.ad, p.id);
        ui->comboBoxTedaviHayvan->addItem(p.ad, p.id);
        ui->comboBoxKronikHayvan->addItem(p.ad, p.id);
        ui->comboBoxBeslenmeHayvan->addItem(p.ad, p.id);
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
        pet ilgiliHayvan = pet::getById(a.pet_id);
        QString satir = petFullLabel(ilgiliHayvan) + " - " + a.tarih_saat.toString("dd.MM.yyyy hh:mm") + " - " + a.durum;
        QListWidgetItem *item = new QListWidgetItem(satir);
        item->setData(Qt::UserRole, a.id);
        ui->listWidgetRandevu->addItem(item);
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

        if (asiAdi.isEmpty()) {
            return;
        }

        QDate sonrakiTarih;
        QString asiAdiKucuk = asiAdi.toLower();
        if (asiAdiKucuk.contains("parazit")) {
            sonrakiTarih = yapilisTarihi.addDays(60);
        } else {
            sonrakiTarih = yapilisTarihi.addYears(1);
        }

        vaccine::add(petId, asiAdi, yapilisTarihi, sonrakiTarih);

        ui->lineEditAsiAdi->clear();

        refreshVaccineList();
        refreshReminders();
    }

    void MainWindow::refreshVaccineList()
    {
        ui->listWidgetAsilar->clear();
        QList<vaccine> vaccines = vaccine::getAll();
        QDate today = QDate::currentDate();
        for (const vaccine &v : vaccines) {
            pet ilgiliHayvan = pet::getById(v.pet_id);
            QString itemText = petFullLabel(ilgiliHayvan) + " - " + v.asi_adi + " - Sonraki: " + v.sonraki_tarih.toString("dd.MM.yyyy");
            QListWidgetItem *item = new QListWidgetItem(itemText);
            item->setData(Qt::UserRole, v.id);

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

        void MainWindow::refreshChronicList()
        {
            ui->listWidgetKronikDurumlar->clear();
            QDate today = QDate::currentDate();

            QList<chroniccondition> conditions = chroniccondition::getAll();
            for (const chroniccondition &c : conditions) {
                pet ilgiliHayvan = pet::getById(c.pet_id);
                int siklikGun = c.kontrol_sikligi.toInt();
                QDate sonrakiKontrol = c.son_kontrol_tarihi.addDays(siklikGun);
                int daysLeft = today.daysTo(sonrakiKontrol);

                QString itemText = petFullLabel(ilgiliHayvan) + " - " + c.hastalik_adi + " - Sonraki kontrol: " + sonrakiKontrol.toString("dd.MM.yyyy");
                QListWidgetItem *item = new QListWidgetItem(itemText);
                item->setData(Qt::UserRole, c.id);

                if (daysLeft < 0) {
                    item->setForeground(Qt::red);
                    item->setText(itemText + " (GECIKTI!)");
                } else if (daysLeft <= 7) {
                    item->setForeground(QColor(255, 140, 0));
                    item->setText(itemText + " (YAKLASIYOR)");
                }
                ui->listWidgetKronikDurumlar->addItem(item);
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


        void MainWindow::on_btnTedaviEkle_clicked()
        {
            if (ui->comboBoxTedaviHayvan->count() == 0) {
                return;
            }

            int petId = ui->comboBoxTedaviHayvan->currentData().toInt();
            QString tani = ui->lineEditTani->text();
            QString ilac = ui->lineEditIlac->text();
            QDate baslangic = ui->dateEditBaslangic->date();
            QDate bitis = ui->dateEditBitis->date();

            if (tani.isEmpty()) {
                return;
            }

            treatment::add(petId, tani, ilac, baslangic, bitis);

            ui->lineEditTani->clear();
            ui->lineEditIlac->clear();

            ui->listWidgetTedaviler->clear();
            QList<treatment> treatments = treatment::getAll();
            for (const treatment &t : treatments) {
                pet ilgiliHayvan = pet::getById(t.pet_id);
                QString satir = petFullLabel(ilgiliHayvan) + " - " + t.tani + " - " + t.ilac + " (" + t.baslangic_tarihi.toString("dd.MM.yyyy") + " - " + t.bitis_tarihi.toString("dd.MM.yyyy") + ")";
                QListWidgetItem *item = new QListWidgetItem(satir);
                item->setData(Qt::UserRole, t.id);
                ui->listWidgetTedaviler->addItem(item);
            }
        }

        void MainWindow::on_btnKronikEkle_clicked()
        {
            if (ui->comboBoxKronikHayvan->count() == 0) {
                return;
            }

            int petId = ui->comboBoxKronikHayvan->currentData().toInt();
            QString hastalikAdi = ui->lineEditHastalikAdi->text();
            QString notlar = ui->lineEditNotlar->text();
            int siklikGun = ui->spinBoxKontrolSikligi->value();
            QDate sonKontrol = ui->dateEditSonKontrol->date();

            if (hastalikAdi.isEmpty()) {
                return;
            }

            chroniccondition::add(petId, hastalikAdi, notlar, QString::number(siklikGun), sonKontrol);

            ui->lineEditHastalikAdi->clear();
            ui->lineEditNotlar->clear();

            refreshChronicList();
        }


        void MainWindow::on_btnBeslenmeGetir_clicked()
        {
            if (ui->comboBoxBeslenmeHayvan->count() == 0) {
                return;
            }

            int petId = ui->comboBoxBeslenmeHayvan->currentData().toInt();
            pet secilenHayvan = pet::getById(petId);
            QDate today = QDate::currentDate();

            int ayFarki = secilenHayvan.dogum_tarihi.daysTo(today) / 30;
            QString tur = secilenHayvan.tur.toLower();
            bool kedi = tur.contains("kedi");
            bool kopek = tur.contains("kopek") || tur.contains("köpek");

            QString yasGrubu;
            if (ayFarki < 12) {
                yasGrubu = "yavru";
            } else if (ayFarki < 84) {
                yasGrubu = "erişkin";
            } else {
                yasGrubu = "senior";
            }

            QString oneri;

            if (kedi && yasGrubu == "yavru") {
                oneri = "Yuksek proteinli, yavru kedi mamasi onerilir. Gunde 3-4 ogune bolunmus beslenme. Buyume donemi oldugu icin kalsiyum ve DHA icerigi zengin mamalar tercih edilmeli.";
            } else if (kedi && yasGrubu == "erişkin") {
                oneri = "Dengeli erişkin kedi mamasi, gunde 2 ogun. Kilo takibi yapilmali, asiri kilo alimindan kacinilmali.";
            } else if (kedi && yasGrubu == "senior") {
                oneri = "Sindirimi kolay, dusuk kalorili senior kedi mamasi onerilir. Bobrek sagligini destekleyen icerikler tercih edilmeli. Gunde 2-3 kucuk ogun.";
            } else if (kopek && yasGrubu == "yavru") {
                oneri = "Yuksek proteinli, yavru kopek mamasi onerilir. Gunde 3-4 ogune bolunmus beslenme. Irk buyuklugune uygun mama secilmeli (kucuk/orta/buyuk irk formulleri farklidir).";
            } else if (kopek && yasGrubu == "erişkin") {
                oneri = "Dengeli erişkin kopek mamasi, gunde 2 ogun. Aktivite seviyesine gore kalori ayari yapilmali.";
            } else if (kopek && yasGrubu == "senior") {
                oneri = "Eklem sagligini destekleyen (glukozamin icerikli), dusuk kalorili senior kopek mamasi onerilir. Gunde 2 ogun, kilo kontrolu onemli.";
            } else {
                oneri = "Bu tur icin beslenme onerisi tanimli degil.";
            }

            // Kronik durum varsa ek uyari ekle
            QList<chroniccondition> conditions = chroniccondition::getByPet(petId);
            if (!conditions.isEmpty()) {
                oneri += "\n\nDikkat: Bu hayvanin kronik saglik durumu var (";
                for (int i = 0; i < conditions.size(); ++i) {
                    oneri += conditions[i].hastalik_adi;
                    if (i < conditions.size() - 1) {
                        oneri += ", ";
                    }
                }
                oneri += "). Beslenme programi veteriner kontrolunde ozellestirilmelidir.";
            }

            ui->labelBeslenmeOnerisi->setText(oneri);
        }

        void MainWindow::on_btnSahipSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetSahipler->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz sahibi listeden secin.");
                return;
            }

            int ownerId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu sahibi silmek istediginize emin misiniz? Bagli tum hayvanlar ve kayitlari (randevu, asi, tedavi, kronik durum) da silinecek.",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                QList<pet> bagliHayvanlar = pet::getByOwner(ownerId);

                for (const pet &p : bagliHayvanlar) {
                    QList<appointment> hayvanRandevulari = appointment::getByPet(p.id);
                    for (const appointment &a : hayvanRandevulari) {
                        appointment::remove(a.id);
                    }

                    QList<vaccine> hayvanAsilari = vaccine::getByPet(p.id);
                    for (const vaccine &v : hayvanAsilari) {
                        vaccine::remove(v.id);
                    }

                    QList<treatment> hayvanTedavileri = treatment::getByPet(p.id);
                    for (const treatment &t : hayvanTedavileri) {
                        treatment::remove(t.id);
                    }

                    QList<chroniccondition> hayvanKronikleri = chroniccondition::getByPet(p.id);
                    for (const chroniccondition &c : hayvanKronikleri) {
                        chroniccondition::remove(c.id);
                    }

                    pet::remove(p.id);
                }

                owner::remove(ownerId);

                ui->listWidgetSahipler->clear();
                QList<owner> owners = owner::getAll();
                for (const owner &o : owners) {
                    QListWidgetItem *item = new QListWidgetItem(o.ad + " - " + o.telefon + " - " + o.email);
                    item->setData(Qt::UserRole, o.id);
                    ui->listWidgetSahipler->addItem(item);
                }

                ui->comboBoxSahip->clear();
                for (const owner &o : owners) {
                    ui->comboBoxSahip->addItem(o.ad, o.id);
                }

                ui->comboBoxHayvan->clear();
                ui->comboBoxAsiHayvan->clear();
                ui->comboBoxTedaviHayvan->clear();
                ui->comboBoxKronikHayvan->clear();
                ui->comboBoxBeslenmeHayvan->clear();
                QList<pet> kalanHayvanlar = pet::getAll();
                for (const pet &p : kalanHayvanlar) {
                    ui->comboBoxHayvan->addItem(petComboLabel(p), p.id);
                    ui->comboBoxAsiHayvan->addItem(p.ad, p.id);
                    ui->comboBoxTedaviHayvan->addItem(p.ad, p.id);
                    ui->comboBoxKronikHayvan->addItem(p.ad, p.id);
                    ui->comboBoxBeslenmeHayvan->addItem(p.ad, p.id);
                }

                ui->listWidgetHayvanlar->clear();
                for (const pet &p : kalanHayvanlar) {
                    QListWidgetItem *item = new QListWidgetItem(p.ad + " (" + p.tur + ")");
                    item->setData(Qt::UserRole, p.id);
                    ui->listWidgetHayvanlar->addItem(item);
                }

                refreshVaccineList();
                refreshChronicList();
                refreshReminders();
            }
        }

        void MainWindow::on_btnHayvanSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetHayvanlar->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz hayvani listeden secin.");
                return;
            }

            int petId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu hayvani silmek istediginize emin misiniz? Bagli tum kayitlar (randevu, asi, tedavi, kronik durum) da silinecek.",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                QList<appointment> randevular = appointment::getByPet(petId);
                for (const appointment &a : randevular) {
                    appointment::remove(a.id);
                }

                QList<vaccine> asilar = vaccine::getByPet(petId);
                for (const vaccine &v : asilar) {
                    vaccine::remove(v.id);
                }

                QList<treatment> tedaviler = treatment::getByPet(petId);
                for (const treatment &t : tedaviler) {
                    treatment::remove(t.id);
                }

                QList<chroniccondition> kronikler = chroniccondition::getByPet(petId);
                for (const chroniccondition &c : kronikler) {
                    chroniccondition::remove(c.id);
                }

                pet::remove(petId);

                ui->listWidgetHayvanlar->clear();
                QList<pet> pets = pet::getAll();
                for (const pet &p : pets) {
                    owner sahibi = owner::getById(p.owner_id);
                    QString satir = p.ad + " - Sahip: " + sahibi.ad + " - Tür: " + p.tur + " - Irk: " + p.irk + " - Doğum: " + p.dogum_tarihi.toString("dd.MM.yyyy");
                    QListWidgetItem *item = new QListWidgetItem(satir);
                    item->setData(Qt::UserRole, p.id);
                    ui->listWidgetHayvanlar->addItem(item);
                }

                ui->comboBoxHayvan->clear();
                ui->comboBoxAsiHayvan->clear();
                ui->comboBoxTedaviHayvan->clear();
                ui->comboBoxKronikHayvan->clear();
                ui->comboBoxBeslenmeHayvan->clear();
                for (const pet &p : pets) {
                    ui->comboBoxHayvan->addItem(petComboLabel(p), p.id);
                    ui->comboBoxAsiHayvan->addItem(p.ad, p.id);
                    ui->comboBoxTedaviHayvan->addItem(p.ad, p.id);
                    ui->comboBoxKronikHayvan->addItem(p.ad, p.id);
                    ui->comboBoxBeslenmeHayvan->addItem(p.ad, p.id);
                }

                refreshVaccineList();
                refreshChronicList();
                refreshReminders();
            }
        }

        void MainWindow::on_btnRandevuSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetRandevu->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz randevuyu listeden secin.");
                return;
            }

            int appointmentId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu randevuyu silmek istediginize emin misiniz?",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                appointment::remove(appointmentId);

                ui->listWidgetRandevu->clear();
                QList<appointment> appointments = appointment::getAll();
                for (const appointment &a : appointments) {
                    pet ilgiliHayvan = pet::getById(a.pet_id);
                    QString satir = petFullLabel(ilgiliHayvan) + " - " + a.tarih_saat.toString("dd.MM.yyyy hh:mm") + " - " + a.durum;
                    QListWidgetItem *item = new QListWidgetItem(satir);
                    item->setData(Qt::UserRole, a.id);
                    ui->listWidgetRandevu->addItem(item);
                }
            }
        }




        void MainWindow::on_btnAsiSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetAsilar->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz asiyi listeden secin.");
                return;
            }

            int vaccineId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu asi kaydini silmek istediginize emin misiniz?",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                vaccine::remove(vaccineId);
                refreshVaccineList();
                refreshReminders();
            }
        }


        void MainWindow::on_btnTedaviSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetTedaviler->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz tedaviyi listeden secin.");
                return;
            }

            int treatmentId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu tedavi kaydini silmek istediginize emin misiniz?",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                treatment::remove(treatmentId);

                ui->listWidgetTedaviler->clear();
                QList<treatment> treatments = treatment::getAll();
                for (const treatment &t : treatments) {
                    pet ilgiliHayvan = pet::getById(t.pet_id);
                    QString satir = petFullLabel(ilgiliHayvan) + " - " + t.tani + " - " + t.ilac + " (" + t.baslangic_tarihi.toString("dd.MM.yyyy") + " - " + t.bitis_tarihi.toString("dd.MM.yyyy") + ")";
                    QListWidgetItem *item = new QListWidgetItem(satir);
                    item->setData(Qt::UserRole, t.id);
                    ui->listWidgetTedaviler->addItem(item);
                }
            }
        }



        void MainWindow::on_btnKronikSil_clicked()
        {
            QList<QListWidgetItem*> secilenler = ui->listWidgetKronikDurumlar->selectedItems();
            if (secilenler.isEmpty()) {
                QMessageBox::information(this, "Bilgi", "Lutfen silmek istediginiz kayidi listeden secin.");
                return;
            }

            int conditionId = secilenler.first()->data(Qt::UserRole).toInt();

            QMessageBox::StandardButton cevap = QMessageBox::question(this, "Onay",
                                                                      "Bu kronik durum kaydini silmek istediginize emin misiniz?",
                                                                      QMessageBox::Yes | QMessageBox::No);

            if (cevap == QMessageBox::Yes) {
                chroniccondition::remove(conditionId);
                refreshChronicList();
            }
        }


