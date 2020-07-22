#ifndef STORAGEMANIFESTVOLUME_HPP
#define STORAGEMANIFESTVOLUME_HPP
#include <QString>
#include <QJsonObject>

class StorageManifestVolume
{
public:
	StorageManifestVolume();


	//--- model
	QString name = "";
	QString id = "";
	int icon = 0;


	void from_json(const QJsonObject &data);
	QJsonObject to_json();


	void print();

};

#endif // STORAGEMANIFESTVOLUME_HPP
