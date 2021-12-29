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

	ui.dateEdit->setDisplayFormat(QString::fromStdString("yyyy.MM.dd"));
}

RegisterGUI::~RegisterGUI()
{
}

void RegisterGUI::on_backToLoginBtn_clicked() {
	close();
}

void RegisterGUI::on_registerBtn_clicked() {
	try {
		json j;
		j["name"] = ui.nameLineEdit->text().toStdString();
		j["surname"] = ui.surnameLineEdit->text().toStdString();
		j["email"] = ui.emailLineEdit->text().toStdString();
		j["psw"] = ui.pswLineEdit->text().toStdString();
		j["phone"] = ui.phoneLineEdit->text().toStdString();
		j["birthDate"] = ui.dateEdit->date().toString(Qt::ISODate).toStdString();

		// TODO: validation input fields
		cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/user/registration" },
			cpr::Body{ j.dump() },
			cpr::Header{ { "Content-Type", "application/json" } });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Login", QString::fromStdString("User create successfully!"));
			close();
		}
		else {
			ui.dateErrorLabel->setText(QString::fromStdString("An error occour!"));
		}
	}
	catch (...) {
		ui.dateErrorLabel->setText(QString::fromStdString("An error occour!"));
	}
}