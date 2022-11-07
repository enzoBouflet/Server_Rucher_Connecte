#include "datastation.h"

DataStation::DataStation()
{

}

int DataStation::getPression() const
{
    return pression;
}

void DataStation::setPression(int newPression)
{
    pression = newPression;
}

double DataStation::getTemperature() const
{
    return temperature;
}

void DataStation::setTemperature(double newTemperature)
{
    temperature = newTemperature;
}

double DataStation::getHumidite() const
{
    return humidite;
}

void DataStation::setHumidite(double newHumidite)
{
    humidite = newHumidite;
}

int DataStation::getVMax() const
{
    return vMax;
}

void DataStation::setVMax(int newVMax)
{
    vMax = newVMax;
}

int DataStation::getVMoy() const
{
    return vMoy;
}

void DataStation::setVMoy(int newVMoy)
{
    vMoy = newVMoy;
}

int DataStation::getAngleDirection() const
{
    return angleDirection;
}

void DataStation::setAngleDirection(int newAngleDirection)
{
    angleDirection = newAngleDirection;
}
