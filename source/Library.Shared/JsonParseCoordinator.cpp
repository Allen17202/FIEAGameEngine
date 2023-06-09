#include "pch.h"
#include "JsonParseCoordinator.h"
#include "IJsonParseHelper.h"
#include <cassert>

namespace FIEAGameEngine 
{
    RTTI_DEFINITIONS(JsonParseCoordinator::SharedDataContainer);

    void JsonParseCoordinator::SharedDataContainer::Initialize()
    {
        _depth = 0;
    }

    void JsonParseCoordinator::SharedDataContainer::CleanUp()
    {
    }

    JsonParseCoordinator::SharedDataContainer::~SharedDataContainer()
    {
        CleanUp();
    }

    JsonParseCoordinator* JsonParseCoordinator::SharedDataContainer::GetJsonParseCoordinator() const
    {
        return _manager;
    }

    void JsonParseCoordinator::SharedDataContainer::IncrementDepth()
    {
        ++_depth;
    }

    void JsonParseCoordinator::SharedDataContainer::DecrementDepth()
    {
        --_depth;
    }

    std::size_t JsonParseCoordinator::SharedDataContainer::Depth() const
    {
        return _depth;
    }

    void JsonParseCoordinator::SharedDataContainer::SetJsonParseCoordinator(JsonParseCoordinator* manager)
    {
        _manager = manager;
    }

    JsonParseCoordinator::JsonParseCoordinator(SharedDataContainer* sharedData):
        _dataContainer(sharedData)
    {
        _dataContainer->SetJsonParseCoordinator(this);
        Initialize();
    }

    JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& other) noexcept:
        _dataContainer(other._dataContainer),_isClone(other._isClone),_helpers(std::move(other._helpers))
    {
        _dataContainer->SetJsonParseCoordinator(this);
        other._dataContainer = nullptr;
    }

    JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& other) noexcept
    {
        _dataContainer = other._dataContainer;
        _dataContainer->SetJsonParseCoordinator(this);
        _isClone = other._isClone;
        _helpers = std::move(other._helpers);
        other._dataContainer = nullptr;
        if (other._isClone)
        {
            delete& other;
        }
        return *this;

    }

    JsonParseCoordinator::~JsonParseCoordinator()
    {
        if (_isClone)
        {
            delete _dataContainer;
            _dataContainer = nullptr;
        }
        CleanUp();
    }

    void JsonParseCoordinator::Initialize()
    {
        if (_dataContainer != nullptr)
        {
            _dataContainer->Initialize();
        }
        
        for(auto entryHelpers: _helpers)
        {
           entryHelpers->Initialize();
        }
    }

    void FIEAGameEngine::JsonParseCoordinator::CleanUp()
    {
        if (_dataContainer != nullptr)
        {
            _dataContainer->CleanUp();
        }

        for (auto entryHelpers : _helpers)
        {
            entryHelpers->CleanUp();
        }
    }

    gsl::owner<JsonParseCoordinator*> JsonParseCoordinator::Clone() const
    {
        SharedDataContainer* temp = _dataContainer->Create();
        JsonParseCoordinator* manager = new JsonParseCoordinator(temp);
        for (auto entry : _helpers)
        {
            std::shared_ptr<IJsonParseHelper> help = std::move(entry->Create());
            assert(help != nullptr);
            manager->AddHelper(help);
        }
        manager->_isClone = true;
        return manager;
    }

    bool JsonParseCoordinator::isClone() const
    {
        return _isClone;
    }

    void FIEAGameEngine::JsonParseCoordinator::AddHelper(std::shared_ptr<IJsonParseHelper> helper)
    {
        std::shared_ptr<IJsonParseHelper> newHelp;
        if (_isClone)
        {
            newHelp = helper->Create();
        }
        else
        {
            newHelp = std::move(helper);
        }
        _helpers.PushBack(newHelp);

    }

    bool JsonParseCoordinator::RemoveHelper(const std::shared_ptr<IJsonParseHelper>& helper)
    {
        return _helpers.Remove(helper);
    }

    const Vector<std::shared_ptr<IJsonParseHelper>>& JsonParseCoordinator::HelperGetter()
    {
        return _helpers;
    }

    void JsonParseCoordinator::DeserializeObject(const std::string& dataJson)
    {
        std::istringstream input;
        input.str(dataJson);
        DeserializeObject(input);
    }

    void JsonParseCoordinator::DeserializeObjectFromFile(const std::string& filename)
    {
        std::ifstream file;
        file.open(filename);
        if (!file.good())
        {
            throw std::runtime_error("Could not open file.");
        }
        DeserializeObject(file);

    }

    void FIEAGameEngine::JsonParseCoordinator::DeserializeObject(std::istream& dataJson)
    {
        if (_helpers.Size() == 0)
        {
            return;
        }
        assert(_dataContainer != nullptr);
        Json::Value root;
        dataJson >> root;
        ParseMembers(root);
    }

    JsonParseCoordinator::SharedDataContainer* JsonParseCoordinator::GetWrapper()
    {
        return _dataContainer;
    }

    void JsonParseCoordinator::SetWrapper(SharedDataContainer* wrapperAddress)
    {
        if (wrapperAddress == nullptr)
        {
            throw std::runtime_error("Cant set container to null");
        }
        _dataContainer = wrapperAddress;
    }

    void JsonParseCoordinator::ParseMembers(Json::Value& object)
    {
        _dataContainer->IncrementDepth();
        auto valueNames = object.getMemberNames();
        for (const auto& name : valueNames)
        {
           Parse(name, object[name], object[name].isArray());
        }
        _dataContainer->DecrementDepth();
    }

    void JsonParseCoordinator::Parse(const std::string& key, Json::Value& val, bool isArrayElem)
    {
        for (auto help : _helpers)
        {
            help->Initialize();
            bool result = help->StartHandler(*_dataContainer, key, val);
            if (result)
            {
                if (isArrayElem)
                {
                    for (auto& instanceVal : val)
                    {
                        Parse(key, instanceVal, instanceVal.isArray());
                    }
                }
                else if (val.isObject())
                {
                    ParseMembers(val);
                }
                help->EndHandler(*_dataContainer, key);
                help->CleanUp();
                break;
            }
        }
    }
}
