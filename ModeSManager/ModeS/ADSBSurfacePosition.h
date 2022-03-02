#pragma once
#include "ModeSInfo.h"

/*
 * ADSBSurfacePosition : 飞机停在地面上的位置
 * Bit        缩写  说明
 * 00-04(5)   TC   类型编码(Type code), 05-08
 * 05-11(7)   MOV  移动速度(Movement)
 * 12(1)      S    地面轨道状态(Status for ground track)
 * 13-19(7)   TRK  地面轨道(Ground track)
 * 20(1)      T    时间(Time)
 * 21(1)      F    CPR格式(CPR Format)
 * 22-38(17)  LAT  编码后的纬度(Encoded latitude)
 * 39-55(17)  LON  编码后的经度(Encoded longitude)
 * S为0时TRK无效
 */
class ADSBSurfacePosition : public ModeSInfo
{
private:
	double ground_speed;
	double ground_track;
	double latitude;
	double longitude;
public:
	ADSBSurfacePosition(const QString& data);
	virtual ~ADSBSurfacePosition() {};

	virtual ModeSInfo::typeEnum getType() const { return ModeSInfo::typeEnum::ADSB_SurfacePosition; };

	double getGroundSpeed() const { return this->ground_speed; };
	double getGroundTrack() const { return this->ground_track; };
	double getLatitude() const { return this->latitude; };
	double getLongitude() const { return this->longitude; };
};

