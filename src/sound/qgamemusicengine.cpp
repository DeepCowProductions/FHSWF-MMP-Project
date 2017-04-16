#include "qgamemusicengine.h"
#include "QUrl"
#include "QMediaContent"
#include "QFileInfo"

QGameMusicEngine::QGameMusicEngine(QObject *parent) : QObject(parent)
{
    enabled = false;
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
    playlist = new QMediaPlaylist();
    playlist->addMedia(QMediaContent(QUrl::fromLocalFile(QFileInfo(fileName).absoluteFilePath())));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    if(playlist->playbackMode() != QMediaPlaylist::Loop) {
        qDebug() << "QGameMusicEngine::loadGameMusic something went wrong by setting the PlayBackMode";
    }
    enabled = true;
    return true;
}

void QGameMusicEngine::playGameMusic()
{
    if(enabled) {
        if(playlist->isEmpty()) {
            qDebug() << "QGameMusicEngine::playGameMusic: " << playlist->errorString();
        }
        else {
            player = new QMediaPlayer(this);
            player->setPlaylist(playlist);
            if(player->playlist() != NULL)
                player->play();
            player->setVolume(100);
            qDebug() << player->errorString();
        }
    }
}

void QGameMusicEngine::stopGameMusic()
{
    if(player->state() == QMediaPlayer::PlayingState) {
        player->stop();
    }
}

bool QGameMusicEngine::pauseGameMusic()
{
    if(player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    }
    if(player->state() == QMediaPlayer::PausedState)
        return true;
    return false;
}

bool QGameMusicEngine::isPlaying()
{
    if(player->mediaStatus() == QMediaPlayer::NoMedia)
        return false;
    return true;
}

void QGameMusicEngine::clearPlayList()
{
    qDebug() << "Clear playlist: " << playlist->clear();
    qDebug() << "Media in playlist: " << playlist->mediaCount();
}
