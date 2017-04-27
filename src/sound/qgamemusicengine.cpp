#include "qgamemusicengine.h"
#include "QUrl"
#include "QMediaContent"
#include "QFileInfo"
#include "QDir"

QGameMusicEngine::QGameMusicEngine(QObject *parent) : QObject(parent)
{
    enabled = false;
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist();
    player->setVolume(50);
}

bool QGameMusicEngine::loadGameMusic(const QString &fileName)
{
    if(!QFile::exists(fileName))
    {
        qDebug()<< "QGameMusicEngine::loadGameMusic File not found: " << fileName;
        return false;
    }
#ifdef DEBUG_QGAMEMUSICENGINE
    qDebug() << "QGameMusicEngine::loadGameMusic loading sound: " << fileName;
#endif
#ifdef Q_OS_ANDROID
    playlist->addMedia(QUrl(fileName));
#else
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath()));
    //QDir dir;
    //qDebug() << dir.absolutePath();
#endif
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    if(playlist->isEmpty()) {
        qDebug() << "QGameMusicEngine::playGameMusic: " << playlist->errorString();
        return false;
    }
    player->setPlaylist(playlist);
    if(playlist->playbackMode() != QMediaPlaylist::Loop) {
        qDebug() << "QGameMusicEngine::loadGameMusic: something went wrong by setting the PlayBackMode";
        return false;
    }
    return true;
}

void QGameMusicEngine::playGameMusic()
{
    if(!player)
        return;
    if(enabled) {
            if(player->playlist() != NULL)
                player->play();
            //### for debugging
            //qDebug() << "QGameMusicEngine::playGameMusic: " << player->errorString();
    }
}

void QGameMusicEngine::stopGameMusic()
{

    if(!player)
        return;
    if(player->state() == QMediaPlayer::PlayingState) {
        player->stop();
    }
}

bool QGameMusicEngine::pauseGameMusic()
{

    if(!player)
        return false;
    if(player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    }
    if(player->state() == QMediaPlayer::PausedState)
        return true;
    return false;
}

bool QGameMusicEngine::isPlaying()
{

    if(!player)
        return false;
    if(player->mediaStatus() == QMediaPlayer::NoMedia)
        return false;
    return true;
}

void QGameMusicEngine::clearPlayList()
{
    qDebug() << "Clear playlist: " << playlist->clear();
    qDebug() << "Media in playlist: " << playlist->mediaCount();
}
