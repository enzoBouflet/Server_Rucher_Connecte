#ifndef DATARUCHE_H
#define DATARUCHE_H


class DataRuche
{
public:
    DataRuche();
    double getTemperature() const;
    void setTemperature(double newTemperature);

    double getHumidite() const;
    void setHumidite(double newHumidite);

    double getPoid() const;
    void setPoid(double newPoid);

    bool getBascule() const;
    void setBascule(bool newBascule);

    double getBatterie() const;
    void setBatterie(double newBatterie);

    double getLatitude() const;
    void setLatitude(double newLatitude);

    double getLongitude() const;
    void setLongitude(double newLongitude);

    int getId() const;
    void setId(int newId);

private:
    int id;
    double temperature;
    double humidite;
    double poid;
    bool bascule;
    double batterie;
    double latitude;
    double longitude;

};

#endif // DATARUCHE_H
