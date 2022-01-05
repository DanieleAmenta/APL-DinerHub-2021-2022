#include "AdminGUI.h"
#include <QpixMap>

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
		boolean error = false;
		json j;
		ui.nameErrorLabel->setText(QString::fromStdString(""));
		ui.addressErrorLabel->setText(QString::fromStdString(""));
		ui.phoneErrorLabel->setText(QString::fromStdString(""));
		ui.emailErrorLabel->setText(QString::fromStdString(""));
		ui.pswErrorLabel->setText(QString::fromStdString(""));

		string name = ui.restaurantName->text().toStdString();
		if (!regex_match(name, regex(R"([a-zA-Z]{2,})"))) {
			ui.nameErrorLabel->setText(QString::fromStdString("Insert a valid name!"));
			error = true;
		}
		else {
			j["name"] = name;
		}

		string address = ui.restaurantAdd->text().toStdString();
		if (!regex_match(address, regex(R"([#.0-9a-zA-Z\s,-]+)"))) {
			ui.addressErrorLabel->setText(QString::fromStdString("Insert a valid address!"));
			error = true;
		}
		else {
			j["address"] = address;
		}

		string phone = ui.restaurantPhone->text().toStdString();
		if (!regex_match(phone, regex(R"(\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*)"))) {
			ui.phoneErrorLabel->setText(QString::fromStdString("Insert a valid phone number!"));
			error = true;
		}
		else {
			j["phone"] = phone;
		}

		string email = ui.restaurantEmail->text().toStdString();
		if (!regex_match(email, regex(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))"))) {
			ui.emailErrorLabel->setText(QString::fromStdString("Insert a valid email!"));
			error = true;
		}
		else {
			j["email"] = email;
		}

		string psw = ui.restaurantPsw->text().toStdString();
		if (!regex_match(psw, regex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,})"))) {
			ui.pswErrorLabel->setText(QString::fromStdString("Insert a valid password!"));
			error = true;
		}
		else {
			j["psw"] = sha256(psw);
		}

		if (!error) {
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
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void AdminGUI::on_updateProfileBtn_clicked() {
	try {
		boolean error = false;

		ui.updateProfileError->setText(QString::fromStdString(""));
		ui.emailProfileErrorLabel->setText(QString::fromStdString(""));
		ui.pswProfileErrorLabel->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_adminId) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			if (profileEditedEmail) {
				string email = ui.emailLineEdit->text().toStdString();

				if (!regex_match(email, regex(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))"))) {
					ui.emailErrorLabel->setText(QString::fromStdString("Insert a valid email!"));
					error = true;
				}
				else {
					j["email"] = email;
				}
			}

			string psw = ui.pswLineEdit->text().toStdString();
			if (!regex_match(psw, regex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,})"))) {
				ui.pswErrorLabel->setText(QString::fromStdString("Insert a valid password!"));
				error = true;
			}
			else {
				j["psw"] = sha256(psw);
			}

			if (!error) {
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

		ui.AdminInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_adminId) });

		json j = json::parse(r.text);

		if (r.status_code == 200) {
			ui.emailLineEdit->setText(QString::fromStdString(j["email"]));
			ui.pswLineEdit->setText(QString::fromStdString("********"));
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
	ui.TotalCustomerlineEdit->setText(QString::fromStdString(""));
	ui.TotalOrderlineEdit->setText(QString::fromStdString(""));
	ui.TotalslineEdit->setText(QString::fromStdString(""));
	ui.dailyOrderslineEdit->setText(QString::fromStdString(""));
	ui.bestCustomerlineEdit->setText(QString::fromStdString(""));
	ui.bestCustomerOfMonthEdit->setText(QString::fromStdString(""));
	ui.topgrossinglineEdit->setText(QString::fromStdString(""));

	try {
		cpr::Response allUsers = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/allUsers"});

		json dataAllUsers = json::parse(allUsers.text);

		if (allUsers.status_code == 200) {
			ui.TotalCustomerlineEdit->setText(QString::fromStdString(to_string(dataAllUsers["count"])));
		}
		
		cpr::Response totalOrder = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/totalOrder" });

		json dataTotalOrder = json::parse(totalOrder.text);

		if (totalOrder.status_code == 200) {
			ui.TotalOrderlineEdit->setText(QString::fromStdString(to_string(dataTotalOrder["count"])));
		}
		
		cpr::Response totals = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/totals" });

		json dataTotals = json::parse(totals.text);

		if (totals.status_code == 200) {
			ui.TotalslineEdit->setText(QString::fromStdString(to_string(dataTotals["total"])));
		}

		cpr::Response dailyOrders = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/dailyOrders" });

		json dataDailyOrders = json::parse(dailyOrders.text);

		if (dailyOrders.status_code == 200) {
			ui.dailyOrderslineEdit->setText(QString::fromStdString(to_string(dataDailyOrders["average"])));
		}
		
		cpr::Response bestCustomer = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/bestCustomer" });

		json dataBestCustomer = json::parse(bestCustomer.text);

		if (bestCustomer.status_code == 200) {
			ui.bestCustomerlineEdit->setText(QString::fromStdString(to_string(dataBestCustomer["name"])));
		}
		
		cpr::Response bestCustomerOfMonth = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/bestCustomerOfMonth" });

		json dataBestCustomerOfMonth = json::parse(bestCustomerOfMonth.text);

		if (bestCustomerOfMonth.status_code == 200) {
			ui.bestCustomerOfMonthEdit->setText(QString::fromStdString(to_string(dataBestCustomerOfMonth["name"])));
		}
		
		cpr::Response topgrossing = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/topgrossing" });

		json dataTopgrossing = json::parse(topgrossing.text);

		if (topgrossing.status_code == 200) {
			ui.topgrossinglineEdit->setText(QString::fromStdString(to_string(dataTopgrossing["name"])));
		}

		cpr::Response plotOrdersForHour = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/plotOrdersForHour"});

		json dataPlotOrdersForHour = json::parse(plotOrdersForHour.text);
		string url = to_string(dataPlotOrdersForHour["link"]);
		url.erase(remove(url.begin(), url.end(), '"'), url.end());
		if (plotOrdersForHour.status_code == 200) {
			QPixmap pix(url.c_str());
			ui.plotOrdersForHour->setPixmap(pix);
		}

		cpr::Response plotAge = cpr::Get(cpr::Url{ serverStatsUrl + "/adminStats/plotAge" });

		json dataPlotAge = json::parse(plotAge.text);
		string url1 = to_string(dataPlotAge["link"]);
		url1.erase(remove(url1.begin(), url1.end(), '"'), url1.end());
		if (plotAge.status_code == 200) {
			QPixmap pix1(url1.c_str());
			ui.plotAge->setPixmap(pix1);
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
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
