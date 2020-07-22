#include "Appdb.hpp"
#include "QDebug"
#include "QSqlQuery"
#include <QDateTime>

Appdb::Appdb()
{
	this->__db = QSqlDatabase::addDatabase("QSQLITE");

}

bool Appdb::open_db(const QString full_path)
{
	db_system_info->path = full_path;
	qDebug() << "openning db: " << full_path;
	file_name_path = full_path;

	this->__db.setDatabaseName(this->file_name_path);
//	this->__db.setDatabaseName("tst.db");
	bool result = this->__db.open();

	if(result){
		this->is_opened = true;
		this->__read_db_system_info();

		return true;
	}else{
		qDebug() << "error openning db...";

//		qDebug() << this->__db.lastError();
		return false;
    }
}

bool Appdb::close_db(){
	this->is_opened = false;
	this->__db.close();
	return true;
}

QString Appdb::get_db_version()
{

	return this->db_system_info->version;
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

Volumes Appdb::get_volumes(){
	QSqlQuery query;
	query.exec("SELECT uuid, name, path, vtype, description, created, updated FROM volumes");

	Volumes result;

	while (query.next()){
	//		int id = query.value(0).toInt();
		auto volume = VolumeModel();
		volume.uuid = query.value(0).toString();
		volume.name = query.value(1).toString();
		volume.path = query.value(2).toString();
		volume.vtype = query.value(3).toString();
		volume.description = query.value(4).toString();

        volume.created = query.value(5).toDateTime();
        volume.updated = query.value(6).toDateTime();

		result.emplace_back(volume);
	}

	return result;
}


/**
 * @brief Appdb::get_volume
 * @param volume_id
 * @return
 */
VolumeModel Appdb::get_volume(const QString &volume_id){
	VolumeModel result;

	auto sql = QString(R"""(
				   SELECT uuid, name, path, vtype, description, created, updated
				   FROM volumes WHERE uuid='%1';
				   )""").arg(volume_id).simplified();

	QSqlQuery query;
	query.exec(sql);

	if(query.first()){
		result.uuid = query.value(0).toString();
		result.name = query.value(1).toString();
		result.path = query.value(2).toString();
		result.vtype = query.value(3).toString();
		result.description = query.value(4).toString();

        result.created = query.value(5).toDateTime();
        result.updated = query.value(6).toDateTime();

	}

	return result;
}



/**
 * @brief Appdb::get_volume_files
 * @param volume_id
 * @return
 */
Files Appdb::get_volume_files(QString &volume_id){
	Files result;


	auto sql = QString(R"""(
					   SELECT uuid, parent_id, volume_id, name, type, rights, sowner, sgroup, size, ctime, atime, mtime, category, description
					   FROM files WHERE volume_id='%1' AND parent_id='0';
					   )""").arg(volume_id).simplified();

	qDebug() << sql;

	QSqlQuery query;
	query.exec(sql);


	while (query.next()){
	//		int id = query.value(0).toInt();
		auto file_model = FileModel();
		file_model.uuid = query.value(0).toString();
		file_model.parent_id = query.value(1).toString();
		file_model.volume_id = query.value(2).toString();
		file_model.name = query.value(3).toString();
		file_model.ftype = query.value(4).toInt();

		result.emplace_back(file_model);
	}

//	GET_VOLUME_ROOT_FILES = """
//		SELECT uuid, parent_id, volume_id, name, type, rights, sowner, sgroup, size, ctime, atime, mtime, category, description
//			FROM files WHERE volume_id=? AND parent_id='0';
//	"""

	return result;
}

Files Appdb::get_child_files(QString &parent_id){
	Files result;

	auto sql = QString(R"""(
					   SELECT uuid, parent_id, volume_id, name, type, rights, sowner, sgroup, size, ctime, atime, mtime, category, description
					   FROM files WHERE parent_id='%1';
					   )""").arg(parent_id).simplified();

	qDebug() << sql;

	QSqlQuery query;
	query.exec(sql);


	while (query.next()){
	//		int id = query.value(0).toInt();
		auto file_model = FileModel();
		file_model.uuid = query.value(0).toString();
		file_model.parent_id = query.value(1).toString();
		file_model.volume_id = query.value(2).toString();
		file_model.name = query.value(3).toString();
		file_model.ftype = query.value(4).toInt();

		file_model.size = query.value(8).toUInt();

		result.emplace_back(file_model);
	}

//	GET_VOLUME_ROOT_FILES = """
//		SELECT uuid, parent_id, volume_id, name, type, rights, sowner, sgroup, size, ctime, atime, mtime, category, description
//			FROM files WHERE volume_id=? AND parent_id='0';
//	"""

	return result;
}



/**
 * @brief Appdb::create_volume_record
 * @param model
 * @return
 */
bool Appdb::create_volume_record(const VolumeModel &model){

	auto sql = QString(R"""(
					   INSERT INTO
                       volumes(uuid, name, path, vtype, description, created, updated)
                       VALUES('%1', '%2', '%3', '%4', '%5', datetime('now', 'localtime'), datetime('now', 'localtime'));
                       )""").arg(model.uuid, model.name, model.path, model.vtype, model.description).simplified();

	QSqlQuery query;
	bool result = query.exec(sql);

	return result;
}

bool Appdb::create_file_record(const FileModel &model){
//	auto sql = QString(R"""(
//					   INSERT INTO
//					   files(volume_id, parent_id, uuid, name, type,
//							rights, sowner, sgroup, size, ctime, atime, mtime, category, description)
//					   VALUES('%1', '%2', '%3', '%4', '%5',
//					   %6, %7, %8, %9, %10, %11, %12, '%13', '%14');
//					   )""").arg(
//							model.volume_id, model.parent_id, model.uuid, model.name, model.ftype,
//							11111, 1000, 1000, 1000, 2000, 2000, 2000, "", "desc").simplified();

	auto sql = QString(R"""(
					   INSERT INTO
					   files(volume_id, parent_id, uuid, name, type,
							rights, sowner, sgroup, size, ctime, atime, mtime, category, description)
					   VALUES('%1', '%2', '%3', '%4', '%5',
					   %6, %7, %8, %9, %10, %11, %12, '%13', '%14');
					   )""").arg(model.volume_id)
							.arg(model.parent_id)
							.arg(model.uuid)
							.arg(model.name)
							.arg(model.ftype)
							.arg(11111)
							.arg(1000)
							.arg(1000)
							.arg(model.size)
							.arg(2000)
							.arg(2000)
							.arg(2000)
							.arg("", "desc").simplified();

//	QSqlQuery query;
//		query.prepare("INSERT INTO employee (id, name, salary) "
//					  "VALUES (:id, :name, :salary)");
//		query.bindValue(":id", 1001);
//		query.bindValue(":name", "Thad Beaumont");
//		query.bindValue(":salary", 65000);
//		query.exec();

//	QSqlQuery query;
//	  query.prepare("INSERT INTO employee (id, name, salary) "
//					"VALUES (?, ?, ?)");
//	  query.addBindValue(1001);
//	  query.addBindValue("Thad Beaumont");
//	  query.addBindValue(65000);
//	  query.exec();



//	INSERT INTO
//			files(volume_id, parent_id, uuid, name, type, rights, sowner, sgroup, size, ctime, atime, mtime, category, description)
//			VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?);

//	qDebug() << sql;
//	bool result = true;
	QSqlQuery query;
	bool result = query.exec(sql);
//	qDebug() << "create file result: " << result;
	return result;
}

/**
 * @brief Appdb::remove_volume_record
 * @param volume_id
 * @return
 */
bool Appdb::remove_volume_record(const QString &volume_id){

	auto sql = QString(R"""(
					   DELETE FROM volumes WHERE uuid='%1';
					   )""").arg(volume_id).simplified();

	QSqlQuery query;
	bool result = query.exec(sql);
	return result;

}

/**
 * @brief Appdb::remove_volume_files
 * @param volume_id
 * @return
 */
bool Appdb::remove_volume_files(const QString &volume_id){
	auto sql = QString(R"""(
					   DELETE FROM files WHERE volume_id='%1';
					   )""").arg(volume_id).simplified();

	QSqlQuery query;
	bool result = query.exec(sql);
	return result;

}


/**
 * @brief Appdb::update_volume_record
 * @param model
 * @return
 */
bool Appdb::update_volume_record(const VolumeModel &model){
	auto sql = QString(R"""(
					   UPDATE volumes
                       SET name='%1', vtype='%2', description='%3', updated=datetime('now', 'localtime')
					   WHERE uuid='%4';
					   )""").arg(model.name, model.vtype, model.description, model.uuid).simplified();

	qDebug() << sql;

	QSqlQuery query;
	bool result = query.exec(sql);
	return result;


}

void Appdb::start_transaction(){
	QSqlDatabase::database().transaction();
}

void Appdb::end_transaction(){
	QSqlDatabase::database().commit();
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
			this->db_system_info->version = value;
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
