#pragma once
#ifndef HREGEXPMANAGER_H
#define HREGEXPMANAGER_H

#include <QRegExp>
#include <QRegularExpression>
#include <QRegExpValidator>

class HRegExpManager
{
public:
    static HRegExpManager * getInstance();

    /**
     * @brief 非负整数
     */
    QRegExpValidator * getNoNegIntegerValidator();

    /**
     * @brief 获得正整数
     */
    QRegExpValidator * getPosIntegerValidator();

    /**
     * @brief 非正整数
     */
    QRegExpValidator * getNoPosIntegerValidator();

    /**
     * @brief 整数
     */
    QRegExpValidator * getrIntegerValidator();

    /**
     * @brief 非负浮点数
     */
    QRegExpValidator * getNoNegFloatValidator();

    /**
     * @brief 正浮点数
     */
    QRegExpValidator * getPosFloatValidator();

    /**
     * @brief 非正浮点数
     */
    QRegExpValidator * getNoPosFloatValidator();

    /**
     * @brief 负浮点数
     */
    QRegExpValidator * getNegFloatValidator();

    /**
     * @brief 浮点数
     */
    QRegExpValidator * getFloatValidator();

    /**
     * @brief 英文字符串
     */
    QRegExpValidator * getCharacterStringValidator();

    /**
     * @brief 大写英文字符串
     */
    QRegExpValidator * getUpCharacterStringValidator();

    /**
     * @brief 小写英文字符串
     */
    QRegExpValidator * getSmallCharacterStringValidator();

    /**
     * @brief 数字英文
     */
    QRegExpValidator * getNumberAndWordStrValidator();

    /**
     * @brief 数字、英文字母、下划线 组成的字符串
     */
    QRegExpValidator * getNumberWordUnderLineValidator();

    /**
     * @brief email地址
     */
    QRegExpValidator * getEmailAddrValidator();

    /**
     * @brief url
     */
    QRegExpValidator * getUrlValidator();

    /**
     * @brief 年-月-日
     */
    QRegExpValidator * getYearMonthDayValidator();

    /**
     * @brief 月/日/年
     */
    QRegExpValidator * getMonthDayYearValidator();

    /**
     * @brief Email
     */
    QRegExpValidator * getEmailValidator();
    /**
     * @brief 电话号码
     */
    QRegExpValidator * getCellPhoneNumberValidator();

    /**
     * @brief IP地址
     */
    QRegExpValidator * getIpAddressValidator();

    /**
     * @brief MAC地址
     */
    QRegExpValidator * getMacAddressValidator();

    /**
     * @brief 值类型
     */
    QRegExpValidator * getValueTypeValidator();


private:
    HRegExpManager();
};

#endif // HREGEXPMANAGER_H
