#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // Create three arrays to store the shapes of hour hand,minute hand,and second hand
    // each of the arrays contains three sets of coordinates
    static const QPoint hourHand[3] =
    {
        QPoint(4,  4),
        QPoint(-4, 4),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] =
    {
        QPoint(4,  4),
        QPoint(-4, 4),
        QPoint(0, -70)
    };
    static const QPoint secondHand[3] =
    {
        QPoint(2,  2),
        QPoint(-2, 2),
        QPoint(0, -90)
    };

    // Create the painter and move it to the center of the main window
    int      side = qMin(width(), height());
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 250.0, side / 250.0);

    // Drawing the dials
    for (int i = 0; i < 60; ++i)
    {
        if ((i % 5) != 0)    // The dial at every 5 minutes will draw slightly longer
            painter.drawLine(92, 0, 96, 0);
        else
            painter.drawLine(86, 0, 96, 0);
        painter.rotate(6.0); // Each dial is rotated by an increment of 6 degrees
    }

    // Drawing the hands of the clock
    QTime time = QTime::currentTime();
    // Draw hour hand
    painter.save();
    painter.rotate((time.hour() * 360) / 12);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(hourHand, 3);     // Draws the convex polygon
    painter.restore();
    // Draw minute hand
    painter.save();
    painter.rotate((time.minute() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawConvexPolygon(minuteHand, 3);   // Draws the convex polygon
    painter.restore();
    // Draw second hand
    painter.save();
    painter.rotate((time.second() * 360) / 60);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    painter.drawConvexPolygon(secondHand, 3);   // Draws the convex polygon
    painter.restore();
}
