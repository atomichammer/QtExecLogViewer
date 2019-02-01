#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    void loadCSVFile(QString &filename);
    QList<QStringList> str;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;

};

#endif // MAINWINDOW_H
