#ifndef ADDNOTEWINDOW_H
#define ADDNOTEWINDOW_H

#include <QDialog>
#include <RAM.h>

namespace Ui {
class AddNoteWindow;
}

///
/// \brief The AddNoteWindow class
///Класс окна добавления. Содержит сигнал отправки данных в главную форму.

class AddNoteWindow : public QDialog
{
    Q_OBJECT
signals:
        void sendDataFromAdd(RAM obj);///<сигнал отправки данных в главную форму.
public:
    explicit AddNoteWindow(QWidget *parent = nullptr);
    ~AddNoteWindow();

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::AddNoteWindow *ui;///<указатель на элементы пользовательского интерфейса

};

#endif // ADDNOTEWINDOW_H
