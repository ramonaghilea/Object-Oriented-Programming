#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestWeek13.h"
#include "Service.h"

class TestWeek13 : public QMainWindow
{
    Q_OBJECT

public:
    TestWeek13(Service& service, QWidget *parent = Q_NULLPTR);

private:
    Service& service;
    Ui::TestWeek13Class ui;

    void connectSignalsAndSlots();

    void populateSortedList();
    void getNumberCarsByGivenManufacturer();
};
