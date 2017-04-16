#ifndef QGAMEMUSICENGINE_H
#define QGAMEMUSICENGINE_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QFile>

/**
 * @brief The QGameMusicEngine class for the gamemusic in Space Invaders
 */
class QGameMusicEngine : public QObject
{
    Q_OBJECT
public:
    explicit QGameMusicEngine(QObject *parent = 0);

    void startGameMusic(bool newVal){enabled = newVal;}
    bool isPlaying()const{return enabled;}
signals:

public slots:
    /**
     * @brief SoundEngine::loadSound Preload a file, so that it can be played with low latency afterwrds.
     * @param fileName Must be a .wav file.
     * @return True on success
     */
    bool loadGameMusic(const QString &fileName);

    /**
     * @brief playGameMusic plays the gamemusic of the playlist
     */
    void playGameMusic();

    /**
     * @brief stopGameMusic stops the gamemusic
     */
    void stopGameMusic();

    /**
     * @brief pauseGameMusic pauses the gamemusic
     * @return true on success
     */
    bool pauseGameMusic();

    /**
     * @brief isPlaying
     * @return True, if the gamemusic is playing
     */
    bool isPlaying();

    void clearPlayList();

private:
    bool enabled;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;

};

#endif // QGAMEMUSICENGINE_H
