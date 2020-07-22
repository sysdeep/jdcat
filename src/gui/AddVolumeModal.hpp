#ifndef ADDVOLUMEMODAL_HPP
#define ADDVOLUMEMODAL_HPP

#include <QDialog>
#include <QString>
#include "../storage/Storage.hpp"
#include "core/models/FileModel.hpp"
#include "ScanWorker.hpp"

namespace Ui {
class AddVolumeModal;
}


struct ScanParams{
	QString path;
	QString name;
	QString icon;
	QString description;
};


class AddVolumeModal : public QDialog
{
	Q_OBJECT

public:
	explicit AddVolumeModal(Storage *storage, QWidget *parent = 0);
	~AddVolumeModal();


	bool need_update = false;			// флаг выше для необходимости обновления данных

private slots:
	void on_show_select_path_clicked();
	void on_start_btn_clicked();
	void on_button_stop_clicked();

	void on_button_ready_clicked();

public slots:
	void at_prescan(int);
	void at_current_counter(int);
	void at_scan_complete();



signals:
	void set_scan_path(const QString&);
	void set_stop_scan();

private:
	Storage *__storage;
	Ui::AddVolumeModal *ui;

	//---
	QThread *__scan_thread;
	ScanWorker *__scan_worker;

	bool __create_volume_record(QString volume_id, QString name, QString path, QString vtype, QString description);

	bool __start_scan(const ScanParams& params);

	void __stop_scan();
	void __init_scan_page(const ScanParams& params);

//	int		__current_files = 0;
//	void __scan_dir(QDir dir, QString parent_id, QString volume_id);

//	int		__total_files = 0;
//	void	__prescan_dir(QDir dir);

//	void	__inc_current_counter();




};

#endif // ADDVOLUMEMODAL_HPP
