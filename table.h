#ifndef TABLE1_H
#define TABLE1_H

#include <QObject>
#include <QtWidgets>
#include "RAM.h"
///
/// \brief The Table class
/// ����� ������� ���������� �� QTableView � ����� ���������������� ������� ������� � �������� �����
/// � ������� ��� ����������� ���������������� ���������� DragNDrop ��� �������������� ���������� � ����� ���������,
/// � ��� �� �������� ������ ������ ���� ������ ���������
///
class Table : public QTableView
{
    Q_OBJECT
public:
    Table(QWidget * parent = nullptr);
    void setSp(QLinkedList<RAM> *temp);

private slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QLinkedList<RAM> *sp;///<��������� �� ������ ������ �� �������� ����, ��������� ��� ����� �������� ������� � ������
    QItemSelection *nowsel=nullptr;///<��������� �� ������� ���������� �������
    QModelIndex index;///<����������, ����� ������ ��� �������
};

#endif // TABLE1_H
