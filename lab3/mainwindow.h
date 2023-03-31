#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

class QLabel;

class QCheckBox;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void bootStrap();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_4_pressed();

    void on_pushButton_5_pressed();

    void on_pushButton_3_clicked();

signals:
    void error(QString err);

private:
    Ui::MainWindow *ui;
    std::vector<bool> flags;
    std::vector<QLabel*> labels;
    std::vector<QCheckBox*> checkboxes;
    std::vector<QAction> shortcut;
    vector<vector<int>> vec;
    void foo();
    bool flag = false;
};
#endif // MAINWINDOW_H
