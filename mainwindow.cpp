
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(1200, 800);
    pix = new QPixmap(700, 700);
    delta = 0.9 * pix->width() / (double)(2 * range);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    pix->fill(Qt::white);
    QPainter painter(pix);
    painter.setBrush(Qt::NoBrush);
    int textStep = range / 5;
    for(int i = 0; i <= 2 * range;i++)
    {
        painter.setPen(QPen(Qt::gray,1));
        painter.drawLine(pix->width()*(0.05+step*i),pix->height()*0.05,pix->width()*(0.05+step*i),pix->height()*0.95);
        painter.drawLine(pix->width()*0.05,pix->height()*(0.05+step*i),pix->width()*0.95,pix->height()*(0.05+step*i));
        painter.setPen(QPen(Qt::black,1));
        if(i % textStep == 0)
            painter.drawText(pix->width()*(0.04+step*i),pix->height()/1.90, QString::number((i-range)));
        if(i!=range && i % textStep == 0)
            painter.drawText(pix->width()/2.10,pix->height()*(0.955-step*i), QString::number((i-range)));
    }
    painter.setPen(QPen(Qt::black,3));
    painter.drawLine(pix->width()*0.05,pix->height()/2,pix->width()*0.95,pix->height()/2);
    painter.drawLine(pix->width()/2,pix->height()*0.95,pix->width()/2,pix->height()*0.05);
    painter.setPen(QPen(Qt::red,4));
    if(!polygonChosen && rect != nullptr && !lines.isEmpty())
    {
        painter.drawRect(*rect);
        for(int i = 0; i < lines.size(); i++)
        {
            painter.setPen(QPen(Qt::blue,3));
            painter.drawLine(getXY(lines[i].x1(), lines[i].y1()).first, getXY(lines[i].x1(), lines[i].y1()).second,
                             getXY(lines[i].x2(), lines[i].y2()).first, getXY(lines[i].x2(), lines[i].y2()).second);
            QVector<double> visible = DrawLiangaBarski(lines[i]);
            painter.setPen(QPen(Qt::green,3));
            painter.drawLine(getXY(visible[0], visible[1]).first, getXY(visible[0], visible[1]).second,
                             getXY(visible[2], visible[3]).first, getXY(visible[2], visible[3]).second);
        }
    }
    if(polygonChosen && !polygon.isEmpty() && !lines.isEmpty())
    {
        painter.setPen(QPen(Qt::red,4));
        for(int i = 1; i <= polygon.size(); i++)
        {
            painter.drawLine(getXY(polygon[i - 1].x(), polygon[i - 1].y()).first,
                             getXY(polygon[i - 1].x(), polygon[i - 1].y()).second,
                             getXY(polygon[i % polygon.size()].x(), polygon[i % polygon.size()].y()).first,
                             getXY(polygon[i % polygon.size()].x(), polygon[i % polygon.size()].y()).second);
        }
        for(int i = 0; i < lines.size(); i++)
        {
            painter.setPen(QPen(Qt::blue,3));
            painter.drawLine(getXY(lines[i].x1(), lines[i].y1()).first, getXY(lines[i].x1(), lines[i].y1()).second,
                             getXY(lines[i].x2(), lines[i].y2()).first, getXY(lines[i].x2(), lines[i].y2()).second);
            QVector<double> visible = DrawCyrusBeck(lines[i]);
            painter.setPen(QPen(Qt::green,3));
            if(visible.size() > 0)
            {
                qDebug("OK\n");
                painter.drawLine(getXY(visible[0], visible[1]).first, getXY(visible[0], visible[1]).second,
                             getXY(visible[2], visible[3]).first, getXY(visible[2], visible[3]).second);
            }
        }
    }
    ui->graph_label->setPixmap(*pix);
}

void MainWindow::updatePicture()
{
    rect = new QRect(QPoint(getXY(Xmin, Ymax).first, getXY(Xmin, Ymax).second),
                     QPoint(getXY(Xmax, Ymin).first, getXY(Xmax, Ymin).second));
    update();
}

QVector<double> MainWindow::DrawLiangaBarski(QLine line)
{
    double x1 = line.x1(), y1 = line.y1(), x2 = line.x2(), y2 = line.y2();
    double newx1, newx2, newy1, newy2;
    double dx = x2 - x1, dy = y2 - y1, t1 = 0, t2 = 1, temp;
    QVector<double> p = {-dx, dx, -dy, dy};
    QVector<double> q = {x1 - Xmin, Xmax - x1, y1 - Ymin, Ymax - y1};
    for (int i = 0; i < 4; i++)
    {
        if(p[i] != 0)
            temp = (q[i]) / p[i];
        else
            temp = INT_MAX;
        if (p[i] < 0)
        {
            t1 = std::max(t1, temp);
        }
        else
        {
            t2 = std::min(t2, temp);
        }
    }
    if (t1 < t2)
    {
        newx1 = line.x1() + t1 * p[1];
        newx2 = line.x1() + t2 * p[1];
        newy1 = line.y1() + t1 * p[3];
        newy2 = line.y1() + t2 * p[3];
    }
    return {newx1, newy1, newx2, newy2};
}

QVector<double> MainWindow::DrawCyrusBeck(QLine line)
{
    QPoint D = line.p2() - line.p1();
    QPoint orientier = polygon[2];
    double t1 = 0, t2 = 1;
    int i = 0;
    while (i != polygon.size())
    {
        QPoint p1 = polygon[i];
        i++;
        QPoint p2 = polygon[i % polygon.size()];
        QPoint n = getNormal(p1, p2, orientier);
        QPoint w = line.p1() - p1;
        double Q = QVector2D::dotProduct(QVector2D(w), QVector2D(n));
        double P = QVector2D::dotProduct(QVector2D(D), QVector2D(n));
        if (P == 0)
        {
            if (Q < 0)
            {
                return{};
            }
            else
            {
                continue;
            }
        }
        double t = -Q / P;
        if (P > 0)
        {
            t1 = std::max(t1, t);
        }
        else
        {
            t2 = std::min(t2, t);
        }
        orientier = p1;
    }
    if (t1 <= t2)
    {
        //qDebug("ok\n");
        double x1 = line.x1() + D.x() * t1;
        double y1 = line.y1() + D.y() * t1;
        double x2 = line.x1() + D.x() * t2;
        double y2 = line.y1() + D.y() * t2;
        return {x1, y1, x2, y2};
    }
    else
    {
        return {};
    }
}

QPoint MainWindow::getNormal(QPoint p1, QPoint p2, QPoint q)
{
    QPoint vect = p2 - p1;
    QPoint nTemp = QPoint(-vect.y(), vect.x());
    QPoint n = nTemp;
//    QPoint v = q - p1;
//    double insideOrOutside = v.x() * nTemp.y() - v.y() * nTemp.x();

//    if (insideOrOutside < 0)
//    {
//        n = QPoint(vect.y(), -vect.x());
//    }
//    else
//    {
//        n = QPoint(-vect.y(), vect.x());
//    }
    return n;
}

std::pair<double, double> MainWindow::getXY(double x, double y)
{
    std::pair<double, double> res;
    double centerX = pix->width()/2;
    double centerY = pix->height()/2;
    res.first = centerX + (double)delta * x;
    res.second = centerY - (double)delta * y;
    return res;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0, "open file", "*.txt");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        polygonChosen = false;
        lines.clear();
        QTextStream stream(&file);
        stream>>n;
        int x1, y1, x2, y2;
        for(int i = 0; i < n; i++)
        {
            stream>>x1>>y1>>x2>>y2;
            lines.push_back(QLine(x1, y1, x2, y2));
        }
        stream>>Xmin>>Ymin>>Xmax>>Ymax;
        rect = new QRect(QPoint(getXY(Xmin, Ymax).first, getXY(Xmin, Ymax).second),
                         QPoint(getXY(Xmax, Ymin).first, getXY(Xmax, Ymin).second));
        update();
    }
}


void MainWindow::on_zoomIn_clicked()
{
    if(range > 5)
    {
        range -= 5;
        step = 0.9/(2 * range);
        delta = 0.9 * pix->width() / (2 * range);
        updatePicture();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(range < 100)
    {
        range += 5;
        step = 0.9/(2 * range);
        delta = 0.9 * pix->width() / (2 * range);
        updatePicture();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(0, "open file", "*.txt");
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        polygonChosen = true;
        polygon.clear();
        lines.clear();
        QTextStream stream(&file);
        stream>>n>>k;
        int x1, y1, x2, y2;
        for(int i = 0; i < n; i++)
        {
            stream>>x1>>y1>>x2>>y2;
            lines.push_back(QLine(x1, y1, x2, y2));
        }
        for(int i = 0; i < k; i++)
        {
            stream>>x1>>y1;
            polygon.push_back(QPoint(x1, y1));
        }
        update();
    }
}

