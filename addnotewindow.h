#ifndef ADDNOTEWINDOW_H
#define ADDNOTEWINDOW_H

#include <QDialog>
#include <RAM.h>

namespace Ui {
class AddNoteWindow;
}

///
/// \brief The AddNoteWindow class
///����� ���� ����������. �������� ������ �������� ������ � ������� �����.

class AddNoteWindow : public QDialog
{
    Q_OBJECT
signals:
        void sendDataFromAdd(RAM obj);///<������ �������� ������ � ������� �����.
public:
    explicit AddNoteWindow(QWidget *parent = nullptr);
    ~AddNoteWindow();

private slots:
    void on_AcceptButton_clicked();

private:
    Ui::AddNoteWindow *ui;///<��������� �� �������� ����������������� ����������

};

#endif // ADDNOTEWINDOW_H
