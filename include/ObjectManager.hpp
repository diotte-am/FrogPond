
#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP


#include "SceneNode.hpp"


// Purpose:
// This class sets up a full graphics program using SDL
//
//
//
class ObjectManager{
public:
    // Singleton pattern for having one single ObjectManager
    // class at any given time.
    static ObjectManager& Instance();

    // Destructor
    ~ObjectManager();
    // Add a new object
    void AddSceneNode(SceneNode*& o);
    // Retrieve a reference to an object
    Object& GetObject(unsigned int index);
    // Deletes all of the objects
    void RemoveAll();
    // Update all objects
    void UpdateAll(glm::mat4 projectionMatrix, Camera* camera);
    // Render All Objects
    void RenderAll();

private:
	// Constructor is private because we should
    // not be able to construct any other managers,
    // this how we ensure only one is ever created
    ObjectManager();
    // Objects in our scene 
    std::vector<Object*> m_objects;
    std::vector<SceneNode*> m_nodes;
};



#endif
