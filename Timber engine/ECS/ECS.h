#pragma once
//#include <iostream>
//#include <vector>
//#include <bitset>
//#include <algorithm>
//#include <array>
//#include <memory>
//#include <map>
//#include <GL/glew.h>

class Entity;
class Component;
class EntityManager;
class System;
class SystemManager;
class ECS;

using ULLong = std::size_t;
constexpr  ULLong MAX_COMPONENTS = 64;
constexpr ULLong MAX_SYSTEMS= 64;

inline ULLong computeComponentTypeID() {
	static ULLong lastID = 0;
	return lastID++;
}

template <typename T> ULLong getComponentTypeID() noexcept {
	static ULLong typeID = computeComponentTypeID();
	return typeID;
}

inline ULLong computeSystemTypeID() {
	static ULLong lastSystemID = 0;
	return lastSystemID++;
}

template <typename T> ULLong getSystemTypeID() noexcept {
	static ULLong sTypeID = computeSystemTypeID();
	return sTypeID;
}

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using SystemBitSet = std::bitset<MAX_SYSTEMS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;
using SystemArray = std::array<System*, MAX_SYSTEMS>;

class Component
{
private:
	GLboolean active = true;

public:
	Entity * entity;

	Component() {}
	virtual ~Component() {}

	virtual void update(GLfloat deltatime) {}
	virtual void render() {}
	
	GLboolean isActive() { return active; }
	void destroy() { active = false; }
};

class Entity
{
private:
	bool active = true;
	bool renderable = false;
	ULLong id;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitset;


public:
	void update(GLfloat deltatime){ for (auto&c : components) c->update(deltatime); }
	void render(){ for (auto&c : components) c->render(); }

	bool isActive() const { return active; }
	void setID(ULLong newID) { id = newID; }
	void setRenderable(bool flag) { renderable = flag; }
	void destroy() { active = false; }

	template<typename T> bool hasComponent() const;

	template<typename T, typename... Targs> T& addComponent(Targs&&... mArgs);

	template<typename T> T& getComponent() const;

	ULLong getID() { return id; }
	bool isRenderable() { return renderable; }
};

template<typename T>
inline bool Entity::hasComponent() const
{
	return componentBitset[getComponentTypeID<T>()];
}

template<typename T, typename ...Targs>
inline T & Entity::addComponent(Targs && ...mArgs)
{
	T* c(new T(std::forward<Targs>(mArgs)...));
	c->entity = this;
	std::unique_ptr<Component> uPtr{ c };
	components.emplace_back(std::move(uPtr));

	componentArray[getComponentTypeID<T>()] = c;
	componentBitset[getComponentTypeID<T>()] = true;

	//c->init();
	return *c;
	// TODO: insert return statement here
}

template<typename T>
inline T & Entity::getComponent() const
{
	auto ptr(componentArray[getComponentTypeID<T>()]);
	return *static_cast<T*>(ptr);
}


class EntityManager
{
public:
	std::vector<std::unique_ptr<Entity>> entities;

	EntityManager() {}
	void update(GLfloat deltatime){ for (auto&c : entities) c->update(deltatime); }
	void render(){ for (auto&c : entities) c->render(); }
	void flush() { entities.clear(); }
	void refresh() 
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->isActive();
		}),
			std::end(entities));
	}
	Entity& addEntity() {
		static ULLong newID = 0;
		Entity* e = new Entity();
		e->setID(newID);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};

class System {
private:
	GLboolean active = true;
public:
	System() {}
	virtual ~System() {}
	SystemManager* sManager;
	EntityManager* eManager;
	virtual void preUpdate(GLfloat deltatime) {}
	virtual void update(GLfloat deltatime) {}
	virtual void render() {}
	GLboolean isActive() { return active; }
	void destroy() { active = false; }

};

class SystemManager {
private:
	std::vector<std::unique_ptr<System>> systems;
	SystemArray systemArray;
	SystemBitSet systemBitset;
	EntityManager* eManager;
public:
	SystemManager(EntityManager& eManager) :eManager(&eManager) {}

	void preUpdate(GLfloat deltatime) { for (auto&s : systems) s->preUpdate(deltatime); }
	void update(GLfloat deltatime) { for (auto&s : systems) s->update(deltatime); }
	void render() { for (auto&s : systems) s->render(); }
	void flush() { systems.clear(); }

	void refresh()
	{
		systems.erase(std::remove_if(std::begin(systems), std::end(systems),
			[](const std::unique_ptr<System> &mSystem)
		{
			return !mSystem->isActive();
		}),
			std::end(systems));
	}

	template<typename S>
	inline bool hasSystem() {
		return systemBitset[getSystemTypeID<S>()];
	}

	template<typename S, typename ...Sargs>
	inline S & addSystem(Sargs && ...mArgs);

	template<typename S>
	inline S& getSystem() {
		auto ptr(systemArray[getSystemTypeID<S>()]);
		return *static_cast<S*>(ptr);
	}
};

template<typename S, typename ...Sargs>
inline S & SystemManager::addSystem(Sargs && ...mArgs)
{
	S* s(new S(std::forward<Sargs>(mArgs)...));
	s->sManager = this;
	s->eManager = eManager;
	std::unique_ptr<System> uPtr{ s };
	systems.emplace_back(std::move(uPtr));

	systemArray[getSystemTypeID<S>()] = s;
	systemBitset[getSystemTypeID<S>()] = true;

	return *s;
}


class ECS {
public:
	EntityManager eManager;
	SystemManager sManager;

	ECS() :sManager(eManager), eManager() {}

	void update(GLfloat deltatime) {
		eManager.update(deltatime);
		sManager.preUpdate(deltatime);
		sManager.update(deltatime);
	}

	void render() {
		//eManager.render();	//Won't be usefull if only systems can render
		sManager.render();
	}

	void refresh() {
		eManager.refresh();
		sManager.refresh();
	}
	void flush() {
		eManager.flush();
		sManager.flush();
	}
};

