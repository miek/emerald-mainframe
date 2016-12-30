/*
 *  Copyright (C) 2016, Mike Walters <mike@flomp.net>
 *
 *  This file is part of emerald-mainframe.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "filesource.h"
#include <QtConcurrent>
#include <chrono>
#include <thread>

FileSource::FileSource(const char *path)
{
    f = fopen(path, "rb");
    if (!f)
        throw new std::runtime_error("FileSource::FileSource: File not found");
}

FileSource::~FileSource()
{
    stop();
    if (f)
        fclose(f);
}

void FileSource::start()
{
    runThread = true;
    qDebug() << "running thread";
    future = QtConcurrent::run(this, &FileSource::produceSamples);
}

void FileSource::produceSamples()
{
    char buffer[0x4000];
    while (runThread) {
        auto result = fread(buffer, 1, 0x4000, f);
        if (result < 4) {
            qDebug() << "FileSource: Reached end of file" << result;
            rewind(f);
            continue;
        }

        auto magic = *(uint16_t*)buffer;
        auto frequency = *(uint16_t*)(buffer + 2);
        if (magic != 0x7F7F) {
            qDebug() << "FileSource: Out of sync (bad magic)";
            continue;
        }
        if (frequency < 0 || frequency > 8000) {
            qDebug() << "FileSource: Out of sync (bad frequency)";
            continue;
        }
        auto samples = std::make_shared<std::vector<std::complex<float>>>();
        for (int i = 4; i < 0x4000; i += 2) {
            samples->emplace_back(buffer[i] / 128.0f, buffer[i + 1] / 128.0f);
        }
        emit samplesProduced(frequency, 20000000, samples);
        std::this_thread::sleep_for(std::chrono::microseconds(819));
    }
}

void FileSource::stop()
{
    if (runThread) {
        runThread = false;
        future.waitForFinished();
    }
}

