#ifndef VECTORSCOPE_H
#define VECTORSCOPE_H

#include <iostream>

#include <QtMath>
#include <QPixmap>
#include <QPainter>
#include <map>

struct PointComparator {
    bool operator()(const QPointF &lhs, const QPointF &rhs) {
        return (lhs.x() < rhs.x() || (lhs.x() == rhs.x() && lhs.y() < rhs.y()));
    }
};

class VectorScope
{
public:
    VectorScope(int width, int height);
    ~VectorScope();
    const QPixmap* getPixmap();
    void processImage(QImage *image);

private:
    QPainter *painter;
    QPixmap *pm;
    int width, height;
    std::map<QPointF, QColor, PointComparator> vectorscope;

    void processPixelColor(QColor const &color);
};

#endif // VECTORSCOPE_H
