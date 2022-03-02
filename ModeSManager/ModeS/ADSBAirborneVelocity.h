#pragma once
#include "ModeSInfo.h"

/*
 * ADSBAirborneVelocity : 飞机空速
 * Bit        缩写  说明
 * 00-04(5)   TC   类型编码(Type code), 19
 * 05-07(3)   ST   子类型(Sub-type)
 * 08(1)      IC   意图变更标志位(Intent change flag)
 * 09(1)      IFR  IFR 能力标志(IFR capability flag)
 * 10-12(3)   NUC  导航精度类别(Navigation uncertainty category for velocity)
 * ...
 * 35(1)      VSRC 垂直速度来源(Source bit for vertical rate)
 * 36(1)      SVR  垂直速度方向位(Sign bit for vertical rate)
 * 37-45(9)   VR   垂直速度(Vertical rate)
 * 46-47(2)        Reserved
 * 48(1)      SDIF 大气压高度与 GNSS 高度差符号位(Sign bit for GNSS and Baro altitudes difference)
 * 49-55(7)   DALT 大气压高度与 GNSS 高度差值(Difference between GNSS and Baro altitudes)
 *
 * ST = 1或2
 * 13(1)      DEW  东西方向位(Direction for E-W velocity component)
 * 14-23(10)  VEW  东西方向速度(East-West velocity component)
 * 24(1)      DNS  南北方向位(Direction for N-S velocity component)
 * 25-34(10)  VNS  南北方向速度(North-South velocity component)
 *
 * ST = 3或4
 * 13(1)      SH   磁航向状态位(Status bit for magnetic heading)
 * 14-23(10)  HDG  磁航向(Magnetic heading)
 * 24(1)      T    空速类型(Airspeed type)
 * 25-34(10)  AS   空速(Airspeed)
 */
class ADSBAirborneVelocity : public ModeSInfo
{
private:
	double heading;
	double airspeed;
	double vertial_speed;
public:
	ADSBAirborneVelocity(const QString& data);
	virtual ~ADSBAirborneVelocity() {};

	virtual ModeSInfo::typeEnum getType() const { return ModeSInfo::typeEnum::ADSB_AirborneVelocity; };

	double getHeading() const { return this->heading; };
	double getAirspeed() const { return this->airspeed; };
	double getVertialSpeed() const { return this->vertial_speed; };
};

