#pragma once
#include <QMainWindow>
#include <QWebChannel>
#include <QUdpSocket>
#include "ModesManager/ModeSManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow* ui;

	QWebChannel* web_channel;
	QUdpSocket* udp_server;

	ModeSManager* manager;

public slots:
	void setLabelMousePosition(const QString& lat, const QString& lng);
	void ReadUdp();
};
