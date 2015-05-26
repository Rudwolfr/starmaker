#include "planetmaker.h"
#include "ui_planetmaker.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtGui/QIcon>

PlanetMaker::PlanetMaker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.btnCrear, SIGNAL(clicked()), this, SLOT(escribir()));//Conectando función limpiar para cambio de estado
	connect(ui.btnLimpiar, SIGNAL(clicked()), this, SLOT(limpiar()));//Conectando función limpiar para cambio de estado
	connect(ui.btnSalir, SIGNAL(clicked()),SLOT(close()));//Conectando función quit para salir de la aplicación
	
	
	//Muestra cuadros de texto
	ui.leNodoAscendente->setToolTip("Cuando la órbita cruza la elíptica (Longitud en grados)");
	ui.leArgPeriastro->setToolTip("Ángulo del nodo hacia el Pericentro (en grados)");

	//Estos QLineEdit sólo aceptan números
	ui.leExcentricidad->setValidator( new QDoubleValidator(0.0, 3.00, 4, this));//Inicio 0, Limite 3, decimales
	ui.leInclinacion->setValidator( new QDoubleValidator(0.0, 359.99, 2, this));//Limite a 359.99
	ui.leNodoAscendente->setValidator( new QDoubleValidator(0.0, 359.99, 2, this));
	ui.leArgPeriastro->setValidator( new QDoubleValidator(0.0, 359.99, 2, this));

	ui.leInclinacionRU->setValidator( new QDoubleValidator(0.0, 359.99, 2, this));
	ui.leNodoAscendenteRU->setValidator( new QDoubleValidator(0.0, 359.99, 2, this));

}

void PlanetMaker::escribir(){

//Declaramos variable y de dónde se obtienen en el GUI, de paso se convierte a Float si es necesario
QString nplaneta = ui.lePlaneta->text();
QString estrellam = ui.leEstrellaMadre->text();
QString textura = ui.leTextura->text();
float radio = ui.leRadio->text().toFloat();;

QString epoca = ui.leEpoca->text();
float periodo = ui.lePeriodo->text().toFloat();
QString semiejem = ui.leSemiejeMayor->text();
QString excentricidad = ui.leExcentricidad->text();
QString inclinacion = ui.leInclinacion->text();
QString NodoAscendente = ui.leNodoAscendente->text();
QString argPeriastro = ui.leArgPeriastro->text();

//Rotación Uniforme
QString periodoRU = ui.lePeriodoRU->text();
QString inclinacionRU = ui.leInclinacionRU->text();
QString nodoascendenteRU = ui.leNodoAscendenteRU->text();


//Valores útiles
const unsigned int RJupiter = 71492;//Radio de Júpiter en kilómetros
float RTierra = 6378.140;

//Nombre de Archivo
const QString extension =".ssc";
QString filename = nplaneta+extension;


//Escribe el archivo
QFile file(filename);
if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

QTextStream out(&file);

out <<"\""<<nplaneta<<"\""<<" "<<"\""<<estrellam<<"\"";
out <<"\n";
out <<"{";
out <<"\n";
out <<"Texture "<<"\""<<textura<<"\"";
out <<"\n";

if(ui.rdRadioJ->isChecked())
{
float radioJ=radio*RJupiter;//El porcentaje se divide entre el radio de Júpiter para obtener el total de radio
out <<"Radius "<<radioJ<<" # "<<radio<<" RJ"; //
} else {
if(ui.rdRadioT->isChecked())
{
float radioT=radio*RTierra;//El porcentaje se divide entre el radio de la Tierra para obtener el total de radio
out <<"Radius "<<radioT<<" # "<<radio<<" RT"; //
} else {
out <<"Radius "<<radio;
}
}

out <<"\n";
out <<"\n";
out <<"EllipticalOrbit";
out <<"\n";
out <<"{";
out <<"\n";

if(ui.leEpoca->text().isEmpty())
{

} else {
out <<"Epoch\t"<<epoca;
out <<"\n";
}

if(ui.chkDias->isChecked())
{
float periodoAU=periodo/365;//El periodo se divide entre 365
out <<"Period\t"<<periodoAU<<" # "<<periodo<<" days"; //; //
} else {
out <<"Period\t"<<periodo;
}
out <<"\n";
out <<"SemiMajorAxis\t"<<semiejem;
out <<"\n";

if(ui.leExcentricidad->text().isEmpty())
{

} else {
out <<"Eccentricity\t"<<excentricidad;
out <<"\n";
}

if(ui.leInclinacion->text().isEmpty())
{

} else {
out <<"Inclination\t"<<inclinacion;
out <<"\n";
}

if(ui.leNodoAscendente->text().isEmpty())
{

} else {
out <<"AscendingNode\t"<<NodoAscendente;
out <<"\n";
out <<"}";
out <<"\n";
out <<"\n";
}


if(ui.leArgPeriastro->text().isEmpty())
{
out <<"}";
out <<"\n";
out <<"\n";
} else {
out <<"ArgOfPericenter\t"<<argPeriastro;
out <<"\n";
out <<"}";
out <<"\n";
out <<"\n";
}
out <<"UniformRotation\t";
out <<"\n";
out <<"{";
out <<"\n";

if(ui.lePeriodoRU->text().isEmpty())
{

} else {
out <<"Period\t"<<periodoRU;//Dividir entre 365 si es por días
out <<"\n";
}

if(ui.leInclinacionRU->text().isEmpty())
{

} else {
out <<"Inclination\t"<<inclinacionRU;
out <<"\n";
}


if(ui.leNodoAscendenteRU->text().isEmpty())
{

} else {
out <<"Ascending Node\t"<<nodoascendenteRU;
out <<"\n";
}
out <<"}";
out <<"\n";
out <<"}";
}


void PlanetMaker::limpiar(){

    //QString SET="";//Declaramos variable local de caracteres SET, aunque de haber querido podrías haberse llamado de otra forma
    
	//Aquí se limpian

	
	//ui.lePlaneta->setText(SET); Así habría sido para cada uno

	//Función que limpia todos los QLineEdit
	foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
    widget->clear();
}

	ui.rdRadioJ->setChecked(true);
	ui.rdRadioT->setChecked(false);
	
	
}

void PlanetMaker::keyPressEvent(QKeyEvent *event)//Función que hace salir de la aplicación al teclear Esc
{
   if (event->key() == Qt::Key_Escape) {
	   this->close();
   }
}

PlanetMaker::~PlanetMaker()
{

}
