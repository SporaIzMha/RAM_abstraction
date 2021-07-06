#include "table.h"

/// ����������� ��������� ������� ������� ��������� ������
/// \brief Table::Table
/// \param parent ��������� ������������ ������
Table::Table(QWidget *parent)
    : QTableView (parent)
{
    this->acceptDrops();
}

/// ����� ��� ��������� �� ������ �� �������� ����
/// \brief Table::setSp
/// \param temp ��������� �� ���� ��������� �� ���������� ������
void Table::setSp(QLinkedList<RAM> *temp)
{
    sp = temp;//������ � ������������ ������ �� ��������� ���� ������ ������� ������
}

///
/// \brief Table::mousePressEvent
/// \param event ������� �������
/// ���������������� ������� ������� �� ������ ����
/// ��� ������� ����� �� ������ ���������� ������� � ���������� �� � 2 ������ ������
/// ��������� ��� ���������� ��������� �������� � ����������� ����� ������ ���������
void Table::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)//���� ������ �� ����� ������ ����
    {
        this->selectRow(this->indexAt(event->pos()).row());//�������� ������ ��� ��������
        nowsel = new QItemSelection(this->currentIndex(),this->currentIndex());//����������, ��� ��������
    }
      index = this->indexAt(event->pos());//������ ������ � ������������ ������� �������
}


/// ���������������� ������� �������� ����
/// ����� ���������� �������� ���������� ���������� ���������� ������ � mimeData Drag Event�
/// \brief Table::mouseMoveEvent
/// \param event

void Table::mouseMoveEvent(QMouseEvent *event)
{
    QLinkedList<RAM>::iterator iter;//�������� ��� ������
    if(nowsel == nullptr)//���� ������ �� ��������
        return;//��������� �����
    if(!sp->isEmpty())//���� ������ �� ����
        if(nowsel->indexes().first().row()>=0 && (event->buttons() & Qt::LeftButton) && index.isValid())
        {
            //���� id ���������� ������ ������ ��� ����� 0 � ������ ����� ������ � index ����������
            QDrag *drag = new QDrag(this);//������� ����� ������� ��������������
            QMimeData *mimeData = new QMimeData();
            QString str;

            for(iter=sp->begin();iter!=sp->end();iter++)//�������� �� ������
                if(iter->getId()==this->currentIndex().row())//���� ������ � ID, ����������� � ������� ���������� ������
                {
                    str =   iter->getBrand() + ";"+//���������� ��� ������ � str
                            iter->getModel() + ";"+
                            QString::number(iter->getVolume()) + ";"+
                            RAM::InfacetoS(iter->getFormFactor()) + ";"+
                            RAM::TypetoS(iter->getType()) + ";"+
                            QString::number(iter->getFrequency()) + ";"+
                            QString::number(iter->getPrice())+";";
                }

            mimeData->setText(str);//str ���������� � mimeData
            mimeData->setParent(this);
            drag->setMimeData(mimeData);//mimeData ���������� � drag
            drag->exec();//�������� ���������� ������� ��������������
            return;
        }
}

