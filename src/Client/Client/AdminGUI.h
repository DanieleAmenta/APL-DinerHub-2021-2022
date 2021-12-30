#pragma once

#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_AdminGUI.h"

#include <regex>
#include <nlohmann/json.hpp>
#include "SpinBoxDelegate.h"

#include "Utils.h"

using json = nlohmann::json;
using namespace std;

class AdminGUI : public QDialog, public Ui::AdminGUI
{
	Q_OBJECT

private:
	Ui::AdminGUI ui;

	const int userIdCol = 0;
	const int userNameCol = 1;
	const int userSurnameCol = 2;
	const int userEmailCol = 3;
	const int userPhoneCol = 4;
	const int userBalanceCol = 5;

	const int restaurantIdCol = 0;
	const int restaurantNameCol = 1;
	const int restaurantAddressCol = 2;
	const int restaurantPhoneCol = 3;

	int session_adminId = 0;			// there is no admin with id equal to 0
	int session_deleteUserId = 0;		// there is no user with id equal to 0
	int session_deleteRestaurantId = 0;		// there is no restaurant with id equal to 0

	boolean firstEditEmail = true;
	boolean firstEditPsw = true;

	boolean profileEditedEmail = false;
	boolean profileEditedPsw = false;

public:
	AdminGUI(QWidget* parent = Q_NULLPTR);
	~AdminGUI();

	void setAdminId(int id) {
		session_adminId = id;
	}

	void setDeleteUserId(int id) {
		session_deleteUserId = id;
	}

	void setDeleteRestaurantId(int id) {
		session_deleteRestaurantId = id;
	}

	int getAdminId() {
		return session_adminId;
	}

	int getDeleteUserId() {
		return session_deleteUserId;
	}

	int getDeleteRestaurantId() {
		return session_deleteRestaurantId;
	}

	void resetAdminId() {
		session_adminId = 0;
	}

	void resetDeleteUserId() {
		session_deleteUserId = 0;
	}

	void resetDeleteRestaurantId() {
		session_deleteRestaurantId = 0;
	}

	void goToUserListTab();

	void goToRestaurantListTab();

	void goToProfileTab();

	void goToStatsTab();

	void logoutUser();

	void resetVariables() {
		firstEditEmail = true;
		firstEditPsw = true;

		profileEditedEmail = false;
		profileEditedPsw = false;
	}

private slots:
	void on_userList_cellClicked(int row, int column);
	void on_restaurantList_cellClicked(int row, int column);

	void on_deleteUserBtn_clicked();
	void on_deleteRestaurantBtn_clicked();
	void on_createRestaurantBtn_clicked();
	void on_updateProfileBtn_clicked();

	void on_emailLineEdit_textChanged(QString text);
	void on_pswLineEdit_textChanged(QString text);

	// User List window navbar
	void on_restaurantListTab_clicked();
	void on_profileTab_clicked();
	void on_statsTab_clicked();
	void on_logoutTab_clicked();

	// Restaurant List window navbar
	void on_userListTab_2_clicked();
	void on_profileTab_2_clicked();
	void on_statsTab_2_clicked();
	void on_logoutTab_2_clicked();

	// Profile window navbar
	void on_userListTab_3_clicked();
	void on_restaurantListTab_3_clicked();
	void on_statsTab_3_clicked();
	void on_logoutTab_3_clicked();

	// Stats window navbar
	void on_userListTab_4_clicked();
	void on_restaurantListTab_4_clicked();
	void on_profileTab_4_clicked();
	void on_logoutTab_4_clicked();
};
