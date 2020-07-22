#include "AddVolumeModal.hpp"
#include "ui_AddVolumeModal.h"

AddVolumeModal::AddVolumeModal(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddVolumeModal)
{
	ui->setupUi(this);
}

AddVolumeModal::~AddVolumeModal()
{
	delete ui;
}
