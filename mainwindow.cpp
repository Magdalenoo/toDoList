#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(std::make_unique<Ui::MainWindow>())
    , path(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\toDoFile.txt")
{
    ui->setupUi(this);

    readFile();
}

MainWindow::~MainWindow()
{
    writeFile();
}

//Reading file in which tasks were saved
void MainWindow::readFile()
{
    QFile file(path);

    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error", file.errorString());

        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);

        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

//Writing tasks to file
void MainWindow::writeFile()
{
    QFile file(path);

    if (!file.open(QIODevice::ReadWrite))
    {
        QMessageBox::critical(this, "Error", file.errorString());

        return;
    }

    QTextStream out(&file);

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        out << ui->listWidget->item(i)->text() << "\n";
    }

    file.close();
}

void MainWindow::on_addButton_clicked()
{
    QString userInput = ui->userText->text().trimmed();

    if (userInput.isEmpty() || userInput.trimmed().isEmpty())
    {
        QMessageBox msgWarning;

        msgWarning.setText("Task cannot be empty.\nEnter the task name.");

        msgWarning.setIcon(QMessageBox::Critical);

        msgWarning.setWindowTitle("Caution");

        msgWarning.exec();
    }

    QListWidgetItem* item = new QListWidgetItem(ui->userText->text(), ui->listWidget);

    ui->listWidget->addItem(item);

    item->setFlags(item->flags() | Qt::ItemIsEditable);

    ui->userText->clear();

    ui->userText->setFocus();
}


void MainWindow::on_deleteButton_clicked()
{
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());

    delete item;
}


void MainWindow::on_deleteAllButton_clicked()
{
    //Confirmation of deletion all tasks
    QMessageBox::StandardButton reply;

    reply = QMessageBox::critical(this, "Confirm Deletion", "Are you sure you want to delete all tasks?",
                                  QMessageBox::Yes|QMessageBox::No);


    if(reply == QMessageBox::No)
    {
        return;
    }

    //Confirmed, list widget and file can be cleared
    ui->listWidget->clear();

    QFile file(path);

    //Clearing the contents of the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::critical(this, "Error", file.errorString());

        return;
    }

    file.close();
}

