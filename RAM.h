#ifndef RAM_H
#define RAM_H

#include <QString>

///
/// \brief The RAM class
/// ����� ����������� ������
/// �������� �������� �������������� ����������� ������, � ��� �� ������ ��� ������
///
class RAM
{
public:

    ///
    /// \brief The FormFactors enum
    /// ����������, ����� ���� ������ � ����������� ������
    enum FormFactors
    {
        DIMM,
        SO_DIMM,
        RDIMM,
    };

    ///
    /// \brief The Types enum
    /// ���������� ��� ����������� ������
    enum Types
    {
        DDR,
        DDR2,
        DDR3,
        DDR4,
    };

private:
    int Id;///<ID ����������� ������
    QString Brand;///<������������� ����������� ������
    QString Model;///<������ ����������� ������
    int Volume;///<����� ����������� ������
    FormFactors FormFactor;///<���� ������ ����������� ������
    Types Type;///<��� ����������� ������
    double Frequency;///<������� ����������� ������
    double Price;///<���� ����������� ������
public:
    RAM();
    RAM(const QString cBrand, const QString cModel, const int cVolume, const FormFactors cFormFactor, const Types cType, const double cFrequency, const double cPrice);
    QString getBrand() const;          ///<�����
    void setBrand(const QString &value);      ///<�����
    QString getModel() const;  ///<�����
    void setModel(const QString &value); ///<�����
    int getVolume() const;  ///<�����
    void setVolume(int value); ///<�����
    FormFactors getFormFactor() const;  ///<�����
    void setFormFactor(const FormFactors &value); ///<�����
    Types getType() const; ///<�����
    void setType(const Types &value); ///<�����
    double getFrequency() const;                 ///<�����
    void setFrequency(double value); ///<�����
    double getPrice() const;                ///<�����
    void setPrice(double value); ///<�����
    int getId() const;                ///<�����
    void setId(int value);   ///<�����
    static FormFactors StoInface (const QString value);
    static QString InfacetoS(const FormFactors value);
    static Types StoType(const QString value);
    static QString TypetoS(const Types value);
};

#endif // RAM_H
