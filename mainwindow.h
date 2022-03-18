#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QHBoxLayout>
#include<QMouseEvent>
#include<QWidget>
#include<QPaintEvent>
#include<QPalette>
#include "NeuralNetworkImport.h"
#include "NeuralNetwork.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MyWidget:public QWidget
{
    Q_OBJECT

signals:
    void onPixmap(QPixmap pixmap);
public:

    void setPointSize(size_t x);
    void ClearPoints();
protected:
   void paintEvent(QPaintEvent *event)override;
private:
    std::list<QPoint> m_points;
    size_t m_pointSize;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onSizeChanged();
    void onActionNew();
    void onPixmapReady(QPixmap pixmap);
    void onLoadNet();
private:
    Ui::MainWindow *ui;
    std::unique_ptr<MyWidget> m_myWidget;
    std::unique_ptr<NeuralNetwork> m_neuralNet;
};
#endif // MAINWINDOW_H
