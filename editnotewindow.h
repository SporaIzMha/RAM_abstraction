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
/// ����� ���� ��������������
/// c������� ������ ��� �������������� ������������ ������� � ���������� �����
///
class EditNoteWindow : public QDialog
{
    Q_OBJECT
signals:
    ///
    /// \brief sendDataFromEdit
    /// \param obj ������ ��� �������� � �������� �����
    /// ������, ���������� ����������������� ������ ������� � �������� ����
    void sendDataFromEdit(RAM obj);
public:
    explicit EditNoteWindow(QWidget *parent = nullptr);
    ~EditNoteWindow();

private:
    Ui::EditNoteWindow *ui;///<��������� �� ������� ����������������� ����������


public slots:
   void recieveDataToRedact(RAM temp);
private slots:
   void on_AcceptButton_clicked();
};

#endif // EDITNOTEWINDOW_H
