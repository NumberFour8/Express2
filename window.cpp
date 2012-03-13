#include "window.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), ldr("test.txt")
{
  ui->setupUi(this); 

  LinkedList<Loader::Transform>& ll = ldr.getTransforms();
  objects = new GRect*[ll.count()];

  int j = 0;
  for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i,++j){
      Loader::Transform& Tr = *i;
      const char* name = Loader::getTransformString(Tr.type).c_str();

      QString label;
      if (Tr.type != Loader::ttRotate)
        label.sprintf("%s [%d,%d]",name,(int)Tr.p1,(int)Tr.p2);
      else label.sprintf("%s [%d]",name,(int)Tr.p1);

      ui->transformList->addItem(label);

      objects[j] = new GRect(j,5.0f);
      objects[j]->position()[0] = objects[j]->position()[1] = 0;
  }

}

MainWindow::~MainWindow()
{
    for (int i = 0;i < ldr.getTransforms().count();++i)
        delete objects[i];
    delete[] objects;

    delete ui;
}

void MainWindow::Render()
{
    QGraphicsScene MyScene;
    MyScene.setSceneRect(ui->view->x(),ui->view->y(),ui->view->width(),ui->view->height());
    ui->view->setScene(&MyScene);

    for (int i = 0;i < 100;i+=5){
       MyScene.addLine(i,0,i,MyScene.height(),QPen(QColor(0xef,0xef,0xef)));
       MyScene.addLine(0,i,MyScene.width(),i,QPen(QColor(0xef,0xef,0xef)));
    }

}

void MainWindow::moveItemUp ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko nahoru
}


void MainWindow::moveItemDown ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko dolu  
}
