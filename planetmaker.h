#ifndef PLANETMAKER_H
#define PLANETMAKER_H

#include <QMainWindow>
#include "ui_planetmaker.h"

class PlanetMaker : public QMainWindow
{
	Q_OBJECT

public:
	PlanetMaker(QWidget *parent = 0);
	~PlanetMaker();

private:
	Ui::PlanetMaker ui;

public slots://Declaramos slots
	void escribir();
	void limpiar();

protected:
    void keyPressEvent(QKeyEvent * event);
};

#endif // PLANETMAKER_H
