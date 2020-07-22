/*
 *
 * {
 *		"version"	: 1,
 *		"description"	: "super db",
 *		"created"		: datetime,
 *		"updated"		: datetime,
 *
 *		"volumes": [
			{
				"name": "vol1",
				"id": "volid",
				"icon": 1,
			}
		]
 * }
 */
#ifndef STORAGEMANIFEST_HPP
#define STORAGEMANIFEST_HPP
#include <QString>
#include <QDir>
#include <QDate>
#include <QJsonDocument>
#include <QList>

#include "./StorageManifestVolume.hpp"



class StorageManifest
{
public:
	StorageManifest(const QString &ipath);



	//--- data
	int version = 0;
	QString description = "";
	QDate created;
	QDate updated;
	QList<StorageManifestVolume> volumes;
	//--- data



	QString path;



	bool write();
	bool read();

	void print();

//	static void read_file(const QString &path);
//	static void write_file(const QString &path);

//	static QString file_name = "manifest";

private:
	void __from_json(const QJsonDocument &doc);
	QJsonDocument __to_json();
};

#endif // STORAGEMANIFEST_HPP
