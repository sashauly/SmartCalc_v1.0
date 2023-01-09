#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmath.h>
#include <stdlib.h>

#include <QMainWindow>
extern "C" {
    #include "../parser.h"
    #include "../stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;

 private slots:
  void digits_numbers();
  void operations();
  void arithmetic();
  void func();
  void clear();
  void on_pushButton_dot_clicked();
  void on_pushButton_pi_clicked();
  void on_pushButton_equal_clicked();
};
#endif  // MAINWINDOW_H
