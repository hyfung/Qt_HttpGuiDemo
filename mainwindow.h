#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNetworkRequestFinished();

    void on_pushButton_get_clicked();

    void on_pushButton_post_clicked();

    void on_pushButton_put_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* pNetworkAccessManager_;
    QNetworkReply* pReply_;
    QStandardItemModel* model_;
    bool isAccessingNetwork_ = false;
};
#endif // MAINWINDOW_H
