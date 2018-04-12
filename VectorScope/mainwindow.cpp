#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <time.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clock_t t = clock();

    ui->comboBox->addItem("colorwheel");
    ui->comboBox->addItem("colorbar");
    ui->comboBox->addItem("test");
    ui->comboBox->addItem("woman");
    ui->comboBox->addItem("house");
    ui->comboBox->addItem("natalie");
    ui->comboBox->addItem("colorfulpencils");

    image = new QImage();
    QString path = "C:/Users/anonymvs/Documents/VectorScope";
    path.append("/colorwheel.jpg");
    //path.append("/colorbar.jpg");
    image->load(path);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,400,400);

    vs = new VectorScope(400,400);
    vs->processImage(image);

    //the time of image processing
    clock_t t2 = clock();
    QString str = "time in ms: ";
    float dt = (float) t2 - t;
    str += QString::number(dt);
    ui->dt_in_ms->setText(str);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    scene->addPixmap(*vs->getPixmap());
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    delete image;
    image = new QImage();
    QString path = "C:/Users/anonymvs/Documents/VectorScope";
    QString ct = ui->comboBox->currentText();
    path.append("/");
    path.append(ct);
    path.append(".jpg");
    std::cout << path.data() << "\n";
    image->load(path);

    clock_t t = clock();
    vs->processImage(image);
    clock_t t2 = clock();

    QString str = "time in ms: ";
    float dt = (float) t2 - t;
    str += QString::number(dt / CLOCKS_PER_SEC * 1000);
    ui->dt_in_ms->setText(str);
}
