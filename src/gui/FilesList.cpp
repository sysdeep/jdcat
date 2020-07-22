#include <QDebug>
#include "FilesList.hpp"

FilesList::FilesList(QWidget *parent) : QWidget(parent)
{

	this->setMinimumWidth(500);
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);

    __tree = new QTreeView();
    __navigator = new FilesListNavigator();

    main_layout->addWidget(__navigator);
    main_layout->addWidget(__tree);


    QStringList labels = {"Название", "Размер"};
    __files_model = new QStandardItemModel();
    __files_model->setHorizontalHeaderLabels(labels);


    __tree->setModel(__files_model);
    __tree->setAlternatingRowColors(true);
	__tree->setSortingEnabled(true);
    __tree->setRootIsDecorated(false);
	__tree->setColumnWidth(0, 200);



	this->connect(__tree, SIGNAL(doubleClicked(const QModelIndex &)),
					  this, SLOT(__on_file_dclicked(const QModelIndex &)));


	connect(__navigator, &FilesListNavigator::open_root, [this](){
		this->__on_navigator_root();
	});

	connect(__navigator, &FilesListNavigator::open_folder, [this](QString id){
		this->__on_navigator_folder(id);
	});
}

void FilesList::clear(){
	__files_model->removeRows(0, __files_model->rowCount());
}

void FilesList::set_files(Files &files)
{

	//--- clean model
	this->clear();

	for(auto &file : files){

		QList<QStandardItem*> row;



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

		// 4 - 52
		QIcon item_icon;
		if(file.ftype == 0){
			item_icon = QIcon(":/files/media/icons/files/folder.png");
		}else{
			item_icon = QIcon(":/files/media/icons/files/file.png");
		}


		auto name_item = new QStandardItem(item_icon, file.name);
	////		auto size_item = new QStandardItem(QString::number(file.size) + QString(" b"));



	////        auto name_item = new QStandardItem(file.name);

		row.append(name_item);
		if(file.ftype == 1){
			auto size_item = new QStandardItem(file.formatted_size());
			row.append(size_item);
		}

		for(auto &cell : row){
			cell->setEditable(false);
			cell->setData(file.uuid, Qt::UserRole + 1);
			cell->setData(file.ftype, Qt::UserRole + 2);
			cell->setData(file.name, Qt::UserRole + 3);
		}

		this->__files_model->appendRow(row);
	////		auto row = new QList<QStandardItem*>();
	////		row->append(new QStandardItem(file.name));
	////		QStandardItem *item = new QStandardItem(file.name);
	////		this->__files_model->appendRow(item);
	}
//	__tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//	ui->files_list->header()->setStretchLastSection(true);
    this->__files_model->sort(0);
}

void FilesList::clear_history()
{
	__navigator->clear();
}

void FilesList::__on_navigator_folder(QString id)
{
	qDebug() << "folder";
	emit open_folder(id);
}

void FilesList::__on_navigator_root()
{
	qDebug() << "root";
	emit(open_root());
}

void FilesList::__on_file_dclicked(const QModelIndex &index)
{
	QString selected_file_uuid = index.data(Qt::UserRole + 1).toString();
	int ftype = index.data(Qt::UserRole + 2).toInt();

	//--- если файл - не открываем дальше
	if(ftype == 1){
		return;
	}


	QString folder_name = index.data(Qt::UserRole + 3).toString();


	__navigator->push(selected_file_uuid, folder_name);

	emit open_folder(selected_file_uuid);


//    QElapsedTimer timer;
//    timer.start();

//    auto files = this->storage->get_child_files(selected_file_uuid);

//    qDebug() << "get_child_files took " << timer.elapsed() << "ms";

//    timer.restart();

//	//--- fill filles
//	this->__fill_files(files);

//    qDebug() << "__fill_files took " << timer.elapsed() << "ms";


//	//--- push history
//	this->__history_list.append(selected_file_uuid);
//	this->__update_back_button();
}
