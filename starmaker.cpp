#include "starmaker.h"
#include "ui_starmaker.h"
#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <QtGui/QIcon>


StarMaker::StarMaker(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowIcon(QIcon("/Resources/icons/StarMaker32.png"));

	//Menú
	connect(ui.actionGuardar, SIGNAL(triggered()), this, SLOT(convertir()));
	connect(ui.actionPlanetas, SIGNAL(triggered()), this, SLOT(planetas()));
	connect(ui.actionSalir, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionStarMaker, SIGNAL(triggered()), this, SLOT(about()));


	ui.cbHoras_ar->setFocus();//Establece foco en cbHoras_ar

	//Muestra cuadros de textos, la mayoría ya añadidos en el ui en QT Designer
	//ui.ledistancia->setToolTip("Distancia de la estrella en años luz");

	//Estos QLineEdit sólo aceptan números
	//ui.leSegundos_ar->setValidator( new QIntValidator(0, 59, this) );//Esto es para enteros, pero necesito decimales también
	ui.leSegundos_ar->setValidator( new QDoubleValidator(0.0, 59.999, 3, this));//Éste es el bueno, 0 es el fondo, límite 59.999, decimales 3
	ui.leSegundos->setValidator( new QDoubleValidator(0.0, 59.99, 2, this));



	//Valores para cbHoras_Ar (el _Ar es por arco)
	for(unsigned short int i = 0; i< 24; i++)
	{
		ui.cbHoras_ar->addItem(QString::number(i));
	}

	//Valores para cbHoras (de arco)
	for(short int i = -90; i< 91; i++)
	{
		ui.cbHoras->addItem(QString::number(i));
	}
	ui.cbHoras->setCurrentIndex(90);

	for(unsigned short int j = 0; j< 60; j++)
	{
		ui.cbMinutos_ar->addItem(QString::number(j));
		ui.cbMinutos->addItem(QString::number(j));
	}

	//AppMag está seleccionado por defecto.
	ui.rb_appmag->setChecked(true);

	connect(ui.btncrear, SIGNAL(clicked()), this, SLOT(convertir()));//Conectando función convertir para cambio de estado
	connect(ui.btnlimpiar, SIGNAL(clicked()), this, SLOT(limpiar()));//Conectando función limpiar para cambio de estado
	connect(ui.btnsalir, SIGNAL(clicked()), qApp, SLOT(quit()));//Conectando función quit para salir de la aplicación
}

StarMaker::~StarMaker()
{

}

void StarMaker::convertir(){
    
//Función que convierte horas a grados
float grados;//Declaramos variables grados
float grados_ar;

float parsec;

QString SET=""; //Declaramos variable local de caracteres
bool ok; //Declaramos variable tipo booleano

//Ascensión Recta

unsigned short int horas_ar = ui.cbHoras_ar->currentText().toInt(&ok,10);//Declaramos variable horas_ar y de dónde obtener el valor en el GUI, luego se convierte a Entero
unsigned short int minutos_ar = ui.cbMinutos_ar->currentText().toInt(&ok,10);
float segundos_ar = ui.leSegundos_ar->text().toFloat();

//Declinación

short int horas = ui.cbHoras->currentText().toInt(&ok,10);//Declaramos variable horas y de dónde obtener el valor en el GUI. Aquí las horas pueden ser negativas
unsigned short int minutos = ui.cbMinutos->currentText().toInt(&ok,10);
float segundos = ui.leSegundos->text().toFloat();

//Valores útiles
const unsigned long int RSol = 696342;//Radio del Sol en kilómetros


grados = ((horas*3600)+(minutos*60)+(segundos))/(3600);//Convierte horas a grados
grados_ar = (horas_ar*15)+(minutos_ar/4)+(segundos_ar/240);



//Esta parte escribe el archivo

QString nestrella = ui.lenomestrella->text();


QString otrosnombres = ui.leotrosnombres->text();
otrosnombres.replace(QString(","), QString(":"));//Reemplaza las comas por dos puntos

const QString extension =".stc";
QString filename = nestrella+extension;

float radio = ui.leradio->text().toFloat();;




QFile file(filename);
if (!file.open(QIODevice::Append | QIODevice::Text))
        return;

QTextStream out(&file);

if(ui.leotrosnombres->text().isEmpty())
{
out <<  "\""<<nestrella<<"\"";
out << "\n";
} else {
out <<  "\""<<nestrella<<":"<<otrosnombres<<"\"";
out << "\n";
}

out << "{";
out << "\n";
out << "\tRA "<< grados_ar;
out << "\n";
out << "\tDec " << grados;
out << "\n";
if(ui.chkParsec->isChecked())
{
float light_years=ui.ledistancia->text().toFloat();
parsec = light_years * 3.2616;
out <<"\tDistance "<< parsec; //Lectura de LineEdit
} else {
out << "\tDistance "<< this->ui.ledistancia->text(); //Lectura de LineEdit
}
out << "\n";
out << "\tSpectralType "<< "\""<<this->ui.le_tespectral->text()<<"\"";
out << "\n";
if(ui.rb_appmag->isChecked())
{
out <<"\tAppMag "<< this->ui.lemagnitud->text(); //Lectura de LineEdit
out << "\n";
}
if(ui.rb_absmag->isChecked())
{
out <<"\tAbsMag "<< this->ui.lemagnitud->text(); //Lectura de LineEdit
out << "\n";
}


if(ui.leradio->text().isEmpty())
{

} else {
if(ui.chkRadioSol->isChecked())
{
float radioE=radio*RSol;//El porcentaje se divide entre el radio del Sol para obtener el total de radio

out <<"\tRadius "<<radioE<<" # "<<radio<<" Sol Radius"; //
} else {
out <<"\tRadius\t"<<this->ui.leradio->text();
out <<"\n";
}
}

out << "\n";
out << "}";

}

void StarMaker::limpiar(){
    //Función que limpia los LineEdit
    QString SET="";//Declaramos variable local de caracteres SET, aunque de haber querido podrías haberse llamado de otra forma
    
	//Aquí se limpian

	//Función que limpia todos los QLineEdit
	foreach(QLineEdit *widget, this->findChildren<QLineEdit*>()) {
    widget->clear();
	}
	
	ui.cbHoras_ar->setCurrentIndex(0);
	ui.cbMinutos_ar->setCurrentIndex(0);
    //ui.leSegundos_ar->setText(SET);

    ui.cbHoras->setCurrentIndex(90);
    ui.cbMinutos->setCurrentIndex(0);
   
	ui.chkParsec->setChecked(false);
}

void StarMaker::planetas(){
    winplanet = new PlanetMaker(this); //Abre la ventana para crear planetas
    winplanet->show();
}

void StarMaker::about()
{
    QMessageBox::about(this,tr("Acerca de la aplicación"),tr("Un programa sencillo para crear estrellas en Celestia.\nHecho por Rudwolf"));
}
