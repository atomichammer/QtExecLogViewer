#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDateTime>
#include <QDebug>
#include "csvreader.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename;

    QString path;
    path = "";
    filename = QFileDialog::getOpenFileName(this, tr("Select Log File"),
                path,
                tr("Data (*.%1)").arg("csv"));

    if (!filename.isEmpty())
    {
        loadCSVFile(filename);
    }
}

void MainWindow::loadCSVFile(QString &filename)
{

    if (!filename.isEmpty())
    {
        CsvReader *csv = new CsvReader(0,filename); //
        if (csv->Open())
        {
            str = csv->CSVRead();
            model = new QStandardItemModel();
            QStandardItem *item;
            QStandardItem *parentItem;
            QList<QStandardItem*> list;
            QList<QStandardItem*> listFound;
            QDateTime timestamp;
            for(int i = 0; i < str.length(); i++)
            {
                listFound = model->findItems(str.at(i).at(0));
                if(listFound.length() > 0)
                {
                    parentItem = listFound.at(0);
                }
                else
                {
                    parentItem = new QStandardItem(str.at(i).at(0));
                }
                //convert unix timestamps to human readable format
                uint startTime = str.at(i).at(1).left(10).toUInt();
                uint stopTime = str.at(i).at(2).left(10).toUInt();
                uint duration = stopTime - startTime;
                timestamp.setTime_t(startTime);
                item = new QStandardItem(timestamp.toString(Qt::SystemLocaleShortDate));
                list << item;
                timestamp.setTime_t(stopTime);
                item = new QStandardItem(timestamp.toString(Qt::SystemLocaleShortDate));
                list << item;
                item = new QStandardItem(QTime(0,0,0,0).addSecs(duration).toString());
                list << item;
                parentItem->appendRow(list);
                //if its a new parent item
                if(listFound.length() == 0)
                    model->appendRow(parentItem);
                list.clear();
            }
            ui->listView->setModel(model);
            proxyModel = new QSortFilterProxyModel();
            proxyModel->setSourceModel(model);
            ui->tableView->setModel(model);
            model->setHorizontalHeaderLabels(QStringList() << "Start time" << "Stop Time" << "Duration");
            connect(ui->listView, SIGNAL(clicked(QModelIndex)),ui->tableView, SLOT(setRootIndex(QModelIndex)));
        }
    }
}
