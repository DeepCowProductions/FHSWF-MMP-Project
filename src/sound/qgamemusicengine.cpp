#include "qgamemusicengine.h"

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
    playlist->addMedia(QUrl(fileName));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    if(playlist->playbackMode() != QMediaPlaylist::Loop) {
        qDebug() << "QGameMusicEngine::loadGameMusic something went wrong by setting the PlayBackMode";
    }
    return true;
}

void QGameMusicEngine::playGameMusic()
{
    if(enabled) {
        if(playlist->isEmpty()) {
            qDebug() << "QGameMusicEngine::playGameMusic: " << playlist->errorString();
        }
        else {
            player = new QMediaPlayer();
            player->setPlaylist(playlist);
            if(player->playlist() != null)
                player->play();
        }
    }
}

void QGameMusicEngine::stopGameMusic()
{
    if(player->state() == QMediaPlayer::PlayingState) {
        player->stop();
        qDebug() << "Clear playlist: " << playlist->clear();
        qDebug() << "Media in playlist: " << playlist->mediaCount();
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
