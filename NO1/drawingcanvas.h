#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QVector>
#include <QMouseEvent>

class DrawingCanvas : public QWidget
{
    Q_OBJECT

public:
    enum CalculationType {
        None,
        SlowHull,
        ConvexHull
    };
    explicit DrawingCanvas(QWidget *parent = nullptr);

public slots:
    void clearCanvas();
    void runConvexHull();
    void runSlowConvexHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int orientation(const QPoint &p, const QPoint &q, const QPoint &r);
    QVector<QPoint> calculateSlowConvexHull();
    QVector<QPoint> calculateConvexHull();

private:
    QVector<QPoint> m_clickpoints;
    QVector<QPoint> m_hullPoints;
    CalculationType m_currentAlgorithm = None;
    long long m_iterationCount = 0;

signals:
};

bool comparePoints(const QPoint &a, const QPoint &b);

#endif // DRAWINGCANVAS_H
