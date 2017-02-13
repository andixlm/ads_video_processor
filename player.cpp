#include <QThread>

#include "player.h"

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

void Player::play()
{
    if (!isRunning()) {
        if (isStopped()) {
            mIsStopped = false;
        }

        start(LowPriority);
    }
}

void Player::stop()
{
    mIsStopped = true;
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
