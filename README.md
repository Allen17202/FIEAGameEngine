# FIEAGameEngine
Data-Driven game engine developed using modern C++ standard  
This engine is component-based & JSON is used as its configuration language.

## Features include Custom Implementations of various containers based on those residing in the standard template library :-
- Singly Linked List  
- Vector  
- Hashmap  
- Stack  

## Features also include Various Design Patterns :-
- Singleton  
- Composite  
- Factory  
- Chain of Responsibility  
- Observer Pattern  

## Some of the various components of this engine are :-
- *Datum : Run-time polymorphic homogeneous container which stores values of type Integer, Float, Vector, Matrix, Table, String, Pointer.*  
- *Scope : Scope is a dynamic hierarchical database which stores Datums by name.*  
- *Factory : Class that allows instantiation of other objects at runtime by the use of their Typename.*   
- *Action : Specific actions that can be performed by any entity/Game Object.*  
- *Reaction : Reaction is a abstract base class which ties the Event System to the Rest of the engine and which which responds to an action.*  
- *Event System : Entities/Game Objects can subscribe to events. Events are processed and delivered through an event queue which resides in the Game World.*  
 
