#include <qdebug.h>
#include <QElapsedTimer>
#include <QMenu>
#include "VolumesList.hpp"
#include "lib/constants.hpp"

VolumesList::VolumesList(QWidget *parent) : QWidget(parent)
{
    this->setMaximumWidth(200);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->__list = new QListWidget();

    main_layout->addWidget(__list);



    __list->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(__list, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(__on_volumes_cmenu(QPoint)));
	connect(__list, &QListWidget::customContextMenuRequested, [this](const QPoint &pos){
		qDebug() << pos.x();
		//	// Handle global position
		QPoint globalPos = this->mapToGlobal(pos);

		// Create menu and insert some actions
		QMenu myMenu;
		myMenu.addAction("Remove", this, SLOT(__on_remove_volume()));
		myMenu.addAction("Edit", this, SLOT(__on_edit_volume()));
	//	myMenu.addAction("Erase",  this, SLOT(eraseItem()));

		// Show context menu at handling position
		myMenu.exec(globalPos);
    });




		this->connect(__list, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(__on_volume_selected(QListWidgetItem *)));
	////	this->connect(ui->volumes_list, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(__on_volume_selected(QListWidgetItem *)));

}


/**
 * @brief VolumesList::set_volumes
 * @param volumes_list
 * png - 3ms
 *	svg - 26ms
 */
void VolumesList::set_volumes(const QList<StorageManifestVolume> *volumes_list){
		QElapsedTimer timer;
		timer.start();

		__list->clear();

		for(auto &volume : *volumes_list){

//			QString icon_rc;
//			if(VolumeIconsMap.contains(volume.vtype)){
//				icon_rc = VolumeIconsMap[volume.vtype];
//			}else{
//				icon_rc = VolumeIconsMap["other"];
//			}

//			QIcon volume_icon(icon_rc);

//			auto *item = new QListWidgetItem(volume_icon, volume.name);
			auto *item = new QListWidgetItem(volume.name);

			item->setData(Qt::UserRole + 1, volume.id);
			__list->addItem(item);
		}

		qDebug() << "fill volumes took: " << timer.elapsed() << " ms";
}







void VolumesList::update_volume(const VolumeModel &volume)
{
	for(int i=0; i < __list->count(); i++){
		auto item = __list->item(i);
		auto item_id = item->data(Qt::UserRole + 1).toString();
		if(item_id == volume.uuid){
//						qDebug() << "update list at: " << i;
			item->setText(volume.name);

			QString icon_rc;
			if(VolumeIconsMap.contains(volume.vtype)){
				icon_rc = VolumeIconsMap[volume.vtype];
			}else{
				icon_rc = VolumeIconsMap["other"];
			}

			QIcon volume_icon(icon_rc);
			item->setIcon(volume_icon);
		}
	}
}

QString VolumesList::get_current_volume_id()
{
	return __current_volume_id;
}





/**
 * @brief VolumesList::__on_volume_selected - - событие щелчка на томе
 */
void VolumesList::__on_volume_selected(QListWidgetItem * item){

	auto volume_id = item->data(Qt::UserRole + 1).toString();

	if(volume_id == this->__current_volume_id)	return;

	this->__current_volume_id = volume_id;

	emit volume_selected(volume_id);

}






void VolumesList::__on_remove_volume()
{
	qDebug() << "on remove";
}






void VolumesList::__on_edit_volume(){
	qDebug() << "on edit";


	bool found = false;
	QString volume_id;
	// If multiple selection is on, we need to erase all selected items
	for (int i = 0; i < __list->selectedItems().size(); ++i) {
		// Get curent item on selected row
		QListWidgetItem *item = __list->item(__list->currentRow());

		//--- get volume id
		volume_id = item->data(Qt::UserRole + 1).toString();
		found = true;
//		qDebug() << "edit volume: " << volume_id;

//		VolumeModel model = this->storage->get_volume(volume_id);
//		qDebug() << "name: " << model.name;

		emit volume_edit(volume_id);
		//--- only 1
		break;

//		bool remove_result = this->storage->remove_volume(volume_id);

//		if(remove_result){
//			// And remove it
//			delete item;
//			this->__clear_files();
//		}
	}

}
