#include "UserGUI.h"
#include <QpixMap>

UserGUI::UserGUI(QWidget* parent, int UserId, string token)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.errorsLabel->setText(QString::fromStdString(""));

	// Select all cells when click in a cell of a row
	ui.restaurantList->setSelectionBehavior(QTableView::SelectRows);
	ui.dishList->setSelectionBehavior(QTableView::SelectRows);
	ui.orderList->setSelectionBehavior(QTableView::SelectRows);

	// Set session variable
	this->setUserId(UserId);
	this->setToken(token);

	goToOrderTab();
}

UserGUI::~UserGUI()
{
}

/**
* After click on a restaurant, show Restaurant Menu in the other table
*/
void UserGUI::on_restaurantList_cellClicked(int row, int column)
{
	try {
		QString restaurantSelectedId = ui.restaurantList->item(row, restaurantIdCol)->text();
		string restaurantSelectedIdStd = restaurantSelectedId.toStdString();

		// Set session variable
		setRestaurantId(stoi(restaurantSelectedIdStd));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/restaurant/" + restaurantSelectedIdStd },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;

			// Clean all rows
			ui.dishList->setRowCount(0);
			ui.dishList->setItemDelegateForColumn(dishQuantityCol, &delegate);

			for (json dish : j) {
				ui.dishList->insertRow(rowIndex);

				QTableWidgetItem* dishId = new QTableWidgetItem();
				dishId->setText(QString::fromStdString(to_string(dish["DishId"])));
				ui.dishList->setItem(rowIndex, dishIdCol, dishId);
				dishId->setFlags(dishId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishName = new QTableWidgetItem();
				dishName->setText(QString::fromStdString(dish["Name"]));
				ui.dishList->setItem(rowIndex, dishNameCol, dishName);
				dishName->setFlags(dishName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishType = new QTableWidgetItem();
				dishType->setText(QString::fromStdString(getDishType(dish["Type"])));
				ui.dishList->setItem(rowIndex, dishTypeCol, dishType);
				dishType->setFlags(dishType->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishPrice = new QTableWidgetItem();
				dishPrice->setText(QString::fromStdString(to_string(dish["Price"])));
				ui.dishList->setItem(rowIndex, dishPriceCol, dishPrice);
				dishPrice->setFlags(dishPrice->flags() & ~Qt::ItemIsEditable);

				// edit this cell to set dish quantity for the order
				QTableWidgetItem* dishQuantity = new QTableWidgetItem();
				dishQuantity->setText(QString::fromStdString("0"));
				ui.dishList->setItem(rowIndex, dishQuantityCol, dishQuantity);

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

/**
* Submit an order
*/
void UserGUI::on_submitOrderBtn_clicked() {
	try {
		int dishOrdered = 0;
		json dishes = {};

		for (int i = 0; i < ui.dishList->rowCount(); i++) {
			QString dishQuantity = ui.dishList->item(i, dishQuantityCol)->text();
			string dishQuantityStd = dishQuantity.toStdString();
			int dishQuantityInt = stoi(dishQuantityStd);

			if (dishQuantityInt > 0) {
				QString dishId = ui.dishList->item(i, dishIdCol)->text();
				string dishIdStd = dishId.toStdString();

				cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/" + dishIdStd },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (r.status_code == 200) {
					json j = json::parse(r.text);

					j.erase(j.find("Id"));

					json dishType = { {"Dish", j}, {"Quantity", dishQuantityStd} };
					dishes.push_back(dishType);

					dishOrdered++;
				}
			}
		}

		if (dishOrdered > 0) {
			// The total will be calculated by the server
			json order = { {"Total", 0.0}, {"UserId", getUserId()}, {"RestaurantId", getRestaurantId()}, {"Dishes", dishes}, {"Date", currentISO8601TimeUTC()} };

			cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/order/create" },
				cpr::Body{ order.dump() },
				cpr::Header{ { "Content-Type", "application/json" }, {"Authorization", "Bearer " + getToken()} });

			if (r.status_code == 200) {
				goToSummaryTab();
			}
			else {
				QMessageBox::warning(this, "Login", "Generic error. Please login again!");
				logoutUser();
			}
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

/**
* Update user balance and update the data shown
*/
void UserGUI::on_updateBalanceBtn_clicked() {
	try {
		double modifyBalance = ui.balanceSpinBox->value();

		// Check limits QDoubleSpinBox
		if (modifyBalance > -100 && modifyBalance < 100) {

			string modifyBalanceStd = to_string(modifyBalance);

			if (modifyBalance != 0.00) {

				cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/user/update/balance" },
					cpr::Parameters{ {"id", to_string(UserGUI::getUserId())}, {"balance", modifyBalanceStd} },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (r.status_code == 200) {
					boolean result = updateProfileBalance(to_string(UserGUI::getUserId()));

					QMessageBox::information(this, "Balance", "Balance updated successfully!");

					if (result) {
						ui.balanceSpinBox->setValue(0.00);
						ui.errorProfileBalanceLabel->setText(QString::fromStdString("Balance updated successfully!"));
					}
				}
			}
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

/**
* If the user changes his name, the event is captured by this function
* and written in a variable
*/
void UserGUI::on_nameLineEdit_textChanged(QString text) {
	if (firstEditName) {
		firstEditName = false;
	}
	else {
		profileEditedName = true;
	}
}

/**
* If the user changes his surname, the event is captured by this function
* and written in a variable
*/
void UserGUI::on_surnameLineEdit_textChanged(QString text) {
	if (firstEditSurname) {
		firstEditSurname = false;
	}
	else {
		profileEditedSurname = true;
	}
}

/**
* If the user changes his email, the event is captured by this function
* and written in a variable
*/
void UserGUI::on_emailLineEdit_textChanged(QString text) {
	if (firstEditEmail) {
		firstEditEmail = false;
	}
	else {
		profileEditedEmail = true;
	}
}

/**
* If the user changes his phone, the event is captured by this function
* and written in a variable
*/
void UserGUI::on_phoneLineEdit_textChanged(QString text) {
	if (firstEditPhone) {
		firstEditPhone = false;
	}
	else {
		profileEditedPhone = true;
	}
}

/**
* Update user profile (name, email, password, etc.)
*/
void UserGUI::on_updateProfileBtn_clicked() {
	try {
		boolean error = false;
		ui.errorProfileBalanceLabel->setText(QString::fromStdString(""));

		ui.nameErrorLabel->setText(QString::fromStdString(""));
		ui.surnameErrorLabel->setText(QString::fromStdString(""));
		ui.emailErrorLabel->setText(QString::fromStdString(""));
		ui.pswErrorLabel->setText(QString::fromStdString(""));
		ui.phoneErrorLabel->setText(QString::fromStdString(""));
		ui.errorProfileLabel->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_userId) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			if (profileEditedName) {
				string name = ui.nameLineEdit->text().toStdString();

				if (!regex_match(name, regex(R"([a-zA-Z]{2,})"))) {
					ui.nameErrorLabel->setText(QString::fromStdString("Insert a valid name!"));
					error = true;
				}
				else {
					j["Name"] = name;
				}
			}
			if (profileEditedSurname) {
				string surname = ui.surnameLineEdit->text().toStdString();

				if (!regex_match(surname, regex(R"([a-zA-Z]{2,})"))) {
					ui.surnameErrorLabel->setText(QString::fromStdString("Insert a valid surname!"));
					error = true;
				}
				else {
					j["Surname"] = surname;
				}
			}
			if (profileEditedEmail) {
				string email = ui.emailLineEdit->text().toStdString();

				if (!regex_match(email, regex(R"(([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+))"))) {
					ui.emailErrorLabel->setText(QString::fromStdString("Insert a valid email!"));
					error = true;
				}
				else {
					j["Email"] = email;
				}
			}

			string psw = ui.pswLineEdit->text().toStdString();
			if (!regex_match(psw, regex(R"((?=.*[a-z])(?=.*[A-Z])(?=.*\d)[a-zA-Z\d\w\W]{8,})"))) {
				ui.pswErrorLabel->setText(QString::fromStdString("Insert a valid password!"));
				error = true;
			}
			else {
				j["Psw"] = sha256(psw);
			}

			j.erase(j.find("Id"));

			if (profileEditedPhone) {
				string phone = ui.phoneLineEdit->text().toStdString();

				if (!regex_match(phone, regex(R"(\s*(?:\+?(\d{1,3}))?[-. (]*(\d{3})[-. )]*(\d{3})[-. ]*(\d{4})(?: *x(\d+))?\s*)"))) {
					ui.phoneErrorLabel->setText(QString::fromStdString("Insert a valid phone number!"));
					error = true;
				}
				else {
					j["phone"] = phone;
				}
			}

			if (!error) {
				cpr::Response rUpdate = cpr::Put(cpr::Url{ serverUrl + "/user/update" },
					cpr::Body{ j.dump() },
					cpr::Header{ { "Content-Type", "application/json" }, {"Authorization", "Bearer " + getToken()} });

				if (rUpdate.status_code == 200) {
					// Logout the user as he may have changed his password

					resetVariables();
					QMessageBox::information(this, "Login", QString::fromStdString(rUpdate.text) + " - Please, login again!");
					logoutUser();
				}
				else {
					ui.errorProfileLabel->setText(QString::fromStdString("An error occour!"));
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
				ui.restaurantList->insertRow(rowIndex);

				QTableWidgetItem* restaurantId = new QTableWidgetItem();
				restaurantId->setText(QString::fromStdString(to_string(restaurant["RestaurantId"])));
				ui.restaurantList->setItem(rowIndex, restaurantIdCol, restaurantId);
				restaurantId->setFlags(restaurantId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantName = new QTableWidgetItem();
				restaurantName->setText(QString::fromStdString(restaurant["Name"]));
				ui.restaurantList->setItem(rowIndex, restaurantNameCol, restaurantName);
				restaurantName->setFlags(restaurantName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantAddress = new QTableWidgetItem();
				restaurantAddress->setText(QString::fromStdString(restaurant["Address"]));
				ui.restaurantList->setItem(rowIndex, restaurantAddressCol, restaurantAddress);
				restaurantAddress->setFlags(restaurantAddress->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantPhone = new QTableWidgetItem();
				restaurantPhone->setText(QString::fromStdString(restaurant["Phone"]));
				ui.restaurantList->setItem(rowIndex, restaurantPhoneCol, restaurantPhone);
				restaurantPhone->setFlags(restaurantPhone->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* restaurantEmail = new QTableWidgetItem();
				restaurantEmail->setText(QString::fromStdString(restaurant["Email"]));
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
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/user/" + to_string(session_userId) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;

			// Clean all rows
			ui.orderList->setRowCount(0);

			for (json order : j) {
				ui.orderList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["OrderId"])));
				ui.orderList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				// Get restaurant name
				cpr::Response restaurant = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(order["RestaurantId"]) },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (restaurant.status_code == 200) {
					json jRestaurant = json::parse(restaurant.text);

					QTableWidgetItem* orderRestaurantId = new QTableWidgetItem();
					orderRestaurantId->setText(QString::fromStdString(jRestaurant["Name"]));
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
				orderTotal->setText(QString::fromStdString("E. " + to_string(order["Total"])));
				ui.orderList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				// Get order string
				string orderStatusStd = getOrderStatus(order["Status"]);
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
		profileEditedPhone = false;

		ui.UserInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(session_userId) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		json j = json::parse(r.text);

		ui.nameLineEdit->setText(QString::fromStdString(j["Name"]));
		ui.surnameLineEdit->setText(QString::fromStdString(j["Surname"]));
		ui.emailLineEdit->setText(QString::fromStdString(j["Email"]));
		ui.pswLineEdit->setText(QString::fromStdString("********"));
		ui.phoneLineEdit->setText(QString::fromStdString(j["Phone"]));
		ui.dateLineEdit->setText(QString::fromStdString((j["BirthDate"])));

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
	
	ui.countOrderLineEdit->setText(QString::fromStdString(""));
	ui.totalOrderLineEdit->setText(QString::fromStdString(""));
	ui.favouriteRestaurantLineEdit->setText(QString::fromStdString(""));
	ui.bestDishLineEdit->setText(QString::fromStdString(""));

	try {

		cpr::Response pingResponse = cpr::Get(cpr::Url{ serverStatsUrl + "/ping" });

		if (pingResponse.status_code == 200) {
			// Returns the number of orders placed by an users
			cpr::Response countOrder = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/countOrder/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });

			if (countOrder.status_code == 200) {
				json dataCountOrder = json::parse(countOrder.text);

				ui.countOrderLineEdit->setText(QString::fromStdString(to_string(dataCountOrder["count"])));
			}

			// Returns money spent by a customer
			cpr::Response totalOrder = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/totalOrder/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });
						
			if (totalOrder.status_code == 200) {
				json dataTotalOrder = json::parse(totalOrder.text);

				string count = to_string(dataTotalOrder["count"]);
				count.erase(remove(count.begin(), count.end(), '"'), count.end());
				ui.totalOrderLineEdit->setText(QString::fromStdString(count));
			}

			// Returns a customer's favorite restaurant
			cpr::Response favouriteRestaurant = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/favoriteRestaurant/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });

			if (favouriteRestaurant.status_code == 200) {
				json dataFavoriteRestaurant = json::parse(favouriteRestaurant.text);

				string restaurantName = to_string(dataFavoriteRestaurant["name"]);
				restaurantName.erase(remove(restaurantName.begin(), restaurantName.end(), '"'), restaurantName.end());
				ui.favouriteRestaurantLineEdit->setText(QString::fromStdString(restaurantName));
			}

			// Returns the dish most ordered by a user
			cpr::Response bestDish = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/bestDish/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });

			if (bestDish.status_code == 200) {
				json dataBestDish = json::parse(bestDish.text);

				string dishName = to_string(dataBestDish["name"]);
				dishName.erase(remove(dishName.begin(), dishName.end(), '"'), dishName.end());
				ui.bestDishLineEdit->setText(QString::fromStdString(dishName));
			}

			// Returns a graph showing the orders for day of week
			cpr::Response orderfordayofweek = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/orderfordayofweek/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });
						
			if (orderfordayofweek.status_code == 200) {
				json dataOrderfordayofweek = json::parse(orderfordayofweek.text);
				string url = to_string(dataOrderfordayofweek["link"]);
				url.erase(remove(url.begin(), url.end(), '"'), url.end());

				QPixmap pix(url.c_str());
				ui.orderfordayofweek->setPixmap(pix);
			}

			// Returns a graph showing the comparison between the order total
			cpr::Response orderCost = cpr::Get(cpr::Url{ serverStatsUrl + "/userStats/orderCost/" + to_string(session_userId) },
				cpr::Parameters{ {"token", getToken()} });
						
			if (orderCost.status_code == 200) {
				json dataOrderCost = json::parse(orderCost.text);
				string url1 = to_string(dataOrderCost["link"]);

				url1.erase(remove(url1.begin(), url1.end(), '"'), url1.end());
				QPixmap pix1(url1.c_str());
				ui.orderCost->setPixmap(pix1);
			}
		}
		else {
			QMessageBox::warning(this, "Fatal Error", "Stats server is not available. Please try later!");
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
	
}

void UserGUI::logoutUser() {
	resetUserId();
	resetToken();
	resetRestaurantId();

	close();
}

/**
* Update balance and return new value
*/
boolean UserGUI::updateProfileBalance(string userId) {
	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/user/balance/" + userId },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

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
