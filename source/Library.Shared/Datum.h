#pragma once
//#include <cstddef>

#include <cassert>
//#include <stdexcept>
#include "RTTI.h"
#include<glm/glm.hpp>
#include "HashMap.h"

namespace FIEAGameEngine 
{
	class Scope;
	class Datum final
	{
		friend class Scope;
	public:
		enum class DatumTypes
		{
			Unknown = 0,
			Integer,
			Float,
			String,
			Vector,
			Matrix,
			Pointer,
			Table, 
			Begin = Unknown,
			End = Table
		};

		Datum() = default;
		/// <summary>
		/// Copy Constructor
		/// </summary>
		/// <param name="other"></param>
		Datum(const Datum& other);

		/// <summary>
		/// Copy Assignment Operator
		/// </summary>
		/// <param name="other">copied datum</param>
		/// <returns>copied datum</returns>
		Datum& operator=(const Datum& other);
		/// <summary>
		/// Scalar Int Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(int32_t data);
		/// <summary>
		/// Scalar Float Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(float data);
		/// <summary>
		/// Scalar String Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(const std::string& data);
		/// <summary>
		/// Scalar Vector Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(const glm::vec4& data);
		/// <summary>
		/// Scalar Matrix Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(const glm::mat4& data);
		/// <summary>
		/// Scalar RTTI Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(RTTI* const data);

		/// <summary>
		/// Scalar Scope Copy Assignment
		/// </summary>
		/// <param name="data"></param>
		/// <returns></returns>
		Datum& operator=(Scope& data);

		/// <summary>
		/// Move Constructor
		/// </summary>
		/// <param name="other">moved datum</param>
		/// <returns></returns>
		Datum(Datum&& other) noexcept;
		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">moved Datum</param>
		/// <returns>Moved Datum</returns>
		Datum& operator=(Datum&& other) noexcept;
		/// <summary>
		/// Destructor
		/// </summary>
		~Datum();

		/// <summary>
		/// Equality Operator Datum
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const Datum& rhs) const;
		/// <summary>
		/// Inequality Operator Datum
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const Datum& rhs) const;
		/// <summary>
		/// Equality Operator Int
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(int32_t rhs) const;

		/// <summary>
		/// Inequality Operator Int
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(int32_t rhs) const;
		/// <summary>
		/// Equality Operator Float
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(float rhs) const;
		/// <summary>
		/// Inequality Operator Float
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(float rhs) const;
		/// <summary>
		/// Equality Operator String
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const std::string& rhs) const;
		/// <summary>
		/// Inequality Operator String
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const std::string& rhs) const;
		/// <summary>
		/// Equality Operator Vector
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const glm::vec4& rhs) const;
		/// <summary>
		/// Ineqaulity Operator Vector
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const glm::vec4& rhs) const;
		
		/// <summary>
		/// Equality Operator Matrix
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const glm::mat4& rhs) const;
		/// <summary>
		/// Inequality Operator Matrix
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const glm::mat4& rhs) const;

		/// <summary>
		///  Equality Operator RTTI
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator==(const RTTI* const rhs) const;
		/// <summary>
		/// InEquality Operator RTTI
		/// </summary>
		/// <param name="rhs"></param>
		/// <returns></returns>
		bool operator!=(const RTTI* const rhs) const;

		Scope& operator[](std::uint32_t index);


		/// <summary>
		/// Type: returns the type of Datum
		/// </summary>
		/// <returns></returns>
		DatumTypes Type() const;
		/// <summary>
		/// Sets the type of Datum
		/// </summary>
		/// <param name="type"></param>
		void SetType(DatumTypes type);
		/// <summary>
		/// Retuens Size
		/// </summary>
		/// <returns></returns>
		std::size_t Size() const;
		/// <summary>
		/// Returns Capacity
		/// </summary>
		/// <returns></returns>
		std::size_t Capacity() const;
		/// <summary>
		/// Returns whther Datum has external storage
		/// </summary>
		/// <returns></returns>
		bool isExternal() const;
		/// <summary>
		/// Resizes Datum: allows growing and shrinking
		/// </summary>
		/// <param name="value"></param>
		void Resize(std::size_t value);
		/// <summary>
		/// Clears items from Datum
		/// </summary>
		void Clear();

		/// <summary>
		/// Set external Storage for Int array
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStorageInt(int32_t* values, std::size_t sizeArray);
		/// <summary>
		/// Set ExternalStorage for Float array
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStorageFloat(float* values, std::size_t sizeArray);
		/// <summary>
		/// Set External Storage for String
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStorageString(std::string* values, std::size_t sizeArray);
		/// <summary>
		/// Set External Storage for Vector
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStorageVector(glm::vec4* values, std::size_t sizeArray);
		/// <summary>
		/// Set External Storage for MAtrix
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStorageMatrix(glm::mat4* values, std::size_t sizeArray);
		/// <summary>
		/// Set External Storage for RTTI
		/// </summary>
		/// <param name="values"></param>
		/// <param name="sizeArray"></param>
		void SetStoragePointer(RTTI** values, std::size_t sizeArray);

		void SetStorage(DatumTypes type, void* data, std::size_t sizeArray);


		/// <summary>
		/// Set value at valueIndex in storage
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetInt(int32_t value, std::size_t valueIndex = 0);
		/// <summary>
		/// Set float value at the index specified
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetFloat(float value, std::size_t valueIndex = 0);
		/// <summary>
		/// Set String Value at index Specified
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetString(const std::string& value, std::size_t valueIndex = 0);
		/// <summary>
		/// Set Vector value at index specified
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetVector(const glm::vec4& value, std::size_t valueIndex = 0);
		/// <summary>
		/// Set matrix value at index specified
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetMatrix(const glm::mat4& value, std::size_t valueIndex = 0);
		/// <summary>
		/// Set RTTI pointer at value specified
		/// </summary>
		/// <param name="values"></param>
		/// <param name="valueIndex"></param>
		void SetPointer(RTTI* values, std::size_t valueIndex = 0);

		/// <summary>
		/// Set Table pointer at value specified
		/// </summary>
		/// <param name="values"></param>
		/// <param name="valueIndex"></param>
		void SetTable(Scope& values, std::size_t valueIndex = 0);

		/// <summary>
		/// Get int value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		int32_t GetInt(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Get Float value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		float GetFloat(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Get String value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		const std::string& GetString(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Get vector value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		const glm::vec4& GetVector(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Get matrix value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		const glm::mat4& GetMatrix(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Get pointer value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		RTTI* const GetPointer(std::size_t valueIndex = 0) const;

		/// <summary>
		/// Get pointer value stored at index
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		Scope& GetTable(std::size_t valueIndex = 0) const;

		/// <summary>
		/// String to int conversion
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		int StringToInt(const std::string& value) const;
		/// <summary>
		/// String to float conversion
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		float StringToFloat(const std::string& value) const;
		/// <summary>
		/// String to vector conversion
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		glm::vec4 StringToVector(const std::string& value) const;
		/// <summary>
		/// String to Matrix conversion
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		glm::mat4 StringToMatrix(const std::string& value) const;
		/// <summary>
		/// Value to string conversion
		/// </summary>
		/// <param name="valueIndex"></param>
		/// <returns></returns>
		std::string ToString(std::size_t valueIndex = 0) const;
		/// <summary>
		/// Set value from a string
		/// </summary>
		/// <param name="value"></param>
		/// <param name="valueIndex"></param>
		void SetFromString(const std::string& value, std::size_t valueIndex = 0);

		/// <summary>
		/// Places int value specified to back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackInt(int32_t value);
		/// <summary>
		/// Places float calue specified to back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackFloat(float value);
		/// <summary>
		/// Places string values in back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackString(const std::string& value);
		/// <summary>
		/// Places Vector value in back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackVector(const glm::vec4& value);
		/// <summary>
		/// Places matrix value in back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackMatrix(const glm::mat4& value);
		/// <summary>
		/// Places rtti pointer in back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackPointer(RTTI* value);

		/// <summary>
		/// Pops the value stored in the back of the array
		/// </summary>
		void PopBack();

		/// <summary>
		/// Gets the first int value of array
		/// </summary>
		/// <returns></returns>
		int& FrontInt();
		/// <summary>
		/// Gets the first index of float array
		/// </summary>
		/// <returns></returns>
		float& FrontFloat();
		/// <summary>
		/// Gets the first string value stored in array
		/// </summary>
		/// <returns></returns>
		std::string& FrontString();
		/// <summary>
		/// Gets the first vector value stored in array
		/// </summary>
		/// <returns></returns>
		glm::vec4& FrontVector();
		/// <summary>
		/// Gets the first matrix value stored in array
		/// </summary>
		/// <returns></returns>
		glm::mat4& FrontMatrix();
		/// <summary>
		/// Gets the first pointer value stored in array
		/// </summary>
		/// <returns></returns>
		RTTI*& FrontPointer();
		int& FrontInt() const;
		float& FrontFloat() const;
		const std::string& FrontString() const;
		const glm::vec4& FrontVector() const;
		const glm::mat4& FrontMatrix() const;
		const RTTI* FrontPointer() const;

		/// <summary>
		/// Gets the last int value stored in array
		/// </summary>
		/// <returns></returns>
		int& BackInt();
		/// <summary>
		/// Gets the last float value stored in array
		/// </summary>
		/// <returns></returns>
		float& BackFloat();
		/// <summary>
		/// Gets the last string value stored in array
		/// </summary>
		/// <returns></returns>
		std::string& BackString();
		/// <summary>
		/// Gets the last vector value stored in array
		/// </summary>
		/// <returns></returns>
		glm::vec4& BackVector();
		/// <summary>
		/// Gets the last matrix value stored in array
		/// </summary>
		/// <returns></returns>
		glm::mat4& BackMatrix();
		/// <summary>
		/// Gets the last pointer value stored in array
		/// </summary>
		/// <returns></returns>
		RTTI*& BackPointer();
		int& BackInt() const;
		float& BackFloat() const;
		const std::string& BackString() const;
		const glm::vec4& BackVector() const;
		const glm::mat4& BackMatrix() const;
		const RTTI* BackPointer() const;

		/// <summary>
		/// Searchs for int value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindInt(int valueToBeFound) const;
		/// <summary>
		/// Searches for float value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindFloat(float valueToBeFound) const;
		/// <summary>
		/// Searches for string value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindString(const std::string& valueToBeFound) const;

		/// <summary>
		/// Searches for vector value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindVector(const glm::vec4& valueToBeFound) const;
		/// <summary>
		/// Searches for Matrix value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindMatrix(const glm::mat4& valueToBeFound) const;
		/// <summary>
		/// Searches for Pointer value
		/// </summary>
		/// <param name="valueToBeFound"></param>
		/// <returns></returns>
		std::pair<std::size_t, bool> FindPointer(const RTTI* valueToBeFound) const;

		/// <summary>
		/// Remove value stored at the index
		/// </summary>
		/// <param name="valueIndex"></param>
		void RemoveAt(std::size_t valueIndex);
		/// <summary>
		/// Remove int value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemoveInt(int value);
		/// <summary>
		/// Remove float value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemoveFloat(float value);
		/// <summary>
		/// Removes string value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemoveString(const std::string& value);
		/// <summary>
		/// Removes Vector value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemoveVector(const glm::vec4& value);
		/// <summary>
		/// Removes Matrix value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemoveMatrix(const glm::mat4& value);
		/// <summary>
		/// Removes Pointer value specified
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		bool RemovePointer(const RTTI* value);

		/// <summary>
		/// Growns array, cannot shrink
		/// </summary>
		/// <param name="capacity"></param>
		void Reserve(size_t capacity);

		static const HashMap<std::string, Datum::DatumTypes> _stringDatumTypesMap;
		static const HashMap<Datum::DatumTypes, std::string> _datumTypesStringMap;
	private:
		union DatumValues final
		{
			int* i;
			float* f;
			std::string* s;
			glm::vec4* v;
			glm::mat4* m;
			RTTI** p;
			void* vp;
			std::uint8_t* by;
			Scope** t;
		};

		/// <summary>
		/// Places Table in back of array
		/// </summary>
		/// <param name="value"></param>
		void PushBackTable(Scope& value);

		DatumValues _data { nullptr };
		std::size_t _size{ 0 };
		std::size_t _capacity{ 0 };
		DatumTypes _type{ DatumTypes::Unknown };
		bool _isExternal{ false };

		static constexpr size_t _typeSizes[static_cast<int>(DatumTypes::End) + 1] =
		{
			0, // Unknown
			sizeof(std::int32_t),
			sizeof(float),
			sizeof(std::string),
			sizeof(glm::vec4),
			sizeof(glm::mat4),
			sizeof(RTTI*),
			sizeof(Scope*),
		};
	};
}
//#include "Datum.inl"
