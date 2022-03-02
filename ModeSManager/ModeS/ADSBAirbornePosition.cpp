#include "ADSBAirbornePosition.h"

ADSBAirbornePosition::ADSBAirbornePosition(const QString& data) : ModeSInfo(data)
{
	// quint64 TC  = (this->ME & (0x1Full << 51)) >> 51;
	// quint64 SS  = (this->ME & (0x03ull << 49)) >> 49;
	// quint64 SAF = (this->ME & (0x01ull << 48)) >> 48;
	quint64 ALT = (this->ME & (0x0FFFull << 36)) >> 36;
	// quint64 T   = (this->ME & (0x01ull << 35)) >> 35;
	quint64 F   = (this->ME & (0x01ull << 34)) >> 34;
	quint64 LAT = (this->ME & (0x1FFFFull << 17)) >> 17;
	quint64 LON = (this->ME & (0x1FFFFull << 00)) >> 00;

	quint64 Q   = (ALT & (0x01 << 4)) >> 4;
	if (Q == 1)
	{
		this->altitude = 25 * (((ALT & 0xFE0) >> 1 ) | (ALT & 0x00F)) - 1000;
	}
	else
	{
		quint64 Hm = ((ALT & 0x4) << 5) | ((ALT & 0x1) << 6) | ((ALT & 0x200) >> 4)
			| ((ALT & 0x80) >> 3) | ((ALT & 0x20) >> 2) | ((ALT & 0x10) >> 2) | ((ALT & 0x8) >> 2) | ((ALT & 0x2) >> 1);
		quint64 Hs = ((ALT & 0x400) >> 8) | ((ALT & 0x100) >> 7) | ((ALT & 0x40) >> 6);
		// 格雷码转数字
		for (int i = 8; i > 0; i >>= 1)
		{
			Hm ^= Hm >> i;
			Hs ^= Hs >> i;
		}
		this->altitude = 500 * Hm + 100 * Hs - 1200;
	}

	ModeSInfo::encodeCPR(F, LAT, LON, true, &this->latitude, &this->longitude);
}
