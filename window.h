#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "loader.h"
#include "grect.h"

namespace Ui
{
  class MainWindow;
}

class QGraphicsScene;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    // pres tento ukazatel je dostupny kazdy objekt v okne
    // napr ui->view pro komponentu QGraphicsView vpravo v okne a
    // ui->transformList pro seznam transformaci vlevo v okne
    Ui::MainWindow *ui;
    Loader ldr;
    GRect **objects;

    void Render();

  private slots:
    void moveItemUp ();
    void moveItemDown ();

};

#endif
