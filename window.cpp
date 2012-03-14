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

      MyObjects[j] = new GRect(j,5.0f);
      MyObjects[j]->position()[0] = MyObjects[j]->position()[1] = 0;
  }


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
    for (int i = 0;i < 1000;i+=20){
       MyScene->addLine(i,0,i,1000,QPen(QColor(0xef,0xef,0xef)));
       MyScene->addLine(0,i,1000,i,QPen(QColor(0xef,0xef,0xef)));
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
