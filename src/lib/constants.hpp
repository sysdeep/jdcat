#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include <QMap>
#include <QStringList>

//namespace DBEvents {
//  static constexpr char script_mclass_created[]			= "script_mclass_created";      //!< desription: Создан сценарий
//  static constexpr char script_mclass_updated[]			= "script_mclass_updated";      //!< desription: Обновлён сценарий
//  static constexpr char script_mclass_deleted[]			= "script_mclass_deleted";      //!< desription:
//  static constexpr char script_mclass_smart_deleted[]	= "script_mclass_smart_deleted";
//}




















//namespace VolumesNum {
//	static constexpr int harddisk = 1;
//	static constexpr int cd = 2;
//}

//namespace VolumesIcon {
//	static constexpr char harddisk[] = ":/volumes/media/icons/volumes/harddisk.png";
//	static constexpr char cd[] = ":/volumes/media/icons/volumes/cd.png";
//}


//void(int i){
//	switch (i) {
//		case VolumesNum::harddisk:
//			VolumesIcon::harddisk;
//			break;
//		default:
//			break;
//	}
//	VolumesIcon::
//}


//class VolumeIcons{
//public:
//	static QMap<int, QString> icons;
//};

static QMap<QString, QString> VolumeIconsMap = {
	{"cd", ":/volumes/media/icons/volumes/cd.png"},				// ok
	{"audio_cd", ":/volumes/media/icons/volumes/audio_cd.png"},			// ok
	{"dvd", ":/volumes/media/icons/volumes/dvd.png"},				// ok
	{"folder", ":/volumes/media/icons/volumes/folder.png"},			// ok
	{"hdd", ":/volumes/media/icons/volumes/hdd.png"},				// ok
	{"hdd_usb", ":/volumes/media/icons/volumes/hdd_usb.png"},			// ok
	{"flash", ":/volumes/media/icons/volumes/flash.png"},				// ok
	{"sd", ":/volumes/media/icons/volumes/sd.png"},				// ok
	{"floppy", ":/volumes/media/icons/volumes/floppy.png"},			// ok
	{"net", ":/volumes/media/icons/volumes/net.png"},				// ok
	{"tape", ":/volumes/media/icons/volumes/tape.png"},				// ok
	{"crypted", ":/volumes/media/icons/volumes/crypted.png"},
	{"bdrom", ":/volumes/media/icons/volumes/bdrom.png"},
	{"other", ":/volumes/media/icons/volumes/other.png"}
};

//static QMap<QString, QString> VolumeIconsMap = {
//	{"cd", ":/volumes/media/icons/volumes/cd.png"},				// ok
//	":/volumes/media/icons/volumes/audio_cd.png",			// ok
//	":/volumes/media/icons/volumes/dvd.png",				// ok
//	":/volumes/media/icons/volumes/folder.png",			// ok
//	":/volumes/media/icons/volumes/hdd.png",				// ok
//	":/volumes/media/icons/volumes/hdd_usb.png",			// ok
//	":/volumes/media/icons/volumes/flash.png",				// ok
//	":/volumes/media/icons/volumes/sd.png",				// ok
//	":/volumes/media/icons/volumes/floppy.png",			// ok
//	":/volumes/media/icons/volumes/net.png",				// ok
//	":/volumes/media/icons/volumes/tape.png",				// ok
//	":/volumes/media/icons/volumes/crypted.png",
//	":/volumes/media/icons/volumes/bdrom.png",
//	":/volumes/media/icons/volumes/other.png"
//};

//static QStringList VolumeIconsList = {
//	":/volumes/media/icons/volumes/cd.png",				// ok
//	":/volumes/media/icons/volumes/audio_cd.png",			// ok
//	":/volumes/media/icons/volumes/dvd.png",				// ok
//	":/volumes/media/icons/volumes/folder.png",			// ok
//	":/volumes/media/icons/volumes/hdd.png",				// ok
//	":/volumes/media/icons/volumes/hdd_usb.png",			// ok
//	":/volumes/media/icons/volumes/flash.png",				// ok
//	":/volumes/media/icons/volumes/sd.png",				// ok
//	":/volumes/media/icons/volumes/floppy.png",			// ok
//	":/volumes/media/icons/volumes/net.png",				// ok
//	":/volumes/media/icons/volumes/tape.png",				// ok
//	":/volumes/media/icons/volumes/crypted.png",
//	":/volumes/media/icons/volumes/bdrom.png",
//	":/volumes/media/icons/volumes/other.png"
//};

//static QStringList VolumeNamesList = {
//	"cd",				// ok
//	"audio cd",			// ok
//	"dvd",				// ok
//	"folder",			// ok
//	"hdd",				// ok
//	"hdd_usb",			// ok
//	"flash",				// ok
//	"sd",				// ok
//	"floppy",			// ok
//	"net",				// ok
//	"tape",				// ok
//	"crypted",
//	"bdrom",
//	"other"
//};






#endif // CONSTANTS_HPP
