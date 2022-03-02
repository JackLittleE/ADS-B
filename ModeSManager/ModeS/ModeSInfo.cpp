#include "ModeSInfo.h"
#include <QDateTime>
#include <QtMath>

#include "ADSBIdentification.h"
#include "ADSBSurfacePosition.h"
#include "ADSBAirbornePosition.h"
#include "ADSBAirborneVelocity.h"

ModeSInfo::ModeSInfo(const QString& data)
{
	int len = data.size();
	if (len != 56 && len != 112)
		throw "长度错误";
	if (!ModeSInfo::CRC(data))
		throw "CRC 错误";

	this->DF = data.midRef(0, 5).toULongLong(nullptr, 2);
	this->TCA = data.midRef(5, 3).toULongLong(nullptr, 2);
	this->ICAO = QString::number(data.midRef(8, 24).toULongLong(nullptr, 2)).rightJustified(6, '0', true);
	this->ME = len == 112 ? data.midRef(32, 56).toULongLong(nullptr, 2) : 0;
	// this->PI = data.midRef(len == 112 ? 88 : 32, 24).toULongLong(nullptr, 2);

	this->time = QDateTime::currentMSecsSinceEpoch();
	this->meta_data = data;
}


bool ModeSInfo::CRC(const QString& data)
{
	uint32_t bit;
	uint32_t crc = 0;
	for (int i = 0; i < data.size(); i += 8)
	{
		bit = data.midRef(i, 8).toUInt(nullptr, 2);
		crc ^= bit << 16;
		for (int j = 0; j < 8; j++)
			if (crc & 0x00800000)
				crc = (crc << 1) ^ 0x00FFF409;
			else
				crc <<= 1;
	}
	return crc == 0;
}

void ModeSInfo::encodeCPR(quint64 CPR_f, quint64 CPR_lat, quint64 CPR_lon, bool mode, double* lat, double* lon)
{
	const double local_lat = 31.73403;
	const double local_lon = 118.87027;
	const quint64 NZ = 15;
	double Dlat = (mode ? 360.0 : 90.0) / (4 * NZ - (double)CPR_f);
	double n = floor(local_lat / Dlat) - floor(0.5 + fmod(local_lat, Dlat) / Dlat - (double)CPR_lat / 0x20000);
	*lat = Dlat * (n + (double)CPR_lat / 0x20000);
	double NL;
	if (fabs(*lat) > 87)
		NL = 1.0;
	else if (fabs(*lat) == 87)
		NL = 2.0;
	else if (fabs(*lat) == 0)
		NL = 59.0;
	else
		NL = floor(2 * M_PI / acos(1 - (1 - cos(M_PI / 30)) / pow(cos(*lat * M_PI / 180), 2)));
	double Dlon = (mode ? 360.0 : 90.0) / (NL - (double)CPR_f);
	double m = floor(local_lon / Dlon) + floor(0.5 + fmod(local_lon, Dlon) / Dlon - (double)CPR_lon / 0x20000);
	*lon = Dlon * (m + (double)CPR_lon / 0x20000);
}

ModeSInfo* ModeSInfo::fromstr(const QString& data)
{
	quint64 TC = data.midRef(32, 5).toULongLong(nullptr, 2);
	if (1 <= TC && TC <= 4)
		return new ADSBIdentification(data);
	if (5 <= TC && TC <= 8)
		return new ADSBSurfacePosition(data);
	if ((9 <= TC && TC <= 18) || (20 <= TC && TC <= 22))
		return new ADSBAirbornePosition(data);
	if (TC == 19)
		return new ADSBAirborneVelocity(data);
	throw "未知类别";
}
