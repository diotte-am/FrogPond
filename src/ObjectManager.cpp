#include "ObjectManager.hpp"

// Constructor is empty
ObjectManager::ObjectManager(){

}

ObjectManager::~ObjectManager(){

}

ObjectManager& ObjectManager::Instance(){
    static ObjectManager* instance = new ObjectManager();
    return *instance;
}

// Retrieve a reference to an object
Object& ObjectManager::GetObject(unsigned int index){
    return *m_objects[index];
}

void ObjectManager::AddSceneNode(SceneNode*& o){
    m_nodes.push_back(o);
}

void ObjectManager::RemoveAll(){
    for(int i=0; i < m_objects.size(); i++){
        delete m_objects[i];
    }
    for(int i=0; i < m_nodes.size(); i++){
        delete m_nodes[i];
    }
}

void ObjectManager::UpdateAll(glm::mat4 projectionMatrix, Camera* camera){
    for(int i=0; i < m_objects.size(); i++){
        m_objects[i]->Update(projectionMatrix, camera);
    }
    for(int i=0; i < m_nodes.size(); i++){
        m_nodes[i]->Update(projectionMatrix, camera);
    }
}

void ObjectManager::RenderAll(){
    for(int i=0; i < m_objects.size(); i++){
        m_objects[i]->Render();
    }

    for(int i=0; i < m_nodes.size(); i++){
        m_nodes[i]->Draw();
    }
}

