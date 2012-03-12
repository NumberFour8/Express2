#include "window.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ldr("C:\\test.txt")
{
  ui->setupUi(this); 

  LinkedList<Loader::Transform>& ll = ldr.getTransforms();
  for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i){
      ui->transformList->addItem(QString(Loader::getTransformString((*i).type).c_str()));
  }

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
