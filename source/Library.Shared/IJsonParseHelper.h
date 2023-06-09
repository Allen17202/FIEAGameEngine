#pragma once
#include <json/json.h>
#include <gsl/gsl>
#include "RTTI.h"
#include "JsonParseCoordinator.h"

namespace FIEAGameEngine 
{
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI);
	public:
		/// <summary>
		/// Destructor
		/// </summary>
		virtual ~IJsonParseHelper() = 0;
		/// <summary>
		/// Overridded implemetations will create instance of the helper
		/// </summary>
		/// <returns>instance of the helper</returns>
		virtual std::shared_ptr<IJsonParseHelper> Create() const = 0;
		/// <summary>
		/// Initialize this helper, called before each file is parsed
		/// </summary>
		virtual void Initialize();
		virtual void CleanUp();
		/// <summary>
		/// Attempt to handle key value pair
		/// </summary>
		/// <returns>bool representing if it can handle the pair</returns>
		virtual bool StartHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key, Json::Value& val) = 0;
		/// <summary>
		/// Complete handeling of th key value pair
		/// </summary>
		/// <returns>bool representing if it can handle the pair</returns>
		virtual bool EndHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key) = 0;
	};
}
