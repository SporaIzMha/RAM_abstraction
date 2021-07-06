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
/// Класс основного окна
/// содержит основные объекты и методы для работы программы
/// а так же хранит данные программы во время ее работы
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    ///
    /// \brief sendDataToEdit
    /// \param obj Объект, передающийся в форму редактирования
    /// Сигнал передачи данных в форму редактирования
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

    Ui::MainWindow *ui;///<Указатель на элементы пользовательского интерфейса(всего, что находится в конструкторе окна)
    QLinkedList<RAM> *sp;///<Двусвязный список, хранящий данные
    EditNoteWindow *edit;///<Окно редактирования
    AddNoteWindow *add;///<Окно добавления
    QTranslator translator;///<Переводчик
    QMenu *menu;///<Контекстное меню

public slots:
    void slotGet_from_Redact(RAM temp);
    void slotGet_from_Add(RAM temp);
protected:
    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dropEvent(QDropEvent *e);
};
