#ifndef SINGLE_APPLICATION
#define SINGLE_APPLICATION

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>

class SingleApplication : public QApplication {
	Q_OBJECT
public:
	SingleApplication(int &argc, char *argv[], const QString& uniqueKey);
	~SingleApplication ();

	bool isRunning();
	bool sendMessage(const QString& message);

public slots:
	bool receiveMessage();

signals:
	bool messageAvailable(const QString& message);

private:
	bool running;
	QString uniqueKey;
	QSharedMemory sharedMemory;
	QLocalServer *localServer;

	static const int timeout = 1000;
};
#endif // SINGLE_APPLICATION
