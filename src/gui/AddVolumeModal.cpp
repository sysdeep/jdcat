#include <QFileDialog>
#include <QDir>
#include <QUuid>
#include <QStringList>
#include <QElapsedTimer>
#include <QIcon>
#include "AddVolumeModal.hpp"
#include "ui_AddVolumeModal.h"
#include "qdebug.h"
#include "core/models/VolumeModel.hpp"

#include <QtConcurrent/QtConcurrent>
#include "../lib/constants.hpp"

AddVolumeModal::AddVolumeModal(Storage *storage, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddVolumeModal)
{
	this->__storage = storage;
	ui->setupUi(this);
	this->ui->pager->setCurrentIndex(0);


	//--- fill volume type
	QMap<QString, QString>::const_iterator i = VolumeIconsMap.constBegin();
	while(i != VolumeIconsMap.constEnd()){
		ui->icon_select->addItem(QIcon(i.value()), i.key());
		++i;
	}
	ui->icon_select->setCurrentIndex(0);




	ui->label_total_files->setText("0");
	ui->label_current_file->setText("0");

	ui->progressBar->setMaximum(100);
	ui->progressBar->setValue(0);


}





AddVolumeModal::~AddVolumeModal(){
	delete ui;
}



/**
 * @brief AddVolumeModal::on_show_select_path_clicked
 */
void AddVolumeModal::on_show_select_path_clicked(){

	auto src_path = QFileDialog::getExistingDirectory(this, "Выбор каталога для сканирования", "/home/nia");

	if(src_path.isEmpty())	return;


	QDir path = QDir(src_path);
	auto dir_name = path.dirName();




	ui->edit_path->setText(src_path);
	ui->edit_name->setText(dir_name);


	ui->progressBar->setMinimum(0);
	ui->progressBar->setMaximum(100);
	ui->progressBar->setValue(0);



}



/**
 * @brief AddVolumeModal::on_start_btn_clicked
 */
void AddVolumeModal::on_start_btn_clicked(){
	qDebug() << "start";


//	this->ui->pager->setCurrentIndex(1);
//	return;



//	// TODO: checks!!!
//	const QString path = ui->edit_path->text();
//	const QString name = ui->edit_name->text();
//	const QString description = ui->edit_description->toPlainText();


//	const QString vicon_text = ui->icon_select->currentText();

//	qDebug() << "path: " << path;
//	qDebug() << "name: " << name;
//	qDebug() << "icon: " << vicon_text;
//	qDebug() << "description: " << description;


	//--- scan params
	ScanParams params;
	params.path = ui->edit_path->text();
	params.name = ui->edit_name->text();
	params.icon = ui->icon_select->currentText();
	params.description = ui->edit_description->toPlainText();

	//--- show scan params
	this->__init_scan_page(params);

	//--- goto info page
	this->ui->pager->setCurrentIndex(1);

	//--- start
	this->__start_scan(params);
	return;


}








void AddVolumeModal::at_prescan(int res){

	ui->progressBar->setMaximum(res);
	ui->progressBar->setValue(0);

	ui->label_total_files->setText(QString::number(res));
	ui->label_current_file->setText("0");

}


void AddVolumeModal::at_current_counter(int counter){

	this->ui->label_current_file->setText(QString::number(counter));
	this->ui->progressBar->setValue(counter);
}

void AddVolumeModal::at_scan_complete(){
	qDebug() << "on_scan_complete";

	//--- lock buttons
	ui->button_stop->setDisabled(true);
	ui->button_ready->setDisabled(false);
}




/**
 * @brief AddVolumeModal::__create_volume_record
 * @param name
 * @param path
 * @param vtype
 * @param description
 * @return
 */
bool AddVolumeModal::__create_volume_record(QString volume_id, QString name, QString path, QString vtype, QString description){



	VolumeModel volume_model = VolumeModel();
	volume_model.uuid = volume_id;
	volume_model.name = name;
	volume_model.path = path;
	volume_model.vtype = vtype;
    volume_model.description = description;

	bool result = this->__storage->create_volume(volume_model);
	qDebug() << result;

//	bool result = true;

	return result;
}







bool AddVolumeModal::__start_scan(const ScanParams &params){

	//--- create volume record
	QString volume_id = QUuid::createUuid().toString().replace("{", "").replace("}", "");
	bool volume_created = this->__create_volume_record(volume_id, params.name, params.path, params.icon, params.description);
	if(!volume_created){
		qDebug() << "error create volume...";
		return false;
	}


	//--- создаём обработчик
	// https://ru.stackoverflow.com/questions/543639/qthread-%d0%9f%d0%be%d1%82%d0%be%d0%ba%d0%b8-%d0%ba%d0%b0%d0%ba-%d0%bf%d1%80%d0%b0%d0%b2%d0%b8%d0%bb%d1%8c%d0%bd%d0%be-%d0%b7%d0%b0%d0%ba%d1%80%d1%8b%d1%82%d1%8c-%d0%bf%d0%be%d1%82%d0%be%d0%ba
	ScanWorker *worker = new ScanWorker(this->__storage, params.path, volume_id);

	connect(worker, SIGNAL(prescan_finished(int)), this, SLOT(at_prescan(int)));			// кол-во файлов для сканирования
	connect(worker, SIGNAL(scan_finished()), this, SLOT(at_scan_complete()));				// сканирование завершено
	connect(worker, SIGNAL(current_counter(int)), this, SLOT(at_current_counter(int)));		// тек. номер файла
	connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));						// по завершению - чистим всё
	connect(this, SIGNAL(set_stop_scan()), worker, SLOT(stop()));

	//--- запускаем разово в отдельном потоке
	QtConcurrent::run(worker, &ScanWorker::start);

	this->need_update = true;

	return true;



//	this->__current_files = 0;

//	QElapsedTimer etimer;
//	etimer.start();
//	this->__storage->start_transaction();
//	this->__scan_dir(QDir(path), "0", volume_id);
//	this->__storage->end_transaction();


//	auto elapsed = etimer.elapsed();
//	ui->label_elapsed_time->setText(QString::number(elapsed));

	//	this->need_update = true;
}

void AddVolumeModal::__stop_scan(){
	emit set_stop_scan();
}

void AddVolumeModal::__init_scan_page(const ScanParams &params){
	//--- update scan params info
	ui->re_path->setText(params.path);
	ui->re_name->setText(params.name);
	ui->re_icon->setText(params.icon);
	ui->re_description->setText(params.description);


	//--- update scan info
	ui->label_total_files->setText("0");
	ui->label_current_file->setText("0");
	ui->label_elapsed_time->setText("0");

	//--- lock buttons
	ui->button_stop->setDisabled(false);
	ui->button_ready->setDisabled(true);


}

//void AddVolumeModal::__scan_dir(QDir dir, QString parent_id, QString volume_id)
//{

//	//--- files
//	qDebug() << "--- files ---";
//	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
//	QStringList files = dir.entryList();
//	for(int i=0; i<files.count(); i++){

//		FileModel model = FileModel();
//		model.name = files[i];
//		model.uuid = QUuid::createUuid().toString().replace("{", "").replace("}", "");
//		model.parent_id = parent_id;
//		model.ftype = 1;
//		model.volume_id = volume_id;

////		qDebug() << model.parent_id << ":" << model.uuid << " - " << model.name;
//		this->__storage->create_file(model);
//		this->__inc_current_counter();

////		qDebug() << files[i];
////		qDebug() << QUuid::createUuid();
//	}



//	//--- folders
//	qDebug() << "--- folders ---";
//	dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
//	QStringList folders = dir.entryList();
//	for(int i=0; i<folders.count(); i++){


//		FileModel model = FileModel();
//		model.name = folders[i];
//		model.uuid = QUuid::createUuid().toString().replace("{", "").replace("}", "");
//		model.parent_id = parent_id;
//		model.ftype = 0;
//		model.volume_id = volume_id;


//		this->__storage->create_file(model);
//		this->__inc_current_counter();





//		qDebug() << folders[i];

//		QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(folders.at(i));
//		__scan_dir(QDir(newPath), model.uuid, volume_id);
//	}
//}

//void AddVolumeModal::__prescan_dir(QDir dir){
//	//--- files
//	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
//	QStringList files = dir.entryList();
//	this->__total_files += files.count();

//	//--- folders
//	dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
//	QStringList folders = dir.entryList();
//	this->__total_files += folders.count();
//	for(int i=0; i<folders.count(); i++){

//		QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(folders.at(i));
//		this->__prescan_dir(QDir(newPath));
//	}
//}

//void AddVolumeModal::__inc_current_counter(){
//	this->__current_files += 1;
//	ui->progressBar->setValue(this->__current_files);
//	ui->label_current_file->setText(QString::number(this->__current_files));
//}

void AddVolumeModal::on_button_stop_clicked(){
	this->__stop_scan();
}

void AddVolumeModal::on_button_ready_clicked(){
	this->need_update = true;
	this->close();
}
