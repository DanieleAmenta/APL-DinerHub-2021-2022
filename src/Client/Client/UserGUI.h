#pragma once

#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_UserGUI.h"

#include <regex>
#include <nlohmann/json.hpp>
#include "SpinBoxDelegate.h"

#include "Utils.h"

using json = nlohmann::json;
using namespace std;

class UserGUI : public QDialog, public Ui::UserGUI
{
	Q_OBJECT

private:
	Ui::UserGUI ui;

	const int restaurantIdCol = 0;
	const int restaurantNameCol = 1;
	const int restaurantAddressCol = 2;
	const int restaurantPhoneCol = 3;
	const int restaurantEmailCol = 4;

	const int dishIdCol = 0;
	const int dishNameCol = 1;
	const int dishTypeCol = 2;
	const int dishPriceCol = 3;
	const int dishQuantityCol = 4;

	const int orderIdCol = 0;
	const int orderRestaurantCol = 1;
	const int orderTotalCol = 2;
	const int orderStatusCol = 3;

	int session_userId = 0;			// there is no user with id equal to 0
	string session_token = "";
	int session_restaurantId = 0;	// there is no restaurant with id equal to 0

	boolean firstEditName = true;
	boolean firstEditSurname = true;
	boolean firstEditEmail = true;
	boolean firstEditPhone = true;

	boolean profileEditedName = false;
	boolean profileEditedSurname = false;
	boolean profileEditedEmail = false;
	boolean profileEditedPhone = false;

public:
	UserGUI(QWidget* parent = Q_NULLPTR, int UserId = 0, string token = "");
	~UserGUI();

	SpinBoxDelegate delegate;

	void setUserId(int id) {
		session_userId = id;
	}

	void setToken(string token) {
		session_token = token;
	}

	void setRestaurantId(int id) {
		session_restaurantId = id;
	}

	int getUserId() {
		return session_userId;
	}

	string getToken() {
		return session_token;
	}

	int getRestaurantId() {
		return session_restaurantId;
	}

	void resetUserId() {
		session_userId = 0;
	}

	void resetToken() {
		session_token = "";
	}

	void resetRestaurantId() {
		session_restaurantId = 0;
	}

	void goToOrderTab();

	boolean updateProfileBalance(string userId);

	void goToSummaryTab();

	void goToProfileTab();

	void goToStatsTab();

	void logoutUser();

	void resetVariables() {
		firstEditName = true;
		firstEditSurname = true;
		firstEditEmail = true;
		firstEditPhone = true;

		profileEditedName = false;
		profileEditedSurname = false;
		profileEditedEmail = false;
		profileEditedPhone = false;
	}

private slots:
	void on_restaurantList_cellClicked(int row, int column);
	void on_submitOrderBtn_clicked();

	void on_updateBalanceBtn_clicked();
	
	void on_nameLineEdit_textChanged(QString text);
	void on_surnameLineEdit_textChanged(QString text);
	void on_emailLineEdit_textChanged(QString text);
	void on_phoneLineEdit_textChanged(QString text);

	void on_updateProfileBtn_clicked();

	// Order window navbar
	void on_summaryTab_clicked();
	void on_profileTab_clicked();
	void on_statsTab_clicked();
	void on_logoutTab_clicked();

	// Summary window navbar
	void on_orderTab_2_clicked();
	void on_profileTab_2_clicked();
	void on_statsTab_2_clicked();
	void on_logoutTab_2_clicked();

	// Profile window navbar
	void on_orderTab_3_clicked();
	void on_summaryTab_3_clicked();
	void on_statsTab_3_clicked();
	void on_logoutTab_3_clicked();

	// Stats window navbar
	void on_orderTab_4_clicked();
	void on_summaryTab_4_clicked();
	void on_profileTab_4_clicked();
	void on_logoutTab_4_clicked();
};