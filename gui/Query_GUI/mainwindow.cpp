#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    // Get the SQL command from the text input field
    QString sqlCommand = ui->lineEdit->text();

    // Create a QSqlQuery object and set it to the SQL command
    QSqlQuery query;
    query.setForwardOnly(true);
    query.prepare(sqlCommand);

    // Execute the query
    if (query.exec()) {
        // Iterate over the results of the query
        while (query.next()) {
            // Print the results to the text output field
            ui->textEdit->append(query.value(0).toString());
        }
    }
}



