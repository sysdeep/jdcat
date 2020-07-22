#ifndef FILESLISTNAVIGATOR_HPP
#define FILESLISTNAVIGATOR_HPP

#include <QWidget>
#include <QLineEdit>
#include <QStringList>
#include <QPushButton>



//struct FilesListNavigatorItem{
//	QStri
//};


class FilesListNavigator : public QWidget
{
    Q_OBJECT
public:
    explicit FilesListNavigator(QWidget *parent = nullptr);

	void push(QString path_item_id, QString path_item_name);
    void pop();
    void clear();

private:
    QLineEdit *__edit_path;
    QPushButton *__btn_back;
	QStringList *__path_items_id;
	QStringList *__path_items_name;

    void __update();
	void __on_back();

signals:
	void open_root();
	void open_folder(QString id);


signals:

};

#endif // FILESLISTNAVIGATOR_HPP
