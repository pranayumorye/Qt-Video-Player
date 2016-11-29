#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

#include <QtWidgets>


    MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    player->setVideoOutput(vw);
    pl = new QMediaPlaylist(player);
    player->setPlaylist(pl);

    QWidget *window = new QWidget;
    this->setCentralWidget(window);

    ql = new QListWidget(this);

    QBoxLayout *disp = new QHBoxLayout;
    disp->addWidget(vw,3);
    disp->addWidget(ql);

    QBoxLayout *all= new QVBoxLayout;
    all->addLayout(disp);
    window->setLayout(all);



    dial = new QDial(this);
    dial->setOrientation(Qt::Horizontal);
    dial->setRange(0,100);
    dial->setValue(50);
    dial->setNotchesVisible(true);
    dial->setMinimumSize(75,75);


    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    //slider->setMinimumWidth(1200);
    slider->adjustSize();
    slider->setMaximumWidth(5000);



    QLabel *label = new QLabel;
    ui->statusBar->addWidget(label);
    //label->setText(QString(player->duration()));



    ui->statusBar->addWidget(slider);
    ui->statusBar->addWidget(dial);

    player->setVolume(50);


    ui->statusBar->setMinimumHeight(75);

    vw->setMinimumSize(500,250);


    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);
    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);
    connect(dial,&QDial::valueChanged,player,&QMediaPlayer::setVolume);
    connect(ql,&QListWidget::currentRowChanged,pl,&QMediaPlaylist::setCurrentIndex);
    connect(pl,&QMediaPlaylist::currentMediaChanged,this,&MainWindow::metadataHandler);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","C:\\Pranay\\Hollywoo","Video File(*.*)");
    on_actionStop_triggered();
    player->setMedia(QUrl::fromLocalFile(filename));
    pl->clear();
    pl->addMedia(QUrl::fromLocalFile(filename));
    ql->clear();
    ql->addItem(filename);
    qDebug()<<player->currentMedia().canonicalUrl().toString();
    db.addTrack(player->currentMedia().canonicalUrl().toString());
    metadataHandler();
}

void MainWindow::on_actionPlay_triggered()
{
    if(ui->actionPlay->text()=="Play")
    {
    player->play();
    ui->actionPlay->setText("Pause");
    }

    else
    {
        ui->actionPlay->setText("Play");
        player->pause();
    }
}


void MainWindow::on_actionPause_triggered()
{
}



void MainWindow::on_actionStop_triggered()
{
    player->stop();
}


void MainWindow::on_actionAdd_to_Playlist_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open a File","C:\\Pranay\\Hollywoo","Video File(*.*)");
    pl->addMedia(QUrl::fromLocalFile(filename));
    ql->addItem(filename);

}

void MainWindow::on_actionHide_triggered(bool checked)
{
    if(checked)
    {
        ql->hide();
    }
    else{
        ql->show();
    }

}

void MainWindow::on_actionNext_triggered()
{
    player->stop();
    pl->next();
    player->play();
    if(pl->isEmpty())
    {
        qDebug()<<"empty";
    }
}

void MainWindow::on_actionPrev_triggered()
{
    pl->previous();
    player->play();
}

void MainWindow::on_actionClear_Playlist_triggered()
{
    pl->clear();
    ql->clear();
}

void MainWindow::on_actionMute_triggered(bool checked)
{
   if(checked)
    {
       player->setMuted(true);
       dial->setValue(0);
    }
   else{
       player->setMuted(false);
       dial->setValue(50);
   }

}


void MainWindow::on_action16_9_triggered()
{
    vw->setAspectRatioMode(Qt::KeepAspectRatio);
}

void MainWindow::on_action5_4_triggered()
{
    vw->setAspectRatioMode(Qt::IgnoreAspectRatio);
}



void MainWindow::on_actionFavourite_triggered()
{


}

void MainWindow::metadataHandler()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QIcon hollowstar(":/ic_star_border_black_48dp_2x.png");

    db.current_path = player->currentMedia().canonicalUrl().toString();
    current_playing_rating = db.getRatingOfTrack(db.current_path);

    switch(current_playing_rating)
    {
        case 0:
            ui->actionStar1->setIcon(hollowstar);
            ui->actionStar2->setIcon(hollowstar);
            ui->actionStar3->setIcon(hollowstar);
            ui->actionStar4->setIcon(hollowstar);
            ui->actionStar5->setIcon(hollowstar);
            break;
        case 1:
            ui->actionStar1->setIcon(solidstar);
            ui->actionStar2->setIcon(hollowstar);
            ui->actionStar3->setIcon(hollowstar);
            ui->actionStar4->setIcon(hollowstar);
            ui->actionStar5->setIcon(hollowstar);
            break;
        case 2:
            ui->actionStar1->setIcon(solidstar);
            ui->actionStar2->setIcon(solidstar);
            ui->actionStar3->setIcon(hollowstar);
            ui->actionStar4->setIcon(hollowstar);
            ui->actionStar5->setIcon(hollowstar);
            break;
        case 3:
            ui->actionStar1->setIcon(solidstar);
            ui->actionStar2->setIcon(solidstar);
            ui->actionStar3->setIcon(solidstar);
            ui->actionStar4->setIcon(hollowstar);
            ui->actionStar5->setIcon(hollowstar);
            break;
        case 4:
            ui->actionStar1->setIcon(solidstar);
            ui->actionStar2->setIcon(solidstar);
            ui->actionStar3->setIcon(solidstar);
            ui->actionStar4->setIcon(solidstar);
            ui->actionStar5->setIcon(hollowstar);
            break;
        case 5:
            ui->actionStar1->setIcon(solidstar);
            ui->actionStar2->setIcon(solidstar);
            ui->actionStar3->setIcon(solidstar);
            ui->actionStar4->setIcon(solidstar);
            ui->actionStar5->setIcon(solidstar);
            break;
    }


    QString artist_name1;
    if(artist_list.size() == 0)
        current_playing_artist_name = "Unknown Artist";
    else
    {
        artist_name1 = artist_list.at(0);
        current_playing_artist_name = artist_name1;
    }

    if(current_playing_title != "")
    {
       }
}

void MainWindow::on_actionStar1_triggered()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QIcon hollowstar(":/ic_star_border_black_48dp_2x.png");

    db.setRatingOfTrack(player->currentMedia().canonicalUrl().toString(), 1);

    ui->actionStar1->setIcon(solidstar);
    ui->actionStar2->setIcon(hollowstar);
    ui->actionStar3->setIcon(hollowstar);
    ui->actionStar4->setIcon(hollowstar);
    ui->actionStar5->setIcon(hollowstar);
}

void MainWindow::on_actionStar2_triggered()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QIcon hollowstar(":/ic_star_border_black_48dp_2x.png");

    db.setRatingOfTrack(player->currentMedia().canonicalUrl().toString(), 2);
    ui->actionStar1->setIcon(solidstar);
    ui->actionStar2->setIcon(solidstar);
    ui->actionStar3->setIcon(hollowstar);
    ui->actionStar4->setIcon(hollowstar);
    ui->actionStar5->setIcon(hollowstar);
}

void MainWindow::on_actionStar3_triggered()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QIcon hollowstar(":/ic_star_border_black_48dp_2x.png");

    db.setRatingOfTrack(player->currentMedia().canonicalUrl().toString(), 3);
    ui->actionStar1->setIcon(solidstar);
    ui->actionStar2->setIcon(solidstar);
    ui->actionStar3->setIcon(solidstar);
    ui->actionStar4->setIcon(hollowstar);
    ui->actionStar5->setIcon(hollowstar);
}

void MainWindow::on_actionStar4_triggered()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QIcon hollowstar(":/ic_star_border_black_48dp_2x.png");

    db.setRatingOfTrack(player->currentMedia().canonicalUrl().toString(), 4);

    ui->actionStar1->setIcon(solidstar);
    ui->actionStar2->setIcon(solidstar);
    ui->actionStar3->setIcon(solidstar);
    ui->actionStar4->setIcon(solidstar);
    ui->actionStar5->setIcon(hollowstar);
}

void MainWindow::on_actionStar5_triggered()
{
    QIcon solidstar(":/ic_star_black_48dp_2x.png");
    QString temp = player->currentMedia().canonicalUrl().toString();
    db.setRatingOfTrack(temp, 5);
    ui->actionStar1->setIcon(solidstar);
    ui->actionStar2->setIcon(solidstar);
    ui->actionStar3->setIcon(solidstar);
    ui->actionStar4->setIcon(solidstar);
    ui->actionStar5->setIcon(solidstar);
}


void MainWindow::on_action1_0x_triggered()
{
    player->setPlaybackRate(1);
}

void MainWindow::on_action1_5x_triggered()
{
    player->setPlaybackRate(1.5);
}

void MainWindow::on_action2_0x_triggered()
{
    player->setPlaybackRate(2);
}

void MainWindow::on_action5_0x_triggered()
{
    player->setPlaybackRate(5);
}


