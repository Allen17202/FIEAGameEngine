#pragma once
#include <cassert>
#include "IJsonParseHelper.h"
#include "Scope.h"
#include "Stack.h"
#include "Factory.h"
namespace FIEAGameEngine
{
	class JsonTableParseHelper final: public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonTableParseHelper, IJsonParseHelper);
	public:
		class SharedDataContainer final : public JsonParseCoordinator::SharedDataContainer
		{
			RTTI_DECLARATIONS(SharedDataContainer, JsonParseCoordinator::SharedDataContainer);
		public:
			/// <summary>
			/// Constructor For Shared Data Container
			/// </summary>
			/// <param name="scope">scope to be instantied</param>
			SharedDataContainer(Scope* scope);
			/// <summary>
			/// Deleted copy constructor
			/// </summary>
			SharedDataContainer(const JsonTableParseHelper::SharedDataContainer& other) = delete;
			/// <summary>
			/// Defaulted Move Constructor
			/// </summary>
			SharedDataContainer(JsonTableParseHelper::SharedDataContainer&& other) noexcept = default;
			/// <summary>
			/// Deleted Copy Assignment Operator
			/// </summary>
			SharedDataContainer& operator=(const JsonTableParseHelper::SharedDataContainer& other) = delete;
			/// <summary>
			/// Defaulted Move Assignment Operator
			/// </summary>
			/// <param name="other">container to be moved</param>
			SharedDataContainer& operator=(JsonTableParseHelper::SharedDataContainer&& other) noexcept = default;
			/// <summary>
			/// Virtual Overridden Destructor
			/// </summary>
			virtual ~SharedDataContainer() override;
			/// <summary>
			/// Create instance and sets owner
			/// </summary>
			virtual gsl::owner<JsonParseCoordinator::SharedDataContainer*> Create() const override;
			Scope* _scopeData;
		};

		/// <summary>
		/// Defaulted Contructor
		/// </summary>
		JsonTableParseHelper() = default;
		/// <summary>
		/// Deleted Copy Constructor
		/// </summary>
		/// <param name="other">Json parse table helper to be copied</param>
		JsonTableParseHelper(const JsonTableParseHelper& other) = delete;
		/// <summary>
		/// Defaulted move constructor
		/// </summary>
		/// <param name="other"> obj to be moved</param>
		JsonTableParseHelper(JsonTableParseHelper&& other) = default;
		/// <summary>
		/// Deleted Move Assignment
		/// </summary>
		/// <param name="other">obj to be copied</param>
		JsonTableParseHelper& operator=(const JsonTableParseHelper& other) = delete;
		/// <summary>
		/// Defaulted Move Assignment
		/// </summary>
		/// <param name="other">obj to be moved</param>
		JsonTableParseHelper& operator=(JsonTableParseHelper&& other) = default;
		/// <summary>
		/// Overriden Destructor
		/// </summary>
		~JsonTableParseHelper() override;

		/// <summary>
		/// Creates Instance
		/// </summary>
		/// <returns>shared pointer</returns>
		virtual std::shared_ptr<IJsonParseHelper> Create() const override;
		virtual bool StartHandler(JsonParseCoordinator::SharedDataContainer& dat, const std::string& key, Json::Value& val) override;
		virtual bool EndHandler(JsonParseCoordinator::SharedDataContainer& dat, const std::string& key) override;

	private:
		bool DeserializeHelper(const std::string& key, Json::Value& val, const std::string& innerKey, Datum& dat, Datum::DatumTypes type);

		struct StackFrame final{
			Scope& curScope;
			Datum::DatumTypes _type;
			const std::string& _key;
			Json::Value& _val;
			std::string _name;
			bool isType;
		};
		Stack<StackFrame> _stack;
		inline static const std::string classKey{ "class" };
		inline static const std::string typeKey {"type"};
		inline static const std::string valKey{ "value" };
	};
}
