#include "player.h"

const int FRAME_CHANNEL_RGB = 3;

Player::Player(QObject* parent) :
    QThread(parent)
{
    mIsStopped = true;
}

Player::~Player()
{
    mMutex.lock();

    mIsStopped = true;
    mCapture.release();
    mWaitCondition.wakeOne();

    mMutex.unlock();

    wait();
}

bool Player::isStopped() const
{
    return mIsStopped;
}

bool Player::isOpened() const
{
    return mCapture.isOpened();
}

int Player::getFrameRate() const
{
    return mFrameRate;
}

void Player::play()
{
    if (!isRunning()) {
        if (isStopped()) {
            mIsStopped = false;
        }

        start();
    }
}

void Player::pause()
{
    mIsStopped = true;
}

void Player::stop()
{
    if (!isStopped())
        pause();

    if (mCapture.get(CV_CAP_PROP_POS_AVI_RATIO) != 0)
        mCapture.set(CV_CAP_PROP_POS_AVI_RATIO, 0); // Set video to its start.

    emit emptyImage();
}

bool Player::loadVideo(std::string fileName)
{
    mCapture.open(fileName);

    if (mCapture.isOpened()) {
        mFrameRate =
                static_cast<int>(mCapture.get(CV_CAP_PROP_FPS));
        return true;
    }

    return false;
}

bool Player::unpackVideo(std::string dirName)
{
    if (!mCapture.isOpened())
        return false;

    double currentTimePosition = mCapture.get(CV_CAP_PROP_POS_MSEC);
    mCapture.set(CV_CAP_PROP_POS_AVI_RATIO, 0); // Set video to its start position.

    for (int frameCount = 0; mCapture.read(mFrame); ++frameCount) {
        if (mFrame.channels() == FRAME_CHANNEL_RGB) {
            cv::cvtColor(mFrame, mRGBFrame, CV_BGR2RGB);
            mImage = QImage(static_cast<const unsigned char*>(mRGBFrame.data),
                                  mRGBFrame.cols, mRGBFrame.rows, QImage::Format_RGB888);
        } else {
            mImage = QImage(static_cast<const unsigned char*>(mFrame.data),
                            mFrame.cols, mFrame.rows, QImage::Format_Indexed8);
        }

        mImage.save(QString::fromStdString(dirName) +
                    QString("\\frame_") + QString::number(frameCount)
                    + QString(".jpg"));
    }

    mCapture.set(CV_CAP_PROP_POS_MSEC, currentTimePosition);

    return true;
}

bool Player::closeVideo()
{
    if (!mCapture.isOpened())
        return false;

    mCapture.release();
    emit emptyImage();

    return true;
}

void Player::run()
{
    int delay = 1000 / mFrameRate;

    while(!mIsStopped) {
        if (!mCapture.read(mFrame)) {
            mIsStopped = true;
            emit emptyImage();
        }

        if (mFrame.channels() == FRAME_CHANNEL_RGB) {
            cv::cvtColor(mFrame, mRGBFrame, CV_BGR2RGB);
            mImage = QImage(static_cast<const unsigned char*>(mRGBFrame.data),
                                  mRGBFrame.cols, mRGBFrame.rows, QImage::Format_RGB888);
        } else {
            mImage = QImage(static_cast<const unsigned char*>(mFrame.data),
                            mFrame.cols, mFrame.rows, QImage::Format_Indexed8);
        }

        emit processedImage(mImage);
        msleep(delay);
    }
}
