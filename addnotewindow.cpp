#include "addnotewindow.h"
#include "ui_addnotewindow.h"

/// Конструктор инициализирует параметры, устанавливает фоновый цвет.
/// \brief AddNoteWindow::AddNoteWindow
/// \param parent это родительский объект

AddNoteWindow::AddNoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNoteWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd(":/fonovie/fon.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

/// Деструктор удаляет пользовательский интерефейс
/// \brief AddNoteWindow::~AddNoteWindow
///
AddNoteWindow::~AddNoteWindow()
{
    delete ui;
}
/// Передаёт данные из строк, формирует объект, отправляет его в главное окно.
/// \brief AddNoteWindow::on_AcceptButton_clicked
///
void AddNoteWindow::on_AcceptButton_clicked()
{
    RAM *temp = new RAM(ui->BrandLine->text(),//создание объекта из содержимого полей
                                ui->ModelLine->text(),
                                ui->VolumeBox->value(),
                                RAM::StoInface(ui->FormFactorBox->currentText()),
                                RAM::StoType(ui->TypeBox->currentText()),
                                ui->FrequencyBox->value(),
                                ui->PriceBox->value()
                                );
    emit sendDataFromAdd(*temp);
    this->close();
}
