//
// Vectorized and parallelized version of libnoise using the zacc SIMD toolkit
// Copyright (C) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Original libnoise: 
// Copyright (C) 2003, 2004 Jason Bevins
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#pragma once

#include <thread>
#include <mutex>
#include "util/memory.hpp"

namespace zacc {

	/**
	 * @brief provides cloning functionality
	 * @tparam base_t base type
	 * @tparam concrete_t complete composed type
	 */
	template<typename Base, typename Concrete>
	class cloneable : public Base {
	public:
		FORWARD(cloneable);

		virtual ~cloneable() {
		}

		/**
		 * @brief thread safe clone wrapper
		 * @return base pointer to new instance
		 */
		virtual std::shared_ptr<base_t> clone() const {
            return zacc::make_shared<concrete_t>(static_cast<concrete_t const &>(*this));
		}
	};
}