#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include "Client.h"

#include <QMessageBox>
#include <QDialog>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;

Client::Client(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

void Client::on_loginButton_clicked()
{
    QString email = ui.emailField->text();
    QString password = ui.pswField->text();

    string sEmail = email.toStdString();
    string sPsw = password.toStdString();

    cpr::Response r = cpr::Post(cpr::Url{ serverUrl + "/user/login" },
        cpr::Parameters{ {"email", sEmail}, {"psw", sPsw} });

    //ui.textEdit->setText(QString::fromStdString(r.status_code));
    ui.textEdit->setText(QString::number(r.status_code));

    // SE VUOTO, CODICE 204
    if (r.status_code == 200) {
        json j = json::parse(r.text);

        if (j.contains("isAdmin")) {
            bool isAdmin = j["isAdmin"];

            if (isAdmin) {
                adminGUI = new AdminGUI(this);

                ui.emailField->setText(QString::fromStdString(""));
                ui.pswField->setText(QString::fromStdString(""));

                // Set session variable
                adminGUI->setAdminId(j["userId"]);

                adminGUI->show();
            }
            else {
                userGUI = new UserGUI(this);

                ui.emailField->setText(QString::fromStdString(""));
                ui.pswField->setText(QString::fromStdString(""));

                // Set session variable
                userGUI->setUserId(j["userId"]);

                userGUI->show();
            }
        }
        else if (j.contains("isRestaurant")) {
            // All restaurants have isRestaurant set to true, but we do a double check
            bool isRestaurant = j["isRestaurant"];

            if (isRestaurant) {
                restaurantGUI = new RestaurantGUI(this);

                ui.emailField->setText(QString::fromStdString(""));
                ui.pswField->setText(QString::fromStdString(""));

                // Set session variable
                restaurantGUI->setRestaurantId(j["restaurantId"]);

                restaurantGUI->show();
            }
        }
    }
    else {
        QMessageBox::warning(this, "Login", "Username and password are NOT correct");
    }
}

void Client::on_registerButton_clicked() {
    registerGUI = new RegisterGUI();

    ui.emailField->setText(QString::fromStdString(""));
    ui.pswField->setText(QString::fromStdString(""));

    registerGUI->show();
}
