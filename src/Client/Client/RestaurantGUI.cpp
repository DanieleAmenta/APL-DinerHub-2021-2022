#include "RestaurantGUI.h"

#include <QMessageBox>
#include <QDialog>

#include "Utils.h"

RestaurantGUI::RestaurantGUI(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersToPrepare);

	ui.ordersToPrepareList->setSelectionBehavior(QTableView::SelectRows);
	ui.ordersToCollectList->setSelectionBehavior(QTableView::SelectRows);
	ui.ordersHistoryList->setSelectionBehavior(QTableView::SelectRows);
	ui.dishesList->setSelectionBehavior(QTableView::SelectRows);

	goToOrdersToPrepareTab();
}

RestaurantGUI::~RestaurantGUI()
{
}

void RestaurantGUI::goToOrdersToPrepareTab() {
	try {
		ui.RestaurantInterface->setCurrentWidget(ui.OrdersToPrepare);
		ui.ordersToPrepareList->setRowCount(0);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "0"} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersToPrepareList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["orderId"])));
				ui.ordersToPrepareList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["userId"]) });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["name"]) + " " + to_string(jUser["surname"]);

					// remove " from name
					userCleanName.erase(remove(userCleanName.begin(), userCleanName.end(), '"'), userCleanName.end());
					userFullName = userCleanName;
				}
				else {
					userFullName = "Unknown";
				}

				QTableWidgetItem* orderUser = new QTableWidgetItem();
				orderUser->setText(QString::fromStdString(userFullName));
				ui.ordersToPrepareList->setItem(rowIndex, orderUserCol, orderUser);
				orderUser->setFlags(orderUser->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderTotal = new QTableWidgetItem();
				orderTotal->setText(QString::fromStdString(to_string(order["total"])));
				ui.ordersToPrepareList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["status"])));
				ui.ordersToPrepareList->setItem(rowIndex, orderStatusCol, orderStatus);
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

void RestaurantGUI::goToOrdersToCollectTab() {
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersToCollect);
	ui.ordersToCollectList->setRowCount(0);

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "1"} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersToCollectList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["orderId"])));
				ui.ordersToCollectList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["userId"]) });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["name"]) + " " + to_string(jUser["surname"]);

					// remove " from name
					userCleanName.erase(remove(userCleanName.begin(), userCleanName.end(), '"'), userCleanName.end());
					userFullName = userCleanName;
				}
				else {
					userFullName = "Unknown";
				}

				QTableWidgetItem* orderUser = new QTableWidgetItem();
				orderUser->setText(QString::fromStdString(userFullName));
				ui.ordersToCollectList->setItem(rowIndex, orderUserCol, orderUser);
				orderUser->setFlags(orderUser->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderTotal = new QTableWidgetItem();
				orderTotal->setText(QString::fromStdString(to_string(order["total"])));
				ui.ordersToCollectList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["status"])));
				ui.ordersToCollectList->setItem(rowIndex, orderStatusCol, orderStatus);
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

void RestaurantGUI::goToOrdersHistoryTab() {
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersHistory);
	ui.ordersHistoryList->setRowCount(0);

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "2"} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersHistoryList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["orderId"])));
				ui.ordersHistoryList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["userId"]) });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["name"]) + " " + to_string(jUser["surname"]);

					// remove " from name
					userCleanName.erase(remove(userCleanName.begin(), userCleanName.end(), '"'), userCleanName.end());
					userFullName = userCleanName;
				}
				else {
					userFullName = "Unknown";
				}

				QTableWidgetItem* orderUser = new QTableWidgetItem();
				orderUser->setText(QString::fromStdString(userFullName));
				ui.ordersHistoryList->setItem(rowIndex, orderUserCol, orderUser);
				orderUser->setFlags(orderUser->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderTotal = new QTableWidgetItem();
				orderTotal->setText(QString::fromStdString(to_string(order["total"])));
				ui.ordersHistoryList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["status"])));
				ui.ordersHistoryList->setItem(rowIndex, orderStatusCol, orderStatus);
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

void RestaurantGUI::goToProfileTab() {
	try {
		ui.errorProfileLabel->setText(QString::fromStdString(""));

		resetVariables();

		ui.RestaurantInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(getRestaurantId()) });

		json j = json::parse(r.text);

		// TODO: check if fields exists
		ui.nameLineEdit->setText(QString::fromStdString(j["name"]));
		ui.addressLineEdit->setText(QString::fromStdString(j["address"]));
		ui.emailLineEdit->setText(QString::fromStdString(j["email"]));
		ui.pswLineEdit->setText(QString::fromStdString(j["psw"]));
		ui.phoneLineEdit->setText(QString::fromStdString(j["phone"]));
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void RestaurantGUI::goToMenuTab() {
	try {
		ui.addDishLabel->setText(QString::fromStdString(""));
		ui.deleteDishLabel->setText(QString::fromStdString(""));

		ui.RestaurantInterface->setCurrentWidget(ui.Menu);
		ui.dishesList->setRowCount(0);

		ui.dishNameLineEdit->setText(QString::fromStdString(""));
		ui.dishTypeBox->setCurrentText(QString::fromStdString(""));
		ui.addDishLabel->setText(QString::fromStdString(""));
		ui.dishPriceSpinBox->setValue(0.00);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/restaurant/" + to_string(getRestaurantId()) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json dish : j) {
				ui.dishesList->insertRow(rowIndex);

				QTableWidgetItem* dishId = new QTableWidgetItem();
				dishId->setText(QString::fromStdString(to_string(dish["dishId"])));
				ui.dishesList->setItem(rowIndex, dishIdCol, dishId);
				dishId->setFlags(dishId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishName = new QTableWidgetItem();
				dishName->setText(QString::fromStdString(dish["name"]));
				ui.dishesList->setItem(rowIndex, dishNameCol, dishName);
				dishName->setFlags(dishName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishType = new QTableWidgetItem();
				dishType->setText(QString::fromStdString(getDishType(dish["type"])));
				ui.dishesList->setItem(rowIndex, dishTypeCol, dishType);
				dishType->setFlags(dishType->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishPrice = new QTableWidgetItem();
				dishPrice->setText(QString::fromStdString(to_string(dish["price"])));
				ui.dishesList->setItem(rowIndex, dishPriceCol, dishPrice);
				dishPrice->setFlags(dishPrice->flags() & ~Qt::ItemIsEditable);

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

void RestaurantGUI::goToStatsTab() {
	ui.RestaurantInterface->setCurrentWidget(ui.Stats);
}

void RestaurantGUI::logoutUser() {
	session_restaurantId = 0;
	session_selectedOrderId = 0;
	session_selectedDishId = 0;

	close();
}

void RestaurantGUI::on_ordersToPrepareList_cellClicked(int row, int column) {
	QString orderSelectedId = ui.ordersToPrepareList->item(row, orderIdCol)->text();
	string orderSelectedIdStd = orderSelectedId.toStdString();

	// Set session variable
	setSelectedOrderId(stoi(orderSelectedIdStd));
}

void RestaurantGUI::on_ordersToCollectList_cellClicked(int row, int column) {
	QString orderSelectedId = ui.ordersToCollectList->item(row, orderIdCol)->text();
	string orderSelectedIdStd = orderSelectedId.toStdString();

	// Set session variable
	setSelectedOrderId(stoi(orderSelectedIdStd));
}

void RestaurantGUI::on_dishesList_cellClicked(int row, int column) {
	QString dishSelectedId = ui.dishesList->item(row, orderIdCol)->text();
	string dishSelectedIdStd = dishSelectedId.toStdString();

	// Set session variable
	setSelectedDishId(stoi(dishSelectedIdStd));
}

void RestaurantGUI::on_readyToCollectBtn_clicked() {
	try {
		string selectedOrderIdStd = to_string(getSelectedOrderId());
		cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/order/update/status" },
			cpr::Parameters{ {"id", selectedOrderIdStd}, {"status", "1"} });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Order", "Order status successfully!");
			resetSelectedOrderId();
			goToOrdersToPrepareTab();
		}
		else {
			ui.readyToCollectLabel->setText(QString::fromStdString(r.text));
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void RestaurantGUI::on_collectedBtn_clicked() {
	try {
		string selectedOrderIdStd = to_string(getSelectedOrderId());
		cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/order/update/status" },
			cpr::Parameters{ {"id", selectedOrderIdStd}, {"status", "2"} });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Order", "Order status successfully!");
			resetSelectedOrderId();
			goToOrdersToCollectTab();
		}
		else {
			ui.readyToCollectLabel->setText(QString::fromStdString(r.text));
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void RestaurantGUI::on_updateProfileBtn_clicked() {
	try {
		// TODO: validation check
		ui.errorProfileLabel->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(getRestaurantId()) });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			if (profileEditedName) {
				j["name"] = ui.nameLineEdit->text().toStdString();
			}
			if (profileEditedAddress) {
				j["address"] = ui.addressLineEdit->text().toStdString();
			}
			if (emailLineEdit) {
				j["email"] = ui.emailLineEdit->text().toStdString();
			}
			if (profileEditedPsw) {
				j["psw"] = ui.pswLineEdit->text().toStdString();
			}
			if (profileEditedPhone) {
				j["phone"] = ui.phoneLineEdit->text().toStdString();
			}

			cpr::Response rUpdate = cpr::Put(cpr::Url{ serverUrl + "/restaurant/update" },
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

void RestaurantGUI::on_addDishBtn_clicked() {
	try {
		ui.deleteDishLabel->setText(QString::fromStdString(""));

		json j;
		j["name"] = ui.dishNameLineEdit->text().toStdString();
		j["type"] = ui.dishTypeBox->currentIndex();
		j["price"] = ui.dishPriceSpinBox->value();
		j["restaurantId"] = to_string(getRestaurantId());

		cpr::Response r;
		// TODO: validation input fields
		// Check if price is positive
		if (j["price"] > 0) {
			r = cpr::Post(cpr::Url{ serverUrl + "/dish/create" },
				cpr::Body{ j.dump() },
				cpr::Header{ { "Content-Type", "application/json" } });
		}

		if (r.status_code == 200) {
			QMessageBox::information(this, "Login", QString::fromStdString("Dish add successfully to menu!"));

			ui.dishNameLineEdit->setText(QString::fromStdString(""));
			ui.dishTypeBox->setCurrentIndex(0);
			ui.dishPriceSpinBox->setValue(0.0);

			goToMenuTab();
		}
		else {
			ui.addDishLabel->setText(QString::fromStdString("An error occour!"));
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void RestaurantGUI::on_deleteDishBtn_clicked() {
	try {
		string selectedDishIdStd = to_string(getSelectedDishId());
		cpr::Response r = cpr::Delete(cpr::Url{ serverUrl + "/dish/delete/" + selectedDishIdStd });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Delete", "Dish delete successfully!");
			ui.dishesList->setRowCount(0);
			ui.deleteDishLabel->setText(QString::fromStdString(r.text));
			resetSelectedDishId();
			goToMenuTab();
		}
		else {
			ui.deleteDishLabel->setText(QString::fromStdString(r.text));
			QMessageBox::warning(this, "Login", "Generic error. Please login again!");
			logoutUser();
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

void RestaurantGUI::on_nameLineEdit_textChanged(QString text) {
	if (firstEditName) {
		firstEditName = false;
	}
	else {
		profileEditedName = true;
	}
}

void RestaurantGUI::on_addressLineEdit_textChanged(QString text) {
	if (firstEditAddress) {
		firstEditAddress = false;
	}
	else {
		profileEditedAddress = true;
	}
}

void RestaurantGUI::on_emailLineEdit_textChanged(QString text) {
	if (firstEditEmail) {
		firstEditEmail = false;
	}
	else {
		profileEditedEmail = true;
	}
}

void RestaurantGUI::on_pswLineEdit_textChanged(QString text) {
	if (firstEditPsw) {
		firstEditPsw = false;
	}
	else {
		profileEditedPsw = true;
	}
}

void RestaurantGUI::on_phoneLineEdit_textChanged(QString text) {
	if (firstEditPhone) {
		firstEditPhone = false;
	}
	else {
		profileEditedPhone = true;
	}
}

// Orders To Prepare window navbar
void RestaurantGUI::on_ordersToCollectBtn_clicked() {
	goToOrdersToCollectTab();
}

void RestaurantGUI::on_ordersHistoryBtn_clicked() {
	goToOrdersHistoryTab();
}

void RestaurantGUI::on_restaurantProfileBtn_clicked() {
	goToProfileTab();
}

void RestaurantGUI::on_restaurantMenuBtn_clicked() {
	goToMenuTab();
}

void RestaurantGUI::on_restaurantStatsBtn_clicked() {
	goToStatsTab();
}

void RestaurantGUI::on_logoutBtn_clicked() {
	logoutUser();
}

// Orders To Collect window navbar
void RestaurantGUI::on_ordersToPrepareBtn_2_clicked() {
	goToOrdersToPrepareTab();
}

void RestaurantGUI::on_ordersHistoryBtn_2_clicked() {
	goToOrdersHistoryTab();
}

void RestaurantGUI::on_restaurantProfileBtn_2_clicked() {
	goToProfileTab();
}

void RestaurantGUI::on_restaurantMenuBtn_2_clicked() {
	goToMenuTab();
}

void RestaurantGUI::on_restaurantStatsBtn_2_clicked() {
	goToStatsTab();
}

void RestaurantGUI::on_logoutBtn_2_clicked() {
	logoutUser();
}

// Orders History window navbar
void RestaurantGUI::on_ordersToPrepareBtn_3_clicked() {
	goToOrdersToPrepareTab();
}

void RestaurantGUI::on_ordersToCollectBtn_3_clicked() {
	goToOrdersToCollectTab();
}

void RestaurantGUI::on_restaurantProfileBtn_3_clicked() {
	goToProfileTab();
}

void RestaurantGUI::on_restaurantMenuBtn_3_clicked() {
	goToMenuTab();
}

void RestaurantGUI::on_restaurantStatsBtn_3_clicked() {
	goToStatsTab();
}

void RestaurantGUI::on_logoutBtn_3_clicked() {
	logoutUser();
}

// Profile window navbar
void RestaurantGUI::on_ordersToPrepareBtn_4_clicked() {
	goToOrdersToPrepareTab();
}

void RestaurantGUI::on_ordersToCollectBtn_4_clicked() {
	goToOrdersToCollectTab();
}

void RestaurantGUI::on_ordersHistoryBtn_4_clicked() {
	goToOrdersHistoryTab();
}

void RestaurantGUI::on_restaurantMenuBtn_4_clicked() {
	goToMenuTab();
}

void RestaurantGUI::on_restaurantStatsBtn_4_clicked() {
	goToStatsTab();
}

void RestaurantGUI::on_logoutBtn_4_clicked() {
	logoutUser();
}

// Restaurant Menu window navbar
void RestaurantGUI::on_ordersToPrepareBtn_5_clicked() {
	goToOrdersToPrepareTab();
}

void RestaurantGUI::on_ordersToCollectBtn_5_clicked() {
	goToOrdersToCollectTab();
}

void RestaurantGUI::on_ordersHistoryBtn_5_clicked() {
	goToOrdersHistoryTab();
}

void RestaurantGUI::on_restaurantProfileBtn_5_clicked() {
	goToProfileTab();
}

void RestaurantGUI::on_restaurantStatsBtn_5_clicked() {
	goToStatsTab();
}

void RestaurantGUI::on_logoutBtn_5_clicked() {
	logoutUser();
}

// Stats window navbar
void RestaurantGUI::on_ordersToPrepareBtn_6_clicked() {
	goToOrdersToPrepareTab();
}

void RestaurantGUI::on_ordersToCollectBtn_6_clicked() {
	goToOrdersToCollectTab();
}

void RestaurantGUI::on_ordersHistoryBtn_6_clicked() {
	goToOrdersHistoryTab();
}

void RestaurantGUI::on_restaurantProfileBtn_6_clicked() {
	goToProfileTab();
}

void RestaurantGUI::on_restaurantMenuBtn_6_clicked() {
	goToMenuTab();
}

void RestaurantGUI::on_logoutBtn_6_clicked() {
	logoutUser();
}