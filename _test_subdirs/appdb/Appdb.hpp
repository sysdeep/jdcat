#ifndef APPDB_HPP
#define APPDB_HPP

#include "appdb_global.hpp"
#include "QString"
//#include "QSql"
#include "QSqlDatabase"
#include "models.hpp"

class APPDBSHARED_EXPORT Appdb
{

public:
	Appdb();

	QString file_name_path;
	DBSystem db_system_info;

	bool open_db(const QString full_path);
	QString get_db_version();

private:
	QSqlDatabase __db;
	void __read_db_system_info();


};

#endif // APPDB_HPP
