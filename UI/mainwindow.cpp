#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	this->ui->setupUi(this);

	this->web_channel = new QWebChannel(this);
	this->web_channel->registerObject("web_channel", this);
	this->ui->map_viewer->load(QUrl("qrc:/Map/Map.html"));
	this->ui->map_viewer->page()->setWebChannel(this->web_channel);

	this->udp_server = new QUdpSocket(this);
	this->udp_server->bind(QHostAddress(QString("0.0.0.0")), 6666);
	connect(this->udp_server, SIGNAL(readyRead()), this, SLOT(ReadUdp()));

	this->manager = new ModeSManager();
}

MainWindow::~MainWindow()
{
	this->udp_server->abort();
	this->udp_server->close();
	delete this->udp_server;

	this->web_channel->deregisterObject(this);
	delete this->web_channel;

	delete this->ui;
}

void MainWindow::setLabelMousePosition(const QString& lat, const QString& lng)
{
	this->ui->mouse_position->setText(QString("%0, %1").arg(lat).arg(lng));
}

void MainWindow::ReadUdp()
{
	QByteArray buffer;
	buffer.resize(((QUdpSocket*)sender())->bytesAvailable());
	((QUdpSocket*)sender())->readDatagram(buffer.data(), buffer.size());

	if (!buffer.isEmpty())
	{
		try
		{
			auto info = this->manager->AddInfo(buffer);

			if (info->getType() == ModeSInfo::typeEnum::ADSB_AirbornePosition)
			{
				auto ICAO = info->getICAO();
				auto lat = ((ADSBAirbornePosition*)info)->getLatitude();
				auto lng = ((ADSBAirbornePosition*)info)->getLongitude();
				auto time = info->getTime();

				QString cmd = QString("AddPoint(\"%0\", %1, %2, %3)")
					.arg(ICAO)
					.arg(lat)
					.arg(lng)
					.arg(time);
				this->ui->map_viewer->page()->runJavaScript(cmd);
			}
		}
		catch (const char* e)
		{
			qDebug() << e;
			return;
		}
	}
}