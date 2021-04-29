#ifndef __ECS_H_
#define __ECS_H_

#include <SDL2/SDL.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class Component;
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

// using a power of likely makes it easier for the machine to use the bitset
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component {
public:
  Entity *entity;

  virtual ~Component() {}

  virtual void init() {}
  virtual void update(const std::vector<SDL_Event> &events) {}
  virtual void draw() {}
};

class Entity {
public:
  void update(const std::vector<SDL_Event> &events) {
    for (auto &c : components)
      c->update(events);
  }

  void draw() {
    for (auto &c : components)
      c->draw();
  }

  bool isActive() { return active; }
  void destroy() { active = false; }

  template <typename T> bool hasComponent() const {
    return componentBitSet[getComponentTypeID<T>()];
  }

  template <typename T, typename... TArgs> T &addComponent(TArgs &&... mArgs) {
    T *c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{c};
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitSet[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
  }

  template <typename T> T &getComponent() const {
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *static_cast<T *>(ptr);
  }

private:
  bool active = true;
  std::vector<std::unique_ptr<Component>> components;

  ComponentArray componentArray;
  ComponentBitSet componentBitSet;
};

class Manager {
public:
  void update(const std::vector<SDL_Event> &events) {
    for (auto &e : entities) {
      e->update(events);
    }
  }

  void draw() {
    for (auto &e : entities)
      e->draw();
  }

  void refresh() {
    entities.erase(std::remove_if(entities.begin(), entities.end(),
                                  [](const std::unique_ptr<Entity> &mEntity) {
                                    return !mEntity->isActive();
                                  }),
                   entities.end());
  }

  Entity &addEntity() {
    Entity *e = new Entity();
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return *e;
  }

private:
  std::vector<std::unique_ptr<Entity>> entities;
};

#endif // __ECS_H_
