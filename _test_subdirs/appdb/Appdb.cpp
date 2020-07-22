#include "Appdb.hpp"
#include "QDebug"
#include "QSqlQuery"

Appdb::Appdb()
{
	this->__db = QSqlDatabase::addDatabase("QSQLITE");
}

bool Appdb::open_db(const QString full_path)
{
	qDebug() << "openning db: " << full_path;
	file_name_path = full_path;

	this->__db.setDatabaseName(this->file_name_path);
//	this->__db.setDatabaseName("tst.db");
	bool result = this->__db.open();

	if(result){
		this->__read_db_system_info();
		return true;
	}else{
		qDebug() << "error openning db...";

//		qDebug() << this->__db.lastError();
		return false;
	}
}

QString Appdb::get_db_version()
{

	return this->db_system_info.version;
//	QSqlQuery query;
//	query.exec("SELECT value FROM system WHERE key='version'");
////	query.exec("SELECT * FROM system");

//	while (query.next()){
////		int id = query.value(0).toInt();
////		QString key = query.value(1).toString();
////		QString value = query.value(2).toString();
////		qDebug() << id << key << value;
//////		QString version = query.value(0).toString();
//////		qDebug() << version;
//////	QString name = query.value(1).toString();
//////	QString age = query.value(2).toString();
//////	ui->textEdit->insertPlainText(_id+" "+name+" "+age+"\n");
//	}

//	qDebug() << "end selection";

//	return QString("10101");

}

void Appdb::__read_db_system_info()
{
	QSqlQuery query;
//	query.exec("SELECT value FROM system WHERE key='version'");
	query.exec("SELECT * FROM system");

	while (query.next()){
//		int id = query.value(0).toInt();
		QString key = query.value(1).toString();
		QString value = query.value(2).toString();

		if(key == QString("version")){
			this->db_system_info.version = value;
		}
//		qDebug() << id << key << value;
////		QString version = query.value(0).toString();
////		qDebug() << version;
////	QString name = query.value(1).toString();
////	QString age = query.value(2).toString();
////	ui->textEdit->insertPlainText(_id+" "+name+" "+age+"\n");
	}

//	qDebug() << "end selection";

//	return QString("10101");

}
