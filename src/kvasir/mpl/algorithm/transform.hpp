//          Copyright Odin Holmes 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
#pragma once

#include "../compatability/dependent_call.hpp"
#include "../functional/bind.hpp"
#include "../functional/call.hpp"
#include "../types/list.hpp"

namespace kvasir {
	namespace mpl {
		namespace c {
			/// transform a list using a type wrapped predicate
			template <typename F, typename C = listify>
			struct transform {
				template <typename... Ts>
				using f = KVASIR_D_CALL(C, Ts)<typename F::template f<Ts>...>;
			};
			template <template <typename...> class F, typename C>
			struct transform<cfe<F, identity>, C> {
				template <typename... Ts>
				using f = typename dcall<C, sizeof...(Ts)>::template f<typename dcallf<bool(sizeof...(Ts))>::template f1<F, Ts>...>;
			};
			template <template <typename...> class F, template <typename...> class C>
			struct transform<cfe<F, identity>, cfe<C, identity>> {
				template <typename... Ts>
				using f = C<F<Ts>...>;
			};
			template <typename F, template <typename...> class C>
			struct transform<F, cfe<C, identity>> {
				template <typename... Ts>
				using f = C<typename F::template f<Ts>...>;
			};
		}

		/// transform each element in a list with a function
		template <typename List, template <typename...> class F>
		using transform = c::call<c::transform<c::cfe<F>, c::listify>, List>;
	}
}
