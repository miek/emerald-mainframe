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

#pragma once

#include "source.h"
#include <QFuture>
#include <memory>

using Sample = std::complex<float>;

class FileSource : public Source
{
    Q_OBJECT

public:
    FileSource(const char *path);
    ~FileSource();

    void start() override;
    void stop() override;

signals:
    void samplesProduced(uint64_t frequency, int sample_rate, std::shared_ptr<std::vector<Sample>> samples);

private:
    void produceSamples();

    FILE *f;
    bool runThread = false;
    QFuture<void> future;
};
