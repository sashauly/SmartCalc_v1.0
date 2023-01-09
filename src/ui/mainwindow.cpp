#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_erase, SIGNAL(clicked()), this, SLOT(clear()));

  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(arithmetic()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(func()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {  // добавление чисел и точки в лейбл

  QPushButton *button = (QPushButton *)sender();
  QString result_label = (ui->result_show->text() + button->text());
  ui->result_show->setText(result_label);
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->result_show->text();

  if (button == ui->pushButton_open) {
    ui->result_show->setText(result_label + "(");
  } else if (button == ui->pushButton_close) {
    ui->result_show->setText(result_label + ")");
  }
}

void MainWindow::arithmetic() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->result_show->text();

  if (button == ui->pushButton_plus) {
    ui->result_show->setText(result_label + "+");
  } else if (button == ui->pushButton_minus) {
    ui->result_show->setText(result_label + "-");
  } else if (button == ui->pushButton_mult) {
    ui->result_show->setText(result_label + "*");
  } else if (button == ui->pushButton_div) {
    ui->result_show->setText(result_label + "/");
  } else if (button == ui->pushButton_pow) {
    ui->result_show->setText(result_label + "^");
  }
}

void MainWindow::func() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->result_show->text();

  if (button == ui->pushButton_sin) {
    ui->result_show->setText(result_label + "sin(");
  } else if (button == ui->pushButton_cos) {
    ui->result_show->setText(result_label + "cos(");
  } else if (button == ui->pushButton_tan) {
    ui->result_show->setText(result_label + "tan(");
  } else if (button == ui->pushButton_asin) {
    ui->result_show->setText(result_label + "asin(");
  } else if (button == ui->pushButton_acos) {
    ui->result_show->setText(result_label + "acos(");
  } else if (button == ui->pushButton_atan) {
    ui->result_show->setText(result_label + "atan(");
  } else if (button == ui->pushButton_sqrt) {
    ui->result_show->setText(result_label + "sqrt(");
  } else if (button == ui->pushButton_mod) {
    ui->result_show->setText(result_label + "mod");
  } else if (button == ui->pushButton_ln) {
    ui->result_show->setText(result_label + "ln(");
  } else if (button == ui->pushButton_log) {
    ui->result_show->setText(result_label + "log(");
  }
}

void MainWindow::clear() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->pushButton_clear) {
    ui->result_show->setText("");
  } else {
    QString result_label = ui->result_show->text();
    result_label.resize(result_label.size() - 1);
    ui->result_show->setText(result_label);
  }
}

void MainWindow::on_pushButton_dot_clicked() {
  int count = 0;
  QString str = ui->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  for (int i = 0; i < len; i++) {
    if (str[i] == '.') {
      count = 1;
    } else if (!is_number(str[i])) {
      count = 0;
    }
  }
  if (len != 0) {
    if (count == 0 && (is_number(str[len - 1]))) {
      ui->result_show->setText(ui->result_show->text() + ".");
    }
  }
}

void MainWindow::on_pushButton_pi_clicked() {
  int count = 0;
  QString str = ui->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  for (int i = 0; i < len; i++) {
    if (str[i] == '.') {
      count = 1;
    } else if (!is_number(str[i])) {
      count = 0;
    }
  }
  int j = len - 1;
  if (len == 0) {
    ui->result_show->setText(ui->result_show->text() + "3.141592653589793");
  } else if (count == 0 && (str[j] != '1' && str[j] != '2' && str[j] != '3' &&
                            str[j] != '4' && str[j] != '5' && str[j] != '6' &&
                            str[j] != '7' && str[j] != '8' && str[j] != '9' &&
                            str[j] != '.')) {
    ui->result_show->setText(ui->result_show->text() + "3.141592653589793");
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  QString str_expr = ui->result_show->text();
  QByteArray ba = str_expr.toLocal8Bit();
  char *c_str2 = ba.data();
  char outStr[256] = {0};
  double x = 0.0;
  double error = 0;
  if (str_expr.contains('x')) {
        str_expr.replace("x", ui->x_value->text());
        x = ui->x_value->text().toDouble();
      }
  error = s21_smart_calc(c_str2, x);
  sprintf(outStr, "%.15g", error);
  ui->result_show->setText(outStr);
}
