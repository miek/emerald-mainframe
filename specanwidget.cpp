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

#include "specanwidget.h"
#include <QDebug>

SpecanWidget::SpecanWidget() : fft(128), skipCount(1024)
{

}

void SpecanWidget::handleFFTResult(uint64_t frequency, int sample_rate, std::vector<Sample> &result)
{
	// TODO: things
}

void SpecanWidget::handleSamples(uint64_t frequency, int sample_rate, std::shared_ptr<std::vector<Sample>> samples)
{
	qDebug() << "got samples " << frequency;

	auto result = std::vector<Sample>(fft.getSize());
	auto end = samples->size() - fft.getSize();
	for (int i = skipCount; i < end; i += fft.getSize()) {
		fft.process(&result[0], &samples.get()[i]);
		handleFFTResult(frequency, sample_rate, result);
	}
}