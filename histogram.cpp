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

#include "histogram.h"
#include <stdexcept>

Histogram::Histogram(int horizontal_bins, int vertical_bins, int history_count)
	: hbins(horizontal_bins), vertical_bins(vertical_bins)
{
	for (auto&& hbin : hbins) {
		hbin.pos = 0;
		hbin.items.reserve(history_count);
	}
}

void Histogram::insert(int hbin, float value)
{
	if (hbin >= hbins.size())
		throw new std::runtime_error("Histogram::insert: hbin value too large");

	hbins[hbin].insert(int(value * vertical_bins));
}
