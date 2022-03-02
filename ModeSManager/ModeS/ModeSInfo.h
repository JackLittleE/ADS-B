#pragma once
#include <QtGlobal>
#include <QString>

/*
 * ModeS 消息格式
 * Bit         缩写  说明
 * 000-004(5)  DF   下行格式(Downlink Format)
 * 005-007(3)  TCA   转发器格式(Transponder capability)
 * 008-031(24) ICAO ICAO地址(ICAO aircraft address)
 * 032-087(56) ME   消息(Message, extended squitter)
 * 088-111(24) PI   校验(Parity/Interrogator ID)
 */
class ModeSInfo
{
protected:
	qint64 time; // 接收到信息的时间

	quint64 DF;
	quint64 TCA;
	QString ICAO;
	quint64 ME;
	// quint64 PI;

	QString meta_data; // 数据

public:
	enum class typeEnum {ADSB_Identification, ADSB_SurfacePosition, ADSB_AirbornePosition, ADSB_AirborneVelocity};

	ModeSInfo(const QString& data);
	virtual ~ModeSInfo() {};

	// 获取消息的类别
	virtual ModeSInfo::typeEnum getType() const = 0;

	qint64 getTime() const { return this->time; };
	quint64 getDF() const { return this->DF; };
	quint64 getTCA() const { return this->TCA; };
	const QString& getICAO() const { return this->ICAO; };
	quint64 getME() const { return this->ME; };
	// quint64 getPI() const { return this->PI; };
	const QString& getMetaData() { return this->meta_data; };

	// ModeS的CRC校验
	static bool CRC(const QString& data);

	// CPR本地解码
	// mode 0 == SurfacePos, 1 == AirbornePos
	static void encodeCPR(quint64 CPR_f, quint64 CPR_lat, quint64 CPR_lon, bool mode, double* lat, double* lon);

	// 从字符串生成数据
	static ModeSInfo* fromstr(const QString& data);
};

