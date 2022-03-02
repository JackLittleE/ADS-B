#include "ModeSManager.h"

ModeSManager::~ModeSManager()
{
    for (auto& i : this->all_info)
    {
        for (auto& j : i)
        {
            delete j;
        }
    }
}

const ModeSInfo* ModeSManager::AddInfo(const QString& data)
{
    ModeSInfo* info = ModeSInfo::fromstr(data);
    const QString& ICAO = info->getICAO();
    if (!this->all_info.count(ICAO))
        this->all_info[ICAO] = QVector<ModeSInfo*>();
    this->all_info[ICAO].push_back(info);
    return info;
}
