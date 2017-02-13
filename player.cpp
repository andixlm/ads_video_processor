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
