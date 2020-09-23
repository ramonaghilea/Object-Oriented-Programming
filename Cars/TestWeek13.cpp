#include "TestWeek13.h"

TestWeek13::TestWeek13(Service& service, QWidget *parent)
    : service(service), QMainWindow(parent)
{
    ui.setupUi(this);
    this->populateSortedList();
    this->connectSignalsAndSlots();
}

void TestWeek13::connectSignalsAndSlots()
{
    QObject::connect(this->ui.ShowCarsButton, &QPushButton::clicked, this, &TestWeek13::getNumberCarsByGivenManufacturer);

}

void TestWeek13::populateSortedList()
{
    this->ui.CarsListWidget->clear();
    
    vector<Car> allCarsSorted = this->service.getAllCarsSortedByManufacturer();
    for (int indexCar = 0; indexCar < allCarsSorted.size(); indexCar++)
    {
        this->ui.CarsListWidget->addItem(QString::fromStdString(allCarsSorted[indexCar].asString()));

        QColor colour(QString::fromStdString(allCarsSorted[indexCar].getColour()));
        this->ui.CarsListWidget->item(indexCar)->setTextColor(colour);
    }
}

void TestWeek13::getNumberCarsByGivenManufacturer()
{
    std::string manufacturer = this->ui.ManufacturerLineEdit->text().toStdString();

    int numberCars = this->service.getNumberCarsForGivenManufacturer(manufacturer);

    this->ui.NumberCarsValueLabel->setText(QString::fromStdString(to_string(numberCars)));
}
