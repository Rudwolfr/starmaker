#ifndef STARMAKER_H
#define STARMAKER_H

#include <QMainWindow>
#include "ui_starmaker.h"
#include <planetmaker.h> 

class StarMaker : public QMainWindow
{
	Q_OBJECT

public:
    StarMaker(QWidget *parent = 0);
	~StarMaker();

public slots://Declaramos slots
    void convertir();
	void limpiar();
	void about();
	void planetas();

private:
	Ui::StarMakerClass ui;
	PlanetMaker *winplanet;//Declarando la ventana para planetas
};

#endif // STARMAKER_H
