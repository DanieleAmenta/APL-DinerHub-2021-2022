#include "AdminGUI.h"

#include <QMessageBox>
#include <QDialog>

#include "Utils.h"

AdminGUI::AdminGUI(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.userList->setSelectionBehavior(QTableView::SelectRows);
	ui.restaurantList->setSelectionBehavior(QTableView::SelectRows);

	goToUserListTab();
}

AdminGUI::~AdminGUI()
{
}

void AdminGUI::on_userList_cellClicked(int row, int column)
{
	QString selectedUserId = ui.userList->item(row, userIdCol)->text();
	string selectedUserIdStd = selectedUserId.toStdString();
	setDeleteUserId(stoi(selectedUserIdStd));
}

void AdminGUI::on_restaurantList_cellClicked(int row, int column)
{
	QString selectedRestaurantId = ui.restaurantList->item(row, restaurantIdCol)->text();
	string selectedUserRestaurantStd = selectedRestaurantId.toStdString();
	setDeleteRestaurantId(stoi(selectedUserRestaurantStd));
}

void AdminGUI::on_deleteUserBtn_clicked() {
	try {
		string selectedUserIdStd = to_string(getDeleteUserId());
		cpr::Response r = cpr::Delete(cpr::Url{ serverUrl + "/user/delete/" + selectedUserIdStd });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Delete", "User delete successfully!");
			ui.userList->setRowCount(0);
			ui.userListErrorLabel->setText(QString::fromStdString(r.text));
			resetDeleteUserId();
			goToUserListTab();
		}
		else {
			ui.userListErrorLabel->setText(QString::fromStdString(r.text));
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::on_deleteRestaurantBtn_clicked() {
	try {
		string selectedRestaurantIdStd = to_string(getDeleteRestaurantId());
		cpr::Response r = cpr::Delete(cpr::Url{ serverUrl + "/restaurant/delete/" + selectedRestaurantIdStd });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Delete", "Restaurant delete successfully!");
			ui.userList->setRowCount(0);
			ui.deleteRestaurantLabel->setText(QString::fromStdString(r.text));
			resetDeleteRestaurantId();
			goToRestaurantListTab();
		}
		else {
			ui.userListErrorLabel->setText(QString::fromStdString(r.text));
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::on_createRestaurantBtn_clicked() {
	try {
		json j;
		j["name"] = ui.restaurantName->text().toStdString();
		j["address"] = ui.restaurantAdd->text().toStdString();
		j["phone"] = ui.restaurantPhone->text().toStdString();
		j["email"] = ui.restaurantEmail->text().toStdString();
		j["psw"] = ui.restaurantPsw->text().toStdString();

		// TODO: validation input fields
		cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/restaurant/create" },
			cpr::Body{ j.dump() },
			cpr::Header{ { "Content-Type", "application/json" } });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Login", QString::fromStdString("Restaurant create successfully!"));
			goToRestaurantListTab();
		}
		else {
			ui.createRestaurantError->setText(QString::fromStdString("An error occour!"));
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::on_updateProfileBtn_clicked() {
	try {
		// TODO: validation check
		ui.updateProfileError->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_adminId) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			if (profileEditedEmail) {
				j["email"] = ui.emailLineEdit->text().toStdString();
			}
			if (profileEditedPsw) {
				j["psw"] = ui.pswLineEdit->text().toStdString();
			}

			cpr::Response rUpdate = cpr::Put(cpr::Url{ serverUrl + "/user/update" },
				cpr::Body{ j.dump() },
				cpr::Header{ { "Content-Type", "application/json" } });

			if (rUpdate.status_code == 200) {
				resetVariables();
				QMessageBox::information(this, "Login", QString::fromStdString(rUpdate.text) + " - Please, login again!");
				logoutUser();
			}
			else {
				ui.updateProfileError->setText(QString::fromStdString("An error occour!"));
			}
		}
		else {
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::on_emailLineEdit_textChanged(QString text) {
	if (firstEditEmail) {
		firstEditEmail = false;
	}
	else {
		profileEditedEmail = true;
	}
}

void AdminGUI::on_pswLineEdit_textChanged(QString text) {
	if (firstEditPsw) {
		firstEditPsw = false;
	}
	else {
		profileEditedPsw = true;
	}
}

void AdminGUI::goToUserListTab() {
	try {
		ui.AdminInterface->setCurrentWidget(ui.UserList);
		ui.userList->setRowCount(0);
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/all" });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json user : j) {
				ui.userList->insertRow(rowIndex);

				QTableWidgetItem* userId = new QTableWidgetItem();
				userId->setText(QString::fromStdString(to_string(user["userId"])));
				ui.userList->setItem(rowIndex, userIdCol, userId);
				userId->setFlags(userId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* userName = new QTableWidgetItem();
				userName->setText(QString::fromStdString(user["name"]));
				ui.userList->setItem(rowIndex, userNameCol, userName);
				userName->setFlags(userName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* userSurname = new QTableWidgetItem();
				userSurname->setText(QString::fromStdString(user["surname"]));
				ui.userList->setItem(rowIndex, userSurnameCol, userSurname);
				userSurname->setFlags(userSurname->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* userPhone = new QTableWidgetItem();
				userPhone->setText(QString::fromStdString(user["phone"]));
				ui.userList->setItem(rowIndex, userPhoneCol, userPhone);
				userPhone->setFlags(userPhone->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* userEmail = new QTableWidgetItem();
				userEmail->setText(QString::fromStdString(user["email"]));
				ui.userList->setItem(rowIndex, userEmailCol, userEmail);
				userEmail->setFlags(userEmail->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* userBalance = new QTableWidgetItem();
				userBalance->setText(QString::fromStdString(to_string(user["balance"])));
				ui.userList->setItem(rowIndex, userBalanceCol, userBalance);
				userBalance->setFlags(userBalance->flags() & ~Qt::ItemIsEditable);

				rowIndex++;
			}
		}
		else {
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::goToRestaurantListTab() {
	ui.AdminInterface->setCurrentWidget(ui.RestaurantList);
	ui.restaurantList->setRowCount(0);

	ui.restaurantName->setText(QString::fromStdString(""));
	ui.restaurantAdd->setText(QString::fromStdString(""));
	ui.restaurantPhone->setText(QString::fromStdString(""));
	ui.restaurantEmail->setText(QString::fromStdString(""));
	ui.restaurantPsw->setText(QString::fromStdString(""));

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/all" });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json restaurant : j) {
				ui.restaurantList->insertRow(rowIndex);

				QTableWidgetItem* restaurantId = new QTableWidgetItem();
				restaurantId->setText(QString::fromStdString(to_string(restaurant["restaurantId"])));
				ui.restaurantList->setItem(rowIndex, restaurantIdCol, restaurantId);
				restaurantId->setFlags(restaurantId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantName = new QTableWidgetItem();
				restaurantName->setText(QString::fromStdString(restaurant["name"]));
				ui.restaurantList->setItem(rowIndex, restaurantNameCol, restaurantName);
				restaurantName->setFlags(restaurantName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantAddress = new QTableWidgetItem();
				restaurantAddress->setText(QString::fromStdString(restaurant["address"]));
				ui.restaurantList->setItem(rowIndex, restaurantAddressCol, restaurantAddress);
				restaurantAddress->setFlags(restaurantAddress->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantPhone = new QTableWidgetItem();
				restaurantPhone->setText(QString::fromStdString(restaurant["phone"]));
				ui.restaurantList->setItem(rowIndex, restaurantPhoneCol, restaurantPhone);
				restaurantPhone->setFlags(restaurantPhone->flags() & ~Qt::ItemIsEditable);

				rowIndex++;
			}
		}
		else {
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::goToProfileTab() {
	ui.AdminInterface->setCurrentWidget(ui.Profile);

	try {
		ui.updateProfileError->setText(QString::fromStdString(""));

		profileEditedEmail = false;
		profileEditedPsw = false;

		ui.AdminInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_adminId) });

		json j = json::parse(r.text);

		if (r.status_code == 200) {
			// TODO: check if fields exist
			ui.emailLineEdit->setText(QString::fromStdString(j["email"]));
			ui.pswLineEdit->setText(QString::fromStdString(j["psw"]));
		}
		else {
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::goToStatsTab() {
	ui.AdminInterface->setCurrentWidget(ui.Stats);
}

void AdminGUI::logoutUser() {
	resetAdminId();
	resetDeleteUserId();
	resetDeleteRestaurantId();

	close();
}

// User List window navbar
void AdminGUI::on_restaurantListTab_clicked() {
	goToRestaurantListTab();
}

void AdminGUI::on_profileTab_clicked() {
	goToProfileTab();
}

void AdminGUI::on_statsTab_clicked() {
	goToStatsTab();
}

void AdminGUI::on_logoutTab_clicked() {
	logoutUser();
}

// Restaurant List window navbar
void AdminGUI::on_userListTab_2_clicked() {
	goToUserListTab();
}

void AdminGUI::on_profileTab_2_clicked() {
	goToProfileTab();
}

void AdminGUI::on_statsTab_2_clicked() {
	goToStatsTab();
}

void AdminGUI::on_logoutTab_2_clicked() {
	logoutUser();
}

// Profile window navbar
void AdminGUI::on_userListTab_3_clicked() {
	goToUserListTab();
}

void AdminGUI::on_restaurantListTab_3_clicked() {
	goToRestaurantListTab();
}

void AdminGUI::on_statsTab_3_clicked() {
	goToStatsTab();
}

void AdminGUI::on_logoutTab_3_clicked() {
	logoutUser();
}

// Stats window navbar
void AdminGUI::on_userListTab_4_clicked() {
	goToUserListTab();
}

void AdminGUI::on_restaurantListTab_4_clicked() {
	goToRestaurantListTab();
}

void AdminGUI::on_profileTab_4_clicked() {
	goToProfileTab();
}

void AdminGUI::on_logoutTab_4_clicked() {
	logoutUser();
}
