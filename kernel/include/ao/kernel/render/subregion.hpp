/*
 *  Copyright (C) 2016 Matthew Keeter  <matt.j.keeter@gmail.com>
 *
 *  This file is part of the Ao library.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  Ao is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Ao.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <array>
#include <vector>
#include <utility>
#include <functional>

#include "ao/kernel/eval/interval.hpp"

class Region;

/*
 *  A Subregion is a view into a Region, used when recursively rendering
 *  to quickly get at position values without copying a lot of memory around.
 */
class Subregion
{
public:
    /*
     *  A subregion is constructed from a parent Region.
     *
     *  When that parent region is destroyed, all child subregions are
     *  invalidated (because their pointers point into the parent region)
     */
    Subregion(const Region& r);

    /*
     *  Splits the region along its largest axis
     *
     *  The returned regions become invalid if their parent is destroyed
     */
    std::pair<Subregion, Subregion> split() const;

    /*
     *  Splits a region along the larger of the X and Y axes
     *
     *  The returned regions become in valid if their parent is destroyed
     */
    std::pair<Subregion, Subregion> splitXY() const;

    /*
     *  Returns true if the region can be split
     */
    bool canSplit() const;
    bool canSplitXY() const;

    /*
     *  Splits this subregion into (1 << dims) other subregions
     *
     *  This function may only be called with relevant dimensions that are
     *  equal and divisible by 2
     *
     *  dims must be 2 or 3
     */
    std::vector<Subregion> splitEven(int dims) const;

    /*
     *  Returns true if we can octsect the given subregion
     */
    bool canSplitEven(int dims) const;

    /*
     *  Returns the number of voxels in this region
     */
    size_t voxels() const;

    class Axis
    {
    public:
        Axis(Interval bounds, const std::vector<float>& vs);

        /*
         *  Splits the region along a voxel boundary
         */
        std::pair<Axis, Axis> split() const;

        /*
         *  Accessor functions for the interval object
         */
        float lower() const { return bounds.lower(); }
        float upper() const { return bounds.upper(); }

        /*
         *  Returns the value at a given index.
         */
        float pos(size_t i) const { return ptr[i]; }

        /*  Bounds of this axis  */
        const Interval bounds;

        /*  This is a pointer into an array of voxel positions  */
        const float* const ptr;

        /*  min is the position within the global voxel space  */
        const size_t min;

        /*  size is the number of voxels in the space  */
        const size_t size;

    protected:
        /*
         *  Private constructor used when splitting Axis
         */
        Axis(Interval bounds, const float* values,
                      size_t size, size_t min);
    };

    const Axis X, Y, Z;

protected:
    /*
     *  Private constructor used when spliting
     */
    Subregion(const Axis& x, const Axis& y, const Axis& z);
};
