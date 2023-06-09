#include "pch.h"
#include "Datum.h"
//#include <glm/gtx/string_cast.hpp>

using namespace std;
namespace FIEAGameEngine
{
	const HashMap<std::string,Datum::DatumTypes> Datum::_stringDatumTypesMap
	{
		std::make_pair("integer", Datum::DatumTypes::Integer),
		std::make_pair("float", Datum::DatumTypes::Float),
		std::make_pair("string", Datum::DatumTypes::String),
		std::make_pair("vector", Datum::DatumTypes::Vector),
		std::make_pair("matrix", Datum::DatumTypes::Matrix),
		std::make_pair("table", Datum::DatumTypes::Table)
	};

	const HashMap<Datum::DatumTypes,std::string> Datum::_datumTypesStringMap
	{
		std::make_pair(Datum::DatumTypes::Integer, "integer"),
		std::make_pair(Datum::DatumTypes::Float, "float"),
		std::make_pair(Datum::DatumTypes::String, "string"),
		std::make_pair(Datum::DatumTypes::Vector, "vector"),
		std::make_pair(Datum::DatumTypes::Matrix, "matrix"),
		std::make_pair(Datum::DatumTypes::Table, "table")
	};

	Datum::Datum(const Datum& other) :
		_type(other._type), _isExternal(other._isExternal)
	{
		if (other._isExternal)
		{
			_data = other._data;
			_capacity = other._capacity;
			_size = other._size;
		}
		else
		{
			Reserve(other._capacity);
			if (other._type == DatumTypes::String)
			{
				for (size_t i = 0; i < other._size; ++i)
				{
					PushBackString(other.GetString(i));
				}
			}
			else
			{
				memcpy_s(_data.vp, _capacity * _typeSizes[static_cast<int>(_type)], other._data.vp, other._capacity * _typeSizes[static_cast<int>(other._type)]);
				_size = other._size;
			}
		}
	}

	Datum& Datum::operator=(const Datum& other)
	{
		if (&other != this)
		{
			if (_type != DatumTypes::Unknown && other._type == DatumTypes::Unknown)
			{
				throw std::runtime_error("Operation invalid with Unknown Type");

			}

			if (!_isExternal)
			{
				Resize(0);
				_data.vp = nullptr;
			}

			_type = other._type;

			if (other._isExternal)
			{
				_data = other._data;
				_capacity = other._capacity;
				_size = other._size;
				_isExternal = true;
			}
			else
			{
				Resize(other._capacity);
				if (other._type == DatumTypes::String)
				{
					for (size_t i = 0; i < other._size; ++i)
					{
						SetString(other.GetString(i), i);
					}
				}
				else
				{
					memcpy_s(_data.vp,
						_size * _typeSizes[static_cast<int>(_type)],
						other._data.vp,
						other._size * _typeSizes[static_cast<int>(other._type)]);
				}
			}
		}
		return *this;
	}
	Datum& Datum::operator=(int32_t data)
	{
		SetType(DatumTypes::Integer);
		Resize(0);
		PushBackInt(data);
		return *this;
	}
	Datum& Datum::operator=(float data)
	{
		SetType(DatumTypes::Float);
		Resize(0);
		PushBackFloat(data);
		return *this;
	}
	Datum& Datum::operator=(const std::string& data)
	{
		SetType(DatumTypes::String);
		Resize(0);
		PushBackString(data);
		return *this;
	}
	Datum& Datum::operator=(const glm::vec4& data)
	{
		SetType(DatumTypes::Vector);
		Resize(0);
		PushBackVector(data);
		return *this;
	}
	Datum& Datum::operator=(const glm::mat4& data)
	{
		SetType(DatumTypes::Matrix);
		Resize(0);
		PushBackMatrix(data);
		return *this;
	}

	Datum& Datum::operator=(RTTI* const data)
	{
		SetType(DatumTypes::Pointer);
		Resize(0);
		PushBackPointer(data);
		return *this;
	}

	Datum& Datum::operator=(Scope& data)
	{
		SetType(DatumTypes::Table);
		Resize(1);
		SetTable(data);
		return *this;
	}

	Datum::Datum(Datum&& other) noexcept :
		_data(other._data), _size(other._size), _capacity(other._capacity), _type(other._type), _isExternal(other._isExternal)
	{
		other._data.vp = nullptr;
		other._size = 0;
		other._capacity = 0;
		other._type = DatumTypes::Unknown;
		other._isExternal = false;

	}

	Datum& Datum::operator=(Datum&& other) noexcept
	{
		if (&other != this)
		{
			if (!_isExternal)
			{
				Clear();
				free(_data.vp);
			}

			_data = other._data;
			_capacity = other._capacity;
			_size = other._size;
			_type = other._type;
			_isExternal = other._isExternal;

			other._data.vp = nullptr;
			other._size = 0;
			other._capacity = 0;
			other._type = DatumTypes::Unknown;
			other._isExternal = false;
		}
		return *this;
	}

	Datum::~Datum()
	{
		if (!_isExternal)
		{
			if (_type == DatumTypes::String)
			{
				Clear();
			}
			free(_data.vp);
		}
	}

	bool Datum::operator==(const Datum& rhs) const
	{
		bool equalFLag = false;
		if (rhs._type == _type && rhs._size == _size)
		{
			if (rhs._data.vp == _data.vp)
			{
				equalFLag = true;
			}
			else
			{
				if (_type == DatumTypes::String)
				{
					for (size_t i = 0; i < _size; ++i)
					{
						if (rhs._data.s[i] != _data.s[i])
						{
							return equalFLag;
						}
					}
					equalFLag = true;
				}
				else if (_type == DatumTypes::Pointer|| _type == DatumTypes::Table)
				{
					for (size_t i = 0; i < _size; ++i)
					{
						RTTI* l = _data.p[i];
						RTTI* r = rhs._data.p[i];
						if (l != r && l != nullptr && !(l->Equals(r)))
						{
							return equalFLag;
						}
					}
					equalFLag = true;
				}
				else
				{
					if (memcmp(_data.vp, rhs._data.vp, _size) == 0)
					{
						equalFLag = true;
					}
				}
			}
		}
		return equalFLag;
	}

	bool Datum::operator!=(const Datum& rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator!=(int32_t rhs) const
	{
		return !operator==(rhs);
	}

	bool Datum::operator==(int32_t rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::Integer && _size == 1 && FrontInt() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	  bool Datum::operator!=(float rhs) const
	{
		return !operator==(rhs);
	}

	  bool Datum::operator==(float rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::Float && _size == 1 && FrontFloat() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	  bool Datum::operator!=(const std::string& rhs) const
	{
		return !operator==(rhs);
	}

	  bool Datum::operator==(const std::string& rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::String && _size == 1 && FrontString() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	 bool Datum::operator!=(const glm::vec4& rhs) const
	{
		return !operator==(rhs);
	}

	 bool Datum::operator==(const glm::vec4& rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::Vector && _size == 1 && FrontVector() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	 bool Datum::operator!=(const glm::mat4& rhs) const
	{
		return !operator==(rhs);
	}

	 bool Datum::operator==(const glm::mat4& rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::Matrix && _size == 1 && FrontMatrix() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	 bool Datum::operator==(const RTTI* const rhs) const
	{
		bool equalsFlag = false;
		if (_type == DatumTypes::Pointer && _size == 1 && FrontPointer() == rhs)
		{
			equalsFlag = true;
		}
		return equalsFlag;
	}

	 bool Datum::operator!=(const RTTI* const rhs) const
	{
		return !operator==(rhs);
	}

	 Scope& Datum::operator[](std::uint32_t index)
	 {
		 return GetTable(index);
	 }

	 Datum::DatumTypes Datum::Type() const
	{
		return _type;
	}

	 void Datum::SetType(DatumTypes type)
	{
		if (_type != type)
		{
			if (_type != DatumTypes::Unknown)
			{
				throw std::runtime_error("Datum Type must be Unknown to be assigned a type");
			}
			_type = type;
		}
	}

	 std::size_t Datum::Size() const
	{
		return _size;
	}

	 std::size_t Datum::Capacity() const
	{
		return _capacity;
	}

	 bool Datum::isExternal() const
	{
		return _isExternal;
	}

	 void Datum::Resize(std::size_t value)
	{
		if (_isExternal)
		{
			throw runtime_error("Cannot resize from External Data");
		}
		if (_type == DatumTypes::Unknown && value != 0)
		{
			throw runtime_error("Cannot resize Unknown Data");
		}
		if (value == 0)
		{
			Clear();
			free(_data.vp);
			_capacity = 0;
			_size = 0;
			_data.vp = nullptr;
			return;
		}
		if (_type == DatumTypes::String && value < _size)
		{
			for (size_t i = value; i < _size; ++i)
			{
				_data.s[i].~basic_string();
			}
		}

		void* newData = realloc(_data.vp, value * _typeSizes[static_cast<int>(_type)]);
		assert(newData != nullptr);
		_data.vp = newData;

		if (_type == DatumTypes::String && value > _size)
		{
			for (size_t i = _size; i < value; ++i)
			{
				new (_data.s + i) std::string("vacant"s);
			}
		}
		_capacity = value;
		_size = value;
	}

	 void Datum::Clear()
	{
		if (_type == DatumTypes::String)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				_data.s[i].~basic_string();
			}
		}
		_size = 0;
	}

	 void Datum::SetStorageInt(int32_t* values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::Integer);
		assert(_capacity == 0);
		_data.i = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetStorageFloat(float* values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::Float);
		assert(_capacity == 0);
		_data.f = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetStorageString(std::string* values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::String);
		assert(_capacity == 0);
		_data.s = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetStorageVector(glm::vec4* values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::Vector);
		assert(_capacity == 0);
		_data.v = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetStorageMatrix(glm::mat4* values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::Matrix);
		assert(_capacity == 0);
		_data.m = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetStoragePointer(RTTI** values, std::size_t sizeArray)
	{
		if (values == nullptr)
		{
			throw std::runtime_error("The array passed is a nullptr, can not set storage");
		}
		SetType(DatumTypes::Pointer);
		assert(_capacity == 0);
		_data.p = values;
		_capacity = _size = sizeArray;
		_isExternal = true;
	}

	 void Datum::SetInt(int32_t value, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::Integer);
		_data.i[valueIndex] = value;
	}

	 void Datum::SetFloat(float value, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::Float);
		_data.f[valueIndex] = value;
	}

	 void Datum::SetString(const std::string& value, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::String);
		_data.s[valueIndex] = value;
	}

	 void Datum::SetVector(const glm::vec4& value, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::Vector);
		_data.v[valueIndex] = value;
	}

	 void Datum::SetMatrix(const glm::mat4& value, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::Matrix);
		_data.m[valueIndex] = value;
	}

	 void Datum::SetPointer(RTTI* values, std::size_t valueIndex)
	{
		if (valueIndex >= _size)
		{
			throw std::runtime_error("The array index passed is out of bounds");
		}
		SetType(DatumTypes::Pointer);
		_data.p[valueIndex] = values;
	}


	 void Datum::SetTable(Scope& values, std::size_t valueIndex)
	 {
		 if (valueIndex >= _size)
		 {
			 throw std::runtime_error("The array index passed is out of bounds");
		 }
		 SetType(DatumTypes::Table);
		 _data.t[valueIndex] = &values;
	 }


	 int32_t Datum::GetInt(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.i[valueIndex];
	}

	 float Datum::GetFloat(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.f[valueIndex];
	}

	 const std::string& Datum::GetString(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.s[valueIndex];
	}

	 const glm::vec4& Datum::GetVector(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.v[valueIndex];
	}

	 const glm::mat4& Datum::GetMatrix(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.m[valueIndex];
	}

	 RTTI* const Datum::GetPointer(std::size_t valueIndex) const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (valueIndex >= _size)
		{
			throw runtime_error("Array Index out of bounds");
		}
		return _data.p[valueIndex];
	}

	 Scope& Datum::GetTable(std::size_t valueIndex) const
	 {
		 if (_type != DatumTypes::Table)
		 {
			 throw runtime_error("The Datum type is not a correct");
		 }
		 if (valueIndex >= _size)
		 {
			 throw runtime_error("Array Index out of bounds");
		 }
		 return *_data.t[valueIndex];
	 }

	 void Datum::SetFromString(const std::string& value, std::size_t valueIndex)
	{
		switch (_type)
		{
		case Datum::DatumTypes::Unknown:
			throw std::runtime_error("Can not set from an Unknown Datum");
			break;
		case Datum::DatumTypes::Integer:
			SetInt(StringToInt(value), valueIndex);
			break;
		case Datum::DatumTypes::Float:
			SetFloat(StringToFloat(value), valueIndex);
			break;
		case Datum::DatumTypes::String:
			SetString(value, valueIndex);
			break;
		case Datum::DatumTypes::Vector:
			SetVector(StringToVector(value), valueIndex);
			break;
		case Datum::DatumTypes::Matrix:
			SetMatrix(StringToMatrix(value), valueIndex);
			break;
		case Datum::DatumTypes::Pointer:
			throw std::runtime_error("Can not set to an Pointer Datum");
			break;
		}
	}

	 int Datum::StringToInt(const std::string& value) const
	{
		int valueConversion;
		sscanf_s(value.c_str(), "%d", &valueConversion);
		return valueConversion;
	}

	 float Datum::StringToFloat(const std::string& value) const
	{
		float valueConversion;
		sscanf_s(value.c_str(), "%f", &valueConversion);
		return valueConversion;
	}

	 glm::vec4 Datum::StringToVector(const std::string& value) const
	{
		float a, b, c, d;
		sscanf_s(value.c_str(), "vec4(%f, %f, %f, %f)", &a, &b, &c, &d);
		glm::vec4 valueConversion(a, b, c, d);
		return valueConversion;
	}

	 glm::mat4 Datum::StringToMatrix(const std::string& value) const
	{
		float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
		sscanf_s(value.c_str(), "mat4((%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f), (%f, %f, %f, %f))", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m, &n, &o, &p);
		glm::mat4 valueConversion(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
		return valueConversion;
	}

	 std::string Datum::ToString(std::size_t valueIndex) const
	{

		switch (_type)
		{
		case Datum::DatumTypes::Unknown:
			throw std::runtime_error("Can not set from an Unknown Datum");
			break;
		case Datum::DatumTypes::Integer:
			return std::to_string(GetInt(valueIndex));
			break;
		case Datum::DatumTypes::Float:
			return std::to_string(GetFloat(valueIndex));
			break;
		case Datum::DatumTypes::String:
			return GetString(valueIndex);
			break;
		case Datum::DatumTypes::Vector:
			glm::vec4 temp = GetVector(valueIndex);
			return "vec4("s + std::to_string(temp.x) + ", "s + std::to_string(temp.y) + ", "s + std::to_string(temp.z) + ", "s + std::to_string(temp.w) + ")"s;
			break;
		case Datum::DatumTypes::Matrix:
			glm::mat4 tempMat = GetMatrix(valueIndex);
			return "mat4(("s +
				std::to_string(tempMat[0][0]) + ", "s + std::to_string(tempMat[0][1]) + ", "s + std::to_string(tempMat[0][2]) + ", "s + std::to_string(tempMat[0][3]) + "), ("s +
				std::to_string(tempMat[1][0]) + ", "s + std::to_string(tempMat[1][1]) + ", "s + std::to_string(tempMat[1][2]) + ", "s + std::to_string(tempMat[1][3]) + "), ("s +
				std::to_string(tempMat[2][0]) + ", "s + std::to_string(tempMat[2][1]) + ", "s + std::to_string(tempMat[2][2]) + ", "s + std::to_string(tempMat[2][3]) + "), ("s +
				std::to_string(tempMat[3][0]) + ", "s + std::to_string(tempMat[3][1]) + ", "s + std::to_string(tempMat[3][2]) + ", "s + std::to_string(tempMat[3][3]) + "))"s;
			break;
		case Datum::DatumTypes::Pointer:
		{
			const RTTI* tempPointer = GetPointer(valueIndex);
			if (tempPointer == nullptr)
			{
				return "nullptr"s;
			}
			else
			{
				return tempPointer->ToString();
			}
		}
		break;
		default:
			return "Error has occured";
			break;
		}
	}

	 void Datum::PushBackInt(int32_t value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Integer);
		}

		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		_data.i[_size - 1] = value;
	}

	 void Datum::PushBackFloat(float value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Float);
		}

		if (_type != DatumTypes::Float)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		_data.f[_size - 1] = value;
	}

	 void Datum::PushBackString(const std::string& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::String);
		}

		if (_type != DatumTypes::String)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		new (_data.s + (_size - 1)) std::string(value);
	}

	 void Datum::PushBackVector(const glm::vec4& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Vector);
		}

		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		_data.v[_size - 1] = value;
	}

	 void Datum::PushBackMatrix(const glm::mat4& value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Matrix);
		}

		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		_data.m[_size - 1] = value;
	}

	 void Datum::PushBackPointer(RTTI* value)
	{
		if (_type == DatumTypes::Unknown)
		{
			SetType(DatumTypes::Pointer);
		}

		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("Can not Push Back: Type is inconsistent");
		}
		Reserve(_size + 1);
		++_size;
		_data.p[_size - 1] = value;
	}

	 void Datum::PushBackTable(Scope& value)
	 {

		 SetType(DatumTypes::Table);
		 if (_type != DatumTypes::Table)
		 {
			 throw runtime_error("Can not Push Back: Type is inconsistent");
		 }
		 Reserve(_size + 1);
		 ++_size;
		 _data.t[_size - 1] = &value;
	 }
	 void Datum::PopBack()
	{
		Resize(_size - 1);
	}

	 int& Datum::FrontInt()
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.i[0];
	}
	 float& Datum::FrontFloat()
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.f[0];
	}

	 std::string& Datum::FrontString()
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.s[0];
	}

	 glm::vec4& Datum::FrontVector()
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.v[0];
	}

	 glm::mat4& Datum::FrontMatrix()
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.m[0];
	}

	 RTTI*& Datum::FrontPointer()
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.p[0];
	}

	 int& Datum::FrontInt() const
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.i[0];
	}
	 float& Datum::FrontFloat() const
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.f[0];
	}
	 const std::string& Datum::FrontString() const
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.s[0];
	}
	 const glm::vec4& Datum::FrontVector() const
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.v[0];
	}
	 const glm::mat4& Datum::FrontMatrix() const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.m[0];
	}

	 const RTTI* FIEAGameEngine::Datum::FrontPointer() const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.p[0];
	}

	 int& Datum::BackInt()
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the back of a empty list");
		}
		return _data.i[_size - 1];
	}
	 float& Datum::BackFloat()
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.f[_size - 1];
	}
	 std::string& Datum::BackString()
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.s[_size - 1];
	}
	 glm::vec4& Datum::BackVector()
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.v[_size - 1];
	}
	 glm::mat4& Datum::BackMatrix()
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.m[_size - 1];
	}

	 RTTI*& FIEAGameEngine::Datum::BackPointer()
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.p[_size - 1];
	}

	 int& Datum::BackInt() const
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the back of a empty list");
		}
		return _data.i[_size - 1];
	}
	 float& Datum::BackFloat() const
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.f[_size - 1];
	}
	 const std::string& Datum::BackString() const
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.s[_size - 1];
	}
	 const glm::vec4& Datum::BackVector() const
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.v[_size - 1];
	}
	 const glm::mat4& Datum::BackMatrix() const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.m[_size - 1];
	}

	 const RTTI* FIEAGameEngine::Datum::BackPointer() const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not correct");
		}
		if (_size == 0)
		{
			throw std::runtime_error("Can not get the front of a empty list");
		}
		return _data.p[_size - 1];
	}

	 std::pair<std::size_t, bool> Datum::FindInt(int valueToBeFound) const
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.i[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}
	 std::pair<std::size_t, bool> Datum::FindFloat(float valueToBeFound) const
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.f[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}
	 std::pair<std::size_t, bool> Datum::FindString(const std::string& valueToBeFound) const
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.s[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}
	 std::pair<std::size_t, bool> Datum::FindVector(const glm::vec4& valueToBeFound) const
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.v[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}
	 std::pair<std::size_t, bool> Datum::FindMatrix(const glm::mat4& valueToBeFound) const
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.m[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}

	 std::pair<std::size_t, bool> Datum::FindPointer(const RTTI* valueToBeFound) const
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueFound = false;
		std::size_t valueIndex = 0;
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.p[i] == valueToBeFound)
			{
				valueFound = true;
				valueIndex = i;
				break;
			}
		}
		return std::make_pair(valueIndex, valueFound);
	}

	 void Datum::RemoveAt(std::size_t valueIndex)
	{
		if (_isExternal)
		{
			throw std::runtime_error("Datum is specfiied to have external storation, cannot use function");
		}
		if (_type == DatumTypes::Unknown)
		{
			throw std::runtime_error("Can not remove from Unknown Datum");
		}

		if (valueIndex < _size)
		{
			if (_type == DatumTypes::String)
			{
				_data.s[valueIndex].~basic_string();
			}

			memmove_s(_data.by + valueIndex * _typeSizes[static_cast<int>(_type)],
				(_size - valueIndex) * _typeSizes[static_cast<int>(_type)],
				_data.by + (valueIndex + 1) * _typeSizes[static_cast<int>(_type)],
				(_size - valueIndex - 1) * _typeSizes[static_cast<int>(_type)]);
			--_size;
		}
	}

	 bool Datum::RemoveInt(int value)
	{
		if (_type != DatumTypes::Integer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindInt(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 bool Datum::RemoveFloat(float value)
	{
		if (_type != DatumTypes::Float)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindFloat(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 bool Datum::RemoveString(const std::string& value)
	{
		if (_type != DatumTypes::String)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindString(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 bool Datum::RemoveVector(const glm::vec4& value)
	{
		if (_type != DatumTypes::Vector)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindVector(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 bool Datum::RemoveMatrix(const glm::mat4& value)
	{
		if (_type != DatumTypes::Matrix)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindMatrix(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 bool Datum::RemovePointer(const RTTI* value)
	{
		if (_type != DatumTypes::Pointer)
		{
			throw runtime_error("The Datum type is not a correct");
		}
		bool valueRemoved = false;
		std::pair valueFound = FindPointer(value);

		if (valueFound.second)
		{
			RemoveAt(valueFound.first);
			valueRemoved = true;
		}
		return valueRemoved;
	}

	 void Datum::SetStorage(DatumTypes type, void* data, std::size_t sizeArray)
	 {
		 assert(data != nullptr);
		 /*if (_size == 0)
		 {
			 throw std::runtime_error("External storage size must be greater than 0");
		 }*/
		 if (_type == DatumTypes::Unknown)
		 {
			 SetType(type);
		 }
		 else if (_type != type)
		 {
			 throw std::runtime_error("Invalid Operation");
		 }
		 _isExternal = true;
		 _size = sizeArray;
		 _capacity = sizeArray;
		 _data.vp = data;
	 }

	void Datum::Reserve(size_t capacity)
	{
		//assert(_type != DatumTypes::Unknown);
		/*if (_type == DatumTypes::Unknown)
		{
			throw runtime_error("The Datum type is not a correct");
		}*/
		//assert(_isExternal != true);
		if (capacity > _capacity)
		{
			size_t size = _typeSizes[static_cast<int>(_type)];
			//assert(size > 0);
			void* data = realloc(_data.vp, capacity * size);
			assert(data != nullptr);
			_data.vp = data;
			_capacity = capacity;
		}
	}
}
