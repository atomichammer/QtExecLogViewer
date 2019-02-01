#ifndef CSVREADER_H
#define CSVREADER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>


class QTextStream;

// ����� ������ ������� CSV-������
class CsvReader: public QObject
{
    Q_OBJECT

private:
    QFile _file;                        // ucxo���� CSV-�a��
    QChar _separator;                   // �����������, �� �������� ������������ �������� �� �������
    QList<QStringList> _lines_list;     // ������ ���������� � ���������� ������� CSV-�����

public:
    CsvReader(QObject *parent = 0, const QString& file_name = QString(""));
    ~CsvReader();
    void setFileName(const QString& name) { _file.setFileName(name); }  // ycma�o�ka ����� �����
    bool Open();                                                        // omkp�mue �����
    QList<QStringList> CSVRead();                                       // ������ �����
    void close() { if(isOpen()) _file.close(); }                        // �akp�mue �����
    bool isOpen() const { return _file.isOpen(); }                      // npo�epka �������� �����

};
#endif // CSVREADER_H
