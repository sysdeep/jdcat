#ifndef ADDVOLUMEMODAL_HPP
#define ADDVOLUMEMODAL_HPP

#include <QDialog>

namespace Ui {
class AddVolumeModal;
}

class AddVolumeModal : public QDialog
{
	Q_OBJECT

public:
	explicit AddVolumeModal(QWidget *parent = 0);
	~AddVolumeModal();

private:
	Ui::AddVolumeModal *ui;
};

#endif // ADDVOLUMEMODAL_HPP
