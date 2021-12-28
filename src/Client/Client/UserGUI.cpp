#include "UserGUI.h"

#include <QMessageBox>
#include <QDialog>

#include "Utils.h"

UserGUI::UserGUI(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.errorsLabel->setText(QString::fromStdString("Work in progress!"));

	// select all cells when click in a cell of a row
	ui.restaurantList->setSelectionBehavior(QTableView::SelectRows);
	ui.dishList->setSelectionBehavior(QTableView::SelectRows);
	ui.orderList->setSelectionBehavior(QTableView::SelectRows);

	goToOrderTab();
}

UserGUI::~UserGUI()
{
}

void UserGUI::on_restaurantList_cellClicked(int row, int column)
{
	QString restaurantSelectedId = ui.restaurantList->item(row, restaurantIdCol)->text();
	string restaurantSelectedIdStd = restaurantSelectedId.toStdString();

	// Set session variable
	UserGUI::setRestaurantId(stoi(restaurantSelectedIdStd));

	cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/restaurant/" + restaurantSelectedIdStd });

	json j = json::parse(r.text);

	// TODO: CHECK RESPONSE CODE TO PROCEDE WITH EXECUTION
	int rowIndex = 0;

	// Clean all rows
	ui.dishList->setRowCount(0);
	ui.dishList->setItemDelegateForColumn(dishQuantityCol, &delegate);

	for (json dish : j) {
		// TODO: check if null, print a default string
		// TODO: verify is exist a better method to do this
		ui.dishList->insertRow(rowIndex);

		QTableWidgetItem* dishId = new QTableWidgetItem();
		dishId->setText(QString::fromStdString(to_string(dish["dishId"])));
		ui.dishList->setItem(rowIndex, dishIdCol, dishId);
		dishId->setFlags(dishId->flags() & ~Qt::ItemIsEditable);

		QTableWidgetItem* dishName = new QTableWidgetItem();
		dishName->setText(QString::fromStdString(dish["name"]));
		ui.dishList->setItem(rowIndex, dishNameCol, dishName);
		dishName->setFlags(dishName->flags() & ~Qt::ItemIsEditable);

		QTableWidgetItem* dishType = new QTableWidgetItem();
		dishType->setText(QString::fromStdString(to_string(dish["type"])));
		ui.dishList->setItem(rowIndex, dishTypeCol, dishType);
		dishType->setFlags(dishType->flags() & ~Qt::ItemIsEditable);

		QTableWidgetItem* dishPrice = new QTableWidgetItem();
		dishPrice->setText(QString::fromStdString(to_string(dish["price"])));
		ui.dishList->setItem(rowIndex, dishPriceCol, dishPrice);
		dishPrice->setFlags(dishPrice->flags() & ~Qt::ItemIsEditable);

		// edit this cell to set dish quantity for the order
		QTableWidgetItem* dishQuantity = new QTableWidgetItem();
		dishQuantity->setText(QString::fromStdString("0"));
		ui.dishList->setItem(rowIndex, dishQuantityCol, dishQuantity);

		rowIndex++;
	}
}

void UserGUI::on_submitOrderBtn_clicked() {
	int dishOrdered = 0;
	json dishes = {};

	for (int i = 0; i < ui.dishList->rowCount(); i++) {
		QString dishQuantity = ui.dishList->item(i, dishQuantityCol)->text();
		string dishQuantityStd = dishQuantity.toStdString();
		int dishQuantityInt = stoi(dishQuantityStd);

		// TODO: check if dish exists
		if (dishQuantityInt > 0) {
			QString dishId = ui.dishList->item(i, dishIdCol)->text();
			string dishIdStd = dishId.toStdString();

			cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/" + dishIdStd });
			json j = json::parse(r.text);

			json dishType = { {"Dish", j}, {"quantity", dishQuantityStd} };
			dishes.push_back(dishType);

			// TODO: calculate order total like server API (also client-side to deny submit of the request)
			dishOrdered++;
		}
	}

	if (dishOrdered > 0) {
		json order = { {"total", 0.0} , {"userId", UserGUI::getUserId()}, {"restaurantId", UserGUI::getRestaurantId()}, {"dishes", dishes} };

		// TODO: check if is possible to submit the order based on the user balance (also client-side)
		cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/order/create" },
			cpr::Body{ order.dump() },
			cpr::Header{ { "Content-Type", "application/json" } });

		// TODO: Clean all window and show windows with summary (create showOrderSummary in UserGUI.h)
		// TODO: show error to user
	}
}

void UserGUI::on_updateBalanceBtn_clicked() {
	// TODO: try-catch
	// TODO: message based to response code
	double modifyBalance = ui.balanceSpinBox->value();

	// Check limits QDoubleSpinBox
	if (modifyBalance > -100 && modifyBalance < 100) {

		string modifyBalanceStd = to_string(modifyBalance);

		if (modifyBalance != 0.00) {

			cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/user/update/balance" },
				cpr::Parameters{ {"id", to_string(UserGUI::getUserId())}, {"balance", modifyBalanceStd} });

			boolean result = updateProfileBalance(to_string(UserGUI::getUserId()));

			QMessageBox::information(this, "Balance", "Balance updated successfully!");

			if (result) {
				ui.balanceSpinBox->setValue(0.00);
				ui.errorProfileBalanceLabel->setText(QString::fromStdString("Balance updated successfully!"));
			}
		}
	}
}

void UserGUI::on_nameLineEdit_textChanged(QString text) {
	if (firstEditName) {
		firstEditName = false;
	}
	else {
		profileEditedName = true;
	}
}

void UserGUI::on_surnameLineEdit_textChanged(QString text) {
	if (firstEditSurname) {
		firstEditSurname = false;
	}
	else {
		profileEditedSurname = true;
	}
}

void UserGUI::on_emailLineEdit_textChanged(QString text) {
	if (firstEditEmail) {
		firstEditEmail = false;
	}
	else {
		profileEditedEmail = true;
	}
}

void UserGUI::on_pswLineEdit_textChanged(QString text) {
	if (firstEditPsw) {
		firstEditPsw = false;
	}
	else {
		profileEditedPsw = true;
	}
}

void UserGUI::on_phoneLineEdit_textChanged(QString text) {
	if (firstEditPhone) {
		firstEditPhone = false;
	}
	else {
		profileEditedPhone = true;
	}
}

void UserGUI::on_updateProfileBtn_clicked() {
	try {
		// TODO: validation check
		ui.errorProfileBalanceLabel->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_userId) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			if (profileEditedName) {
				j["name"] = ui.nameLineEdit->text().toStdString();
			}
			if (profileEditedSurname) {
				j["surname"] = ui.surnameLineEdit->text().toStdString();
			}
			if (profileEditedEmail) {
				j["email"] = ui.emailLineEdit->text().toStdString();
			}
			if (profileEditedPsw) {
				j["psw"] = ui.pswLineEdit->text().toStdString();
			}
			if (profileEditedPhone) {
				j["phone"] = ui.phoneLineEdit->text().toStdString();
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
				ui.errorProfileLabel->setText(QString::fromStdString("An error occour!"));
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

void UserGUI::goToOrderTab() {
	ui.UserInterface->setCurrentWidget(ui.Order);
	ui.restaurantList->setRowCount(0);
	ui.dishList->setRowCount(0);

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/all" });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json restaurant : j) {
				// TODO: check if null, print a default string
				// TODO: verify is exist a better method to do this
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

				QTableWidgetItem* restaurantEmail = new QTableWidgetItem();
				restaurantEmail->setText(QString::fromStdString(restaurant["email"]));
				ui.restaurantList->setItem(rowIndex, restaurantEmailCol, restaurantEmail);
				restaurantEmail->setFlags(restaurantEmail->flags() & ~Qt::ItemIsEditable);

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

void UserGUI::goToSummaryTab() {
	try {
		ui.UserInterface->setCurrentWidget(ui.OrdersSummary);
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/user/" + to_string(session_userId) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;

			// Clean all rows
			ui.orderList->setRowCount(0);

			for (json order : j) {
				ui.orderList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["orderId"])));
				ui.orderList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				// Get restaurant name
				cpr::Response restaurant = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(order["restaurantId"]) });
				if (restaurant.status_code == 200) {
					json jRestaurant = json::parse(restaurant.text);

					QTableWidgetItem* orderRestaurantId = new QTableWidgetItem();
					orderRestaurantId->setText(QString::fromStdString(jRestaurant["name"]));
					ui.orderList->setItem(rowIndex, orderRestaurantCol, orderRestaurantId);
					orderRestaurantId->setFlags(orderRestaurantId->flags() & ~Qt::ItemIsEditable);
				}
				else {
					// Restaurant not found
					QTableWidgetItem* orderRestaurantId = new QTableWidgetItem();
					orderRestaurantId->setText(QString::fromStdString("Unknown"));
					ui.orderList->setItem(rowIndex, orderRestaurantCol, orderRestaurantId);
					orderRestaurantId->setFlags(orderRestaurantId->flags() & ~Qt::ItemIsEditable);
				}

				QTableWidgetItem* orderTotal = new QTableWidgetItem();
				orderTotal->setText(QString::fromStdString("E. " + to_string(order["total"])));
				ui.orderList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				// Get order string
				string orderStatusStd = getOrderStatus(order["status"]);
				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(orderStatusStd));
				ui.orderList->setItem(rowIndex, orderStatusCol, orderStatus);
				orderStatus->setFlags(orderStatus->flags() & ~Qt::ItemIsEditable);

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

void UserGUI::goToProfileTab() {
	try {
		ui.errorProfileBalanceLabel->setText(QString::fromStdString(""));

		profileEditedName = false;
		profileEditedSurname = false;
		profileEditedEmail = false;
		profileEditedPsw = false;
		profileEditedPhone = false;

		ui.UserInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_userId) });

		json j = json::parse(r.text);

		// TODO: check if fields exists
		ui.nameLineEdit->setText(QString::fromStdString(j["name"]));
		ui.surnameLineEdit->setText(QString::fromStdString(j["surname"]));
		ui.emailLineEdit->setText(QString::fromStdString(j["email"]));
		ui.pswLineEdit->setText(QString::fromStdString(j["psw"]));
		ui.phoneLineEdit->setText(QString::fromStdString(j["phone"]));
		ui.dateLineEdit->setText(QString::fromStdString((j["birthDate"])));

		// Update balance lineEdit
		boolean result = updateProfileBalance(to_string(session_userId));

		if (!result) {
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void UserGUI::goToStatsTab() {
	ui.UserInterface->setCurrentWidget(ui.Stats);
}

void UserGUI::logoutUser() {
	resetUserId();
	resetRestaurantId();

	close();
}

boolean UserGUI::updateProfileBalance(string userId) {
	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/balance/" + userId });

		if (r.status_code == 200) {
			ui.balanceCount->setText(QString::fromStdString("E. " + r.text));
			return true;
		}
		else {
			ui.errorProfileBalanceLabel->setText(QString::fromStdString("Error during balance update!"));
			return false;
		}
	}
	catch (...) {
		ui.errorProfileBalanceLabel->setText(QString::fromStdString("Generic error!"));
		return false;
	}
}

// Order window navbar
void UserGUI::on_summaryTab_clicked() {
	UserGUI::goToSummaryTab();
}

void UserGUI::on_profileTab_clicked() {
	UserGUI::goToProfileTab();
}

void UserGUI::on_statsTab_clicked() {
	UserGUI::goToStatsTab();
}

void UserGUI::on_logoutTab_clicked() {
	UserGUI::logoutUser();
}

// Summary window navbar
void UserGUI::on_orderTab_2_clicked() {
	UserGUI::goToOrderTab();
}

void UserGUI::on_profileTab_2_clicked() {
	UserGUI::goToProfileTab();
}

void UserGUI::on_statsTab_2_clicked() {
	UserGUI::goToStatsTab();
}

void UserGUI::on_logoutTab_2_clicked() {
	UserGUI::logoutUser();
}

// Profile window navbar
void UserGUI::on_orderTab_3_clicked() {
	UserGUI::goToOrderTab();
}

void UserGUI::on_summaryTab_3_clicked() {
	UserGUI::goToSummaryTab();
}

void UserGUI::on_statsTab_3_clicked() {
	UserGUI::goToStatsTab();
}

void UserGUI::on_logoutTab_3_clicked() {
	UserGUI::logoutUser();
}

// Stats window navbar
void UserGUI::on_orderTab_4_clicked() {
	UserGUI::goToOrderTab();
}

void UserGUI::on_summaryTab_4_clicked() {
	UserGUI::goToSummaryTab();
}

void UserGUI::on_profileTab_4_clicked() {
	UserGUI::goToProfileTab();
}

void UserGUI::on_logoutTab_4_clicked() {
	UserGUI::logoutUser();
}
