#ifndef TERRAIN_NODE_HPP
#define TERRAIN_NODE_HPP
/** @file SceneNode.hpp
 *  @brief SceneNode helps organize a large 3D graphics scene.
 *  
 *  SceneNode helps organize a large 3D graphics scene.
 *  The traversal of the tree takes place starting from
 *  a single SceneNode (typically called root).
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#include <vector>
#include <memory>

#include "Object.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Shader.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class TerrainNode{
public:
    TerrainNode(Object* ob);
    // Our destructor takes care of destroying
    // all of the children within the node.
    // Now we do not have to manage deleting
    // each individual object.
    ~TerrainNode();

    std::vector<TerrainNode*> getChildren(){return m_children;};
    std::string getName(){return m_name;};
    void setPosition(glm::vec3 position){m_localTransform.setPosition(position.x,position.y,position.z);};
    void setScale(glm::vec3 scale){m_localTransform.setScale(scale.x, scale.y, scale.z);};
    void setRotation(float radians, glm::vec3 rotAxis)
    {m_localTransform.setRotation(radians, rotAxis.x, rotAxis.y, rotAxis.z);};

    void resetLocalMatrix(){m_localTransform.LoadIdentity();};
    void loadLocalMatrix(){m_localTransform.updateLocal();};
    int childCount(){ return m_children.size(); };
    TerrainNode* getParent(std::string name) { return m_parent; };
    void setParent(TerrainNode* parent) { m_parent = parent; };

    // Adds a child node to our current node.
    void AddChild(TerrainNode* n);
    // Draws the current SceneNode
    void Draw();
    // Updates the current SceneNode
    void Update(glm::mat4 projectionMatrix, Camera* camera);
    // Returns the local transformation transform
    // Remember that local is local to an object, where it's center is the origin.

    Transform& GetLocalTransform();
    // Returns a SceneNode's world transform
    Transform& GetWorldTransform();
    // For now we have one shader per Node.
    Shader m_shader; 
    
    // NOTE: Protected members are accessible by anything
    // that we inherit from, as well as ?
protected:
    // Parent
    TerrainNode* m_parent;
    std::string m_name;
private:
    // Children holds all a pointer to all of the descendents
    // of a particular SceneNode. A pointer is used because
    // we do not want to hold or make actual copies.
    std::vector<TerrainNode*> m_children;
    // The object stored in the scene graph
    Object* m_object;
    // Each SceneNode nodes locals transform.
    Transform m_localTransform;
    // We additionally can store the world transform
    Transform m_worldTransform;
};

#endif