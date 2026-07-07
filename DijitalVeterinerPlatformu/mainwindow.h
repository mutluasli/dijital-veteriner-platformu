#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "pet.h"
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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
