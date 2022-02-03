#include "HRegExpManager.h"

static HRegExpManager * m_pHRegExpManager = nullptr;
HRegExpManager *HRegExpManager::getInstance()
{
    if(m_pHRegExpManager)
    {
        return m_pHRegExpManager;
    }
    else {
        m_pHRegExpManager = new HRegExpManager;
        return m_pHRegExpManager;
    }
}

HRegExpManager::HRegExpManager()
{

}

QRegExpValidator * HRegExpManager::getNoNegIntegerValidator()
{
    return new QRegExpValidator(QRegExp("^\\d+$"));
}

QRegExpValidator * HRegExpManager::getPosIntegerValidator()
{
    return  new QRegExpValidator(QRegExp("^[0-9]*[1-9][0-9]*$"));
}

QRegExpValidator * HRegExpManager::getNoPosIntegerValidator()
{
   return new QRegExpValidator(QRegExp("^-[0-9]*[1-9][0-9]*$"));
}

QRegExpValidator * HRegExpManager::getrIntegerValidator()
{
    return new QRegExpValidator(QRegExp("^-?\\d+$"));
}

QRegExpValidator * HRegExpManager::getNoNegFloatValidator()
{
    return new QRegExpValidator(QRegExp("^\\d+(\\.\\d+)?$"));
}

QRegExpValidator * HRegExpManager::getPosFloatValidator()
{
    return new QRegExpValidator(QRegExp("^(([0-9]+\\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\\.[0-9]+)|([0-9]*[1-9][0-9]*))$"));
}

QRegExpValidator * HRegExpManager::getNoPosFloatValidator()
{
    return new QRegExpValidator(QRegExp("^((-\\d+(\\.\\d+)?)|(0+(\\.0+)?))$"));
}

QRegExpValidator * HRegExpManager::getNegFloatValidator()
{
    return new QRegExpValidator(QRegExp("^(-(([0-9]+\\.[0-9]*[1-9][0-9]*)|([0-9]*[1-9][0-9]*\\.[0-9]+)|([0-9]*[1-9][0-9]*)))$"));
}

QRegExpValidator * HRegExpManager::getFloatValidator()
{
    return new QRegExpValidator(QRegExp("^(-?\\d+)(\\.\\d+)?$"));
}

QRegExpValidator * HRegExpManager::getCharacterStringValidator()
{
    return new QRegExpValidator(QRegExp("^[A-Za-z]+$"));
}

QRegExpValidator * HRegExpManager::getUpCharacterStringValidator()
{
    return new QRegExpValidator(QRegExp("^[A-Z]+$"));
}

QRegExpValidator * HRegExpManager::getNumberAndWordStrValidator()
{
    return new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$"));
}

QRegExpValidator * HRegExpManager::getNumberWordUnderLineValidator()
{
    return new QRegExpValidator(QRegExp("^\\w+$"));
}

QRegExpValidator * HRegExpManager::getEmailAddrValidator()
{
    return new QRegExpValidator(QRegExp("^[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)+$"));
}

QRegExpValidator * HRegExpManager::getUrlValidator()
{
    return new QRegExpValidator(QRegExp("^[a-zA-z]+://(\\w+(-\\w+)*)(\\.(\\w+(-\\w+)*))*(\?\\S*)?$"));
}

QRegExpValidator * HRegExpManager::getYearMonthDayValidator()
{
//    return new QRegExpValidator(QRegExp("^(d{2}|d{4})-((0([1-9]{1}))|(1[1|2]))-(([0-2]([1-9]{1}))|(3[0|1]))$"));
    return new QRegExpValidator(QRegExp("^([0-9]{2}|[0-9]{4})-((0([1-9]{1}))|(1[1|2]))-(([0-2]([1-9]{1}))|(3[0|1]))$"));
}

QRegExpValidator * HRegExpManager::getMonthDayYearValidator()
{
    return new QRegExpValidator(QRegExp("^((0([1-9]{1}))|(1[1|2]))/(([0-2]([1-9]{1}))|(3[0|1]))/(d{2}|d{4})$"));
}

QRegExpValidator * HRegExpManager::getEmailValidator()
{
    return new QRegExpValidator(QRegExp("([w-.]+)@(([[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.)|(([w-]+.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(]?)$"));
}

QRegExpValidator * HRegExpManager::getCellPhoneNumberValidator()
{
     return new QRegExpValidator(QRegExp("(d+-)?(d{4}-?d{7}|d{3}-?d{8}|^d{7,8})(-d+)?"));
}

QRegExpValidator * HRegExpManager::getIpAddressValidator()
{
    return new QRegExpValidator(QRegExp("^(d{1,2}|1dd|2[0-4]d|25[0-5]).(d{1,2}|1dd|2[0-4]d|25[0-5]).(d{1,2}|1dd|2[0-4]d|25[0-5]).(d{1,2}|1dd|2[0-4]d|25[0-5])$"));
}

QRegExpValidator * HRegExpManager::getMacAddressValidator()
{
    return new QRegExpValidator(QRegExp("^([0-9A-F]{2})(-[0-9A-F]{2}){5}$"));
}

QRegExpValidator * HRegExpManager::getValueTypeValidator()
{
    return new QRegExpValidator(QRegExp("^[-+]?\\d+(\\.\\d+)?$"));
}
