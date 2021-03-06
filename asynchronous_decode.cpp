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

#include "asynchronous_decode.h"
#include <assert.h>
#include "ffmpeg.h"
 QVector<short> AsynchronousDecoder(QString file,MEAudioDecoder *decoder)
{
    do{
         decoder->dealloc();
    }
    while(decoder->OpenFile(file)<0);
    if(decoder->getSuccessFlag()<0)
        return QVector<short>();
    QVector<short> data;
    decoder->decoder(data);
//    plot->update(data);
    qDebug()<<"decode finsih";
    return data;
}

int AsynchronousEncoder(QString file,MEAudioDecoder *decoder,int64_t time,int frames)
{
      return ffmpeg_conver_audio(decoder->getFileName().toLocal8Bit().data(),
                                 file.toLocal8Bit().data(),
                                 decoder->getSampleRate(),
                                 decoder->getChannels(),
                                 time,
                                 frames);
    qDebug()<<"encode finish";
}

void AsychronousInsertMusic(QString file,InsterMusicParam param)
{
    MEAudioDecoder *decoder[2]={param.decoder1,param.decoder2};
    int64_t time=param.time;
    double encodeFrame1=param.encodeFrame1;
    double encoderFrame2=param.encoderFrame2;
        ffmpeg_conver_audio(decoder[0]->getFileName().toLocal8Bit().data(),
                            decoder[1]->getFileName().toLocal8Bit().data(),
                            file.toLocal8Bit().data(),
                            decoder[0]->getSampleRate(),
                            decoder[0]->getChannels(),
                            time,
                            encodeFrame1,
                            encoderFrame2);
        qDebug()<<"encode finish";
}
