#include "addnotewindow.h"
#include "ui_addnotewindow.h"

/// ����������� �������������� ���������, ������������� ������� ����.
/// \brief AddNoteWindow::AddNoteWindow
/// \param parent ��� ������������ ������

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

/// ���������� ������� ���������������� ����������
/// \brief AddNoteWindow::~AddNoteWindow
///
AddNoteWindow::~AddNoteWindow()
{
    delete ui;
}
/// ������� ������ �� �����, ��������� ������, ���������� ��� � ������� ����.
/// \brief AddNoteWindow::on_AcceptButton_clicked
///
void AddNoteWindow::on_AcceptButton_clicked()
{
    RAM *temp = new RAM(ui->BrandLine->text(),//�������� ������� �� ����������� �����
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
