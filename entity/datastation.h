#ifndef DATASTATION_H
#define DATASTATION_H
 /*les deux classes Data permettent de stocker les
  *données des trame recu avant de les envoyers a la bdd */

class DataStation
{
public:
    DataStation();
    int getPression() const;
    void setPression(int newPression);

    double getTemperature() const;
    void setTemperature(double newTemperature);

    double getHumidite() const;
    void setHumidite(double newHumidite);

    int getVMax() const;
    void setVMax(int newVMax);

    int getVMoy() const;
    void setVMoy(int newVMoy);

    int getAngleDirection() const;
    void setAngleDirection(int newAngleDirection);

private:
    int pression;
    double temperature;
    double humidite;
    int vMax;
    int vMoy;
    int angleDirection;

};

#endif // DATASTATION_H
