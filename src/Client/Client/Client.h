#pragma once

#include <QtWidgets/QWidget>

#include "ui_Client.h"
#include "UserGUI.h"
#include "AdminGUI.h"
#include "RestaurantGUI.h"
#include "RegisterGUI.h"

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