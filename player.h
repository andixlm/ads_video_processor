#ifndef PLAYER_H
#define PLAYER_H

#include <QImage>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Player : public QThread
{
    Q_OBJECT

public:
    explicit Player(QObject* parent = nullptr);
    ~Player();

    bool isStopped() const;
    int getFrameRate() const;

    void play();
    void stop();
    bool loadVideo(std::string);

protected:
    void run();

private:
    bool mIsStopped;

    QMutex mMutex;
    QWaitCondition mWaitCondition;

    int mFrameRate;
    cv::Mat mFrame;
    cv::Mat mRGBFrame;
    cv::VideoCapture mCapture;

    QImage mImage;

signals:
    void processedImage(const QImage& image);
};

#endif // PLAYER_H
