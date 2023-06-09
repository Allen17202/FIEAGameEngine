#pragma once
#include "IJsonParseHelper.h"

namespace FIEAGameEngine
{
	class JsonParseHelperInteger final : public IJsonParseHelper
	{
		RTTI_DECLARATIONS(JsonParseHelperInteger, IJsonParseHelper);
	public:
		class SharedDataContainer final : public JsonParseCoordinator::SharedDataContainer
		{
			RTTI_DECLARATIONS(SharedDataContainer, JsonParseCoordinator::SharedDataContainer);
		public:
			/// <summary>
			/// Creates the cloned version of the shared data container within a shared pointer, Override
			/// </summary>
			/// <returns></returns>
			virtual gsl::owner<JsonParseCoordinator::SharedDataContainer*> Create() const override;
			/// <summary>
			/// Initialzes any of the members of the class
			/// </summary>
			virtual void Initialize() override;
			/// <summary>
			/// Pure virtual Destructor to be overwritten by the derived classes
			/// </summary>
			virtual ~SharedDataContainer() override;
			Vector<std::int32_t> _data;
		};
		/// <summary>
		/// Initialzes any of the members of the class
		/// </summary>
		virtual void Initialize() override;
		/// <summary>
		/// Overridded implemetations will create instance of the helper
		/// </summary>
		/// <returns>instance of the helper</returns>
		virtual std::shared_ptr<IJsonParseHelper> Create() const override;
		/// <summary>
		/// Destructor
		/// </summary>
		~JsonParseHelperInteger() override;
		/// <summary>
		/// Attempt to handle key value pair
		/// </summary>
		/// <returns>bool representing if it can handle the pair</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key, Json::Value& val) override;
		/// <summary>
		/// Complete handeling of th key value pair
		/// </summary>
		/// <returns>bool representing if it can handle the pair</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key) override;
	private:
		inline static const std::string _intKey{ "integer" };
		bool _isParsing{ false };
	};
}