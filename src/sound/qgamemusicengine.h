#ifndef QGAMEMUSICENGINE_H
#define QGAMEMUSICENGINE_H

#include <QObject>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QFile>

/**
 * @brief The QGameMusicEngine class for the gamemusic in Space Invaders
 *
 * @author Kuhmichel(10044128)
 * @author Grabelus(10044563)
 */
class QGameMusicEngine : public QObject
{
    Q_OBJECT
public:
    explicit QGameMusicEngine(QObject *parent = 0);

    /**
     * @brief startGameMusic is to enable the music
     * @param newVal true or false
     */
    void startGameMusic(bool newVal){enabled = newVal;}

    /**
     * @brief isPlaying is for checking if music is enabled
     * @return boolean
     */
    bool isPlaying()const{return enabled;}
signals:

public slots:
    /**
     * @brief loadGameMusic Preload a file, so that it can be played with a QPlayer
     * @param fileName is the path to the music file
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

    /**
     * @brief clearPlayList ia for clearing the playlist
     */
    void clearPlayList();

private:
    bool enabled;
    QMediaPlaylist *playlist;
    QMediaPlayer *player;
};

#endif // QGAMEMUSICENGINE_H
