//          Copyright Odin Holmes 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../types/list.hpp"

namespace kvasir {
	namespace mpl {
		namespace c {
			template<typename Input, typename C = listify>
			struct push_back {
				template<typename...Ts>
				using f = KVASIR_D_CALL(C, Ts) <Ts..., Input >;
			};
		}
		namespace impl {
			template <typename Elem, typename List>
			struct push_back_impl {
				// invalid lists get ignored
				using f = Elem;
			};

			/// kvasir::mpl::list implementation
			template <typename Elem, typename... Ts>
			struct push_back_impl<Elem, mpl::list<Ts...>> {
				using f = mpl::list<Ts..., Elem>;
			};
		}

		/// push an element to the back of a list
		/// be wary that pushing to the back of a list can be a linear operation, and is therefore
		/// not recommended as a way of adding to a list
		/// instead, it is conventional to recurse backwards and push to the front instead
		template <typename Elem, typename List>
		using push_back = typename impl::push_back_impl<Elem, List>::f;
	}
}