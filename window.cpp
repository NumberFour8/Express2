#include "window.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ldr("C:\\test.txt")
{
  ui->setupUi(this); 

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::Render()
{
    QGraphicsScene MyScene;
    MyScene.setSceneRect(ui->view->x(),ui->view->y(),ui->view->width(),ui->view->height());
    ui->view->setScene(&MyScene);
}

void MainWindow::moveItemUp ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko nahoru
}


void MainWindow::moveItemDown ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko dolu  
}
