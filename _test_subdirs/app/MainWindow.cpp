#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "qdebug.h"
#include "AddVolumeModal.hpp"
#include "QFileDialog"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	appdb = new Appdb();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_app_close_button_clicked()
{

}

void MainWindow::on_actionAdd_triggered()
{
	qDebug() << "add volume";
	this->add_volume_modal = new AddVolumeModal(this);
	add_volume_modal->show();
//	AddVolumeModal modal = AddVolumeModal(this);
//	modal.show();

}

void MainWindow::on_actionOpen_triggered()
{
	qDebug() << "show open db";
	auto filename = QFileDialog::getOpenFileName(this, "Открыть базу", "/home/nia", "Dcat database (*.dcat)");
	qDebug() << filename;

	bool result = this->appdb->open_db(filename);
	qDebug() << "open result: " << result;

	if(result){
		QString version = appdb->get_db_version();
		qDebug() << "db version: " << version;
	}

	qDebug() << "end action";
}
