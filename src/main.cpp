#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
#include "gui/MainWindow.hpp"
#include "gui/facon/Facon.hpp"
//#include "gui/modals/FaconModal.hpp"
#include "storage/Storage.hpp"
#include <iostream>

int main(int argc, char *argv[]){



	//--- new -----------------------------------------------------------------
//	auto storage = Storage();
////	bool result = storage.create("/home/nia/Development/_QT/QDcat/_storages/st1");
////	std::cout << "create storage result: " << result << std::endl;
//	bool result = storage.open("/home/nia/Development/_QT/QDcat/_storages/st1");
//	std::cout << "open storage result: " << result << std::endl;

//	for(auto vol : storage.manifest->volumes){
//		vol.print();
//	}
//	return 0;




	QApplication a(argc, argv);

//    qDebug() << QStyleFactory::keys();
//    QApplication::setStyle(QStyleFactory::create("Fusion"));

	QFontIcon::addFont(":/fonts/media/fonts/fontawesome.ttf");



//    FaconModal m;
//    m.show();

	MainWindow w;
	w.show();

	return a.exec();



}
