/*!
* 时间：2021年4月21日 15:41:28
* 事件：成功通过utools的内网穿透，实现了不同局部网间电脑的连接！！
*/

#include <QtCore/QCoreApplication>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <QtNetwork/qhostinfo.h>

#define ADDRESS "cn.utools.club"
#define SERVERPORT 2333

QTcpServer* server;
QTcpSocket* s_client, * client;
//服务端
void Connect();
void Server()
{
	server = new QTcpServer;
	server->listen(QHostAddress::Any, SERVERPORT);
	server->connect(server, &QTcpServer::newConnection, [=] {
		if (server == nullptr) { qDebug("server is nullptr!"); return; }
		s_client = server->nextPendingConnection();
		s_client->write("Hello,this is SunRiver. How are you?");
		s_client->connect(s_client, &QTcpSocket::readyRead, [=] {
			qDebug(s_client->readAll());
			});
		});
}

//客户端
void Client()
{
	client = new QTcpSocket;
	const auto& addresses = QHostInfo::fromName(ADDRESS).addresses();
	if (addresses.isEmpty())
	{
		qDebug("Can't get the ip from name!!");
		return;
	}
	quint16 port = 0;
	qDebug("please input port:");
	QTextStream(stdin) >> port;

	client->connectToHost(addresses.first(), port);
	client->connect(client, &QTcpSocket::readyRead, [=] {
		qDebug("Success: connect to SunRiver's server!");
		qDebug(client->readAll());
		client->write("I'm fine. Thanks!");
		});
}

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	qDebug("Wait for connection...");
	Server();
	//Client();
	return a.exec();
}