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
    bool isOpened() const;
    int getFrameRate() const;

    void play();
    void pause();
    void stop();
    bool loadVideo(std::string);
    bool unpackVideo(std::string);
    bool closeVideo();

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
    void emptyImage();
};

#endif // PLAYER_H
