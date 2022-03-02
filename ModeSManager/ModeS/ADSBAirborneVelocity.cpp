#include "ADSBAirborneVelocity.h"
#include <QtMath>

ADSBAirborneVelocity::ADSBAirborneVelocity(const QString& data) : ModeSInfo(data)
{
	// quint64 TC   = (this->ME & (0x1Full << 51)) >> 51;
	quint64 ST   = (this->ME & (0x07ull << 48)) >> 48;
	// quint64 IC   = (this->ME & (0x01ull << 47)) >> 47;
	// quint64 IFR  = (this->ME & (0x01ull << 46)) >> 46;
	// quint64 NUC  = (this->ME & (0x07ull << 43)) >> 43;
	// quint64 VSRC = (this->ME & (0x01ull << 20)) >> 20;
	quint64 SVR  = (this->ME & (0x01ll << 19)) >> 19;
	quint64 VR   = (this->ME & (0x1FFull << 10)) >> 10;
	// quint64 SDIF = (this->ME & (0x01ull << 07)) >> 07;
	// quint64 DALT = (this->ME & (0x7Full << 00)) >> 00;

	this->vertial_speed = (SVR == 0 ? 1 : -1) * 64 * (double)(VR - 1);

	if (ST == 1 || ST == 2)
	{
		quint64 DEW = (this->ME & (0x01ull << 42)) >> 42;
		quint64 VEW = (this->ME & (0x3FFull << 32)) >> 32;
		quint64 DNS = (this->ME & (0x01ull << 31)) >> 31;
		quint64 VNS = (this->ME & (0x3FFull << 21)) >> 21;
		VEW = (ST == 1 ? 1 : 4) * (VEW - 1);
		VNS = (ST == 1 ? 1 : 4) * (VNS - 1);
		this->airspeed = sqrt(VEW * VEW + VNS * VNS);
		this->heading = atan2((DEW == 0 ? 1 : -1) * (double)VEW, (DNS == 0 ? 1 : -1) * (double)VNS) * 180 / M_PI;
		if (this->heading < 0)
			this->heading += 360;
	}
	else // if (ST == 3 || ST == 4)
	{
		// quint64 SH = (this->ME & (0x01ull << 42)) >> 42;
		quint64 HDG = (this->ME & (0x3FFull << 32)) >> 32;
		// quint64 T = (this->ME & (0x01ull << 31)) >> 31;
		quint64 AS = (this->ME & (0x3FFull << 21)) >> 21;
		this->airspeed = (ST == 3 ? 1 : 4) * (AS - 1);
		this->heading = (double)HDG * 360.0 / 1024.0;
	}
}
