#pragma once
#include "Attributed.h"
#include "Factory.h"
#include "GameTime.h"

namespace FIEAGameEngine
{
	class Action;
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed);
	public:
		/// <summary>
		/// Default Constructor
		/// </summary>
		GameObject();
		/// <summary>
		/// Defaulted Copy Constructor
		/// </summary>
		/// <param name="other">game object to be copied</param>
		GameObject(const GameObject& other) = default;
		/// <summary>
		/// Defaulted Move Constructor
		/// </summary>
		/// <param name="other">game object to be moved</param>
		GameObject(GameObject&& other) noexcept = default;
		/// <summary>
		/// Defaulted Copy Assignment Operator
		/// </summary>
		/// <param name="other"></param>
		GameObject& operator=(const GameObject& other) = default;
		/// <summary>
		/// Move Assignment Operator
		/// </summary>
		/// <param name="other">object to be moved</param>
		GameObject& operator=(GameObject&& other) noexcept = default;
		/// <summary>
		/// Virtual Destructor
		/// </summary>
		virtual ~GameObject() override = default;

		/// <summary>
		/// Updates Children of the GameObject
		/// </summary>
		/// <param name="time">current time</param>
		virtual void Update(const GameTime& time);
		/// <summary>
		/// Attributes of GameObject
		/// </summary>
		/// <returns>vector of attributes</returns>
		static const Vector<Signature> Signatures();
		/// <summary>
		/// Assigns ownership
		/// </summary>
		/// <returns>instance of Game Object</returns>
		gsl::owner<GameObject*> Clone() const override;
		bool Equals(const RTTI* other) const override;
		/// <summary>
		/// string of GameObject
		/// </summary>
		/// <returns>string containing GameObject</returns>
		std::string ToString() const override;
		/// <summary>
		/// Finds the Children datum
		/// </summary>
		/// <returns>reference to Datum of Children</returns>
		Datum& GetChildren();
		/// <summary>
		/// Gets the chind at a specified index
		/// </summary>
		/// <param name="index">index of the child were looking for</param>
		/// <returns>reference to game object at the child index</returns>
		GameObject& GetChildAtIndex(std::size_t index = 0);

		/// <summary>
		/// Getter for the Actions Datum
		/// </summary>
		/// <returns> reference to the Actions datum</returns>
		Datum& Actions();

		/// <summary>
		/// Instantiates a new Action Object and adopts into Actions Datum
		/// </summary>
		/// <param name="className"> class name </param>
		/// <param name="instanceName">instance name</param>
		/// <returns> pointer to the action</returns>
		Action* CreateAction(const std::string& className, const std::string& instanceName);

		/// <summary>
		/// Retrieves an action instance from the actions datum at index i
		/// </summary>
		Action& GetActionAtIndex(std::size_t i = 0);

		std::string _name;
		glm::vec4 _position;
		glm::vec4 _rotation;
		glm::vec4 _scale;
	};
	ConcreteFactory(GameObject, Scope);
}