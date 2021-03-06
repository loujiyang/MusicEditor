/**************************************************************************
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>
#include <QList>
#include <QtGui>
#include "QWave2/Waveform.h"
QT_BEGIN_NAMESPACE
class QAction;
class QTableWidget;
class QLCDNumber;
QT_END_NAMESPACE
using namespace QWave2;
//![0]
class Plot;
class MEAudioDecoder;

class MainWindow : public QMainWindow
{
//![0]
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();
    QSize sizeHint() const {
        return QSize(500, 300);
    }
    QMap<QString,QWave2::Waveform*> *getWaveForm();
signals:
    void updateCursorPosition(Waveform* wave, double beg);
public slots:
    void showCurve(int num);
    void encoderFinish(int num);
private slots:
    void addFiles();
    void about();
    void translateMusicFormat();
    void insertMusic();
    void changeSelection(double beg, double dur, Waveform*);
    void setTime(Waveform*,double t);
//![1]
    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void metaStateChanged(Phonon::State newState, Phonon::State oldState);
    void aboutToFinish();
    void tableClicked(int row, int column);
//![1]

private:
    void setupActions();
    void setupMenus();
    void setupUi();

//![2]
    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::MediaObject *metaInformationResolver;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QList<Phonon::MediaSource> sources;
//![2]

    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *addFilesAction;
    QAction *translateAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QAction *insertMusicAction;
    QLCDNumber *timeLcd;
    QTableWidget *musicTable;
//    MEAudioDecoder *decoder;
    int previousRow;
    int justPaintRow;
    double dur;
    double beg;
    QMap<int,MEAudioDecoder*> decoders;
    QMap<QString,Waveform*> waveForms;
public:
    static QFutureWatcher< QVector< short > > *decoderWatcher;
    static QFutureWatcher<int> *encoderWatcher;
};

#endif

