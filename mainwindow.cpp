#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextEdit"

using namespace std;

/// Конструктор главного окна
/// инициализирует основные члены класса и задает начальные параметры объектам пользовательского интерфейса
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getSettings();//получение настроек из реестра


    //флаги для корректной работы перетаскивания
    ui->tableView->viewport()->setAcceptDrops(true);//Разрешает принимать Drop Eventы
    ui->tableView->setDragDropMode(QAbstractItemView::NoDragDrop);//Отключает встроенный DragNDrop
    ui->tableView->setSelectionMode(QTableWidget::SingleSelection);//Выделять только по 1 строке
    ui->tableView->setSelectionBehavior(QTableWidget::SelectRows);//Выделять строки
    ui->tableView->setDropIndicatorShown(true);//Показывать индикатор перетаскивания
    this->setAcceptDrops(1);//Разрешает принимать Dropы главному окну


    sp = new QLinkedList<RAM>;//выделение памяти под двусвязный список(хранит данные)
    ui->tableView->setSp(sp);//установка текущего списка в соответствие списку в таблице


    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(slotGo_to_Redact()));//Коннект нажатия на редактировать в основном меню
    //со слотом передачи данных в форму редактирования
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(slotWindow_Add()));//Коннект нажатия на добавить в основном меню со слотом добавления


    //создание объекта контекстного меню
    menu = new QMenu(this);

    //создание действий добавить и удалить
    QAction * editDevice = new QAction(tr("Edit"), this);
    QAction * deleteDevice = new QAction(tr("Remove"), this);

    //коннект нажатий на действия добавить и удалить соответствующим им слотам
    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotGo_to_Redact()));     // Для вызова диалога редактирования
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_actionDelete_triggered())); // Для удаления записи

    //добавление действий в контекстное меню
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);


    //установка начального языка русский
    on_actionRussian_triggered();
    TableUpdate();
}

///
/// \brief MainWindow::~MainWindow
/// Деструктор главного окна
/// Сохраняет настройки в реестр, затем удаляет интерфейс
MainWindow::~MainWindow()
{
    setSettings();
    delete ui;
}

/// Функция перестройки таблицы, так же содержит настройки остального интерфейса
/// \brief MainWindow::TableUpdate
/// \param find Переменная для функции поиска
void MainWindow::TableUpdate(QString *find)
{
    QLinkedList<RAM>::iterator iter;//указатель для проходки по списку
    QStringList Header;//Массив заголовков
    int count=0;//счетчик записей

    Header.push_back(tr("ID"));//заголовки
    Header.push_back(tr("Brand"));
    Header.push_back(tr("Model"));
    Header.push_back(tr("Volume"));
    Header.push_back(tr("Form Factor"));
    Header.push_back(tr("Type"));
    Header.push_back(tr("Frequency"));
    Header.push_back(tr("Price"));

    //Работа контекстного меню
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slotKontekstMenu(QPoint)));
    menu->actions().at(0)->setText(tr("Edit"));
    menu->actions().at(1)->setText(tr("Delete"));

    //создание модели данных для tableView, и одновременно работа функции поиска
    QStandardItemModel *model = new QStandardItemModel();//модель для таблицы
    QStandardItem *item;//Каждый item - ячейка в модели
    model->setHorizontalHeaderLabels(Header);//применить заголовки к модели
    QBrush brush(QColor(255, 128, 0));//цвет для поиска


    for (iter=sp->begin();iter!=sp->end();iter++)//формирование модели и поиск
    {

        iter->setId(count);//задаем id
        item = new QStandardItem(QString::number(iter->getId()));//записываем в ячейку id
        if(find!=nullptr)//в случае если мы что-то ищем
        {
            if(item->text()==*find)//если текст совпадает с текстом поиска
                item->setBackground(brush);//красим строку в оранжевый
        }
        model->setItem(count,0,item);//ставим этот item в модель

        item = new QStandardItem(iter->getBrand());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,1,item);

        item = new QStandardItem(iter->getModel());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,2,item);

        item = new QStandardItem(QString::number(iter->getVolume()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,3,item);

        item = new QStandardItem(RAM::InfacetoS(iter->getFormFactor()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,4,item);

        item = new QStandardItem(RAM::TypetoS(iter->getType()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,5,item);

        item = new QStandardItem(QString::number(iter->getFrequency()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,6,item);

        item = new QStandardItem(QString::number(iter->getPrice()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,7,item);

        count++;
    }

    ui->tableView->setModel(model);//устанавливаем модель в таблицу
    ui->tableView->resizeRowsToContents();//строки сжимаем до содержимого
    ui->tableView->hideColumn(0);//прячем первую колонну(id)
    ui->actionDelete->setEnabled(!sp->isEmpty());
    ui->actionEdit->setEnabled(!sp->isEmpty());
    ui->ResetButton->setEnabled(!sp->isEmpty());
    ui->lineEdit->setEnabled(!sp->isEmpty());
ui->SearchButton->setEnabled(!sp->isEmpty());
ui->actionSave->setEnabled(!sp->isEmpty());

}

//Основные функции
///
/// \brief MainWindow::on_actionOpen_triggered
/// Открытие файла
/// Вызывает QFileDialog, получает имя файла, открывает его на чтение
/// Читает и парсит строки, записывает их в двусвязный список
/// Далее перестраивает таблицу
void MainWindow::on_actionOpen_triggered()
{
    QString filename;//имя файла
    QStringList slist;//массив строк для разделения данных
    QString sline;//строка для построчного чтения из файла

    filename = QFileDialog::getOpenFileName(this,tr("Open"),":/file/RAM.db",tr("Image Files (*.db)"));
    if(filename.isEmpty())
        return;

    QFile file(filename);//создаем объект файла с таким именем
    file.open( QIODevice::ReadOnly | QIODevice::Text );//указывает что файл текстовый и открыт на чтение


    if(file.readLine().contains("ram"))//проверка файла на соответствие данной программе
        while(!file.atEnd())//до тех пор пока файл не закончится
        {
            sline=file.readLine();//передаём строку из файла
            slist=sline.split(';');//разделяем ее на массив строк по точкам с запятыми

            RAM *temp = new RAM(//создаем новый объект класса с помощью данных, полученных из файла
                                        slist.at(0),
                                        slist.at(1),
                                        slist.at(2).toInt(),
                                        RAM::StoInface(slist.at(3)),
                                        RAM::StoType(slist.at(4)),
                                        slist.at(5).toDouble(),
                                        slist.at(6).toDouble()
                                        );
            this->sp->push_back(*temp);//вставляем его в список
            free(temp);//освобождаем временную память
        }
    else
        QMessageBox::warning(this,tr("Warning"),"Wrong file");//если в файле неверный ключ выводим сообщение об ошибке
    TableUpdate();//перестраиваем таблицу после того как все прочитали
}
///
/// \brief MainWindow::on_actionSave_triggered
/// Сохраняет данные в файл
/// Вызывает QFileDialog, получает имя файла, открывает его на запись
/// Записывает данные в строки через ";" и пишет строки в файл
void MainWindow::on_actionSave_triggered()//сохранить файл
{
    QLinkedList<RAM>::iterator iter;//указатель(итератор) для движения по списку
    QString filename;//имя файла
    filename = QFileDialog::getOpenFileName(this);//открываем файл так же как в открытии
    QFile file(filename);//создаем объект файла
    QTextStream writeStream(&file);//аналог cout но для файла
    file.open(QIODevice::WriteOnly | QIODevice::Text);//файл открыт на запись и имеет текстовый тип
    int i=0;
    for(iter=sp->begin();iter!=sp->end();iter++,i++)//проходим по списку и тащим из каждого объекта данные
    {
        writeStream<<iter->getBrand(); writeStream<<";";//через точку с запятой данные записываются в файл
        writeStream<<iter->getModel(); writeStream<<";";
        writeStream<<QString::number(iter->getVolume()); writeStream<<";";
        writeStream<<RAM::InfacetoS(iter->getFormFactor()); writeStream<<";";
        writeStream<<RAM::TypetoS(iter->getType()); writeStream<<";";
        writeStream<<QString::number(iter->getFrequency()); writeStream<<";";
        writeStream<<QString::number(iter->getPrice()); writeStream<<";";
        if(iter!=--sp->end())//защита от лишней строки в конце файла
            writeStream<<"\n";
    }

    file.close();//закрытие файла


}
/// Слот отправки данных в форму редактирования.
/// Смотрит,какая из строк выделена, ищет в списке объект по его Id и отправляет его в форму редактирования, передавая ей управление.
/// \brief MainWindow::slotGo_to_Redact
void MainWindow::slotGo_to_Redact()//слот для отправки данных в EditWindow
{
    RAM *obj = new RAM();//объект
    QLinkedList<RAM>::iterator iter;//итератор для списка
    edit = new EditNoteWindow(this);//выделяем память под окно редактирования
    connect(this,SIGNAL(sendDataToEdit(RAM)),edit,SLOT(recieveDataToRedact(RAM)));//connect сигнала отправки данных в editnotewindow
    connect(edit,SIGNAL(sendDataFromEdit(RAM)),this,SLOT(slotGet_from_Redact(RAM)));//connect сигнала получения данных из editnotewindow
    for(iter=sp->begin();iter!=sp->end();iter++)//проходим по списку
        if(iter->getId()==ui->tableView->currentIndex().row())//если id в списке совпадает с номером текущей строки
            obj = &(*iter);//в obj записываются данные совпавшего объекта
    emit sendDataToEdit(*obj);//Объект отсылается в форму редактирования
    // если она вызвана без параметра, то по умолчанию идет редактирование
    edit->exec();//передача управления окну редактирования

}

/// Слот получения данных из формы редактирования.
/// В зависимости от значения add либо заменяет данные у существующей записи либо добавляет в список новую.
/// \brief MainWindow::slotGet_from_Redact
/// \param temp объет, полученный из формы редактирования
void MainWindow::slotGet_from_Redact(RAM temp)
{
    QLinkedList<RAM>::iterator iter;
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())//в противном случае ищем циклом элемент который редактировали и меняем данные в нем на полученные из формы
        {
            iter->setBrand(temp.getBrand());//данные меняются с помощью сетеров и гетеров
            iter->setModel(temp.getModel());
            iter->setVolume(temp.getVolume());
            iter->setFormFactor(temp.getFormFactor());
            iter->setType(temp.getType());
            iter->setFrequency(temp.getFrequency());
            iter->setPrice(temp.getPrice());
        }
    TableUpdate();//перестраиваем таблицу
}

/// Слот получения данных из формы добавления
/// \brief MainWindow::slotGet_from_Add
/// \param temp принятый объект из формы добавления
///
void MainWindow::slotGet_from_Add(RAM temp)
{
    sp->push_back(temp);
    TableUpdate();
}

/// Вызывает окно добавления
/// \brief MainWindow::slotWindow_Add
void MainWindow::slotWindow_Add()
{
    add = new AddNoteWindow(this);
    add->setAttribute(Qt::WA_DeleteOnClose);
    connect(add,SIGNAL(sendDataFromAdd(RAM)),this,SLOT(slotGet_from_Add(RAM)));
    add->exec();
}

///
/// \brief MainWindow::on_actionDelete_triggered
/// Функция удаления элемента из списка
void MainWindow::on_actionDelete_triggered()//удаление
{
    QLinkedList<RAM>::iterator iter;//итератор для движения по списку
    for(iter=sp->begin();iter!=sp->end();iter++)//двигаемся по списку от начала до конца
        if(iter->getId()==ui->tableView->currentIndex().row())//смотрим какой из элементов в таблице выделен и удаляем его из списка с помощью id
        {
            sp->erase(iter);//удаляет элемент из списка
        }
    TableUpdate();//перестраиваем таблицу
}


///
/// \brief MainWindow::on_actionRussian_triggered
/// Переводит программу на русский язык
void MainWindow::on_actionRussian_triggered()
{
    QPixmap bkgnd(":/fonovie/rus.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    translator.load(QString(":/Translations/ru.qm"));//загружаем в переводчик файл с переводом
    qApp->installTranslator(&translator);//ставим установщик
    ui->retranslateUi(this);//переводим интерфейс
    ui->actionEnglish->setChecked(false);
    TableUpdate();
}
///
/// \brief MainWindow::on_actionEnglish_triggered
/// Переводит программу на английский язык
void MainWindow::on_actionEnglish_triggered()
{
    QPixmap bkgnd(":/fonovie/eng.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    translator.load(QString(":/Translations/eng.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionRussian->setChecked(false);
    TableUpdate();
}

//работа Drag and Drop
///
/// \brief MainWindow::dragEnterEvent
/// \param e указатель на событие
/// Разрешает или запрещает перетаскивание в зависимости от того, есть ли в мышке данные
///
void MainWindow::dragEnterEvent(QDragEnterEvent *e) //событие входа drag в окно
{

    if(e->mimeData()->hasText())
        e->setAccepted(true);
    else
        e->setAccepted(false);
}
///
/// \brief MainWindow::dragLeaveEvent
/// \param e указатель на событие
/// Разрешает выход события drag из окна
void MainWindow::dragLeaveEvent(QDragLeaveEvent *e)//событие выхода drag из окна
{

    e->setAccepted(true);
}
///
/// \brief MainWindow::dropEvent
/// \param e указатель на событие
/// Если в событии отпускания мышки есть данные забираем их и записываем в список
void MainWindow::dropEvent(QDropEvent *e)
{
    QStringList slist;
    QString line;
    line = e->mimeData()->text();//пишем в line данные из перетаскивания
    slist = line.split(';');//разделяем line сплитом на составляющие
    if(slist.isEmpty())//если список пустой выходим из перетаскивания для предотвращения вылетов
        return;
    RAM *temp = new RAM(//создаем новый объект из полученных данных
                                slist.at(0),
                                slist.at(1),
                                slist.at(2).toInt(),
                                RAM::StoInface(slist.at(3)),
                                RAM::StoType(slist.at(4)),
                                slist.at(5).toDouble(),
                                slist.at(6).toDouble()
                                );
    temp->setId(this->sp->size());//ставим ему id по количеству элементов в списке
    this->sp->push_back(*temp);//записываем его в список
    TableUpdate();//перестраиваем таблицу
}


//работа сохранения/восстановления настроек(сохранение размеров окна)


///
/// \brief MainWindow::setSettings
/// Сохраняет геометрию окна в реестр
void MainWindow::setSettings()
{
    QSettings settings("Course","App");//Создаем объект QSettings
    settings.beginGroup("w");//Начинаем новую группу настроек
    settings.setValue("geometry", saveGeometry()); // сохраняется геометрия окна под ключом "geometry"
    settings.endGroup();//Закрываем группу настроек
}

///
/// \brief MainWindow::getSettings
/// Получает геометрию окна из реестра
void MainWindow::getSettings()
{
    QSettings settings("Course","App"); //Создаем объект QSettings
    settings.beginGroup( "w" );//Начинаем новую группу настроек
    restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray()); // восстанавление настроек геометрии окна по ключу "geometry"
    settings.endGroup();//Закрываем группу настроек
}


//слоты для работы меню, вызова окон итд...


/// Слот вызова контекстного меню
/// \brief MainWindow::slotKontekstMenu
/// \param pos позиция в окне, у которой вызовется меню
void MainWindow::slotKontekstMenu(QPoint pos)
{
    if(!sp->isEmpty())//если в списке есть данные
        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));//меню появляется возле мышки
}


///
/// \brief MainWindow::on_actionAbout_triggered
/// Показывает окно с информацией о программе
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("About"),"Программа разработана: Страчков Владимир Викторович\nИКГ: ИЭУИС 2-2.\nВариант: Автозаправка");
}


/// Функция поиска передает в TableUpdate строку поиска, а она уже светит найденные данные
/// \brief MainWindow::on_SearchButton_clicked
void MainWindow::on_SearchButton_clicked()
{
    QString *str = new QString(ui->lineEdit->text());//берем строку из line edit
    TableUpdate(str);//вызываем отрисовку таблицы, передав туда строку поиска
}


/// Кнопка сброса
/// Служит для сброса сортировки и поиска
/// \brief MainWindow::on_ResetButton_clicked
void MainWindow::on_ResetButton_clicked()
{
    ui->lineEdit->setText("");//очищаем строку поиска
    ui->tableView->clearSpans();//удаляем из таблицы все колонки и строки
    TableUpdate();//снова перестраиваем таблицу
}



/// Создает экземпляр такого же окна с флагом удаления при закрытии.
/// Служит для открытия нескольких файлов.
/// \brief MainWindow::on_actionNewWindow_triggered
void MainWindow::on_actionNewWindow_triggered()
{
    MainWindow *mainwindow = new MainWindow(this);//создание нового окна
    mainwindow->setAttribute(Qt::WA_DeleteOnClose);//окно будет удаляться после закрытия
    mainwindow->show();//показать окно
}





