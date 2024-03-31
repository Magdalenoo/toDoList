#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardPaths>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readFile();

    void writeFile();

private slots:

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_deleteAllButton_clicked();

private:

    //Smart pointer
    std::unique_ptr<Ui::MainWindow> ui;

    QString path;

};
#endif // MAINWINDOW_H
