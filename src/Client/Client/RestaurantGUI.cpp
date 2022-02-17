#include "RestaurantGUI.h"

RestaurantGUI::RestaurantGUI(QWidget* parent, int RestaurantId, string token)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersToPrepare);

	ui.ordersToPrepareList->setSelectionBehavior(QTableView::SelectRows);
	ui.ordersToCollectList->setSelectionBehavior(QTableView::SelectRows);
	ui.ordersHistoryList->setSelectionBehavior(QTableView::SelectRows);
	ui.dishesList->setSelectionBehavior(QTableView::SelectRows);

	// Set session variable
	this->setRestaurantId(RestaurantId);
	this->setToken(token);

	goToOrdersToPrepareTab();
}

RestaurantGUI::~RestaurantGUI()
{
}

/**
* Go to OrdersToPrepare Tab and show all data
*/
void RestaurantGUI::goToOrdersToPrepareTab() {
	try {
		ui.RestaurantInterface->setCurrentWidget(ui.OrdersToPrepare);
		ui.ordersToPrepareList->setRowCount(0);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "0"} },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersToPrepareList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["OrderId"])));
				ui.ordersToPrepareList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["UserId"]) },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["Name"]) + " " + to_string(jUser["Surname"]);

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
				orderTotal->setText(QString::fromStdString(to_string(order["Total"])));
				ui.ordersToPrepareList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["Status"])));
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

/**
* Go to OrdersToCollect Tab and show all data
*/
void RestaurantGUI::goToOrdersToCollectTab() {
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersToCollect);
	ui.ordersToCollectList->setRowCount(0);

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "1"} },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersToCollectList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["OrderId"])));
				ui.ordersToCollectList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["UserId"]) },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["Name"]) + " " + to_string(jUser["Surname"]);

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
				orderTotal->setText(QString::fromStdString(to_string(order["Total"])));
				ui.ordersToCollectList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["Status"])));
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

/**
* Go to OrderHistory Tab and show all data about old orders
*/
void RestaurantGUI::goToOrdersHistoryTab() {
	ui.RestaurantInterface->setCurrentWidget(ui.OrdersHistory);
	ui.ordersHistoryList->setRowCount(0);

	try {
		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/order/restaurant/status" },
			cpr::Parameters{ {"id", to_string(getRestaurantId())}, {"status", "2"} },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json order : j) {
				ui.ordersHistoryList->insertRow(rowIndex);

				QTableWidgetItem* orderId = new QTableWidgetItem();
				orderId->setText(QString::fromStdString(to_string(order["OrderId"])));
				ui.ordersHistoryList->setItem(rowIndex, orderIdCol, orderId);
				orderId->setFlags(orderId->flags() & ~Qt::ItemIsEditable);

				string userFullName = "";
				cpr::Response rUser = cpr::Get(cpr::Url{ serverUrl + "/user/" + to_string(order["UserId"]) },
					cpr::Header{ {"Authorization", "Bearer " + getToken()} });

				if (rUser.status_code == 200) {
					json jUser = json::parse(rUser.text);

					string userCleanName = to_string(jUser["Name"]) + " " + to_string(jUser["Surname"]);

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
				orderTotal->setText(QString::fromStdString(to_string(order["Total"])));
				ui.ordersHistoryList->setItem(rowIndex, orderTotalCol, orderTotal);
				orderTotal->setFlags(orderTotal->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* orderStatus = new QTableWidgetItem();
				orderStatus->setText(QString::fromStdString(getOrderStatus(order["Status"])));
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
		ui.nameErrorLabel->setText(QString::fromStdString(""));
		ui.addressErrorLabel->setText(QString::fromStdString(""));
		ui.emailErrorLabel->setText(QString::fromStdString(""));
		ui.pswErrorLabel->setText(QString::fromStdString(""));
		ui.phoneErrorLabel->setText(QString::fromStdString(""));

		resetVariables();

		ui.RestaurantInterface->setCurrentWidget(ui.Profile);

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(getRestaurantId()) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		json j = json::parse(r.text);

		ui.nameLineEdit->setText(QString::fromStdString(j["Name"]));
		ui.addressLineEdit->setText(QString::fromStdString(j["Address"]));
		ui.emailLineEdit->setText(QString::fromStdString(j["Email"]));
		ui.pswLineEdit->setText(QString::fromStdString("********"));
		ui.phoneLineEdit->setText(QString::fromStdString(j["Phone"]));
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

/**
* Go to Menu Tab and show all data
* This tab allows you to modify the menu and add new dishes
*/
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

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/dish/restaurant/" + to_string(getRestaurantId()) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);

			int rowIndex = 0;
			for (json dish : j) {
				ui.dishesList->insertRow(rowIndex);

				QTableWidgetItem* dishId = new QTableWidgetItem();
				dishId->setText(QString::fromStdString(to_string(dish["DishId"])));
				ui.dishesList->setItem(rowIndex, dishIdCol, dishId);
				dishId->setFlags(dishId->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishName = new QTableWidgetItem();
				dishName->setText(QString::fromStdString(dish["Name"]));
				ui.dishesList->setItem(rowIndex, dishNameCol, dishName);
				dishName->setFlags(dishName->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishType = new QTableWidgetItem();
				dishType->setText(QString::fromStdString(getDishType(dish["Type"])));
				ui.dishesList->setItem(rowIndex, dishTypeCol, dishType);
				dishType->setFlags(dishType->flags() & ~Qt::ItemIsEditable);

				QTableWidgetItem* dishPrice = new QTableWidgetItem();
				dishPrice->setText(QString::fromStdString(to_string(dish["Price"])));
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

	ui.orderReceivedLineEdit->setText(QString::fromStdString(""));
	ui.totalOrderLineEdit->setText(QString::fromStdString(""));
	ui.bestCustomerLineEdit->setText(QString::fromStdString(""));
	ui.customerLineEdit->setText(QString::fromStdString(""));
	ui.bestDishLineEdit->setText(QString::fromStdString(""));

	try {

		cpr::Response pingResponse = cpr::Get(cpr::Url{ serverStatsUrl + "/ping" });

		if (pingResponse.status_code == 200) {
			// Returns the number of orders receveid by a restaurant
			cpr::Response orderReceived = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/orderReceived/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (orderReceived.status_code == 200) {
				json dataOrderReceived = json::parse(orderReceived.text);

				ui.orderReceivedLineEdit->setText(QString::fromStdString(to_string(dataOrderReceived["count"])));
			}

			// Returns the total revenue of a restaurant
			cpr::Response totalOrder = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/totalOrder/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (totalOrder.status_code == 200) {
				json dataTotalOrder = json::parse(totalOrder.text);

				string total = to_string(dataTotalOrder["totalOrder"]);
				total.erase(remove(total.begin(), total.end(), '"'), total.end());
				ui.totalOrderLineEdit->setText(QString::fromStdString(total));
			}

			// Returns the user who spent the most money in a restaurant
			cpr::Response bestCustomer = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/bestCustomer/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (totalOrder.status_code == 200) {
				json dataBestCustomer = json::parse(bestCustomer.text);

				string bestCustomer = to_string(dataBestCustomer["Name"]);
				bestCustomer.erase(remove(bestCustomer.begin(), bestCustomer.end(), '"'), bestCustomer.end());
				ui.bestCustomerLineEdit->setText(QString::fromStdString(bestCustomer));
			}

			// Returns the number of customers who placed their order in a restaurant
			cpr::Response customer = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/customer/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (customer.status_code == 200) {
				json dataCustomer = json::parse(customer.text);

				ui.customerLineEdit->setText(QString::fromStdString(to_string(dataCustomer["Customers"])));
			}

			// Returns the the best-selling dish of a restaurant
			cpr::Response bestDish = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/bestDish/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (customer.status_code == 200) {
				json dataBestDish = json::parse(bestDish.text);

				string bestDish = to_string(dataBestDish["name"]);
				bestDish.erase(remove(bestDish.begin(), bestDish.end(), '"'), bestDish.end());
				ui.bestDishLineEdit->setText(QString::fromStdString(bestDish));
			}

			// Returns a graph showing the time slot with the most receipts for a restaurant
			cpr::Response plotOrdersForHour = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/plotOrderForHour/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });
						
			if (plotOrdersForHour.status_code == 200) {
				json dataPlotOrdersForHour = json::parse(plotOrdersForHour.text);
				string url = to_string(dataPlotOrdersForHour["link"]);
				url.erase(remove(url.begin(), url.end(), '"'), url.end());

				QPixmap pix(url.c_str());
				ui.plotOrdersForHourRestaurant->setPixmap(pix);
			}

			// Returns a graph showing the average age of customers of a restaurant
			cpr::Response plotAge = cpr::Get(cpr::Url{ serverStatsUrl + "/restaurantStats/plotAge/" + to_string(session_restaurantId) },
				cpr::Parameters{ {"token", getToken()} });

			if (plotAge.status_code == 200) {
				json dataPlotAge = json::parse(plotAge.text);
				string url1 = to_string(dataPlotAge["link"]);
				url1.erase(remove(url1.begin(), url1.end(), '"'), url1.end());

				QPixmap pix1(url1.c_str());
				ui.plotAgeRestaurant->setPixmap(pix1);
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

void RestaurantGUI::logoutUser() {
	session_restaurantId = 0;
	session_selectedOrderId = 0;
	session_selectedDishId = 0;

	close();
}

/**
* Save the selected Order ID in a variable
*/
void RestaurantGUI::on_ordersToPrepareList_cellClicked(int row, int column) {
	QString orderSelectedId = ui.ordersToPrepareList->item(row, orderIdCol)->text();
	string orderSelectedIdStd = orderSelectedId.toStdString();

	// Set session variable
	setSelectedOrderId(stoi(orderSelectedIdStd));
}

/**
* Save the selected Order ID in a variable
*/
void RestaurantGUI::on_ordersToCollectList_cellClicked(int row, int column) {
	QString orderSelectedId = ui.ordersToCollectList->item(row, orderIdCol)->text();
	string orderSelectedIdStd = orderSelectedId.toStdString();

	// Set session variable
	setSelectedOrderId(stoi(orderSelectedIdStd));
}

/**
* Save the selected Dish ID in a variable
*/
void RestaurantGUI::on_dishesList_cellClicked(int row, int column) {
	QString dishSelectedId = ui.dishesList->item(row, orderIdCol)->text();
	string dishSelectedIdStd = dishSelectedId.toStdString();

	// Set session variable
	setSelectedDishId(stoi(dishSelectedIdStd));
}

/**
* Change the order status to "ReadyToPickup"
*/
void RestaurantGUI::on_readyToCollectBtn_clicked() {
	try {
		string selectedOrderIdStd = to_string(getSelectedOrderId());
		cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/order/update/status" },
			cpr::Parameters{ {"id", selectedOrderIdStd}, {"status", "1"} },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Order", "Order status successfully!");
			resetSelectedOrderId();
			goToOrdersToPrepareTab();
		}
		else {
			ui.readyToCollectLabel->setText(QString::fromStdString("Generic error!"));
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
* Change the order status to "Collected"
*/
void RestaurantGUI::on_collectedBtn_clicked() {
	try {
		string selectedOrderIdStd = to_string(getSelectedOrderId());
		cpr::Response r = cpr::Patch(cpr::Url{ serverUrl + "/order/update/status" },
			cpr::Parameters{ {"id", selectedOrderIdStd}, {"status", "2"} },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			QMessageBox::information(this, "Order", "Order status successfully!");
			resetSelectedOrderId();
			goToOrdersToCollectTab();
		}
		else {
			ui.readyToCollectLabel->setText(QString::fromStdString("Generic error!"));
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
* Update restaurant profile (name, email, password, etc.)
*/
void RestaurantGUI::on_updateProfileBtn_clicked() {
	try {
		boolean error = false;

		ui.errorProfileLabel->setText(QString::fromStdString(""));
		ui.nameErrorLabel->setText(QString::fromStdString(""));
		ui.addressErrorLabel->setText(QString::fromStdString(""));
		ui.emailErrorLabel->setText(QString::fromStdString(""));
		ui.pswErrorLabel->setText(QString::fromStdString(""));
		ui.phoneErrorLabel->setText(QString::fromStdString(""));

		cpr::Response r = cpr::Get(cpr::Url{ serverUrl + "/restaurant/" + to_string(getRestaurantId()) },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

		if (r.status_code == 200) {
			json j = json::parse(r.text);
			j.erase(j.find("Id"));

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
			if (profileEditedAddress) {
				string address = ui.addressLineEdit->text().toStdString();

				if (!regex_match(address, regex(R"([#.0-9a-zA-Z\s,-]+)"))) {
					ui.addressErrorLabel->setText(QString::fromStdString("Insert a valid address!"));
					error = true;
				}
				else {
					j["Address"] = address;
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
				// If the password passes regex validation, it will be encrypted with SHA256 algorithm
				// It's mandatory to insert a password when admin need to update his profile
				j["Psw"] = sha256(psw);
			}

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
				cpr::Response rUpdate = cpr::Put(cpr::Url{ serverUrl + "/restaurant/update" },
					cpr::Body{ j.dump() },
					cpr::Header{ { "Content-Type", "application/json" }, {"Authorization", "Bearer " + getToken()} });

				if (rUpdate.status_code == 200) {
					// Logout the restaurant as it may have changed his password

					resetVariables();
					QMessageBox::information(this, "Login", QString::fromStdString(rUpdate.text) + " - Please, login again!");
					logoutUser();
				}
				else {
					ui.errorProfileLabel->setText(QString::fromStdString("Generic error!"));
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

/**
* Add a new dish to Restaurant Menu
*/
void RestaurantGUI::on_addDishBtn_clicked() {
	try {
		boolean error = false;
		ui.deleteDishLabel->setText(QString::fromStdString(""));
		ui.dishNameErrorLabel->setText(QString::fromStdString(""));
		ui.dishTypeErrorLabel->setText(QString::fromStdString(""));
		ui.dishPriceErrorLabel->setText(QString::fromStdString(""));

		json j;

		string name = ui.dishNameLineEdit->text().toStdString();
		if (!regex_match(name, regex(R"([#.a-zA-Z\s,-]+)"))) {
			ui.dishNameErrorLabel->setText(QString::fromStdString("Inser a valid name!"));
			error = true;
		}
		else {
			j["Name"] = name;
		}

		int type = ui.dishTypeBox->currentIndex();
		string typeStd = to_string(type);
		if (!regex_match(typeStd, regex(R"([0-4])"))) {
			ui.dishTypeErrorLabel->setText(QString::fromStdString("Inser a valid type!"));
			error = true;
		}
		else {
			j["Type"] = type;
		}

		double price = ui.dishPriceSpinBox->value();
		string priceStd = to_string(price);
		if (!regex_match(priceStd, regex(R"([1-9]\d*(.\d{1,6})?)"))) {
			ui.dishPriceErrorLabel->setText(QString::fromStdString("Inser a valid price!"));
			error = true;
		}
		else {
			j["Price"] = price;
		}
		
		j["RestaurantId"] = to_string(getRestaurantId());

		if (!error) {
			cpr::Response r;

			// Check if price is positive
			if (j["Price"] > 0) {
				r = cpr::Post(cpr::Url{ serverUrl + "/dish/create" },
					cpr::Body{ j.dump() },
					cpr::Header{ { "Content-Type", "application/json" }, {"Authorization", "Bearer " + getToken()} });
			}

			if (r.status_code == 200) {
				QMessageBox::information(this, "Login", QString::fromStdString("Dish add successfully to menu!"));

				ui.deleteDishLabel->setText(QString::fromStdString(""));
				ui.dishNameErrorLabel->setText(QString::fromStdString(""));
				ui.dishTypeErrorLabel->setText(QString::fromStdString(""));
				ui.dishPriceErrorLabel->setText(QString::fromStdString(""));

				ui.dishTypeBox->setCurrentIndex(0);
				ui.dishPriceSpinBox->setValue(0.0);

				goToMenuTab();
			}
			else {
				ui.addDishLabel->setText(QString::fromStdString("An error occour!"));
			}
		}
	}
	catch (...) {
		QMessageBox::warning(this, "Login", "Generic error. Please login again!");
		logoutUser();
	}
}

/**
* Delete selected dish from Restaurant Menu
*/
void RestaurantGUI::on_deleteDishBtn_clicked() {
	try {
		string selectedDishIdStd = to_string(getSelectedDishId());
		cpr::Response r = cpr::Delete(cpr::Url{ serverUrl + "/dish/delete/" + selectedDishIdStd },
			cpr::Header{ {"Authorization", "Bearer " + getToken()} });

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

/**
* If the restaurant changes his name, the event is captured by this function
* and written in a variable
*/
void RestaurantGUI::on_nameLineEdit_textChanged(QString text) {
	if (firstEditName) {
		firstEditName = false;
	}
	else {
		profileEditedName = true;
	}
}

/**
* If the restaurant changes his address, the event is captured by this function
* and written in a variable
*/
void RestaurantGUI::on_addressLineEdit_textChanged(QString text) {
	if (firstEditAddress) {
		firstEditAddress = false;
	}
	else {
		profileEditedAddress = true;
	}
}

/**
* If the restaurant changes his email, the event is captured by this function
* and written in a variable
*/
void RestaurantGUI::on_emailLineEdit_textChanged(QString text) {
	if (firstEditEmail) {
		firstEditEmail = false;
	}
	else {
		profileEditedEmail = true;
	}
}

/**
* If the restaurant changes his phone, the event is captured by this function
* and written in a variable
*/
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