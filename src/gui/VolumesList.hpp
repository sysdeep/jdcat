#ifndef VOLUMESLIST_H
#define VOLUMESLIST_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QList>
#include "core/models/VolumeModel.hpp"
#include "storage/StorageManifestVolume.hpp"




class VolumesList : public QWidget
{
    Q_OBJECT
public:
    explicit VolumesList(QWidget *parent = nullptr);

	void				set_volumes(const QList<StorageManifestVolume> *volumes_list);
	void				update_volume(const VolumeModel &volume);
	QString				get_current_volume_id();

private:
	QListWidget			*__list;

	QString				__current_volume_id;				// тек. том

private slots:
	void __on_volume_selected(QListWidgetItem *);
	void __on_remove_volume();
	void __on_edit_volume();

signals:
	void volume_selected(QString);
	void volume_edit(QString);
};

#endif // VOLUMESLIST_H
