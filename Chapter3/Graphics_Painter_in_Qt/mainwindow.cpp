#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    QPainter textPainter(this);

//    /*----------------------------- Draw text -----------------------------*/
//    textPainter.setFont(QFont("Times", 14, QFont::Bold));        // set the text font setting
//    textPainter.drawText(QPoint(20, 30), "Testing");             // set the text on the screen at the position(20,30)

//    /*----------------------------- Draw straight line -----------------------------*/
//    QPainter linerPainter(this);
//    linerPainter.drawLine(QPoint(50, 60), QPoint(100, 100));     // draw straight line start from (50,60) and ends at (100,100)

//    /*----------------------------- Draw rectangle -----------------------------*/
//    QPainter rectPainter(this);
//    rectPainter.setBrush(Qt::BDiagPattern);
//    rectPainter.drawRect(QRect(40, 120, 80, 30));            // draw a rectangle at (x:40,y:120) with (width:80,height:30)

//    /*----------------------------- Draw ellipse -----------------------------*/
//    QPen ellipsePen;
//    ellipsePen.setColor(Qt::red);                            // Set color to red
//    ellipsePen.setStyle(Qt::DashDotDotLine);                 // set line style

//    QPainter ellipsePainter(this);
//    ellipsePainter.setPen(ellipsePen);                       // apply the QPen class to QPainter
//    ellipsePainter.drawEllipse(QPoint(80, 200), 50, 20);     // draw an ellipse shape at(80,200),horizontal radius:50,vertical radius:20

//    /*----------------------------- Use QPainterPath class to draw rectangle-----------------------------*/
//    QPainterPath rectPath;
//    rectPath.addRect(QRect(150, 20, 100, 50));      // draw rectangle at (x:150,y:20) with (width:100,height:50)

//    QPainter pathPainter(this);
//    pathPainter.setPen(QPen(Qt::red, 1, Qt::DashDotDotLine, Qt::FlatCap, Qt::MiterJoin));
//    pathPainter.setBrush(Qt::yellow);
//    pathPainter.drawPath(rectPath);

//    /*----------------------------- Use QPainterPath class to draw ellipse-----------------------------*/
//    QPainterPath ellipsePath;
//    ellipsePath.addEllipse(QPoint(200, 120), 50, 20);       // draw an ellipse shape at(200,120),horizontal radius:50,vertical radius:20

//    QPainter ellipsePathPainter(this);
//    ellipsePathPainter.setPen(QPen(QColor(79, 103, 25), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
//    ellipsePathPainter.setBrush(QColor(122, 163, 39));
//    ellipsePathPainter.drawPath(ellipsePath);

//    /*----------------------------- Draw an image -----------------------------*/
//    QImage image;
//    image.load("://tux.png");                               // load image

//    QPainter imagePainter(this);
//    imagePainter.drawImage(QPoint(100, 150), image);     // Draws the image at the point(100, 150).

    paintAll();
}

void MainWindow::paintAll(QSvgGenerator *generator)
{
    QPainter painter;

    if (generator)
        painter.begin(generator);
    else
        painter.begin(this);

    /*----------------------------- Draw text -----------------------------*/
    painter.setFont(QFont("Times", 14, QFont::Bold));        // set the text font setting
    painter.drawText(QPoint(20, 30), "Testing");             // set the text on the screen at the position(20,30)

    /*----------------------------- Draw straight line -----------------------------*/
    painter.drawLine(QPoint(50, 60), QPoint(100, 100));     // draw straight line start from (50,60) and ends at (100,100)

    /*----------------------------- Draw rectangle -----------------------------*/
    painter.setBrush(Qt::BDiagPattern);
    painter.drawRect(QRect(40, 120, 80, 30));            // draw a rectangle at (x:40,y:120) with (width:80,height:30)

    /*----------------------------- Draw ellipse -----------------------------*/
    QPen ellipsePen;
    ellipsePen.setColor(Qt::red);                     // Set color to red
    ellipsePen.setStyle(Qt::DashDotDotLine);          // set line style

    painter.setPen(ellipsePen);                       // apply the QPen class to QPainter
    painter.drawEllipse(QPoint(80, 200), 50, 20);     // draw an ellipse shape at(80,200),horizontal radius:50,vertical radius:20

    /*----------------------------- Use QPainterPath class to draw rectangle-----------------------------*/
    QPainterPath rectPath;
    rectPath.addRect(QRect(150, 20, 100, 50));      // draw rectangle at (x:150,y:20) with (width:100,height:50)

    painter.setPen(QPen(Qt::red, 1, Qt::DashDotDotLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(Qt::yellow);
    painter.drawPath(rectPath);

    /*----------------------------- Use QPainterPath class to draw ellipse-----------------------------*/
    QPainterPath ellipsePath;
    ellipsePath.addEllipse(QPoint(200, 120), 50, 20);       // draw an ellipse shape at(200,120),horizontal radius:50,vertical radius:20

    painter.setPen(QPen(QColor(79, 103, 25), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter.setBrush(QColor(122, 163, 39));
    painter.drawPath(ellipsePath);

    /*----------------------------- Draw an image -----------------------------*/
    QImage image;
    image.load("://tux.png");                       // load image
    painter.drawImage(QPoint(100, 150), image);     // Draws the image at the point(100, 150).

    painter.end();
}

void MainWindow::on_actionSave_as_SVG_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save SVG", "", "SVG files (*.svg)");

    if (filePath == "")
        return;

    QSvgGenerator generator;
    generator.setFileName(filePath);
    generator.setSize(QSize(this->width(), this->height()));
    generator.setViewBox(QRect(0, 0, this->width(), this->height()));
    generator.setTitle("SVG Example");
    generator.setDescription("This SVG file is generate by Qt.");

    paintAll(&generator);
}
