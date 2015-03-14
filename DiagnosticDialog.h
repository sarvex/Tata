#ifndef DIAGNOSTIC_DIALOG
#define DIAGNOSTIC_DIALOG

#include <QDialog>

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSettings>
#include <QVBoxLayout>

class DiagnosticDialog : public QDialog {
	Q_OBJECT
public:
	explicit DiagnosticDialog(QDialog *parent = 0);
	~DiagnosticDialog ();

	signals:

public slots:
	bool onSidNidUpdate(const QString& result);
	bool onSectorIdUpdate(const QString& result);
	bool onHdrcUpdate(const QString& result);
	bool onCdmaEcioUpdate(const QString& result);
	bool onHdrEcioUpdate(const QString& result);

	bool onCdmaRssiUpdate(const QString& result);
	bool onPnOffsetUpdate(const QString& result);
	bool onWalshCodeUpdate(const QString& result);
	bool onChannelNumberUpdate(const QString& result);
	bool onBandClassUpdate(const QString& result);
	bool onTxPowerUpdate(const QString& result);
	bool onRxPowerUpdate(const QString& result);
	bool onBsPreviousUpdate(const QString& result);
	bool onMsPreviousUpdate(const QString& result);
	bool onPreviousInUseUpdate(const QString& result);
	bool onPacketZoneIdUpdate(const QString& result);
	bool onLastActiveCallStateUpdate(const QString& result);

	bool onHdrRssiUpdate(const QString& result);
	bool onPerUpdate(const QString& result);
	bool onAtStateUpdate(const QString& result);
	bool onDormantStateUpdate(const QString& result);
	bool onActiveStatePnOffsetUpdate(const QString& result);
	bool onNeighborSetPnOffsetUpdate(const QString& result);
	bool onNeighborSetEcioUpdate(const QString& result);

	bool onUpdateTimeout();

protected:
	void showEvent (QShowEvent* event);
	void hideEvent (QHideEvent* event);

private:
	QLineEdit * sid;
	QLineEdit * sectorId;
	QLineEdit * drc;
	QLineEdit * cdmaEcio;
	QLineEdit * hdrEcio;

	QLineEdit * cdmaRssi;
	QLineEdit * cdmaPnOffset;
	QLineEdit * walshCode;
	QLineEdit * channelNumber;
	QLineEdit * bandClass;
	QLineEdit * txPower;
	QLineEdit * rxPower;
	QLineEdit * bsPrevious;
	QLineEdit * msPrevious;
	QLineEdit * previousInUse;
	QLineEdit * packetZoneId;
	QLineEdit * lastActiveCallState;

	QLineEdit * hdrRssi;
	QLineEdit * per;
	QLineEdit * atState;
	QLineEdit * dormantState;
	QLineEdit * activeStatePnOffset;
	QLineEdit * neighborSetPnOffset;
	QLineEdit * neighborSetEcio;

	QTimer * updateTimer;

	QSettings * settings;

	QFormLayout * layout;
};

#endif // DIAGNOSTIC_DIALOG
