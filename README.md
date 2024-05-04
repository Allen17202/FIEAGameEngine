# FIEAGameEngine
Data-Driven game engine developed using modern C++ standard  
This engine is component-based & JSON is used as its configuration language.

Documentation based on Doxygen/Visual Studio XML formatting.
Each class within the Game Engine is unit-tested using Microsoft's Cpp Unit Test Framework to ensure it performs as intended.

Many of the classes defined in this engine utilizes the Rule of Three and the Rule of Five

## Design Patterns Implemented:
- Singleton  
- Composite  
- Factory  
- Chain of Responsibility  
- Observer Pattern  

 <a name="list-of-features"></a>
## List of Custom Features Implemented
## (Implementations based on the standard template library)
[active]:https://img.shields.io/badge/-Active-success
[depreciated]:https://img.shields.io/badge/-Depreciated-inactive
[updating]:https://img.shields.io/badge/-Updating-purple
[passing]:https://img.shields.io/badge/-Passing-success
[outdated]:https://img.shields.io/badge/-Outdated-blue
[dev]:https://img.shields.io/badge/-Unreleased-important

[version-1.0.0]:https://img.shields.io/badge/Ver.-1.0.0-ff69b4
[version-1.0.1]:https://img.shields.io/badge/Ver.-1.0.1-ff69b4
[version-1.0.2]:https://img.shields.io/badge/Ver.-1.0.2-ff69b4
[version-1.0.3]:https://img.shields.io/badge/Ver.-1.0.3-ff69b4
[version-1.0.4]:https://img.shields.io/badge/Ver.-1.0.4-ff69b4
[version-1.0.5]:https://img.shields.io/badge/Ver.-1.0.5-ff69b4
[version-dev]:https://img.shields.io/badge/Ver.-dev-important

|**Name**|**Description**|**Version**|**Testing**|**Status**|
|:------:|:-------------:|:---------:|:-------:|:--------:|
|**Templated Singly-Linked List(SList)**| Templated class that implements a singly-linked list. Has an embedded class called Iterator that handles transversing the singly-linked list|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Stack**|Templated class that implements a stack.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Templated Vector**| Templated class that implements the dynamic array class Vector. Embedded class Iterator and ConstIterator that handles transversal through the vector class and const-correctness. ConstIterator supports implicit conversion of Iterator to ConstIterator. Defined at Compile time.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Templated Hashmap**| Generic Templated Class that implements a hash map that utilizes the chaining technique. Embedded classes Iterator and ConstIterator handles array transversal.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Datum**| Class that serves as a polymorphic homogenous container whose purpose is to stores an array of values of type primitive or user-defined. Defined at run-time. Values supported include unknown(no value assigned), int, float, vector(4-vec), matrix(4x4 vector), table(Pointer to a Scope), string, and a pointer to an RTTI instance.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Scope**|Class that serves as an dynamic hierarchical database. Scope Objects are tables that create dictonary of name-value pairs where Datum objects are the values. Each entry in Scope has a name and a Datum, where Datum represents an array of values of a single type. Also an entry in a Scope table can refer to another Scope table and thereby provides the means to create user-defined types which are a Datum type.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Attributed**|Class that simplifies the process of mirroring native C++ classes into a form useable in the engine.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**IJsonParseHelper**| Abstract base class interface that is called just before each json file is parsed. Starts the json file handleing system and attempts to complete parsing the file|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**JsonParseCoordinator**|Embedded Wrapper Class that wraps the JsonCpp functionality ina C++ class. Class will represent data that all helpers share with each other and with the coordinator. This is a base class with extensions depending on the JSON file to parse.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**JsonTableParseHelper**| Class that implements IJsonParseHelper where the Json format is defined and start parsing the json file.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**SharedDataContainer**| Class includes any data that might potentially be needed in order to parse a table.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Factory**|Templated Abstract Class that allows instantiation of objects at runtime based on the name of their type(TypeName). Has an associated macro called ConcreteFactory which performs everything needed in order to create a concrete factory for a given product|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Game Object**|Game Object base class which is truthfullyy a wrapper for a table(Attributed Scope). Populates their tables based on data known at compile time.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Action**|Abstract Base Class that extends Attributed abstract base class. Stores a presribed external attribute.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**ActionList**| Concrete Class that implements Action which stores Action nested Scoped. Class also updates each action stored within the object.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**EventSubscriber**|Abstract BAse Class accepts the address of an EventPublisher. RTTI verifies actual event type.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**EventPublisher**|Abstract Base Class that takes a list of event subscribers. Notifies all subscribers of an event.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Event**|Templated Class that derives from EventPublisher. Allows subscribing and Unsubscibing to an event once give the address of an EventSubsciber. Has the message object.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**EventQueue**|Class that once given the address of an Event Publisher, gametime, and an optional delay time can enqueue an event.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**Reaction**| Abstract base class which ties the Event System to the rest of the engine and which responds to an action.|![active][version-1.0.0]|![passing][passing]|![Active][active]|
|**EventMessageAttributed**|Class that implements Attributed which takes a World object, and the subtype to an event to create a attributed message object.|![active][version-1.0.0]|![passing][passing]|![Active][active]|

