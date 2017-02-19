#ifndef FIMAGE_H
#define FIMAGE_H

#include <QImage>
#include <QLabel>

#include "imagetree.h"

class FImage : public QImage
{
public:
    FImage();

private:
    ImageTree mTree;
};

#endif // FIMAGE_H
