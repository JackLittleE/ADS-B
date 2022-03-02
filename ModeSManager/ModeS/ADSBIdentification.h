#pragma once
#include "ModeSInfo.h"

/*
 * ADSBIdentification : 飞机身份和类别信息
 * Bit        缩写  说明
 * 00-04(5)   TC   类型编码(Type code), 01-04
 * 05-07(3)   CA   飞机类别(Aircraft category)
 * 08-55(48)  ID   航班号
 * TC和CA组成尾流类别(Wake vortex category), 不知道和飞机种类有什么关系
 */
class ADSBIdentification : public ModeSInfo
{
private:
	QString ID;
	QString category;
public:
	ADSBIdentification(const QString& data);
	virtual ~ADSBIdentification() {};

	virtual ModeSInfo::typeEnum getType() const { return ModeSInfo::typeEnum::ADSB_Identification; };

	const QString& getID() const { return this->ID; };
	const QString& getCategory() const { return this->category; };
};

