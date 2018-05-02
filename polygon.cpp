#include "polygon.h"

polygon::polygon(int x, int y, int r)
{
    x0 = x;
    y0 = y;
    R = r;
    for (int i = 0; i < 4; i++) {
        children[i] = nullptr;
    }
}

bool polygon::reqSplit(const QImage &img, int P)
{
    if (R == 1) return false;
    int min = 255;
    int max = 0;
    for (int i = x0; i < x0 + R; i++) {
        for (int j = y0; j < y0 + R; j++) {
            int intensity = qGray(img.pixel(i, j));
            if (intensity < min) min = intensity;
            if (intensity > max) max = intensity;
            if (max - min >= P) {
                return true;
            }
        }
    }
    return false;
}

void polygon::draw(QImage &grid)
{
    for (int i = x0; i < x0 + R; i++) grid.setPixel(i, y0 + R/2 - 1, qRgb(0, 0, 0));
    for (int j = y0; j < y0 + R; j++) grid.setPixel(x0 + R/2 - 1, j, qRgb(0, 0, 0));
}

int polygon::getIntensityFromPic(const QImage &img) {
    int intensity = 0;
    for (int i = x0; i < x0 + R; i++) {
        for (int j = y0; j < y0 + R; j++) {
            intensity += qGray(img.pixel(i, j));
        }
    }
    return intensity /= R * R;
}

void polygon::split(const QImage &img, QImage &grid, std::vector<polygon> &polyVector, int P)
{
    if (reqSplit(img, P)) {
        isEmpty = false;
        draw(grid);

//        qDebug() << "1";
        children[0] = new polygon(x0, y0, R/2);
        children[1] = new polygon(x0, y0 + R/2, R/2);
        children[2] = new polygon(x0 + R/2, y0, R/2);
        children[3] = new polygon(x0 + R/2, y0 + R/2, R/2);

//        qDebug() << "2";
        for (int i = 0; i< 4; i++) {
            children[i]->split(img, grid, polyVector, P);
        }

//        for (int x = x0; x <= x0 + R/2; x += R/2) {
//            for (int y = y0; y <= y0 + R/2; y += R/2) {
//                children[i] = new polygon(x, y, R/2);



//                qDebug() << "Hi first!!" << children[i]->getY0();
//                children[i]->split(img, grid, polyVector, P);
//                i++;
//            }
//        }
    } else {
        setIntensity(getIntensityFromPic(img));
    }
    polyVector.push_back(*this);
}







//void polygon::formNewPic(const std::vector<polygon> &polyVector, QImage &res)
//{
////    qDebug() << polyVector[polyVector.size() - 1].getR() << polyVector[polyVector.size() - 2].getR() << polyVector[polyVector.size() - 3].getR() << polyVector[polyVector.size() - 4].getR();
//    for (int k = 0; k < polyVector.size(); k++) {
//        if (polyVector[k].isEmpty) {
//            int px0 = polyVector[k].getX0();
//            int py0 = polyVector[k].getY0();
//            int pR = polyVector[k].getR();
//            int pintensity = polyVector[k].getIntensity();
//            for (int i = px0; i < px0 + pR; i++) {
//                for (int j = py0; j < py0 + pR; j++) {
//                    res.setPixel(i, j, qRgb(pintensity, pintensity, pintensity));
//                }
//            }
//        }
//    }
////    ui->label_pic_res->setPixmap(QPixmap::fromImage(res));
//}




