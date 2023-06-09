#pragma once
#include <cstdint>
#include "RTTI.h"
#include "Factory.h"
namespace FIEAGameEngine
{
	class Foo : public RTTI
	{
		RTTI_DECLARATIONS(Foo, RTTI);

	public:
		explicit Foo(std::int32_t data = 0); // explicit means that 
		Foo(const Foo& rhs); // Copy Construcotr
		Foo(Foo&& rhs) noexcept; // Constructor
		Foo& operator=(const Foo& rhs); // Constructor
		Foo& operator=(Foo&& rhs) noexcept;
		virtual ~Foo();

		bool operator==(const Foo& rhs) const;
		bool operator!=(const Foo& rhs) const;

		std::int32_t Data() const;
		void SetData(std::int32_t data);

	private:
		std::int32_t* _data;
	};
	ConcreteFactory(Foo, RTTI);
}

