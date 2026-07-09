#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "database.h"
#include "owner.h"
#include "pet.h"
#include "vet.h"
#include "appointment.h"
#include "vaccine.h"
#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnSahipEkle_clicked();

    void on_btnHayvanEkle_clicked();

    void on_btnRandevuEkle_clicked();

    void on_btnAsiEkle_clicked();

    void on_btnAsiProgramiOlustur_clicked();

    void refreshReminders();

private:
    Ui::MainWindow *ui;
    void refreshVaccineList();
};
#endif // MAINWINDOW_H
