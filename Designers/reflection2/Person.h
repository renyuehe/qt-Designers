#pragma once
#include "Animal.h"
class Person	: public Animal
{
	Q_OBJECT
public:
    Q_INVOKABLE Person();
	~Person();
    Q_INVOKABLE void setName(QString name);
	QString name() const;

public:
	static int typeId;
private:
	QString m_name;// = "my name is Person";
};
