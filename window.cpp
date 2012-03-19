#include "window.h"
#include "ui_form.h"

const int nScalingFactor = 20; // Škálovací faktor

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), MyLoader("test.txt",nScalingFactor)
{
  ui->setupUi(this); 

  // Vytvoř scénu
  MyScene = new QGraphicsScene;
  MyScene->setSceneRect(-600,-600,1200,1200);

  // Vytvoř tolik objektů, kolik bylo načtených transformací (vždycky bude načtena minimálně jedna a to počáteční poloha)
  MyObjects = new GRect*[MyLoader.getTransforms().count()];
  for (int i = 0;i < MyLoader.getTransforms().count();++i)
      MyObjects[i] = new GRect(i,20.0f,200);

  // Nabinduj scénu na prohlížeč
  ui->view->setScene(MyScene);

  // Proveď transformace, updatuj popisky a vyrenderuj
  TransformAndUpdate();
  Render();

}

MainWindow::~MainWindow()
{
    // Smaž všechny objekty
    for (int i = 0;i < MyLoader.getTransforms().count();++i)
        delete MyObjects[i];
    delete[] MyObjects;

    // Smaž scénu a UI
    delete MyScene;
    delete ui;
}

// Aplikuje všechny transformace a vypíše seznam vlevo
void MainWindow::TransformAndUpdate()
{
    // Začneme s jednotkovou maticí
    Matrix<float> MyMatrix(3,3);
    MyMatrix.identity();

    int j = 0;
    LinkedList<Loader::Transform>& ll = MyLoader.getTransforms();
    for (LinkedList<Loader::Transform>::iterator i = ll.begin();i != ll.end();++i,++j){
        // Přidej transformaci do seznamu vlevo a násob s její maticí naši matici zleva
        AddTransformToList(j,*i);
        MyMatrix = ((*i).T)*MyMatrix;

        // Zresetuj objekt na původní polohu a pak jej transformuj naší maticí
        MyObjects[j]->reset();
        MyObjects[j]->transform(MyMatrix);
    }
}

// Přidá informace o dané transformaci do seznamu vlevo
void MainWindow::AddTransformToList(const int& id,const Loader::Transform &Tr)
{
    QString label;
    QTextStream builder(&label);

    builder << id << ":" << Loader::getTransformString(Tr.type);

     if (Tr.type != Loader::ttRotate)
      builder << " [" << Tr.p1 << "," << Tr.p2 << "]";
    else builder << " [" << (int)Tr.p1 << "]";

    ui->transformList->addItem(label);

}

// Vyrenderuje scénu
void MainWindow::Render()
{
    QColor grid(0xcc,0xc6,0xc6);
    QColor cross(83,83,83);

    // Vykresli síť
    for (int i = -600;i < 600;i+=nScalingFactor){
       MyScene->addLine(i,-600,i,600,QPen(grid));
       MyScene->addLine(-600,i,600,i,QPen(grid));
    }
    MyScene->addLine(0,-600,0,600,QPen(cross));
    MyScene->addLine(-600,0,600,0,QPen(cross));

    // Vykresli objekty
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
