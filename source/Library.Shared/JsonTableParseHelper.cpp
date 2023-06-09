#include "pch.h"
#include "JsonTableParseHelper.h"


namespace FIEAGameEngine
{
	RTTI_DEFINITIONS(JsonTableParseHelper);
	RTTI_DEFINITIONS(JsonTableParseHelper::SharedDataContainer);

	JsonTableParseHelper::SharedDataContainer::SharedDataContainer(Scope* scope):
		_scopeData(scope)
	{
	}

	JsonTableParseHelper::SharedDataContainer::~SharedDataContainer()
	{
	}

	gsl::owner<JsonParseCoordinator::SharedDataContainer*> JsonTableParseHelper::SharedDataContainer::Create() const
	{
		return new JsonTableParseHelper::SharedDataContainer(new Scope());
	}

	JsonTableParseHelper::~JsonTableParseHelper()
	{
	}

	std::shared_ptr<IJsonParseHelper> JsonTableParseHelper::Create() const
	{
		return std::shared_ptr<JsonTableParseHelper>();
	}

	bool JsonTableParseHelper::StartHandler(JsonParseCoordinator::SharedDataContainer& dat, const std::string& key, Json::Value& val)
	{
		JsonTableParseHelper::SharedDataContainer* data = dat.As<JsonTableParseHelper::SharedDataContainer>();
		if (data == nullptr)
		{
			return false;
		}

		if (key == typeKey)
		{
			StackFrame& curFrame = _stack.Top();
			Datum::DatumTypes type;
			try
			{
				type = Datum::_stringDatumTypesMap.At(val.asString());
			}
			catch(std::runtime_error)
			{
				return false;
			}
			curFrame._type = type;
			const std::string& tempKey = curFrame._key;
			Datum& tempDat = curFrame.curScope.Append(tempKey);
			tempDat.SetType(type);

			if (curFrame.isType)
			{
				curFrame.isType = false;
				if (curFrame._name.empty() == false)
				{
					auto nestScope = Factory<Scope>::Create(curFrame._name);
					curFrame.curScope.Adopt(*nestScope, tempKey);
					StackFrame newStack{ *nestScope, Datum::DatumTypes::Unknown,key, val,std::string(),false};
					_stack.Push(newStack);
				}
				else
				{
					if (!val.isArray())
					{
						return DeserializeHelper(key, val, tempKey, tempDat, type);
					}
				}

			}
		}
		else if (key == classKey)
		{
			StackFrame& curFrame = _stack.Top();
			curFrame._name = val.asString();
		}
		else if (key == valKey)
		{
			StackFrame& curFrame = _stack.Top();
			Datum::DatumTypes type = curFrame._type;
			const std::string& tempkey = curFrame._key;
			Datum & tempDatum = curFrame.curScope.Append(tempkey);

			if (type == Datum::DatumTypes::Unknown)
			{
				curFrame.isType = true;
			}
			else
			{
				if (!val.isArray())
				{
					if (curFrame._name.empty() == false)
					{
						//Scope* nestScope = new Scope();
						auto nestScope = Factory<Scope>::Create(curFrame._name);
						assert(nestScope != nullptr);
						curFrame.curScope.Adopt(*nestScope, tempkey);
						StackFrame newStack{ *nestScope, Datum::DatumTypes::Unknown,key, val,std::string(),false };
						_stack.Push(newStack);
					}
					else
					{
						return DeserializeHelper(key, val, tempkey, tempDatum, type);
					}
				}
			}
		}
		else
		{
			if (_stack.Size() == 0)
			{
				StackFrame initStack{*data->_scopeData,Datum::DatumTypes::Unknown,key,val,std::string(),false};
				_stack.Push(initStack);
			}
			else
			{
				StackFrame newStack{ _stack.Top().curScope,Datum::DatumTypes::Unknown,key,val,std::string(),false};
				_stack.Push(newStack);
			}
		}
		return true;
	}

	bool JsonTableParseHelper::EndHandler(JsonParseCoordinator::SharedDataContainer& dat, const std::string& key)
	{
		JsonTableParseHelper::SharedDataContainer* data = dat.As<JsonTableParseHelper::SharedDataContainer>();
		if (data == nullptr)
		{
			return false;
		}
		if (_stack.Top()._key == key)
		{
			_stack.Pop();
		}
		return false;
	}

	bool JsonTableParseHelper::DeserializeHelper(const std::string& key, Json::Value& val, const std::string& innerKey, Datum& dat, Datum::DatumTypes type)
	{
		switch (type)
		{
		case Datum::DatumTypes::Integer:
		{
			if (dat.isExternal())
			{
				dat.SetInt(val.asInt());
			}
			else
			{
				dat.PushBackInt(val.asInt());
			}
			break;
		}
		case Datum::DatumTypes::Float:
		{
			if (dat.isExternal())
			{
				dat.SetFloat(val.asFloat());
			}
			else
			{
				dat.PushBackFloat(val.asFloat());
			}
			break;
		}
		case FIEAGameEngine::Datum::DatumTypes::String:
		{
			if (dat.isExternal())
			{
				dat.SetString(val.asString());
			}
			else
			{
				dat.PushBackString(val.asString());
			}
			break;
		}
		case FIEAGameEngine::Datum::DatumTypes::Vector:
		{
			if (dat.isExternal())
			{
				dat.SetFromString(val.asString());
			}
			else
			{
				dat.PushBackVector(dat.StringToVector(val.asString()));
			}
			break;
		}
		case FIEAGameEngine::Datum::DatumTypes::Matrix:
		{
			if (dat.isExternal())
			{
				dat.SetFromString(val.asString());
			}
			else
			{
				dat.PushBackMatrix(dat.StringToMatrix(val.asString()));
			}
			break;
		}
		case FIEAGameEngine::Datum::DatumTypes::Table:
		{
			Scope& scopeRef = _stack.Top().curScope.AppendScope(innerKey);
			StackFrame anotherStackFrame{scopeRef, Datum::DatumTypes::Unknown, key, val, std::string(), false};
			_stack.Push(anotherStackFrame);
			break;
		}
		default:
			return false;
			break;
		}
		return true;
	}

}