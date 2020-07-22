#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "AddVolumeModal.hpp"
#include "Appdb.hpp"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	AddVolumeModal *add_volume_modal;


	Appdb *appdb;


private slots:
	void on_app_close_button_clicked();

	void on_actionAdd_triggered();

	void on_actionOpen_triggered();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
