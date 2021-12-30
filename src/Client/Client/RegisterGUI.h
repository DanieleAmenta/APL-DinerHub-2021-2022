#pragma once

#include <iostream>
#include <stdio.h>
#include <cpr/cpr.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_RegisterGUI.h"

#include <regex>
#include <nlohmann/json.hpp>

#include "Utils.h"

using json = nlohmann::json;
using namespace std;

class RegisterGUI : public QDialog, public Ui::RegisterGUI
{
	Q_OBJECT

private:
	Ui::RegisterGUI ui;

public:
	RegisterGUI(QWidget* parent = Q_NULLPTR);
	~RegisterGUI();

private slots:
	void on_backToLoginBtn_clicked();
	void on_registerBtn_clicked();
};