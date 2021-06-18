#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onNetworkRequestFinished()
{
    isAccessingNetwork_ = false;
    QString sHeaders;
    QByteArray rep = pReply_->readAll();
    model_->clear();

    for (auto &pair : pReply_->rawHeaderPairs())
    {
        QList<QString> row;
        QStandardItem* item = 0;
        sHeaders += pair.first;
        sHeaders += ":";
        sHeaders += pair.second;
        sHeaders += "\n";

    }

    ui->textBrowser_responseHeader->setText(sHeaders);
    ui->textBrowser_responseBody->setText(rep);
    pReply_->deleteLater();
    //    ui->tableView_headers->insertRow(0);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pNetworkAccessManager_ = new QNetworkAccessManager();
    model_ = new QStandardItemModel();
    QStringList labels = QObject::trUtf8("Key,Value").simplified().split(",");
    model_->setHorizontalHeaderLabels(labels);
    //    ui->tableView_headers->setShowGrid(true);
    //    ui->tableView_headers->setModel(model_);
    //    ui->tableView_headers->show();
    ui->lineEdit_url->setText("http://localhost:8000");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_get_clicked()
{
    if(isAccessingNetwork_)
        return;
    isAccessingNetwork_ = true;
    QUrl url = ui->lineEdit_url->text();
    QNetworkRequest request = QNetworkRequest(url);
    pReply_ = pNetworkAccessManager_->get(request);
    connect(pReply_, SIGNAL(finished()), this, SLOT(onNetworkRequestFinished()));
}

void MainWindow::on_pushButton_post_clicked()
{
    if(isAccessingNetwork_)
        return;
    isAccessingNetwork_ = true;
    QUrl url = ui->lineEdit_url->text();
    QNetworkRequest request = QNetworkRequest(url);
//    request.setRawHeader();
    pReply_ = pNetworkAccessManager_->post(request, ui->plainTextEdit_requestBody->toPlainText().toUtf8());
    connect(pReply_, SIGNAL(finished()), this, SLOT(onNetworkRequestFinished()));
}

void MainWindow::on_pushButton_put_clicked()
{
    QMessageBox::warning(this, this->windowTitle(), "Method not implemented");
}

void MainWindow::on_pushButton_delete_clicked()
{
    QMessageBox::warning(this, this->windowTitle(), "Method not implemented");
}
