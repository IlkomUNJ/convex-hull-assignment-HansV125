#include "drawingcanvas.h"


DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget{parent}
{}

bool comparePoints(const QPoint &a, const QPoint &b){
    if (a.x() != b.x()){
        return a.x() < b.x();
    }
    return a.y() < b.y();
}

int DrawingCanvas::orientation(const QPoint &p, const QPoint &q, const QPoint &r)
{
    long long val = (long long)(q.y() - p.y()) * (r.x() - q.x()) - (long long)(q.x() - p.x()) * (r.y() - q.y());
    if (val == 0) return 0;
    return (val > 0) ? 1 : 2;
}

QVector<QPoint> DrawingCanvas::calculateSlowConvexHull()
{
    m_iterationCount = 0;
    if (m_clickpoints.size() < 3) return {};

    QVector<QPoint> Edges;
    for (int i = 0; i < m_clickpoints.size(); i++){
        for (int j = 0; j < m_clickpoints.size(); j++){
            if (i == j) continue;
            const QPoint& p = m_clickpoints.at(i);
            const QPoint& q = m_clickpoints.at(j);
            bool valid = true;

            for (int k = 0; k < m_clickpoints.size(); k++){
                if (k == i || k== j) continue;
                m_iterationCount++;
                const QPoint& r = m_clickpoints.at(k);
                if (orientation(p, q, r) == 2){
                    valid = false;
                    break;
                }
            }
            if (valid){
                Edges.append(p);
                Edges.append(q);
            }
        }
    }
    return Edges;
}

QVector<QPoint> DrawingCanvas::calculateConvexHull()
{
    m_iterationCount = 0;
    if (m_clickpoints.size() < 3) return {};

    QVector<QPoint> Points = m_clickpoints;
    std::sort(Points.begin(), Points.end(), comparePoints);

    int n = Points.size();
    QVector<QPoint> Lupper;
    QVector<QPoint> Llower;
    Lupper.append(Points[0]);
    Lupper.append(Points[1]);

    for (int i = 2; i < n; i++){
        Lupper.append(Points[i]);
        while (Lupper.size() > 2) {
            const QPoint &p = Lupper[Lupper.size() - 3];
            const QPoint &q = Lupper[Lupper.size() - 2];
            const QPoint &r = Lupper[Lupper.size() - 1];
            m_iterationCount++;

            if (orientation(p,q,r) == 2){
                Lupper.remove(Lupper.size() - 2);
            } else {
                break;
            }
        }
    }

    Llower.append(Points[n - 1]);
    Llower.append(Points[n - 2]);

    for (int i = n - 3; i >= 0; i--) {
        Llower.append(Points[i]);
        while (Llower.size() > 2){
            const QPoint &p = Llower[Llower.size() - 3];
            const QPoint &q = Llower[Llower.size() - 2];
            const QPoint &r = Llower[Llower.size() - 1];
            m_iterationCount++;

            if (orientation(p,q,r) == 2){
                Llower.remove(Llower.size() - 2);
            } else {
                break;
            }
        }
    }
    if (Llower.size() > 0){
        Llower.removeFirst();
    }
    if (Llower.size() > 0){
        Llower.removeLast();
    }
    QVector<QPoint> List = Lupper;
    List.append(Llower);
    return List;
}


void DrawingCanvas::clearCanvas()
{
    m_clickpoints.clear();
    m_hullPoints.clear();
    m_currentAlgorithm = None;
    m_iterationCount = 0;
    update();
}

void DrawingCanvas::runConvexHull()
{
    if (m_currentAlgorithm == ConvexHull){
        m_currentAlgorithm = None;
        m_hullPoints.clear();
        m_iterationCount = 0;
    } else {
        m_currentAlgorithm = ConvexHull;
        m_hullPoints = calculateConvexHull();
        if (m_hullPoints.size() < 3) {
            m_currentAlgorithm = None;
        }
    }
    update();
}

void DrawingCanvas::runSlowConvexHull()
{
    if (m_currentAlgorithm == SlowHull){
        m_currentAlgorithm = None;
        m_hullPoints.clear();
        m_iterationCount = 0;
    } else {
        m_currentAlgorithm = SlowHull;
        m_hullPoints = calculateSlowConvexHull();
        if (m_hullPoints.size() < 6 && m_clickpoints.size() >= 3){
            if (m_hullPoints.size() == 4) {
            } else {
                m_currentAlgorithm = None;
            }
        }
    }
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QPen pen(Qt::red, 5, Qt::SolidLine);
    painter.setRenderHint(QPainter::Antialiasing);
    if (m_currentAlgorithm == SlowHull) {
        QPen linePen(Qt::blue, 2, Qt::SolidLine);
        painter.setPen(linePen);
        for (int i = 0; i < m_hullPoints.size(); i += 2) {
            const QPoint& p1 = m_hullPoints.at(i);
            const QPoint& p2 = m_hullPoints.at(i + 1);
            painter.drawLine(p1, p2);
        }
    } else if (m_currentAlgorithm == ConvexHull) {
        QPen linePen(Qt::blue, 2, Qt::SolidLine);
        painter.setPen(linePen);
        for (int i = 0; i < m_hullPoints.size(); i++){
            const QPoint& p1 = m_hullPoints.at(i);
            const QPoint& p2 = m_hullPoints.at((i + 1) % m_hullPoints.size());
            painter.drawLine(p1,p2);
        }
    }
    painter.setPen(pen);
    for (const QPoint& point : std::as_const(m_clickpoints)) {
        painter.drawPoint(point);
    }

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 10));
    QString iterationText = QString("Total Iteration Done: %1").arg(m_iterationCount);
    painter.drawText(QPoint(10,20), iterationText);
    QString pointCountText = QString("Points (N): %1").arg(m_clickpoints.size());
    painter.drawText(QPoint(10,40), pointCountText);
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() ==Qt::LeftButton) {
        m_clickpoints.append(event->pos());
        m_hullPoints.clear();
        m_currentAlgorithm = None;
        update();
    }
}
