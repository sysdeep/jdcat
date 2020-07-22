#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QListWidgetItem>
#include <QStandardItemModel>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>

#include "AddVolumeModal.hpp"
#include "storage/dbsqlite/Appdb.hpp"
#include "storage/Storage.hpp"
#include "lib/USettings.hpp"
#include "VolumesList.hpp"
#include "FilesList.hpp"


//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

//	AddVolumeModal *add_volume_modal;


//	Appdb *appdb;

    Storage *storage;
	USettings *usettings;


private slots:

	void on_action_new();
	void on_action_open();
    void on_action_show_facon();
	void on_action_add_volume();
	void on_action_db_info();
	void on_action_exit();




//	void __on_volume_selected(QListWidgetItem *);





	void __on_remove_volume();
//	void __on_edit_volume();

	void on_exp_back_button_clicked();

private:
//	Ui::MainWindow *ui;

	void				create_actions();

    VolumesList *__volumes_list;
    FilesList *__files_list;

	Volumes __volumes;

	QStandardItemModel* __files_model;
	QStringList			__history_list;
	QString				__current_volume_id;				// тек. том


	void				__on_volume_selected(QString &volume_id);
	void				__on_edit_volume(QString &volume_id);

	void				__on_open_folder(QString &folder_id);

	void				__on_go_root();

	void				__fill_files(Files files);
	bool				__open_db(QString path);			// открыть базу
	void				__update_title(QString db_path);	// обновить заголовок
	void				__update_back_button();				// обновить состояние кнопки назад
};

#endif // MAINWINDOW_HPP
