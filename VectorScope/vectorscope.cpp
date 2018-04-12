#include "vectorscope.h"

VectorScope::VectorScope(int width, int height)
            : width{width}, height{height} {
    pm = new QPixmap(width, height);
    painter = new QPainter(pm);
}

VectorScope::~VectorScope() {
    delete pm;
    delete painter;
}

const QPixmap* VectorScope::getPixmap() {
    return pm;
}

void VectorScope::processImage(QImage *image) {
    pm->fill(Qt::black);
    vectorscope.clear();
    for(int i = 0; i < image->size().height(); i++) {
        for(int j = 0; j < image->size().width(); j++) {
            QColor color = image->pixelColor(j, i);
            processPixelColor(color);
        }
    }
}

void VectorScope::processPixelColor(QColor const &color) {
    QPen pen;
    pen.setColor(color);
    painter->setPen(pen);
    double scale = 0.75;
    // form online source i figured the rotation of the colorwheel used in vectorscopes
    // is the following:
    // if 0 degree is around blue, red should be at 256 degree,
    // my calculations by default put red at the bottom. 256 - 90 = 166 degree
    // which i used turn the circle
    double hue = -166 + color.hueF() * 360;
    double sat = color.saturationF() * 255;
    QPointF point(sat * qSin(qDegreesToRadians(hue)) * scale + this->width/2,
            sat * qCos(qDegreesToRadians(hue)) * scale + this->height/2);
    painter->drawPoint(point);
    this->vectorscope.insert(std::make_pair(point, color));
}

