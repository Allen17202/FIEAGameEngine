#include "pch.h"
#include "JsonParseHelperInteger.h"

namespace FIEAGameEngine
{
    RTTI_DEFINITIONS(JsonParseHelperInteger);
    RTTI_DEFINITIONS(JsonParseHelperInteger::SharedDataContainer);


    gsl::owner<JsonParseCoordinator::SharedDataContainer*> JsonParseHelperInteger::SharedDataContainer::Create() const
    {
        return new JsonParseHelperInteger::SharedDataContainer();
    }

    JsonParseHelperInteger::SharedDataContainer::~SharedDataContainer()
    {
    }

    void JsonParseHelperInteger::SharedDataContainer::Initialize()
    {
        _data.Clear();
        _data.ShrinkToFit();
    }

    void JsonParseHelperInteger::Initialize()
    {
        IJsonParseHelper::Initialize();
        _isParsing = false;
    }

    std::shared_ptr<IJsonParseHelper> JsonParseHelperInteger::Create() const
    {
        return std::make_shared<JsonParseHelperInteger>();
    }

    JsonParseHelperInteger::~JsonParseHelperInteger()
    {
    }

    bool JsonParseHelperInteger::StartHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key, Json::Value& val)
    {
        JsonParseHelperInteger::SharedDataContainer* parsedInts = data.As<JsonParseHelperInteger::SharedDataContainer>();
        if (parsedInts == nullptr)
        {
            return false;
        }
        if (key != _intKey)
        {
            return false;
        }
        if (_isParsing)
        {
            throw std::runtime_error("Currently parsing other data");
        }
        _isParsing = true;
        parsedInts->_data.PushBack(val.asInt());
        return true;
    }

    bool JsonParseHelperInteger::EndHandler(JsonParseCoordinator::SharedDataContainer& data, const std::string& key)
    {
        JsonParseHelperInteger::SharedDataContainer* parsedInts = data.As<JsonParseHelperInteger::SharedDataContainer>();
        if (parsedInts == nullptr)
        {
            return false;
        }
        if (key != _intKey)
        {
            return false;
        }
        if (_isParsing == false)
        {
            return false;
        }
        _isParsing = false;
        return true;
    }
}
