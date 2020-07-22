#ifndef VOLUMEMODEL_HPP
#define VOLUMEMODEL_HPP
#include <QString>
#include <list>
#include <QDateTime>

class VolumeModel
{
public:
	VolumeModel();

    QString uuid;
	QString name;
	QString path;
	QString vtype;
	QString description;
    QDateTime created;
    QDateTime updated;
};


using Volumes = std::list<VolumeModel>;

#endif // VOLUMEMODEL_HPP
