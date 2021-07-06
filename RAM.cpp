#include "RAM.h"

QString RAM::getBrand() const
{
    return Brand;
}

void RAM::setBrand(const QString &value)
{
    Brand = value;
}

QString RAM::getModel() const
{
    return Model;
}

void RAM::setModel(const QString &value)
{
    Model = value;
}

int RAM::getVolume() const
{
    return Volume;
}

void RAM::setVolume(int value)
{
    Volume = value;
}

RAM::FormFactors RAM::getFormFactor() const
{
    return FormFactor;
}

void RAM::setFormFactor(const FormFactors &value)
{
    FormFactor = value;
}

RAM::Types RAM::getType() const
{
    return Type;
}

void RAM::setType(const Types &value)
{
    Type = value;
}

double RAM::getFrequency() const
{
    return Frequency;
}

void RAM::setFrequency(double value)
{
    Frequency = value;
}

double RAM::getPrice() const
{
    return Price;
}

void RAM::setPrice(double value)
{
    Price = value;
}

int RAM::getId() const
{
    return Id;
}

void RAM::setId(int value)
{
    Id = value;
}


/// Конструктор по умолчанию инициаилизирует пустой объект
/// \brief RAM::RAM
RAM::RAM():
    Brand("No name"),
    Model("Model"),
    Volume(4),
    FormFactor(DIMM),
    Type(DDR),
    Frequency(2400),
    Price(0)
{}


/// Конструктор с параметрами, инициализирует параметры класса по параметрам
/// \brief RAM::RAM
/// \param cBrand Входное значение производителя
/// \param cModel Входное значение модели
/// \param cVolume Входное значение объёма памяти
/// \param cFormFactor Входное значение форм фактора
/// \param cType Входное значение типа
/// \param cFrequency Входное значение частоты
/// \param cPrice Входное значение цены

RAM::RAM(const QString cBrand,
         const QString cModel,
         const int cVolume,
         const RAM::FormFactors cFormFactor, const RAM::Types cType,
         const double cFrequency,
         const double cPrice):
    Brand(cBrand),
    Model(cModel),
    Volume(cVolume),
    FormFactor(cFormFactor),
    Type(cType),
    Frequency(cFrequency),
    Price(cPrice)
{}

/// Преобразует enum FormFactors в QString
/// \brief RAM::InfacetoS
/// \param value Входное значение FormFactors
/// \return аналогичный QString
///

QString RAM::InfacetoS(const RAM::FormFactors value)
{
    switch (value)
    {
    case DIMM: return "DIMM";
    case SO_DIMM: return "SO_DIMM";
    case RDIMM: return "RDIMM";
    }
    return "DIMM";
}

/// Преобразует QString в enum FormFactors
/// \brief RAM::StoInface
/// \param value Входное значение QString
/// \return аналогичный enum FormFactors

RAM::FormFactors RAM::StoInface (const QString value)
{
    if(value == "DIMM")
        return DIMM;
    if(value == "SO_DIMM")
        return SO_DIMM;
    if(value == "RDIMM")
        return RDIMM;
    return DIMM;
}

/// Преобразует QString в enum Types
/// \brief RAM::StoType
/// \param value Входное значение QString
/// \return аналогичный enum Types

RAM::Types RAM::StoType (const QString value)
{
    if(value == "DDR")
        return DDR;
    if(value == "DDR2")
        return DDR2;
    if(value == "DDR3")
        return DDR3;
    if(value == "DDR4")
        return DDR4;
    return DDR;
}

/// Преобразует enum Types в QString
/// \brief RAM::TypetoS
/// \param value Входное значение Types
/// \return аналогичный QString

QString RAM::TypetoS(const Types value)
{
    switch (value)
    {
    case DDR: return "DDR";
    case DDR2 : return "DDR2";
    case DDR3 : return "DDR3";
    case DDR4 : return "DDR4";
    }
    return "DDR";
}
