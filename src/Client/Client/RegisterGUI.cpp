#include "RegisterGUI.h"

#include <QMessageBox>
#include <QDialog>

#include "Utils.h"

RegisterGUI::RegisterGUI(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.nameErrorLabel->setText(QString::fromStdString(""));
	ui.surnameErrorLabel->setText(QString::fromStdString(""));
	ui.emaiLErrorLabel->setText(QString::fromStdString(""));
	ui.pswErrorLabel->setText(QString::fromStdString(""));
	ui.phoneErrorLabel->setText(QString::fromStdString(""));
	ui.dateErrorLabel->setText(QString::fromStdString(""));
}

RegisterGUI::~RegisterGUI()
{
}

void RegisterGUI::on_backToLoginBtn_clicked() {

}

void RegisterGUI::on_registerBtn_clicked() {

}