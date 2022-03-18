#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMouseEvent>
#include<QPainter>
#include<QSpinBox>
#include<QFileDialog>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_myWidget = std::make_unique<MyWidget>();

    m_neuralNet = std::make_unique<NeuralNetwork>(NeuralNetworkImport::fromJSON(R"(C:\Users\anama\OneDrive\Desktop\SiemensSS\LiveClassification\neural_net.json)"));
    auto layout = new QHBoxLayout(ui->centralwidget);
    layout->addWidget(m_myWidget.get(),4);
    layout->addWidget(ui->frame,1);
    m_myWidget->setAutoFillBackground(true);
    m_myWidget->setPalette(QPalette(Qt::black));
    connect(ui->penSize,&QSpinBox::valueChanged,this,&MainWindow::onSizeChanged);

    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::onActionNew);
    m_myWidget->setPointSize(ui->penSize->value());
    connect(m_myWidget.get(),&MyWidget::onPixmap,this,&MainWindow::onPixmapReady);
    connect(ui->actionLoad_neural_net,&QAction::triggered,this,&MainWindow::onLoadNet);


}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onSizeChanged()
{
    m_myWidget->setPointSize(ui->penSize->value());
    update();
}
void MainWindow::onActionNew()
{
    m_myWidget->ClearPoints();
}
void MainWindow::onPixmapReady(QPixmap pixmap)
{
    ui->imagePreview->setPixmap(pixmap);
    Image myImage;
    myImage.rows = pixmap.height();
    myImage.columns = pixmap.width();
    QImage qimg = pixmap.toImage().convertToFormat(QImage::Format_Grayscale8);
    myImage.pixels = std::vector<uint8_t>(qimg.bits(), qimg.bits() + qimg.width() * qimg.height());
    //if (m_neuralNet != nullptr)
     ui->resultLabel->setNum(m_neuralNet->Predict(myImage));
     update();
}
void MainWindow::onLoadNet()
{
     QString path = QFileDialog::getOpenFileName(this,tr("Select neural file"), "", "*.json");
     m_neuralNet = std::make_unique<NeuralNetwork>(NeuralNetworkImport::fromJSON(std::filesystem::path(path.toStdString())));
}

void MyWidget::setPointSize(size_t x){
    this->m_pointSize = x;
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_points.emplace_back(event->pos());
     update();
}
void MyWidget::mousePressEvent(QMouseEvent *event)
{
    m_points.emplace_back(event->pos());
    update();
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_points.emplace_back(event->pos());
    update();

    auto pixmap = this->grab();
    pixmap = pixmap.scaled(28,28,Qt::IgnoreAspectRatio);
    emit onPixmap(pixmap);
}

void MyWidget::ClearPoints(){
    m_points.clear();
    update();
}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    for(auto point:m_points){
        //painter.drawRect(point.x(),point.y(),10,10);
        painter.fillRect(point.x(),point.y(),m_pointSize,m_pointSize,Qt::lightGray);

    }
}

///override paintEvent
///override press release move
///on press-> collect mouse coordinates
///on move-> keep collecting mouse coordinates
///on release -> update the image label
///                  call grab =>pixmap of widget
///                  resize it!
///                  emit custom signal to pass the image
//              call the classifier
//                  need to build an image
//                  convert pixmap to image
//                  on image, call bits()
//              update result label
///  on file-> new-> empty the container
/// on load neural net -> open file dialog
///                    ->select json
///                    ->import/update a neural net

//set background color
//members : container of coordinates, neural network,?custom widget?
