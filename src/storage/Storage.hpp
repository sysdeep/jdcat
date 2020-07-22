#ifndef STORAGE_HPP
#define STORAGE_HPP
#include "./dbsqlite/Appdb.hpp"
#include "./dbsqlite/models.hpp"
#include "core/models/FileModel.hpp"
#include "core/models/VolumeModel.hpp"
#include "./StorageManifest.hpp"
#include "./Volume.hpp"
/**
 * @brief The Storage class - прокси к текущему типу базы данных
 */

class Storage
{
public:
    Storage();




	//--- new -----------------------------------------------------------------
	StorageManifest *manifest;
	QString path;

	bool create(const QString &path);
	bool open(const QString &path);
	bool save();

//	void create_volume(const QString &name);
//	void get_volume(const QString &name);
	VolumePtr open_volume(const QString &vol_id);
	//--- new -----------------------------------------------------------------


















//    QString file_name_path;
//	DBSystem db_system_info = std::make_shared<DBSystemModel>(DBSystemModel{});

    bool open_db(const QString &full_path);
    bool close_db();


//	QString get_db_version();

    Volumes get_volumes();
	VolumeModel get_volume(const QString &volume_id);
    Files get_volume_files(QString &volume_id);
    Files get_child_files(QString &parent_id);

	DBSystem get_db_system_info();


	bool create_volume(const VolumeModel &model);
	bool create_file(const FileModel &model);

	bool remove_volume(const QString &volume_id);
	bool update_volume(const VolumeModel &volume);



	void		start_transaction();
	void		end_transaction();

private:
    Appdb* __appdb;
//	void __read_db_system_info();




};

#endif // STORAGE_HPP
