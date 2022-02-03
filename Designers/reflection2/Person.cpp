#include "Person.h"
int Person::typeId = qRegisterMetaType<Person*>();
Person::Person()
{

}
Person::~Person()
{

}

void Person::setName(QString name)
{
	this->m_name = name;
}

QString Person::name() const
{
	return m_name;
	//return "";
}