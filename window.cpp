#include "window.h"
#include "ui_form.h"

const int nScalingFactor = 20;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), MyLoader("test.txt",nScalingFactor)
{
  ui->setupUi(this); 

  MyScene = new QGraphicsScene;
  MyScene->setSceneRect(-600,-600,1200,1200);

  MyObjects = new GRect*[MyLoader.getTransforms().count()];

  ui->view->setScene(MyScene);

  TransformAndUpdate();
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

void MainWindow::TransformAndUpdate()
{
    Matrix<float> MyMatrix(3,3);
    MyMatrix.identity();

    int j = 0;
    LinkedList<Loader::Transform>& ll = MyLoader.getTransforms();
    for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i,++j){
        AddTransformToList(*i);
        //MyMatrix = MyMatrix*((*i).T);

        MyObjects[j] = new GRect(j,20.0f);
        MyObjects[j]->setAlpha(200);
        MyObjects[j]->transform((*i).T);
    }
}

void MainWindow::AddTransformToList(const Loader::Transform &Tr)
{
    const char* name = Loader::getTransformString(Tr.type).c_str();

    QString label;
    if (Tr.type != Loader::ttRotate)
      label.sprintf("%s [%d,%d]",name,(int)Tr.p1,(int)Tr.p2);
    else label.sprintf("%s [%d]",name,(int)Tr.p1);

    ui->transformList->addItem(label);
}

void MainWindow::Render()
{
    QColor grid(0xcc,0xc6,0xc6);
    QColor cross(83,83,83);

    for (int i = -600;i < 600;i+=nScalingFactor){
       MyScene->addLine(i,-600,i,600,QPen(grid));
       MyScene->addLine(-600,i,600,i,QPen(grid));
    }
    MyScene->addLine(0,-600,0,600,QPen(cross));
    MyScene->addLine(-600,0,600,0,QPen(cross));

    for (int i = 0;i < MyLoader.getTransforms().count();++i)
      MyScene->addItem(MyObjects[i]);
}

void MainWindow::moveItemUp ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko nahoru
}


void MainWindow::moveItemDown ()
{
  // tento slot je zavolan, kdyz nekdo stiskne tlacitko dolu  
}
