#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUICPP.h"

class GUICPP : public QWidget
{
	Q_OBJECT

public:
	GUICPP(QWidget *parent = Q_NULLPTR);

private:
	Ui::GUICPPClass ui;
};
