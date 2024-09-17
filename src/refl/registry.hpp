#pragma once
#include <type_traits>

namespace refl
{
	template<typename T, template<typename> typename Registry>
	struct is_registered
	{
	template<typename U>
	static constexpr auto test(decltype(Registry<U>::reflector) *) -> std::true_type;

	template<typename U>
	static constexpr auto test(...) -> std::false_type;

	static constexpr bool value = decltype(test<T>(nullptr))::value;
	};

	template<typename T, template<typename> typename Registry>
	constexpr bool is_registered_v = is_registered<T, Registry>::value;

	template<typename T, template<typename> typename Registry>
	concept registered = is_registered_v<T, Registry>;
}

