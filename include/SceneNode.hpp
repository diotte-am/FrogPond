#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <vector>

#include "Object.hpp"
#include "Transform.hpp" 
#include "Camera.hpp"
#include "Shader.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SceneNode{
public:
    // A SceneNode is created by taking
    // a pointer to an object.
    SceneNode(Object* ob, std::string name);
    SceneNode(Object* ob, std::string vertShader, std::string fragShader);

    SceneNode(Object* ob);
    // Our destructor takes care of destroying
    // all of the children within the node.
    // Now we do not have to manage deleting
    // each individual object.
    ~SceneNode();
    // Adds a child node to our current node.
    void AddChild(SceneNode* n);
    // Draws the current SceneNode
    void Draw();
    // Updates the current SceneNode
    void Update(glm::mat4 projectionMatrix, Camera* camera);
    void updateHelper();
    bool nameMatches(std::string name) { return name == m_name; };

    std::vector<SceneNode*> getChildren(){return m_children;};
    std::string getName(){return m_name;};
    void setPosition(glm::vec3 position){m_localTransform.setPosition(position.x,position.y,position.z);};
    void updatePosition(glm::vec3 newPosition) { m_localTransform.updatePosition(newPosition.x, newPosition.y, newPosition.z);};
    void setScale(glm::vec3 scale){m_localTransform.setScale(scale.x, scale.y, scale.z);};
    void setRotation(float radians, glm::vec3 rotAxis)
        {m_localTransform.setRotationIncrement(radians);
            m_localTransform.setRotation(radians, rotAxis.x, rotAxis.y, rotAxis.z);};

    void resetLocalMatrix(){m_localTransform.LoadIdentity();};
    void loadLocalMatrix(){m_localTransform.updateLocal();};
    int childCount(){ return m_children.size(); };
    SceneNode* getParent(std::string name);
    void setParent(SceneNode* parent) { m_parent = parent; };
    void moveRight(glm::vec3 position) { updatePosition(position);}
    void moveLeft(glm::vec3 position) { updatePosition(-position);}

    void moveFoward(glm::vec3 position) { updatePosition(position);}
    void moveBack(glm::vec3 position) { updatePosition(-position);}

    
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
    SceneNode* m_parent;
    std::string m_name;
private:
    // Children holds all a pointer to all of the descendents
    // of a particular SceneNode. A pointer is used because
    // we do not want to hold or make actual copies.
    std::vector<SceneNode*> m_children;
    // The object stored in the scene graph
    Object* m_object;
    // Each SceneNode nodes locals transform.
    Transform m_localTransform;
    // We additionally can store the world transform
    Transform m_worldTransform;





};

#endif  
