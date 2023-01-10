#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->setFixedWidth(290);
  this->setFixedHeight(540);

  ui->result_show->setFixedWidth(270);

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

  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(func()));

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

  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph()));
  ui->pushButton_graph->setCheckable(true);

  connect(ui->pushButton_draw_graph, SIGNAL(clicked()), this,
          SLOT(make_graph()));
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  if (ui->x_value->hasFocus()) {
    QString result_label1 = (ui->x_value->text() + button->text());
    ui->x_value->setText(result_label1);
  } else if (ui->x_min->hasFocus()) {
    int result_label1 = (ui->x_min->text() + button->text()).toInt();
    ui->x_min->setValue(result_label1);
  } else if (ui->x_max->hasFocus()) {
    int result_label1 = (ui->x_max->text() + button->text()).toInt();
    ui->x_max->setValue(result_label1);
  } else if (ui->y_max->hasFocus()) {
    int result_label1 = (ui->y_max->text() + button->text()).toInt();
    ui->y_max->setValue(result_label1);
  } else if (ui->y_min->hasFocus()) {
    int result_label1 = (ui->y_min->text() + button->text()).toInt();
    ui->y_min->setValue(result_label1);
  } else {
    QString result_label2 = (ui->result_show->text() + button->text());
    ui->result_show->setText(result_label2);
  }
}

void MainWindow::operations() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->result_show->text();

  QString str = ui->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  if (button == ui->pushButton_open) {
    ui->result_show->setText(result_label + "(");
  }
  if (len != 0) {
    if (is_number(str[len - 1]) || str[len - 1] == 'x' || result_label[len - 1] == 'i' || str[len - 1] != '.') {
      if (button == ui->pushButton_open) {
        ui->result_show->setText(result_label + "*(");
      }
    }
    if (str[len - 1] != '.' && str[len - 1] != '(' && !is_operation(str[len - 1])) {
      if (button == ui->pushButton_close) {
        ui->result_show->setText(result_label + ")");
      }
    }
  }
}

void MainWindow::arithmetic() {
  QPushButton *button = (QPushButton *)sender();

  QString str = ui->result_show->text();
  int len = str.isNull() ? 0 : str.length();
  if (len != 0) {
    if ((is_number(str[len - 1])) || str[len - 1] == ')' ||
        str[len - 1] == 'x' || str[len - 1] == 'i') {
      if (button == ui->pushButton_plus) {
        ui->result_show->setText(str + "+");
      } else if (button == ui->pushButton_minus) {
        ui->result_show->setText(str + "-");
      } else if (button == ui->pushButton_mult) {
        ui->result_show->setText(str + "*");
      } else if (button == ui->pushButton_div) {
        ui->result_show->setText(str + "/");
      } else if (button == ui->pushButton_pow) {
        ui->result_show->setText(str + "^");
      }
    }
  } else {
      if (button == ui->pushButton_plus) {
        ui->result_show->setText(str + "+");
      } else if (button == ui->pushButton_minus) {
        ui->result_show->setText(str + "-");
      }
  }
}

void MainWindow::func() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->result_show->text();

  int len = result_label.isNull() ? 0 : result_label.length();
  if (len != 0) {
    if (result_label[len - 1] != 'x') {
      if (is_number(result_label[len - 1]) || result_label[len - 1] == ')' || result_label[len - 1] == 'i') {
        if (button == ui->pushButton_sin) {
          ui->result_show->setText(result_label + "*sin(");
        } else if (button == ui->pushButton_cos) {
          ui->result_show->setText(result_label + "*cos(");
        } else if (button == ui->pushButton_tan) {
          ui->result_show->setText(result_label + "*tan(");
        } else if (button == ui->pushButton_asin) {
          ui->result_show->setText(result_label + "*asin(");
        } else if (button == ui->pushButton_acos) {
          ui->result_show->setText(result_label + "*acos(");
        } else if (button == ui->pushButton_atan) {
          ui->result_show->setText(result_label + "*atan(");
        } else if (button == ui->pushButton_sqrt) {
          ui->result_show->setText(result_label + "*sqrt(");
        } else if (button == ui->pushButton_mod) {
          ui->result_show->setText(result_label + "*mod");
        } else if (button == ui->pushButton_ln) {
          ui->result_show->setText(result_label + "*ln(");
        } else if (button == ui->pushButton_log) {
          ui->result_show->setText(result_label + "*log(");
        } else if (button == ui->pushButton_x) {
          ui->result_show->setText(result_label + "*x");
        }
      }
      if (is_operation(result_label[len - 1]) || result_label[len - 1] == '(') {
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
        } else if (button == ui->pushButton_x) {
          ui->result_show->setText(result_label + "x");
        }
      }
    }
  } else {
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
    } else if (button == ui->pushButton_x) {
      ui->result_show->setText(result_label + "x");
    }
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
    ui->result_show->setText(ui->result_show->text() + "pi");
  } else if (count == 0 && (!is_number(str[j]) &&
                            str[j] != '.')) {
    ui->result_show->setText(ui->result_show->text() + "pi");
  }
}

void MainWindow::on_pushButton_equal_clicked() {
  QString str_expr = ui->result_show->text();
  QByteArray ba = str_expr.toLocal8Bit();
  char *c_str2 = ba.data();
  char outStr[256] = {0};
  double x = 0.0;
  double error = 0;
  if (str_expr == "") {
    ui->result_show->setText("Ошибка ввода");
  } else {
    if (str_expr.contains('x')) {
      str_expr.replace("x", ui->x_value->text());
      x = ui->x_value->text().toDouble();
    }
    error = s21_smart_calc(c_str2, x);
    sprintf(outStr, "%.15g", error);
    ui->result_show->setText(outStr);
  }
}

void MainWindow::graph() {
  QPushButton *button = (QPushButton *)sender();
  if (button->isChecked()) {
    button->setChecked(true);
    ui->x_value->setPlaceholderText("Graph enabled");
    ui->result_show->setPlaceholderText("Enter a function containing x:");
    ui->x_value->setEnabled(0);
    ui->pushButton_equal->setEnabled(0);

    this->setFixedWidth(890);
    ui->result_show->setFixedWidth(870);
    ui->x_max->setEnabled(true);
    ui->x_min->setEnabled(true);
    ui->y_max->setEnabled(true);
    ui->y_min->setEnabled(true);
  } else {
    this->setFixedWidth(290);
    ui->result_show->setFixedWidth(270);

    button->setChecked(false);
    ui->x_value->setEnabled(1);
    ui->pushButton_equal->setEnabled(1);

    ui->x_value->setPlaceholderText("Enter x value:");
    ui->result_show->setPlaceholderText("");
    ui->x_max->setEnabled(false);
    ui->x_min->setEnabled(false);
    ui->y_max->setEnabled(false);
    ui->y_min->setEnabled(false);
    ui->widget->replot();
    x.clear();
    y.clear();
    ui->result_show->setText("");
    //        ui->widget->graph(0)->data()->clear();
  }
}

void MainWindow::make_graph() {
  QString str = ui->result_show->text();
  if (str.contains("x") == false) {
    ui->result_show->setText("Expression doesn't contain x");
  } else {
    double x_min_num = ui->x_min->value();
    double x_max_num = ui->x_max->value();
    double y_min_num = ui->y_min->value();
    double y_max_num = ui->y_max->value();

    double step = 0.001 * (qFabs(x_min_num) + qFabs(x_max_num));
    double Y = 0;
    double X = (double)x_min_num;
    while (X < (double)x_max_num) {
      x.push_back(X);
      QByteArray ba = str.toLatin1();
      char *char_array = ba.data();
      Y = s21_smart_calc(char_array, X);
      y.push_back(Y);
      X += step;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setRange(x_min_num, x_max_num);
    ui->widget->yAxis->setRange(y_min_num, y_max_num);
    ui->widget->replot();
    x.clear();
    y.clear();
    ui->widget->graph(0)->data()->clear();
  }
}

void MainWindow::on_pushButton_clear_graph_clicked() {
  ui->widget->replot();
  x.clear();
  y.clear();
  //    ui->result_show->setText("");
  //    ui->widget->graph(0)->data()->clear();
}
