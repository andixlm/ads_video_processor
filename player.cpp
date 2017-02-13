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
