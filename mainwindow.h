#pragma once
#include <QMainWindow>
#include <QLinkedList>
#include <fstream>
#include <sstream>
#include <QFile>
#include<QFileDialog>
#include <QList>
#include <QTranslator>
#include <QLocale>
#include <QtDebug>
#include <QTextStream>
#include <QSettings>
#include "RAM.h"
#include "editnotewindow.h"
#include "table.h"
#include "addnotewindow.h"

namespace Ui
{

class MainWindow;
}

///
/// \brief The MainWindow class
/// ����� ��������� ����
/// �������� �������� ������� � ������ ��� ������ ���������
/// � ��� �� ������ ������ ��������� �� ����� �� ������
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    ///
    /// \brief sendDataToEdit
    /// \param obj ������, ������������ � ����� ��������������
    /// ������ �������� ������ � ����� ��������������
    void sendDataToEdit(RAM obj);


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TableUpdate(QString *find=nullptr);


private slots:
    void on_actionOpen_triggered();

    void slotWindow_Add();

    void on_actionDelete_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void slotGo_to_Redact();

    void slotKontekstMenu(QPoint pos);

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionNewWindow_triggered();

    void on_SearchButton_clicked();

    void setSettings();

    void getSettings();

    void on_ResetButton_clicked();

private:

    Ui::MainWindow *ui;///<��������� �� �������� ����������������� ����������(�����, ��� ��������� � ������������ ����)
    QLinkedList<RAM> *sp;///<���������� ������, �������� ������
    EditNoteWindow *edit;///<���� ��������������
    AddNoteWindow *add;///<���� ����������
    QTranslator translator;///<����������
    QMenu *menu;///<����������� ����

public slots:
    void slotGet_from_Redact(RAM temp);
    void slotGet_from_Add(RAM temp);
protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dropEvent(QDropEvent *e);
};
