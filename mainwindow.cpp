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

#include "mainwindow.h"
#include <QMetaType>
#include "filesource.h"

MainWindow::MainWindow() : source("../datas.bin")
{
    setWindowTitle(tr("emerald-mainframe"));
    setCentralWidget(&specanWidget);

	qRegisterMetaType<uint64_t>("uint64_t");
	qRegisterMetaType<std::shared_ptr<std::vector<Sample>>>("std::shared_ptr<std::vector<Sample>>");

    connect(&source, &FileSource::samplesProduced, &specanWidget, &SpecanWidget::handleSamples);
    source.start();
}

