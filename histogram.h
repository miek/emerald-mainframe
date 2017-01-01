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

#include <vector>

class Histogram
{
public:
	Histogram(int horizontal_bins, int vertical_bins, int history_count);

	void insert(int hbin, float value);

private:
	struct HBin {
		int pos;
		std::vector<int> items;

		void insert(int value) {
			items[pos++] = value;
			pos &= items.size();
		}
	};
	std::vector<HBin> hbins;
	int vertical_bins;
};
