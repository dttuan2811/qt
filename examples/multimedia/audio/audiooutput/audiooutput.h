/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <math.h>

#define BUFFER_SIZE 32768
#define SECONDS 3

#include <QObject>
#include <QMainWindow>
#include <QIODevice>
#include <QTimer>
#include <QPushButton>
#include <QComboBox>

#include <QAudioOutput>

class Generator : public QIODevice
{
    Q_OBJECT
public:
    Generator(QObject *parent);
    ~Generator();

    void start();
    void stop();

    char *t;
    int  len;
    int  pos;
    int  total;
    char *buffer;
    bool finished;
    int  chunk_size;

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    int putShort(char *t, unsigned int value);
    int putLong(char *t, unsigned int value);
    int fillData(char *start, int frequency, int seconds);
};

class AudioTest : public QMainWindow
{
    Q_OBJECT
public:
    AudioTest();
    ~AudioTest();

    QAudioDeviceId  device;
    Generator*        gen;
    QAudioOutput*     audioOutput;
    QIODevice*        output;
    QTimer*           timer;
    QAudioFormat      settings;

    bool              pullMode;
    char*             buffer;

    QPushButton*      button;
    QPushButton*      button2;
    QComboBox*     deviceBox;

private slots:
    void status();
    void writeMore();
    void toggle();
    void togglePlay();
    void state(QAudio::State s);
    void deviceChanged(int idx);
};
