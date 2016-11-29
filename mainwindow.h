#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QSlider>
#include <QShortcut>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QMediaMetaData>
#include <QProgressBar>
#include <QLabel>
#include <QDial>
#include <QVideoWidgetControl>
#include <QBoxLayout>
#include <QKeyEvent>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QKeyEvent>
#include <QMouseEvent>

#include <database.h>

namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DbManager db = DbManager("C:\\Users\\PRANAYUMORYE\\Desktop\\ratings .sqlite");

    bool paused = false;
        bool muted = false;

        QStringList playlistStringList;

        QStringList all_artists;
        QStringList all_albums;
        QStringList all_tracks;


        QString status_bar_message = "";
        int volume = 50;

    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_actionStop_triggered();

    void on_actionAdd_to_Playlist_triggered();

    void on_actionHide_triggered(bool checked);

    void on_actionNext_triggered();

    void on_actionPrev_triggered();

    void on_actionClear_Playlist_triggered();

    void on_actionMute_triggered(bool checked);

    void on_action16_9_triggered();

    void on_action5_4_triggered();

    void on_actionFavourite_triggered();

    void metadataHandler();
    void on_actionStar1_triggered();

    void on_actionStar2_triggered();

    void on_actionStar3_triggered();

    void on_actionStar4_triggered();

    void on_actionStar5_triggered();

    void on_action1_0x_triggered();

    void on_action1_5x_triggered();

    void on_action2_0x_triggered();

    void on_action5_0x_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    QVideoWidget* vw;
    QSlider* slider;
    QSlider* vs;
    QShortcut* shortcut;
    QGraphicsVideoItem *item;
    QMediaPlaylist *pl;
    QListWidget *ql;
    QGraphicsVideoItem *videoItem;
    QDial *dial;


protected:

};

#endif // MAINWINDOW_H
