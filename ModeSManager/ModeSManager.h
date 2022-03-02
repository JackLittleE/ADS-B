#pragma once
#include "ModeS/ModeS.h"
#include <QString>
#include <QVector>
#include <QMap>

class ModeSManager
{
private:
	QMap<QString, QVector<ModeSInfo*>> all_info;

public:
	ModeSManager() {};
	~ModeSManager();

	const ModeSInfo* AddInfo(const QString& data);
	const QVector<ModeSInfo*>& GetInfo(const QString& ICAO) const { return this->all_info[ICAO]; };
	QMap<QString, QVector<ModeSInfo*>> GetAllInfo() const { return this->all_info; };
};

