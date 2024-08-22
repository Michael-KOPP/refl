#include <iostream>
#include <refl/refl.hpp>

class serializer
{
public:
	template<typename T, typename U, typename ... Args>
	void serialize(refl::reflector<T, Args...> const& reflector, U const& t) requires(std::is_base_of_v<T, U>) {
		apply([&] (auto&& ... args) {
			((std::cout << args.name() << " : " << static_cast<T const&>(t).*args.ptr() << std::endl), ...);
			std::cout << std::endl;
		}, reflector);
	}
};

struct Foo
{
	size_t age;
	size_t size;
	std::string name;
};

struct Bar : public Foo
{
	size_t krick;
	double proba;
	bool on;
};

int main()
{
	constexpr auto fooReflector = refl::refl<Foo>("Foo")
		.add("age", &Foo::age)
		.add("size", &Foo::size)
		.add("name", &Foo::name);

	constexpr auto barReflector = refl::refl<Bar>("Bar")
		.add("krick", &Bar::krick)
		.add("proba", &Bar::proba)
		.add("on", &Bar::on);

	Foo foo1{ .age = 10, .size = 20 , .name = "Marc"}, foo2{.age = 20, .size = 30, .name = "Pierre"};
	Bar bar1{ .krick = 10, .proba = 0.1 , .on= false }, bar2{ .krick = 20, .proba = 0.2 , .on = true };
	serializer serializer;

	serializer.serialize(fooReflector, foo1);
	serializer.serialize(fooReflector, foo2);

	serializer.serialize(fooReflector, bar1);

	serializer.serialize(barReflector, bar1);
	serializer.serialize(barReflector, bar2);

	return 0;
}