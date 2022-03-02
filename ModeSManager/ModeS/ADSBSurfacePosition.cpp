#include "ADSBSurfacePosition.h"

ADSBSurfacePosition::ADSBSurfacePosition(const QString& data) : ModeSInfo(data)
{
	// quint64 TC  = (this->ME & (0x1Full << 51)) >> 51;
	quint64 MOV = (this->ME & (0x7Full << 44)) >> 44;
	quint64 S   = (this->ME & (0x01ull << 43)) >> 43;
	quint64 TRK = (this->ME & (0x07ull << 36)) >> 36;
	// quint64 T   = (this->ME & (0x01ull << 35)) >> 35;
	quint64 F   = (this->ME & (0x01ull << 34)) >> 34;
	quint64 LAT = (this->ME & (0x1FFFFull << 17)) >> 17;
	quint64 LON = (this->ME & (0x1FFFFull << 00)) >> 00;

	if (MOV == 0 || (125 <= MOV && MOV <= 127))
		this->ground_speed = -1;
	else if (MOV == 1)
		this->ground_speed = 0;
	else if (2 <= MOV && MOV <= 8)
		this->ground_speed = (double)(MOV - 1) * 0.125;
	else if (9 <= MOV && MOV <= 12)
		this->ground_speed = (double)(MOV - 5) * 0.25;
	else if (13 <= MOV && MOV <= 38)
		this->ground_speed = (double)(MOV - 9) * 0.5;
	else if (39 <= MOV && MOV <= 93)
		this->ground_speed = (double)(MOV - 24) * 1.0;
	else if (94 <= MOV && MOV <= 108)
		this->ground_speed = (double)(MOV - 59) * 2.0;
	else if (109 <= MOV && MOV <= 123)
		this->ground_speed = (double)(MOV - 89) * 5.0;
	else
		this->ground_speed = 175;

	this->ground_track = S ? 360.0 * (double)TRK / 128 : -1;

	ModeSInfo::encodeCPR(F, LAT, LON, false, &this->latitude, &this->longitude);
}
