#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pi.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset() {
    this->ui->lineEdit->clear();
    this->ui->lineEdit->setDisabled(false);
    this->ui->lineEdit->setFocus();
}

bool cmp(const QString &substr, const QString &str, int &index) {
    if (substr.length() > str.length()) {
        index = -1;
        return false;
    }
    for (index = 0; index < substr.length(); ++index) {
        if (substr.at(index) != str.at(index)) return false;
    }
    return true;
}

void MainWindow::on_lineEdit_textEdited(const QString &text) {
    int i;
    if (!cmp(text, PI, i)) {
        if (i == -1) {
            this->ui->label->setText(QStringLiteral("Well done, you've beaten this program."));
        } else {
            this->ui->label->setText(QStringLiteral("Wrong! That should be ") + PI.at(i));
        }
        this->ui->lineEdit->setDisabled(true);

        QTimer::singleShot(1000, this, &MainWindow::reset);
    } else {
        this->ui->label->setText(QString("%1 characters").arg(i));
    }
}
