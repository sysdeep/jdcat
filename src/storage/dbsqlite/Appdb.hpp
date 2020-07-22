#ifndef APPDB_HPP
#define APPDB_HPP


#include "QString"
//#include "QSql"
#include "QSqlDatabase"
#include "models.hpp"
#include "core/models/VolumeModel.hpp"
#include "core/models/FileModel.hpp"

class Appdb
{

public:
	Appdb();

	QString		file_name_path;
	DBSystem	db_system_info = std::make_shared<DBSystemModel>(DBSystemModel{});

	bool		open_db(const QString full_path);
	bool		close_db();
	bool		is_opened = false;


	QString		get_db_version();

	Volumes		get_volumes();
	VolumeModel	get_volume(const QString &volume_id);
	Files		get_volume_files(QString &volume_id);
	Files		get_child_files(QString &parent_id);


	bool		create_volume_record(const VolumeModel &model);
	bool		create_file_record(const FileModel &model);


	bool		remove_volume_record(const QString &volume_id);
	bool		remove_volume_files(const QString &volume_id);
	bool		update_volume_record(const VolumeModel &model);




	void		start_transaction();
	void		end_transaction();

private:
	QSqlDatabase __db;
	void __read_db_system_info();


};



#endif // APPDB_HPP
