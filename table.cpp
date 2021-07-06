#include "table.h"

/// Конструктор разрешает данному виджету принимать данные
/// \brief Table::Table
/// \param parent указывает родительский объект
Table::Table(QWidget *parent)
    : QTableView (parent)
{
    this->acceptDrops();
}

/// Сетер для указателя на список из главного окна
/// \brief Table::setSp
/// \param temp принимает на вход указатель на двусвязный список
void Table::setSp(QLinkedList<RAM> *temp)
{
    sp = temp;//ставим в соответствие список из основного окна списку данного класса
}

///
/// \brief Table::mousePressEvent
/// \param event событие нажатия
/// Переопределееное событие нажатия на кнопку мыши
/// При нажатии любой из клавиш запоминает позицию и записывает ее в 2 разных класса
/// Требуется для выполнения некоторых проверок и минимизации шанса вылета программы
void Table::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)//если нажали на любую кнопку мыши
    {
        this->selectRow(this->indexAt(event->pos()).row());//выделяем строку под курсором
        nowsel = new QItemSelection(this->currentIndex(),this->currentIndex());//запоминаем, что выделили
    }
      index = this->indexAt(event->pos());//ставим индекс в соответствие позиции нажатия
}


/// Переопределенное событие движения мыши
/// После выполнения проверок записывает содержимое выделенной строки в mimeData Drag EventА
/// \brief Table::mouseMoveEvent
/// \param event

void Table::mouseMoveEvent(QMouseEvent *event)
{
    QLinkedList<RAM>::iterator iter;//итератор для списка
    if(nowsel == nullptr)//если ничего не выделено
        return;//завершаем метод
    if(!sp->isEmpty())//если список не пуст
        if(nowsel->indexes().first().row()>=0 && (event->buttons() & Qt::LeftButton) && index.isValid())
        {
            //если id выделенной строки больше или равно 0 и нажата левая кнопка и index существует
            QDrag *drag = new QDrag(this);//создаем новое событие перетаскивания
            QMimeData *mimeData = new QMimeData();
            QString str;

            for(iter=sp->begin();iter!=sp->end();iter++)//проходим по списку
                if(iter->getId()==this->currentIndex().row())//ищем объект с ID, совпадающим с номером выделенной строки
                {
                    str =   iter->getBrand() + ";"+//записываем его данные в str
                            iter->getModel() + ";"+
                            QString::number(iter->getVolume()) + ";"+
                            RAM::InfacetoS(iter->getFormFactor()) + ";"+
                            RAM::TypetoS(iter->getType()) + ";"+
                            QString::number(iter->getFrequency()) + ";"+
                            QString::number(iter->getPrice())+";";
                }

            mimeData->setText(str);//str записываем в mimeData
            mimeData->setParent(this);
            drag->setMimeData(mimeData);//mimeData записываем в drag
            drag->exec();//передаем управление событию перетаскивания
            return;
        }
}

