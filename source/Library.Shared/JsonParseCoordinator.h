#pragma once
#include <gsl/gsl>
#include <json/json.h>
#include <fstream>
#include "RTTI.h"
#include "Vector.h"

namespace FIEAGameEngine
{
	class IJsonParseHelper;

	class JsonParseCoordinator final
	{
	public:
		class SharedDataContainer : public RTTI
		{
			RTTI_DECLARATIONS(SharedDataContainer, RTTI);
			friend class JsonParseCoordinator;
		public:
			/// <summary>
			/// Creates the cloned version of the shared data container within a shared pointer
			/// </summary>
			/// <returns></returns>
			virtual gsl::owner<SharedDataContainer*> Create() const = 0; 
			/// <summary>
			/// Initialzes any of the members of the class
			/// </summary>
			virtual void Initialize();
			/// <summary>
			/// Gets rid of any members of the class, clears it
			/// </summary>
			virtual void CleanUp();
			/// <summary>
			/// Pure virtual Destructor to be overwritten by the derived classes
			/// </summary>
			virtual ~SharedDataContainer() = 0;
			/// <summary>
			/// Getter for the json parse coordinator
			/// </summary>
			/// <returns>Pointer to an associated parse coordinator</returns>
			JsonParseCoordinator* GetJsonParseCoordinator() const;
			/// <summary>
			/// Increments the depth
			/// </summary>
			void IncrementDepth();
			/// <summary>
			/// Decrements the depth
			/// </summary>
			void DecrementDepth();
			/// <summary>
			/// Gets the depth
			/// </summary>
			/// <returns>returns the current depth</returns>
			std::size_t Depth() const;
		private:
			/// <summary>
			/// Setter for the json parse coordinator
			/// </summary>
			void SetJsonParseCoordinator(JsonParseCoordinator* manager);
			std::size_t _depth{ 0 };
			JsonParseCoordinator* _manager{ nullptr };
		};
		/// <summary>
		/// Constructor that takes smart pointer to a shared data container
		/// </summary>
		/// <param name="sharedData"> the container for the shared data</param>
		explicit JsonParseCoordinator(SharedDataContainer* sharedData);
		/// <summary>
		/// Deleted The copy constructor
		/// </summary>
		/// <param name="other"></param>
		JsonParseCoordinator(const JsonParseCoordinator& other) = delete;
		/// <summary>
		/// Deleted The copy assignment 
		/// </summary>
		/// <param name="other"></param>
		JsonParseCoordinator& operator=(const JsonParseCoordinator& other) = delete;
		/// <summary>
		/// Move COnstructor makes shallow copy
		/// </summary>
		/// <param name="other"> coordinator to be moved into this</param>
		JsonParseCoordinator(JsonParseCoordinator&& other) noexcept;
		/// <summary>
		/// Move assignment Operator makes a shallow copy
		/// </summary>
		/// <param name="other">coordinator to be moved into this</param>
		/// <returns>reference to this</returns>
		JsonParseCoordinator& operator=(JsonParseCoordinator&& other) noexcept;
		/// <summary>
		/// Destructor for Json Parse Coordinator
		/// </summary>
		~JsonParseCoordinator();
		/// <summary>
		/// Initialzes any of the members of the class
		/// </summary>
		void Initialize();
		/// <summary>
		/// Gets rid of any members of the class, clears it
		/// </summary>
		void CleanUp();
		/// <summary>
		/// Duplicates this object and return the address
		/// </summary>
		/// <returns>address of the newly duplicated object</returns>
		gsl::owner<JsonParseCoordinator*> Clone() const;
		/// <summary>
		/// Bool to check if the coordinator is a clone
		/// </summary>
		/// <returns>Returns whether the coordinator is a clone</returns>
		bool isClone() const;
		/// <summary>
		/// Adds the helper to the Vector of helpers
		/// </summary>
		/// <param name="helper"> helper to be added to the vector</param>
		void AddHelper(std::shared_ptr<IJsonParseHelper> helper);
		/// <summary>
		/// Removes the helper from the vector of helpers
		/// </summary>
		/// <param name="helper">helper to be removed</param>
		/// <returns>bool signifiying if the helper was removed from the vector of helpers</returns>
		bool RemoveHelper(const std::shared_ptr<IJsonParseHelper>& helper);
		/// <summary>
		/// Getter for the vector of helpers
		/// </summary>
		/// <returns></returns>
		const Vector<std::shared_ptr<IJsonParseHelper>>& HelperGetter();
		/// <summary>
		/// Deserialize a string of data
		/// </summary>
		/// <param name="dataJson">input to be deserialized</param>
		void DeserializeObject(const std::string& dataJson);
		/// <summary>
		/// Deserializes a string of data after getting input from file
		/// </summary>
		/// <param name="filename">file to be opened</param>
		void DeserializeObjectFromFile(const std::string& filename);
		/// <summary>
		/// Deserialize a istring of data
		/// </summary>
		/// <param name="dataJson">input to be Deserialized</param>
		void DeserializeObject(std::istream& dataJson);
		/// <summary>
		/// Getter for the address of the Wrapper
		/// </summary>
		/// <returns>Address of the Wrapper assoiated with this object</returns>
		SharedDataContainer* GetWrapper();
		/// <summary>
		/// Set the Wrapper associated with this object
		/// </summary>
		/// <param name="wrapperAddress">address of wrapper to be set</param>
		void SetWrapper(SharedDataContainer* wrapperAddress);
	private:
		/// <summary>
		/// Retrieves the memebers of the json value object and PArses through each of them
		/// </summary>
		/// <param name="object"> json value object</param>
		void ParseMembers(Json::Value& object);
		/// <summary>
		/// Trigger chain of responsibility for parsing key value pairs
		/// </summary>
		/// <param name="key"></param>
		/// <param name="val">json value object</param>
		/// <param name="isArrayelem">bool for if value is element of array</param>
		void Parse(const std::string& key, Json::Value& val, bool isArrayElem);

		bool _isClone{ false };
		SharedDataContainer* _dataContainer;
		Vector<std::shared_ptr<IJsonParseHelper>> _helpers;
	};
}



