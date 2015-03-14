#include "SystemInformationDialog.h"

#include "Defines.h"
#include "DeamonSetting.h"

#include <QIcon>

SystemInformationDialog::SystemInformationDialog(QDialog *parent) : QDialog(parent) {
	this->setWindowFlags(Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
	this->setWindowIcon(QIcon(":/ttslMax.png"));
	this->setWindowTitle (SYSTEM_INFORMATION_LABEL);

	this->layout = new QFormLayout;
	this->layout->setLabelAlignment (Qt::AlignRight);

	this->operatingSystemName = new QLabel(DeamonSetting::getInstance()->getOperatingSystemName(), this);
	this->layout->addRow (OPERATING_SYSTEM_NAME_LABEL, this->operatingSystemName);

	this->operatingSystemVersion = new QLabel(DeamonSetting::getInstance()->getOperatingSystemVersion(), this);
	this->layout->addRow (OPERATING_SYSTEM_VERSION_LABEL, this->operatingSystemVersion);

	this->processor = new QLabel(DeamonSetting::getInstance()->getProcessor(), this);
	this->layout->addRow (PROCESSOR_LABEL, this->processor);

	this->physicalMemory = new QLabel(DeamonSetting::getInstance()->getPhysicalMemory(), this);
	this->layout->addRow (PHYSICAL_MEMORY_LABEL, this->physicalMemory);

	this->virtualMemory = new QLabel(DeamonSetting::getInstance()->getVirtualMemory(), this);
	this->layout->addRow (VIRTUAL_MEMORY_LABEL, this->virtualMemory);

	this->manufacturer = new QLabel(DeamonSetting::getInstance()->getManufacturer(), this);
	this->layout->addRow (MANUFACTURER_LABEL, this->manufacturer);

	this->setLayout (this->layout);
}

SystemInformationDialog::~SystemInformationDialog () {

}
