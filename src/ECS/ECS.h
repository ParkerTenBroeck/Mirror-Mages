#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "MirrorMages.h"

class EntityComponent;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<EntityComponent*, maxComponents>;

class EntityComponent {
public:
	Entity* entity;

	virtual void init() {}
	virtual void update(float elapsedTime, MirrorMages* context) {}
	virtual void draw(float elapsedTime, MirrorMages* context) {}
	virtual void onUserUpdate(float elapsedTime, MirrorMages* context) {}

	virtual ~EntityComponent(){}
};

class Entity {
private:
	bool active = true;
	std::vector<std::unique_ptr<EntityComponent>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public:
	void update(float elapsedTime, MirrorMages* context) {
		for (auto& c : components) c->update(elapsedTime, context);
	}

	void draw(float elapsedTime, MirrorMages* context) {
		for (auto& c : components) c->draw(elapsedTime, context);
	}

	void onUserUpdate(float elapsedTime, MirrorMages* context) {
		for (auto& c : components) c->onUserUpdate(elapsedTime, context);
	}

	bool isActive() const { return active; }
	void destroy() { active = false;  }

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<EntityComponent> uPtr{c};
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class EntityManager {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update(float elapsedTime, MirrorMages* context) {
		for (auto& e : entities) e->update(elapsedTime, context);
	}
	void draw(float elapsedTime, MirrorMages* context) {
		for (auto& e : entities) e->draw(elapsedTime, context);
	}

	void onUserUpdate(float elapsedTime, MirrorMages* context) {
		for (auto& e : entities) e->onUserUpdate(elapsedTime, context);
	}

	void regresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
			[](const std::unique_ptr<Entity>& mEntity) {
			return !mEntity->isActive();
		}),
		std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};