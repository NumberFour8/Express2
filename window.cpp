#include "window.h"
#include "ui_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), MyLoader("test.txt")
{
  ui->setupUi(this); 

  MyObjects = new GRect*[MyLoader.getTransforms().count()];
  MyScene = new QGraphicsScene;
  ui->view->setScene(MyScene);

  int j = 0;
  LinkedList<Loader::Transform>& ll = MyLoader.getTransforms();
  for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i,++j){
      Loader::Transform& Tr = *i;
      const char* name = Loader::getTransformString(Tr.type).c_str();

      QString label;
      if (Tr.type != Loader::ttRotate)
        label.sprintf("%s [%d,%d]",name,(int)Tr.p1,(int)Tr.p2);
      else label.sprintf("%s [%d]",name,(int)Tr.p1);

      ui->transformList->addItem(label);

      MyObjects[j] = new GRect(j,20.0f);
  }

  MyScene->setSceneRect(-600,-600,1200,1200);
  Render();

}

MainWindow::~MainWindow()
{
    for (int i = 0;i < MyLoader.getTransforms().count();++i)
        delete MyObjects[i];
    delete[] MyObjects;

    delete MyScene;
    delete ui;
}

void MainWindow::Render()
{
    QColor grid(0xcc,0xc6,0xc6);
    QColor cross(83,83,83);

    for (int i = -600;i < 600;i+=20){
       MyScene->addLine(i,-600,i,600,QPen(grid));
       MyScene->addLine(-600,i,600,i,QPen(grid));
    }
    MyScene->addLine(0,-600,0,600,QPen(cross));
    MyScene->addLine(-600,0,600,0,QPen(cross));
    MyScene->addItem(MyObjects[0]);

}

void MainWindow::moveItemUp ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko nahoru
}


void MainWindow::moveItemDown ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko dolu  
}
