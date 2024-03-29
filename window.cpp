#include "window.h"
#include "ui_form.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      SceneRect(-600,-600,1200,1200), nScalingFactor(20), // Velikost scény a škálovací faktor
      MyLoader(),MyObjects(NULL)
{
  ui->setupUi(this); 

  // Vytvoř scénu
  MyScene = new QGraphicsScene;
  MyScene->setSceneRect(SceneRect);

  // Nabinduj scénu na prohlížeč
  ui->view->setScene(MyScene);

  // Vykresli síť
  MakeGrid();
}

MainWindow::~MainWindow()
{
    if (MyObjects){
        // Smaž všechny objekty
        for (int i = 0;i < MyLoader.getTransforms().count();++i)
            delete MyObjects[i];
        delete[] MyObjects;
    }

    // Smaž scénu a UI
    delete MyScene;
    delete ui;
}

// Stará se o otevření souboru
void MainWindow::open()
{
    QString FilePath = QFileDialog::getOpenFileName(this,"Vyberte soubor");

    // Zkus načíst daný soubor
    if (FilePath.isNull() || !MyLoader.load(FilePath.toLocal8Bit().data(),nScalingFactor)){
      QMessageBox::warning(this,"Chyba","Nepodarilo se otevrit soubor!",QMessageBox::Ok,QMessageBox::Ok);
      return;
    }

    // Vytvoř tolik objektů, kolik bylo načtených transformací (vždycky bude načtena minimálně jedna a to počáteční poloha)
    MyObjects = new GRect*[MyLoader.getTransforms().count()];
    for (int i = 0;i < MyLoader.getTransforms().count();++i)
        MyObjects[i] = new GRect(i,20.0f,180);

    // Proveď transformace, updatuj popisky a vyrenderuj
    TransformAndUpdateList();
    MakeObjects();
}

// Aplikuje všechny transformace a vypíše seznam vlevo
void MainWindow::TransformAndUpdateList()
{
    ui->transformList->clear();

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

void MainWindow::MakeGrid()
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

}

// Vytvoří scénu
void MainWindow::MakeObjects()
{
    // Vykresli objekty
    for (int i = 0;i < MyLoader.getTransforms().count();++i)
      MyScene->addItem(MyObjects[i]);
}

void MainWindow::moveItemUp ()
{
   int cr = ui->transformList->currentRow();

    // První a druhý se nesmí přesouvat nahoru
   if (cr <= 1) return;

   // Vyměň transformace a updatuj jejich seznam
   MyLoader.getTransforms().swap(cr,cr-1);
   TransformAndUpdateList();

   ui->transformList->setCurrentRow(cr-1);
   MyScene->update(SceneRect); // Obnov scénu
}


void MainWindow::moveItemDown ()
{
    int cr = ui->transformList->currentRow();

    // První a poslední se nesmí přesouvat dolů
    if (cr == ui->transformList->count()-1 || cr <= 0) return;

    // Vyměň transformace a updatuj jejich seznam
    MyLoader.getTransforms().swap(cr,cr+1);
    TransformAndUpdateList();

    ui->transformList->setCurrentRow(cr+1);
    MyScene->update(SceneRect); // Obnov scénu
}


void MainWindow::itemChanged()
{
    // Vyber ten který je označen
    for (int i = 0;i < MyLoader.getTransforms().count();++i)
      MyObjects[i]->selectMe(ui->transformList->currentRow()==i);

    MyScene->update(SceneRect);
}
