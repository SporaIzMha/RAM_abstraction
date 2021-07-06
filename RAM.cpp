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


/// ����������� �� ��������� ��������������� ������ ������
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


/// ����������� � �����������, �������������� ��������� ������ �� ����������
/// \brief RAM::RAM
/// \param cBrand ������� �������� �������������
/// \param cModel ������� �������� ������
/// \param cVolume ������� �������� ������ ������
/// \param cFormFactor ������� �������� ���� �������
/// \param cType ������� �������� ����
/// \param cFrequency ������� �������� �������
/// \param cPrice ������� �������� ����

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

/// ����������� enum FormFactors � QString
/// \brief RAM::InfacetoS
/// \param value ������� �������� FormFactors
/// \return ����������� QString
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

/// ����������� QString � enum FormFactors
/// \brief RAM::StoInface
/// \param value ������� �������� QString
/// \return ����������� enum FormFactors

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

/// ����������� QString � enum Types
/// \brief RAM::StoType
/// \param value ������� �������� QString
/// \return ����������� enum Types

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

/// ����������� enum Types � QString
/// \brief RAM::TypetoS
/// \param value ������� �������� Types
/// \return ����������� QString

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
