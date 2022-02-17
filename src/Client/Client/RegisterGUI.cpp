#include "RegisterGUI.h"

RegisterGUI::RegisterGUI(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.nameErrorLabel->setText(QString::fromStdString(""));
	ui.surnameErrorLabel->setText(QString::fromStdString(""));
	ui.emailErrorLabel->setText(QString::fromStdString(""));
	ui.pswErrorLabel->setText(QString::fromStdString(""));
	ui.phoneErrorLabel->setText(QString::fromStdString(""));
	ui.dateErrorLabel->setText(QString::fromStdString(""));

	ui.dateEdit->setDisplayFormat(QString::fromStdString("yyyy.MM.dd"));
}

RegisterGUI::~RegisterGUI()
{
}

/**
* Back to login interface
*/
void RegisterGUI::on_backToLoginBtn_clicked() {
	close();
}

/**
* Register a new user
* Registering a restaurant requires admin action through adminGUI
* Registering an admin requires admin action inside MongoDB panel
*/
void RegisterGUI::on_registerBtn_clicked() {
	try {
		ui.nameErrorLabel->setText(QString::fromStdString(""));
		ui.surnameErrorLabel->setText(QString::fromStdString(""));
		ui.emailErrorLabel->setText(QString::fromStdString(""));
		ui.pswErrorLabel->setText(QString::fromStdString(""));
		ui.phoneErrorLabel->setText(QString::fromStdString(""));
		ui.dateErrorLabel->setText(QString::fromStdString(""));

		boolean error = false;
		json j;

		string name = ui.nameLineEdit->text().toStdString();
		if (!regex_match(name, regex(R"([a-zA-Z]{2,})"))) {
			ui.nameErrorLabel->setText(QString::fromStdString("Insert a valid name!"));
			error = true;
		}
		else {
			j["name"] = name;
		}

		string surname = ui.surnameLineEdit->text().toStdString();
		if (!regex_match(surname, regex(R"([a-zA-Z]{2,})"))) {
			ui.surnameErrorLabel->setText(QString::fromStdString("Insert a valid surname!"));
			error = true;
		}
		else {
			j["surname"] = surname;
		}

		string email = ui.emailLineEdit->text().toStdString();
		if (!regex_match(email, regex(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))"))) {
			ui.emailErrorLabel->setText(QString::fromStdString("Insert a valid email!"));
			error = true;
		}
		else {
			j["email"] = email;
		}

		string psw = ui.pswLineEdit->text().toStdString();
		if (!regex_match(psw, regex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,})"))) {
			ui.pswErrorLabel->setText(QString::fromStdString("Insert a valid password!"));
			error = true;
		}
		else {
			j["psw"] = sha256(psw);
		}		

		string phone = ui.phoneLineEdit->text().toStdString();
		if (!regex_match(phone, regex(R"(\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*)"))) {
			ui.phoneErrorLabel->setText(QString::fromStdString("Inser a valid phone number!"));
			error = true;
		}
		else {
			j["phone"] = phone;
		}

		j["birthDate"] = ui.dateEdit->date().toString(Qt::ISODate).toStdString();

		if (!error) {
			cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/user/registration" },
				cpr::Body{ j.dump() },
				cpr::Header{ { "Content-Type", "application/json" } });

			if (r.status_code == 200) {
				QMessageBox::information(this, "Login", QString::fromStdString("User create successfully!"));
				close();
			}
			else {
				ui.dateErrorLabel->setText(QString::fromStdString(r.text));
			}
		}
	}
	catch (...) {
		ui.dateErrorLabel->setText(QString::fromStdString("An error occour!"));
	}
}