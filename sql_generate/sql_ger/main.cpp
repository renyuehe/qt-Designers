#include <QCoreApplication>
#include <QFile>
#include <QTextCodec>
#include "sqlgenerator.h"
#include "SqlStr.h"


////
//QString GetCorrectUnicode(const QByteArray &ba)
//{
//    QTextCodec::ConverterState state;
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QString text = codec->toUnicode(ba.constData(), ba.size(), &state);
//    if (state.invalidChars > 0)
//    {
//        text = QTextCodec::codecForName("GBK")->toUnicode(ba);
//    }
//    else
//    {
//        text = ba;
//    }
//    return text;
//}

//打开文件
bool loadFile(const QString &fileName)
{
    QFile file(fileName); //新建QFile对象
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug() << "打开失败";
        return false ;//只读方式打开文件,出错提示,返回false
    }
    //QTextStream in(&file);//新建文本流对象
//    QApplication::setOverrideCursor(Qt::WaitCursor);
    //>>.读取文件
    QByteArray  text=file.readAll();
    //>>.转换编码
//    QString texts = GetCorrectUnicode(text);
     //qDebug() << texts;
    //>>.设置在文本框里面
//    qDebug() << texts;
    qDebug() << text;
    //设置当前文件

    //鼠标指针变回来
//    QApplication::restoreOverrideCursor();
    file.close();
    return true;
}

#if 1
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    bool result;


//    qDebug() << __LINE__ << QSqlDatabase::drivers();

    /***********************************************/


    /***********************************************/
//    DB_Operation * db = new DB_Operation(QStringLiteral("sqlite"));
//    qDebug() << __LINE__ << db->openDB(QStringLiteral("C:/Users/Administrator/Desktop/test_DB_Operation/四川指标宏业专用标准.hzm"));
//    qDebug() << __LINE__ << db->openDB(QStringLiteral("localhost"), 3306,"test", "root","");
//    QList<QMap<QString, QVariant>> table = db->getMappedObjs("select * from student");
//    qDebug() << __LINE__ << table;

//    if(db->isOpen())
//        qDebug() << QStringLiteral("打开数据库成功 ") << __LINE__;
//    else
//        qDebug() << QStringLiteral("打开数据库失败 ") << __LINE__;

//    qDebug() << __LINE__ << DB_Operation::selectGerner("ZbDict",QString("*"));
//    float f = 333.333;
//    qDebug() << __LINE__ << DB_Operation::selectGerner("ZbDict", true);
//    qDebug() << __LINE__ << DB_Operation::selectGerner("ZbDict", 111);
//    qDebug() << __LINE__ << DB_Operation::selectGerner("ZbDict", 111.333);
//    qDebug() << __LINE__ << DB_Operation::selectGerner("ZbDict", 111.333, "id", QString("DictName"));

//    qDebug() << __LINE__ << SqlGenerator::selectGerner("ZbDict", 111.333, "id", QString("DictName"));

    /******************************************************/

    qDebug() << __LINE__ << SqlStr().select("ZbDict", "*").where(("id=1"));
    qDebug() << __LINE__ << SqlStr().select("ZbDict", 111.333, "id", QString("111"), 222, 333, 444).where("id=1","DictName='工程专业'");

    /******************************************************/



//    qDebug() << __LINE__ << DB_Operation::whereGerner(("id=1"),("DictName='工程专业'"));
//    QString se = DB_Operation::selectGerner("ZbDict","*");
//    QString we = DB_Operation::whereGerner("id=1",("DictName='工程专业'"));

//    qDebug() << __LINE__ << DB_Operation::updateGerner("ZbDict","Id=2");
//    QString up = DB_Operation::updateGerner("ZbDict","Id=5");

//    qDebug() << __LINE__ << DB_Operation::deleteGener("ZbDict");

//    qDebug() << __LINE__ << DB_Operation::insertGernerDirect("ZbDict","id=2");

//    qDebug() << __LINE__ << DB_Operation::insertGernerWithField("ZbDict",QStringList() << "id" << "DictName" , QStringList() << "55" << "无物" );


//    qDebug() << se+we;
//    QList<QMap<QString, QVariant>> table = db->getMappedObjs(se);
//    for(auto row : table){
//        QMap<QString, QVariant>::iterator iter = row.begin();
//        while(iter != row.end()){
//            qDebug() << __LINE__ << iter.value().toString();
//            iter++;
//        }
//    }

//    qDebug() << up+we;
//    db->excuteSQL(up+we);



//    QSqlQuery qry(*db->m_pDB);
//    qry.exec("select * from testFieldTypeTable");
//    QStringList fieldList = db->getFieldList(&qry);
//    for(auto iter:fieldList)
//    {
//        qDebug() << __LINE__ << iter;
//    }

//    QList<QPair<QVariant::Type, QString>> typeNameList = db->getFieldTypeNameList(&qry);
//    for(auto iter:typeNameList)
//    {
//        qDebug() << __LINE__ << iter;
//    }

    //读字段和字段类型
//    QSqlQuery qry(*db->m_pDB);
//    qry.exec("select * from testFieldTypeTable");
//    qDebug() << __LINE__ << qry.isActive();
//    qDebug() << __LINE__ << qry.record().count();
//    for(int i = 0; i<qry.record().count(); ++i){
//        qDebug() << __LINE__ << qry.record().field(i).name() << qry.record().field(i).type();
//    }
//    qry.record().field(1).type();


    //读全部
//    QList<QMap<QString, QVariant>> table = db->getMappedObjs("select * from testFieldTypeTable");
//    qDebug() << table;

    //获得行游标
//    void * query = db->openRecordsetBySql(QStringLiteral("select * from testFieldTypeTable"));

//    QSqlQuery * qry = static_cast<QSqlQuery *>(query);
//    qDebug() << __LINE__ << qry->isValid();
//    qDebug() << __LINE__ << qry->next();
//    qDebug() << __LINE__ << qry->isValid();
//    qDebug() << __LINE__ << qry->isActive();

    {//读
//        //游标+字段：锁定值
//        QString resultStr;
//        qDebug() << __LINE__ << db->readFieldsValueFromRec(query, "DictName", resultStr);
//        qDebug() << __LINE__ << resultStr;
//        qDebug() << endl;

//        //游标+字段：锁定值和更多值
//        QSqlQuery *pQry = static_cast<QSqlQuery *>(query);
//        QString str1;
//        QString str2;
//        qDebug() << __LINE__ << db->readFieldsValueFromRec(query, "DictName", resultStr, str1, str2);
//        qDebug() << __LINE__ << resultStr << str1 << str2;;
//        qDebug() << endl;

//        //游标+字段：锁定列值(相对或绝对)
//        QList<QString> strList;
//        db->readFieldsValueFromRec(query, "DictName", strList, false);
//        for(auto iter:strList)
//        {
//            qDebug() << __LINE__ << iter;
//        }
//        qDebug() << endl;
    }


    {//写
//        QString TTT = "TTT";
//        QString Arg1 = "arg1";
//        QString Arg2 = "art1Value";
//        QString Arg3 = "arg3";

//        qDebug() << __LINE__ << db->addFieldsValueToTbl("testFieldTypeTable", "textTitle", "text", "intTitle", "123" , "realTitle", "22.2", "blobTitle", "blob");

//        QString aaa = "100";
//        double d = 111.11;
//        QByteArray b = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//        qDebug() << __LINE__ << db->addFieldsValueToTbl("testFieldTypeTable", "textTitle", "text", "intTitle", aaa , "realTitle", d, "blobTitle", b);

    //    qDebug() << __LINE__ << db->updateTblFieldsValue(QString("ZbDict"), QString("Id='idValue'"),QString("Id"),QString("updateContaint"), QString("DictName"), QString("updateDictName"));
    }

//    void closeDB();

    return a.exec();
}

#else

int main(int argc, char * argv[])
{
    QCoreApplication a(argc, argv);

//    if(loadFile(QStringLiteral("C:/Users/Administrator/Desktop/test_DB_Operation/四川指标宏业专用标准.hzm")))
//        qDebug() << "文件打开成功";

//    if(loadFile(QStringLiteral("C:/Users/Administrator/Desktop/test_DB_Operation/文件gb2312.txt")))
//        qDebug() << "文件打开成功";

    if(loadFile(QStringLiteral("C:/Users/Administrator/Desktop/test_DB_Operation/文件big5.txt")))
        qDebug() << "文件打开成功";

//    if(loadFile(QStringLiteral("C:/Users/Administrator/Desktop/test_DB_Operation/文件utf8.txt")))
//        qDebug() << "文件打开成功";

    return a.exec();
}

#endif
