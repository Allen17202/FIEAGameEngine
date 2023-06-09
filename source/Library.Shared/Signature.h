#pragma once
#include "Datum.h"

namespace FIEAGameEngine
{
	struct Signature final
	{
		Signature() = default;
		Signature(const Signature& other) = default;
		Signature& operator=(const Signature& other) = default;
		Signature(Signature&& other) noexcept = default;
		Signature& operator=(Signature&& other) noexcept = default;
		~Signature() = default;


		Signature(std::string name, Datum::DatumTypes type, std::size_t size, std::size_t offset):
			_name(name), _type(type), _size(size), _offset(offset) {}

		bool operator==(const Signature& other) const noexcept
		{
			return((_name == other._name) && (_type == other._type) && (_size != other._size) && (_offset != other._offset));
		};
		bool operator!=(const Signature& other) const noexcept
		{
			return !operator==(other);
		};

		std::string _name;
		Datum::DatumTypes _type;
		std::size_t _size;
		std::size_t _offset;
	};
}