#pragma once

#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_RestaurantGUI.h"

#include <regex>
#include <nlohmann/json.hpp>
#include "SpinBoxDelegate.h"

#include "Utils.h"

using json = nlohmann::json;
using namespace std;

class RestaurantGUI : public QDialog, public Ui::RestaurantGUI
{
	Q_OBJECT

private:
	Ui::RestaurantGUI ui;

	const int orderIdCol = 0;
	const int orderUserCol = 1;
	const int orderTotalCol = 2;
	const int orderStatusCol = 3;

	const int dishIdCol = 0;
	const int dishNameCol = 1;
	const int dishTypeCol = 2;
	const int dishPriceCol = 3;

	int session_restaurantId = 0;			// there is no restaurant with id equal to 0
	string session_token = "";
	int session_selectedOrderId = 0;		// there is no order with id equal to 0
	int session_selectedDishId = 0;			// there is no dish with id equal to 0

	boolean firstEditName = true;
	boolean firstEditAddress = true;
	boolean firstEditEmail = true;
	boolean firstEditPhone = true;

	boolean profileEditedName = false;
	boolean profileEditedAddress = false;
	boolean profileEditedEmail = false;
	boolean profileEditedPhone = false;

public:
	RestaurantGUI(QWidget* parent = Q_NULLPTR, int RestaurantId = 0, string token = "");
	~RestaurantGUI();

	void setRestaurantId(int id) {
		session_restaurantId = id;
	}

	void setToken(string token) {
		session_token = token;
	}

	void setSelectedOrderId(int id) {
		session_selectedOrderId = id;
	}

	void setSelectedDishId(int id) {
		session_selectedDishId = id;
	}

	int getRestaurantId() {
		return session_restaurantId;
	}

	string getToken() {
		return session_token;
	}

	int getSelectedOrderId() {
		return session_selectedOrderId;
	}

	int getSelectedDishId() {
		return session_selectedDishId;
	}

	void resetRestaurantId() {
		session_restaurantId = 0;
	}

	void resetToken() {
		session_token = "";
	}

	void resetSelectedOrderId() {
		session_selectedOrderId = 0;
	}

	void resetSelectedDishId() {
		session_selectedDishId = 0;
	}

	void goToOrdersToPrepareTab();

	void goToOrdersToCollectTab();

	void goToOrdersHistoryTab();

	void goToProfileTab();

	void goToMenuTab();

	void goToStatsTab();

	void logoutUser();

	void resetVariables() {
		firstEditName = true;
		firstEditAddress = true;
		firstEditEmail = true;
		firstEditPhone = true;

		profileEditedName = false;
		profileEditedAddress = false;
		profileEditedEmail = false;
		profileEditedPhone = false;
	}

private slots:
	void on_ordersToPrepareList_cellClicked(int row, int column);
	void on_ordersToCollectList_cellClicked(int row, int column);
	void on_dishesList_cellClicked(int row, int column);

	void on_readyToCollectBtn_clicked();
	void on_collectedBtn_clicked();
	void on_updateProfileBtn_clicked();
	void on_addDishBtn_clicked();
	void on_deleteDishBtn_clicked();

	void on_nameLineEdit_textChanged(QString text);
	void on_addressLineEdit_textChanged(QString text);
	void on_emailLineEdit_textChanged(QString text);
	void on_phoneLineEdit_textChanged(QString text);

	// Orders To Prepare window navbar
	void on_ordersToCollectBtn_clicked();
	void on_ordersHistoryBtn_clicked();
	void on_restaurantProfileBtn_clicked();
	void on_restaurantMenuBtn_clicked();
	void on_restaurantStatsBtn_clicked();
	void on_logoutBtn_clicked();

	// Orders To Collect window navbar
	void on_ordersToPrepareBtn_2_clicked();
	void on_ordersHistoryBtn_2_clicked();
	void on_restaurantProfileBtn_2_clicked();
	void on_restaurantMenuBtn_2_clicked();
	void on_restaurantStatsBtn_2_clicked();
	void on_logoutBtn_2_clicked();

	// Orders History window navbar
	void on_ordersToPrepareBtn_3_clicked();
	void on_ordersToCollectBtn_3_clicked();
	void on_restaurantProfileBtn_3_clicked();
	void on_restaurantMenuBtn_3_clicked();
	void on_restaurantStatsBtn_3_clicked();
	void on_logoutBtn_3_clicked();

	// Profile window navbar
	void on_ordersToPrepareBtn_4_clicked();
	void on_ordersToCollectBtn_4_clicked();
	void on_ordersHistoryBtn_4_clicked();
	void on_restaurantMenuBtn_4_clicked();
	void on_restaurantStatsBtn_4_clicked();
	void on_logoutBtn_4_clicked();

	// Restaurant Menu window navbar
	void on_ordersToPrepareBtn_5_clicked();
	void on_ordersToCollectBtn_5_clicked();
	void on_ordersHistoryBtn_5_clicked();
	void on_restaurantProfileBtn_5_clicked();
	void on_restaurantStatsBtn_5_clicked();
	void on_logoutBtn_5_clicked();

	// Stats window navbar
	void on_ordersToPrepareBtn_6_clicked();
	void on_ordersToCollectBtn_6_clicked();
	void on_ordersHistoryBtn_6_clicked();
	void on_restaurantProfileBtn_6_clicked();
	void on_restaurantMenuBtn_6_clicked();
	void on_logoutBtn_6_clicked();
};