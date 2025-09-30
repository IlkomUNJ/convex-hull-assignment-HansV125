#include "drawingwindow.h"
#include "drawingcanvas.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow{parent}
{
    setWindowTitle("Computer Graphics");
    resize(600, 400);

    QWidget *mainContainer = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainContainer);

    DrawingCanvas *canvas = new DrawingCanvas(this);

    QPushButton *SlowHullButton = new QPushButton("Run Slow Convex Hull");
    QPushButton *ConvexHullButton = new QPushButton("Run Convex Hull");
    QPushButton *clearButton = new QPushButton("Clear Canvas");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(SlowHullButton);
    buttonLayout->addWidget(ConvexHullButton);
    buttonLayout->addWidget(clearButton);

    mainLayout->addWidget(canvas);
    mainLayout->addLayout(buttonLayout);
    setCentralWidget(mainContainer);

    QObject::connect(SlowHullButton, &QPushButton::clicked, canvas, &DrawingCanvas::runSlowConvexHull);
    QObject::connect(ConvexHullButton, &QPushButton::clicked, canvas, &DrawingCanvas::runConvexHull);
    QObject::connect(clearButton, &QPushButton::clicked, canvas, &DrawingCanvas::clearCanvas);
}
