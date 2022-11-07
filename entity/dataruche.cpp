#include "dataruche.h"

DataRuche::DataRuche()
{

}

double DataRuche::getTemperature() const
{
    return temperature;
}

void DataRuche::setTemperature(double newTemperature)
{
    temperature = newTemperature;
}

double DataRuche::getHumidite() const
{
    return humidite;
}

void DataRuche::setHumidite(double newHumidite)
{
    humidite = newHumidite;
}

double DataRuche::getPoid() const
{
    return poid;
}

void DataRuche::setPoid(double newPoid)
{
    poid = newPoid;
}

bool DataRuche::getBascule() const
{
    return bascule;
}

void DataRuche::setBascule(bool newBascule)
{
    bascule = newBascule;
}

double DataRuche::getBatterie() const
{
    return batterie;
}

void DataRuche::setBatterie(double newBatterie)
{
    batterie = newBatterie;
}

double DataRuche::getLatitude() const
{
    return latitude;
}

void DataRuche::setLatitude(double newLatitude)
{
    latitude = newLatitude;
}

double DataRuche::getLongitude() const
{
    return longitude;
}

void DataRuche::setLongitude(double newLongitude)
{
    longitude = newLongitude;
}

int DataRuche::getId() const
{
    return id;
}

void DataRuche::setId(int newId)
{
    id = newId;
}
