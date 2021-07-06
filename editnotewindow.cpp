#include "editnotewindow.h"
#include "ui_editnotewindow.h"

///
/// \brief EditNoteWindow::EditNoteWindow
/// \param parent ���������, ����� ������ ����� ������������ ��� ������� �������
/// ����������� �������������� ���������������� ���������
///
EditNoteWindow::EditNoteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNoteWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
    QPixmap bkgnd(":/fonovie/fon.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}
///
/// \brief EditNoteWindow::~EditNoteWindow
/// ���������� ������� ���������������� ����������
///
EditNoteWindow::~EditNoteWindow()
{
    delete ui;
}

///
/// \brief EditNoteWindow::recieveDataToRedact
/// \param temp ������, ���������� �� �������� ����
/// ���� ��������� ������ �� ��������� ����
/// �������� ������ � ���������� ��������� ������� � ��������������� ���� ��������������
///
void EditNoteWindow::recieveDataToRedact(RAM temp)
{

        ui->BrandLine->setText(temp.getBrand());//���������� ������ ������������� � ������ � LineEdit
        ui->ModelLine->setText(temp.getModel());
        ui->VolumeBox->setValue(temp.getVolume());//���������� ����� � SpinBox
        ui->FormFactorBox->setCurrentIndex(temp.getFormFactor());//������������� ������� enum�� � QComboBox��
        ui->TypeBox->setCurrentIndex(temp.getType());
        ui->FrequencyBox->setValue(temp.getFrequency());
        ui->PriceBox->setValue(temp.getPrice());

}

///
/// \brief EditNoteWindow::on_AcceptButton_clicked
/// ��� ������� �� ������ ������� �� ������, ���������� �� �����
/// ����������� ������ � ������������ � ������� ������� � ������� ���� ������ � ������ add
///
void EditNoteWindow::on_AcceptButton_clicked()
{
    RAM *temp = new RAM(ui->BrandLine->text(),//�������� ������� �� ����������� �����
                                ui->ModelLine->text(),
                                ui->VolumeBox->value(),
                                RAM::StoInface(ui->FormFactorBox->currentText()),
                                RAM::StoType(ui->TypeBox->currentText()),
                                ui->FrequencyBox->value(),
                                ui->PriceBox->value()
                                );

    emit sendDataFromEdit(*temp);//�������� ������ ������� � mainwindow ������ � ������ add
    this->close();//�������� �����
}
