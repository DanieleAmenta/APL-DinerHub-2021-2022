#pragma once

#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include <QtWidgets/QWidget>

#include "ui_Client.h"
#include "UserGUI.h"
#include "AdminGUI.h"
#include "RestaurantGUI.h"
#include "RegisterGUI.h"

#include <QDialog>
#include <QMessageBox>

#include <regex>
#include <nlohmann/json.hpp>

#include "Utils.h"

using json = nlohmann::json;
using namespace std;

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget* parent = Q_NULLPTR);

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::ClientClass ui;
    UserGUI* userGUI;
    AdminGUI* adminGUI;
    RestaurantGUI* restaurantGUI;
    RegisterGUI* registerGUI;
};