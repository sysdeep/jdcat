#include <QList>
#include <QStandardItem>
#include <QElapsedTimer>
#include "MainWindow.hpp"
#include "qdebug.h"
#include "QFileDialog"

#include "../lib/constants.hpp"

#include "AddVolumeModal.hpp"
#include "./modals/DBInfoModal.hpp"
#include "./modals/EditVolumeModal.hpp"
#include "./modals/FaconModal.hpp"
#include "./facon/Facon.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
//  ,	ui(new Ui::MainWindow)
{



    QWidget *central_widget = new QWidget();
    central_widget->setMinimumHeight(300);
    central_widget->setMinimumWidth(600);
    QVBoxLayout *central_layout = new QVBoxLayout(central_widget);

    this->setCentralWidget(central_widget);


    //--- main boxes ----------------------------------------------------------
    QHBoxLayout *main_boxes = new QHBoxLayout();

	__volumes_list = new VolumesList(this);
	__files_list = new FilesList(this);


	main_boxes->addWidget(__volumes_list);
	main_boxes->addWidget(__files_list);



    central_layout->addLayout(main_boxes);
    //--- main boxes ----------------------------------------------------------





//    central_layout->addStretch();

    //--- actions box ---------------------------------------------------------
//    QHBoxLayout *actions_box = new QHBoxLayout();
//    central_layout->addLayout(actions_box);

//	QPushButton *button_exit = new QPushButton("Закрыть");
//	button_exit->setIcon(QIcon(":/icons/media/icons/exit.png"));
//    connect(button_exit, &QPushButton::clicked, [this](){
//        this->close();
//    });

//    actions_box->addStretch();
//    actions_box->addWidget(button_exit);
    //--- actions box ---------------------------------------------------------


	this->create_actions();


	connect(__volumes_list, &VolumesList::volume_selected, [this](QString volume_id){
		this->__on_volume_selected(volume_id);
	});

	connect(__volumes_list, &VolumesList::volume_edit, [this](QString volume_id){
		this->__on_edit_volume(volume_id);
	});

	connect(__files_list, &FilesList::open_folder, [this](QString folder_id){
		this->__on_open_folder(folder_id);
	});

	connect(__files_list, &FilesList::open_root, [this](){
		this->__on_go_root();
	});


    //--- default title
    this->__update_title("");
//	this->__update_back_button();





    storage = new Storage();



//	this->connect(ui->files_list, SIGNAL(doubleClicked(const QModelIndex &)),
//				  this, SLOT(__on_file_dclicked(const QModelIndex &)));

////	self.tree_view.doubleClicked.connect(self.__on_double_clicked_item)
////	connect(ui->volumes_list, "clicked", this, );
////	ui->volumes_list->clicked()


    //--- setup settings
    this->usettings = new USettings(".dcat", "settings.json");

//	//--- append menu links
//	// TODO




    //--- open last db
//    if(this->usettings->data.open_last && this->usettings->last_database_exists()){

//        auto last_database = this->usettings->get_last_database();

//		this->__open_db(last_database);
//    }

	//--- new
	this->__open_db("/home/nia/Development/_QT/QDcat/_storages/st1");

}

MainWindow::~MainWindow()
{
	//	delete ui;
}







void MainWindow::on_action_new()
{
	qDebug() << "action new";
}






void MainWindow::on_action_open(){
	qDebug() << "action open";

	auto filename = QFileDialog::getOpenFileName(this, "Открыть базу", "/home/nia", "Dcat database (*.dcat)");

	qDebug() << "on open" << filename;

	if(filename.isEmpty())	return;

    this->__open_db(filename);
}

void MainWindow::on_action_show_facon()
{
    auto *modal = new FaconModal(this);
    modal->show();
}








void MainWindow::on_action_exit()
{
	this->close();
}

/**
 * @brief MainWindow::on_actionAdd_triggered
 */
void MainWindow::on_action_add_volume(){

	auto add_volume_modal = new AddVolumeModal(this->storage, this);
	add_volume_modal->exec();

	if(add_volume_modal->need_update){
		__volumes = storage->get_volumes();
		this->__files_list->clear();
//		this->__volumes_list->set_volumes(__volumes);

	}

	delete add_volume_modal;




//	AddVolumeModal modal = AddVolumeModal(this);
//	modal.show();

}





/**
 * @brief MainWindow::on_actionDB_info_triggered
 */
void MainWindow::on_action_db_info(){

    auto db_info = this->storage->get_db_system_info();
    auto *modal = new DBInfoModal(db_info, this);
    modal->exec();
}



/**
 * @brief MainWindow::__on_volume_selected - событие щелчка на томе
 * @param item
 */
void MainWindow::__on_volume_selected(QString &volume_id){

////	this->__history_list.clear();
////	this->__update_back_button();


	qDebug() << "on volume selected: " << volume_id;
	auto volume_ptr = this->storage->open_volume(volume_id);

//	auto files = storage->get_volume_files(volume_id);

//    __files_list->clear_history();
//    __files_list->set_files(files);
}






/**
 * @brief MainWindow::__on_remove_volume
 */
void MainWindow::__on_remove_volume(){
	qDebug() << "__on_remove_volume";

//	// If multiple selection is on, we need to erase all selected items
//	for (int i = 0; i < ui->volumes_list->selectedItems().size(); ++i) {
//		// Get curent item on selected row
//		QListWidgetItem *item = ui->volumes_list->takeItem(ui->volumes_list->currentRow());

//		//--- get volume id
//		QString volume_id = item->data(Qt::UserRole + 1).toString();
//		qDebug() << "remove volume: " << volume_id;

//		bool remove_result = this->storage->remove_volume(volume_id);

//		if(remove_result){
//			// And remove it
//			delete item;
//			this->__clear_files();
//		}
//	}
}


/**
 * @brief MainWindow::__on_edit_volume
 * @param volume_id
 */
void MainWindow::__on_edit_volume(QString &volume_id){

	VolumeModel volume = this->storage->get_volume(volume_id);


	auto *modal = new EditVolumeModal(&volume, this);
	auto ret = modal->exec();
	delete(modal);

	if(ret == QDialog::Accepted){
		qDebug() << "save volume record";
		auto save_result = this->storage->update_volume(volume);

		if(save_result){
			this->__volumes_list->update_volume(volume);
		}else{
			// TODO
			qDebug() << "unable save volume!!!";
		}


	}else{
		qDebug() << "discard edit";
	}

}

void MainWindow::__on_open_folder(QString &folder_id)
{
	QElapsedTimer timer;
	timer.start();

	auto files = this->storage->get_child_files(folder_id);

	qDebug() << "get_child_files took " << timer.elapsed() << "ms";

	timer.restart();

	//--- fill filles
	this->__files_list->set_files(files);

	qDebug() << "__fill_files took " << timer.elapsed() << "ms";


	//--- push history
//	this->__history_list.append(selected_file_uuid);
	//	this->__update_back_button();
}

void MainWindow::__on_go_root()
{
	auto volume_id = __volumes_list->get_current_volume_id();

	auto files = storage->get_volume_files(volume_id);

	__files_list->clear_history();
	__files_list->set_files(files);
}




/**
 * @brief MainWindow::__fill_files
 * @param files
 */
void MainWindow::__fill_files(Files files){

//	//--- clean model
//	this->__clear_files();

//	for(auto &file : files){

//		QList<QStandardItem*> row;



//        //--- very long!!!!!!!! ----------------------------------------------
//        // 5 - 702!!!!
////        QIcon item_icon;
////        if(file.ftype == 0){
////            item_icon = QIcon(":/files/media/icons/files/folder.svg");
////        }else{
////            item_icon = QIcon(":/files/media/icons/files/file.svg");
////        }


////        auto name_item = new QStandardItem(item_icon, file.name);

//        //--- very long!!!!!!!! ----------------------------------------------

//        // 4 - 52
//        QIcon item_icon;
//        if(file.ftype == 0){
//            item_icon = QIcon(":/files/media/icons/files/folder.png");
//        }else{
//            item_icon = QIcon(":/files/media/icons/files/file.png");
//        }


//        auto name_item = new QStandardItem(item_icon, file.name);
////		auto size_item = new QStandardItem(QString::number(file.size) + QString(" b"));



////        auto name_item = new QStandardItem(file.name);

//		row.append(name_item);
//		if(file.ftype == 1){
//			auto size_item = new QStandardItem(file.formatted_size());
//			row.append(size_item);
//		}

//		for(auto &cell : row){
//			cell->setEditable(false);
//			cell->setData(file.uuid, Qt::UserRole + 1);
//			cell->setData(file.ftype, Qt::UserRole + 2);
//		}

//		this->__files_model->appendRow(row);
////		auto row = new QList<QStandardItem*>();
////		row->append(new QStandardItem(file.name));
////		QStandardItem *item = new QStandardItem(file.name);
////		this->__files_model->appendRow(item);
//	}
//	ui->files_list->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
//	ui->files_list->header()->setStretchLastSection(true);
//	this->__files_model->sort(0);

}


/**
 * @brief MainWindow::__open_db
 * @param path
 * @return
 */
bool MainWindow::__open_db(QString path){


	bool result = this->storage->open(path);
	if(result == false)	return false;

//	bool result = storage->open_db(path);
//	if(result == false)	return false;

//    this->usettings->add_database(path);

	//--- update title text
	this->__update_title(path);


////	if(result){
////		QString version = appdb->get_db_version();
////		qDebug() << "db version: " << version;
////	}



//    //--- save
//	__volumes = storage->get_volumes();



////	this->__fill_volumes(__volumes);

	this->__files_list->clear();
//	this->__volumes_list->set_volumes(__volumes);
	this->__volumes_list->set_volumes(&this->storage->manifest->volumes);

	for(auto q: this->storage->manifest->volumes){
		q.print();
	}

	return true;
}

/**
 * @brief MainWindow::__update_title - обновить заголовок
 * @param db_path
 */
void MainWindow::__update_title(QString db_path){
	QString window_title;
	QString bar_title;
	if(db_path.isEmpty()){
		window_title = "QDcat v 0.0.1";
		bar_title = "---";
	}else{
		window_title = "QDcat v 0.0.1 - ["+ db_path +"]";
		bar_title = db_path;
	}

	this->setWindowTitle(window_title);

	//--- статусная строка

	this->statusBar()->showMessage(bar_title);
}



/**
 * @brief MainWindow::__update_back_button - обновить состояние кнопки
 */
void MainWindow::__update_back_button(){
//	this->ui->exp_back_button->setEnabled(this->__history_list.length() > 0);
}





/**
 * @brief MainWindow::on_exp_back_button_clicked - событие щелчка на кнопке назад
 */
void MainWindow::on_exp_back_button_clicked(){

	this->__history_list.pop_back();				// drop last(current)
	this->__update_back_button();					// update state

	//--- если в истории ничего нет - отображаем корень
	if(this->__history_list.length() == 0){
		auto files = storage->get_volume_files(this->__current_volume_id);
		this->__fill_files(files);
		return;
	}

	//--- получаем родительский id
	auto pre_last_id = this->__history_list.last();

	auto files = this->storage->get_child_files(pre_last_id);

	//--- fill filles
	this->__fill_files(files);

}






void MainWindow::create_actions(){

	//--- file menu -----------------------------------------------------------
	QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));

	QToolBar *main_toolbar = addToolBar(tr("Файл"));

	//--- create - new db
//	const QIcon newIcon = QIcon::fromTheme("document-new");
	const QIcon newIcon = QIcon(":/icons/media/icons/new.png");
	QAction *action_new_db = new QAction(newIcon, tr("Создать базу"), this);
//	newaction_new_db->setShortcuts(QKeySequence::New);
	action_new_db->setStatusTip(tr("Создать новую базу"));
	connect(action_new_db, &QAction::triggered, this, &MainWindow::on_action_new);
	fileMenu->addAction(action_new_db);


	const QIcon openIcon = QIcon(":/icons/media/icons/open.png");
	QAction *action_open_db = new QAction(openIcon, tr("Открыть базу"), this);
//	openAct->setShortcuts(QKeySequence::Open);
	action_open_db->setStatusTip(tr("Открыть базу"));
	connect(action_open_db, &QAction::triggered, this, &MainWindow::on_action_open);
	fileMenu->addAction(action_open_db);


	fileMenu->addSeparator();


	const QIcon add_volume_icon = QIcon(":/icons/media/icons/add.png");
	QAction *action_add_volume = new QAction(add_volume_icon, tr("Добавить том"), this);
//	action_add_volume->setShortcuts(QKeySequence::Open);
	action_add_volume->setStatusTip(tr("Добавить том"));
	connect(action_add_volume, &QAction::triggered, this, &MainWindow::on_action_add_volume);
	fileMenu->addAction(action_add_volume);


	fileMenu->addSeparator();

	const QIcon db_info_icon = QIcon(":/icons/media/icons/db_info.png");
	QAction *action_db_info = new QAction(db_info_icon, tr("Информация о базе"), this);
//	db_info_action->setShortcuts(QKeySequence::Open);
	action_db_info->setStatusTip(tr("Информация о базе"));
	connect(action_db_info, &QAction::triggered, this, &MainWindow::on_action_db_info);
	fileMenu->addAction(action_db_info);


	fileMenu->addSeparator();

	const QIcon exit_icon = QIcon(":/icons/media/icons/exit.png");
	QAction *action_exit = new QAction(exit_icon, tr("Выход"), this);
//	exit_action->setShortcuts(QKeySequence::Open);
	action_exit->setStatusTip(tr("Выход"));
	connect(action_exit, &QAction::triggered, this, &MainWindow::on_action_exit);
	fileMenu->addAction(action_exit);


	//--- file menu -----------------------------------------------------------


    //--- test
    const QIcon qqq_icon = QFontIcon::icon(0xf030);
    QAction *action_qqq = new QAction(qqq_icon, tr("facon"), this);
    connect(action_qqq, &QAction::triggered, this, &MainWindow::on_action_show_facon);
//	fileMenu->addAction(action_exit);
    //--------




	QWidget *spacer = new QWidget();
	auto *qqq = new QHBoxLayout(spacer);
	qqq->addStretch();
	spacer->setLayout(qqq);




//	main_toolbar->addAction(newaction_new_db);
	main_toolbar->addAction(action_open_db);
	main_toolbar->addSeparator();
	main_toolbar->addAction(action_add_volume);
	main_toolbar->addSeparator();
	main_toolbar->addAction(action_db_info);

    main_toolbar->addSeparator();
    main_toolbar->addAction(action_qqq);

	main_toolbar->addWidget(spacer);

	main_toolbar->addAction(action_exit);
}
