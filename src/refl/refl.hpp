#include <tuple>

namespace refl
{
	template<typename Parent, typename T>
	class member {
	public:
		using value_type = T;
	public:
		constexpr member(std::string_view const name, T Parent::* const ptr) : _name(name), _ptr(ptr) {

		}

		constexpr auto name() const -> std::string_view {
			return _name;
		}

		constexpr auto ptr() const -> T Parent::* {
			return _ptr;
		}
	private:
		std::string_view _name;
		T Parent::* _ptr;
	};

	template<typename T>
	struct is_member
	{
		constexpr static bool value = false;
	};

	template<typename Parent, typename T>
	struct is_member<member<Parent, T>>
	{
		constexpr static bool value = true;
	};

	template<typename T>
	constexpr bool is_member_v = is_member<T>::value;

	template<typename T>
	concept Member = is_member_v<T>;

	template<typename T, typename ... Args>
	struct reflector : public std::tuple<Args...>
	{
		using inner_tuple = std::tuple<Args...>;

		constexpr reflector(std::string_view const name, Args&& ... args) : std::tuple<Args...>(std::make_tuple<Args...>(std::forward<Args>(args)...)), _className(name) {

		}

		constexpr reflector(std::string_view const name, std::tuple<Args&&...>&& tuple) : std::tuple<Args...>(std::move(tuple)), _className(name) {

		}

		template<Member member>
		constexpr auto add(member&& m) const -> decltype(auto) {
			return reflector<T, Args..., member>(_className,
				std::tuple_cat(static_cast<inner_tuple const&>(*this), std::make_tuple(std::forward<member>(m)))
			);
		}

		template<typename U>
		constexpr auto add(std::string_view const name, U T::* const ptr) const -> decltype(auto) {
			return this->add(member<T, U>(name, ptr));
		}

	private:

		std::string_view _className;
	};

	template<typename T, typename ... Args>
	constexpr auto refl(std::string_view const name, Args&& ... args) -> decltype(auto) {
		return reflector<T, Args...>(name, std::forward<Args>(args)...);
	}

	template<typename Func, typename T, typename ... Args>
	auto apply(Func&& func, reflector<T, Args...>& r) -> decltype(auto) {
		return std::apply(func, static_cast<reflector<T, Args...>::inner_tuple&>(r));
	}

	template<typename Func, typename T, typename ... Args>
	auto apply(Func && func, reflector<T, Args...> const& r) -> decltype(auto) {
		return std::apply(func, static_cast<reflector<T, Args...>::inner_tuple const&>(r));
	}
}