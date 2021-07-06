#include "editnotewindow.h"
#include "ui_editnotewindow.h"

///
/// \brief EditNoteWindow::EditNoteWindow
/// \param parent указывает, какой объект будет родительским для данного объекта
/// Конструктор инициализирует пользовательский интерфейс
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
/// Деструктор удаляет пользовательский интерефейс
///
EditNoteWindow::~EditNoteWindow()
{
    delete ui;
}

///
/// \brief EditNoteWindow::recieveDataToRedact
/// \param temp объект, полученный из главного окна
/// Слот получения данных из основного окна
/// Получает данные и записывает параметры объекта в соответствующие поля редактирования
///
void EditNoteWindow::recieveDataToRedact(RAM temp)
{

        ui->BrandLine->setText(temp.getBrand());//записывает строки производителя и модели в LineEdit
        ui->ModelLine->setText(temp.getModel());
        ui->VolumeBox->setValue(temp.getVolume());//записывает числа в SpinBox
        ui->FormFactorBox->setCurrentIndex(temp.getFormFactor());//Устанавливает индексы enumов в QComboBoxах
        ui->TypeBox->setCurrentIndex(temp.getType());
        ui->FrequencyBox->setValue(temp.getFrequency());
        ui->PriceBox->setValue(temp.getPrice());

}

///
/// \brief EditNoteWindow::on_AcceptButton_clicked
/// При нажатии на кнопку принять из данных, полученных из полей
/// формируется объект и отправляется с помощью сигнала в главное окно вместе с флагом add
///
void EditNoteWindow::on_AcceptButton_clicked()
{
    RAM *temp = new RAM(ui->BrandLine->text(),//создание объекта из содержимого полей
                                ui->ModelLine->text(),
                                ui->VolumeBox->value(),
                                RAM::StoInface(ui->FormFactorBox->currentText()),
                                RAM::StoType(ui->TypeBox->currentText()),
                                ui->FrequencyBox->value(),
                                ui->PriceBox->value()
                                );

    emit sendDataFromEdit(*temp);//отсылаем данные обратно в mainwindow вместе с ключом add
    this->close();//закрытие формы
}
