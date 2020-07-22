#ifndef USETTINGS_HPP
#define USETTINGS_HPP
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QStringList>


struct SettingsModel{
	QString version = "0.1";
	int max_last_bases = 20;
	bool open_last = true;
	QStringList lastbases = {};
};



class USettings{
public:
	USettings(const QString dirname, const QString filename);

	QString			dir_name = ".dcat";				// config file place
	QString			file_name = "settings.json";	// config file name

	SettingsModel	data;							// config data


	bool			read();							// read config from file
	bool			save();							// write config to file


	bool			last_database_exists();			// check if databases
	QString			get_last_database();			// get last
    bool            add_database(const QString& db_path);  // добавить базу в историю


private:
	QString			__expand_file_path();
	bool			__read_json(const QJsonObject &json);
	QJsonObject		__write_json();

    bool            __init_path();					// init path on settings is not exeists


};

#endif // USETTINGS_HPP
