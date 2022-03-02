#pragma once
#include "ModeSInfo.h"

/*
 * ADSBSurfacePosition : 飞机空中位置
 * Bit        缩写  说明
 * 00-04(5)   TC   类型编码(Type code), 09-18, 20-22
 * 05-06(2)   SS   监控状态(Surveillance status)
 * 07(1)      SAF  单天线标志(Single antenna flag)
 * 08-19(12)  ALT  编码后的高度(Encoded altitude)
 * 20(1)      T    时间(Time)
 * 21(1)      F    CPR格式(CPR Format)
 * 22-38(17)  LAT  编码后的纬度(Encoded latitude)
 * 39-55(17)  LON  编码后的经度(Encoded longitude)
 */
class ADSBAirbornePosition : public ModeSInfo
{
private:
	quint64 altitude;
	double latitude;
	double longitude;
public:
	ADSBAirbornePosition(const QString& data);
	virtual ~ADSBAirbornePosition() {};

	virtual ModeSInfo::typeEnum getType() const { return ModeSInfo::typeEnum::ADSB_AirbornePosition; };

	quint64 getAltitude() const { return this->altitude; };
	double getLatitude() const { return this->latitude; };
	double getLongitude() const { return this->longitude; };
};

