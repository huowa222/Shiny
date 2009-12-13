/*
The zlib/libpng License

Copyright (c) 2007 Aidin Abedi, http://shinyprofiler.sourceforge.net

This software is provided 'as-is', without any express or implied warranty. In no event will
the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following
restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that 
       you wrote the original software. If you use this software in a product, 
       an acknowledgment in the product documentation would be appreciated but is 
       not required.

    2. Altered source versions must be plainly marked as such, and must not be 
       misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SHINY_DATA_H
#define SHINY_DATA_H

#include "ShinyPrereqs.h"

namespace Shiny {


//-----------------------------------------------------------------------------
	
	struct ProfileLastData {
		uint32_t entryCount;
		tick_t selfTicks;
	};


//-----------------------------------------------------------------------------

	struct ProfileData {

		template <typename T>
		struct Data {
			T cur;
			float avg;

			void computeAverage(float a_damping) { avg = a_damping * (avg - cur) + cur; }
			void copyAverage(void) { avg = (float) cur; }
			void clear(void) { cur = 0; avg = 0; }
		};


		Data<uint32_t> entryCount;
		Data<tick_t> selfTicks;
		Data<tick_t> childTicks;


		tick_t totalTicksCur(void) const { return selfTicks.cur + childTicks.cur; }
		float totalTicksAvg(void) const { return selfTicks.avg + childTicks.avg; }

		void computeAverage(float a_damping) {
			entryCount.computeAverage(a_damping);
			selfTicks.computeAverage(a_damping);
			childTicks.computeAverage(a_damping);
		}

		void copyAverage(void) {
			entryCount.copyAverage();
			selfTicks.copyAverage();
			childTicks.copyAverage();
		}

		void clearAll(void) {
			entryCount.clear();
			selfTicks.clear();
			childTicks.clear();
		}

		void clearCurrent(void) {
			entryCount.cur = 0;
			selfTicks.cur = 0;
			childTicks.cur = 0;
		}
	};


} // namespace Shiny

#endif // ifndef SHINY_*_H