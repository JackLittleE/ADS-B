#include "ADSBIdentification.h"

ADSBIdentification::ADSBIdentification(const QString& data) : ModeSInfo(data)
{
	quint64 TC = (this->ME & (0x1Full << 51)) >> 51;
	quint64 CA = (this->ME & (0x07ull << 48)) >> 48;

	this->ID = QString();
	quint64 mask = 0x3Full;
	for (int i = 7; i >= 0; i--)
	{
		quint8 c = quint8((ME & (mask << (6 * i))) >> (6 * i));
		this->ID += QChar(c | (1 <= c && c <= 26 ? 0x40 : 0x00));
	}

	if (CA == 0)
	{
		this->category = "	No category information";
		return;
	}
	switch (TC)
	{
		case 1:
			this->category = "Reserved";
			break;
		case 2:
			switch (CA)
			{
				case 1:
					this->category = "Surface emergency vehicle";
					break;
				case 3:
					this->category = "Surface service vehicle";
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					this->category = "Ground obstruction";
					break;
				default:
					this->category = "Reserved";
			}
			break;
		case 3:
			switch (CA)
			{
				case 1:
					this->category = "Glider, sailplane";
					break;
				case 2:
					this->category = "Lighter-than-air";
					break;
				case 3:
					this->category = "Parachutist, skydiver";
					break;
				case 4:
					this->category = "Ultralight, hang-glider, paraglider";
					break;
				case 6:
					this->category = "Unmanned aerial vehicle";
					break;
				case 7:
					this->category = "Space or transatmospheric vehicle";
					break;
				default:
					this->category = "Reserved";
			}
			break;
		case 4:
			switch (CA)
			{
				case 1:
					this->category = "Light (less than 7000 kg)";
					break;
				case 2:
					this->category = "Medium 1 (between 7000 kg and 34000 kg)";
					break;
				case 3:
					this->category = "Medium 2 (between 34000 kg to 136000 kg)";
					break;
				case 4:
					this->category = "High vortex aircraft";
					break;
				case 5:
					this->category = "Heavy (larger than 136000 kg)";
					break;
				case 6:
					this->category = "High performance (>5 g acceleration) and high speed (>400 kt)";
					break;
				case 7:
					this->category = "Rotorcraft";
					break;
				default:
					this->category = "Reserved";
			}
			break;
		default:
			this->category = "Reserved";
	}
}
