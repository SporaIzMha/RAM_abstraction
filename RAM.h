#ifndef RAM_H
#define RAM_H

#include <QString>

///
/// \brief The RAM class
/// Класс оперативной памяти
/// содержит основные характеристики оперативной памяти, а так же методы для работы
///
class RAM
{
public:

    ///
    /// \brief The FormFactors enum
    /// Показывает, какой Форм фактор у оперативной памяти
    enum FormFactors
    {
        DIMM,
        SO_DIMM,
        RDIMM,
    };

    ///
    /// \brief The Types enum
    /// Показывает тип оперативной памяти
    enum Types
    {
        DDR,
        DDR2,
        DDR3,
        DDR4,
    };

private:
    int Id;///<ID оперативной памяти
    QString Brand;///<Производитель оперативной памяти
    QString Model;///<Модель оперативной памяти
    int Volume;///<Объём оперативной памяти
    FormFactors FormFactor;///<Форм фактор оперативной памяти
    Types Type;///<Тип оперативной памяти
    double Frequency;///<Частота оперативной памяти
    double Price;///<Цена оперативной памяти
public:
    RAM();
    RAM(const QString cBrand, const QString cModel, const int cVolume, const FormFactors cFormFactor, const Types cType, const double cFrequency, const double cPrice);
    QString getBrand() const;          ///<Гетер
    void setBrand(const QString &value);      ///<Сетер
    QString getModel() const;  ///<Гетер
    void setModel(const QString &value); ///<Сетер
    int getVolume() const;  ///<Гетер
    void setVolume(int value); ///<Сетер
    FormFactors getFormFactor() const;  ///<Гетер
    void setFormFactor(const FormFactors &value); ///<Сетер
    Types getType() const; ///<Гетер
    void setType(const Types &value); ///<Сетер
    double getFrequency() const;                 ///<Гетер
    void setFrequency(double value); ///<Сетер
    double getPrice() const;                ///<Гетер
    void setPrice(double value); ///<Сетер
    int getId() const;                ///<Гетер
    void setId(int value);   ///<Сетер
    static FormFactors StoInface (const QString value);
    static QString InfacetoS(const FormFactors value);
    static Types StoType(const QString value);
    static QString TypetoS(const Types value);
};

#endif // RAM_H
