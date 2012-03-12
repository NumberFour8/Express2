#include "window.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ldr("test.txt")
{
  ui->setupUi(this); 

 Matrix<double> m(2,2);
 m(0,0) = 1; m(0,1) = 2;
 m(1,0) = 3; m(1,1) = 3;

 Vector<double> v(2,1,4);

 Vector<double> r = m*v;

  LinkedList<Loader::Transform>& ll = ldr.getTransforms();
  for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i){
      Loader::Transform& Tr = *i;
      const char* name = Loader::getTransformString(Tr.type).c_str();

      QString label;
      if (Tr.type != Loader::ttRotate)
        label.sprintf("%s [%d,%d]",name,(int)Tr.p1,(int)Tr.p2);
      else label.sprintf("%s [%d]",name,(int)Tr.p1);

      ui->transformList->addItem(label);
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
