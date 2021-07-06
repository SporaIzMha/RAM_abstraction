#ifndef EDITNOTEWINDOW_H
#define EDITNOTEWINDOW_H

#include <QDialog>
#include <QDebug>
#include "RAM.h"
namespace Ui {
class EditNoteWindow;
}

///
/// \brief The EditNoteWindow class
/// Класс окна редактирования
/// cодержит методы для редактирования существующих записей и добавления новых
///
class EditNoteWindow : public QDialog
{
    Q_OBJECT
signals:
    ///
    /// \brief sendDataFromEdit
    /// \param obj объект для передачи в основную форму
    /// Сигнал, отсылающий отредактированный объект обратно в основное окно
    void sendDataFromEdit(RAM obj);
public:
    explicit EditNoteWindow(QWidget *parent = nullptr);
    ~EditNoteWindow();

private:
    Ui::EditNoteWindow *ui;///<Указатель на объекты пользовательского интерфейса


public slots:
   void recieveDataToRedact(RAM temp);
private slots:
   void on_AcceptButton_clicked();
};

#endif // EDITNOTEWINDOW_H
