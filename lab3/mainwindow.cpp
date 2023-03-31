#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QTime>
#include <QShortcut>
#include "lab2.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    for(int i = 0; i < 4; ++i) this->flags.emplace_back(false);
//    ui->pushButton_4->hide();
//    ui->pushButton_5->hide();
    ui->label->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_dark.png"));
    ui->label->setScaledContents (true);
    labels.emplace_back(ui->label);
    ui->label_2->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_dark.png"));
    ui->label_2->setScaledContents (true);
    labels.emplace_back(ui->label_2);
    ui->label_3->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_dark.png"));
    ui->label_3->setScaledContents (true);
    labels.emplace_back(ui->label_3);
    ui->label_4->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_dark.png"));
    ui->label_4->setScaledContents (true);
    labels.emplace_back(ui->label_4);

    ui->label_5->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_light.png"));
    ui->label_5->setScaledContents (true);
    ui->label_5->hide();
    labels.emplace_back(ui->label_5);
    ui->label_6->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_light.png"));
    ui->label_6->setScaledContents (true);
    ui->label_6->hide();
    labels.emplace_back(ui->label_6);
    ui->label_7->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_light.png"));
    ui->label_7->setScaledContents (true);
    ui->label_7->hide();
    labels.emplace_back(ui->label_7);
    ui->label_8->setPixmap (QPixmap ("C:/Users/DF/Documents/untitled1/bulb_light.png"));
    ui->label_8->setScaledContents (true);
    ui->label_8->hide();
    labels.emplace_back(ui->label_8);

    this->checkboxes = {ui->checkBox, ui->checkBox_2, ui->checkBox_3, ui->checkBox_4};
    ui->horizontalSlider->setMaximum(1000);
    ui->horizontalSlider->setMinimum(0);
    ui->progressBar->setValue(0);
    ui->spinBox->setValue(0);
    ui->horizontalSlider->setValue(0);
    vec = {{PIN_12, PIN_18}, {PIN_21, PIN_23}};
    for (auto &i : vec) {
      for (auto &j : i) {
        gpio_export(j);
        gpio_set_dir(j, "out");
        gpio_set_value(j, 0);
      }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked() {
    for (int i = 0; i < 4; ++i){
        this->flags.at(i) = (this->checkboxes.at(i)->checkState() == Qt::Checked);
        if (this->flags.at(i)){
            this->labels[i]->hide();
            this->labels[i+4]->show();
            gpio_set_value(vec[i / 2][i % 2], true);
        } else{
            this->labels[i]->show();
            this->labels[i+4]->hide();
            gpio_set_value(vec[i / 2][i % 2], false);
        }
    }

}
void switchingLEDS(const std::vector<QCheckBox*>& bulbs, const bool flag) {
    if (flag){
        bulbs.at(0)->setCheckState(Qt::Checked);
        bulbs.at(1)->setCheckState(Qt::Checked);
        bulbs.at(2)->setCheckState(Qt::Unchecked);
        bulbs.at(3)->setCheckState(Qt::Unchecked);
    } else{
        bulbs.at(0)->setCheckState(Qt::Unchecked);
        bulbs.at(1)->setCheckState(Qt::Unchecked);
        bulbs.at(2)->setCheckState(Qt::Checked);
        bulbs.at(3)->setCheckState(Qt::Checked);
    }
}

void delay(const int& t = 1000) {
    QTime dieTime= QTime::currentTime().addMSecs(t);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::on_pushButton_clicked() {
     flag = true;
     bool temp = true;
     while (flag){
        switchingLEDS(this->checkboxes, temp);
        on_pushButton_2_clicked();
        delay(1100 - ui->horizontalSlider->value());
        temp = !temp;
     }
}




void MainWindow::on_horizontalSlider_valueChanged(int value) {
    int temp = ui->horizontalSlider->value() / 10;
    ui->progressBar->setValue(temp);
    ui->spinBox->setValue(temp);
}


void MainWindow::on_spinBox_valueChanged(int arg1) {
    int temp = ui->spinBox->value();
    ui->progressBar->setValue(temp);
    ui->horizontalSlider->setValue(temp*10);
}


void MainWindow::on_pushButton_4_pressed()
{
    int temp = ui->horizontalSlider->value() - 10;
    ui->horizontalSlider->setValue(temp);
//    ui->progressBar->setValue(temp);
//    ui->spinBox->setValue(temp);

}


void MainWindow::on_pushButton_5_pressed()
{
    int temp = ui->horizontalSlider->value() + 10;
    ui->horizontalSlider->setValue(temp);
//    ui->progressBar->setValue(temp);
//    ui->spinBox->setValue(temp);

}


void MainWindow::on_pushButton_3_clicked()
{
    flag = false;
}

