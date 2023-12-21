#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glad/glad.h>

#include <vector>
#include <iostream>

#include "SceneNode.hpp"
#include "TerrainNode.hpp"
#include "Camera.hpp"

class Renderer{
public:
    // The constructor	
    // Sets the width and height of the rendererer draws to
    Renderer(unsigned int w, unsigned int h);
    // Destructor
    ~Renderer();
    // Update the scene
    void Update();
    // Render the scene
    void Render();
    // Sets the root of our renderer to some node to
    // draw an entire scene graph
    void setRoot(SceneNode* startingNode);
    void setTerrain(TerrainNode* TerrainNode);
    SceneNode* getRoot(unsigned int index){ return m_roots[index];};
    void setChild(unsigned int index, SceneNode* child);
    void setChild(unsigned int index, SceneNode* child, SceneNode* parent);
    void setChild(unsigned int index, SceneNode* child, std::string parent);

    void setHumanPos(SceneNode* human){ m_humanPos = human;};
    SceneNode* getHumanPointer(){ return m_humanPos; };
    // Returns the camera at an index
    Camera*& GetCamera(unsigned int index){
        if(index > m_cameras.size()-1){
            // TODO: Some sort of error reporting here.
        }
        return m_cameras[index];
    }

// TODO: maybe write getter/setter methods
protected:
    // One or more cameras camera per Renderer
    std::vector<Camera*> m_cameras;

    // Root scene node
    SceneNode* m_humanPos;
    std::vector<SceneNode*> m_roots;
    std::vector<TerrainNode*> m_terrain;
    // Store the projection matrix for our camera.
    glm::mat4 m_projectionMatrix;

private:
    // Screen dimension constants
    int m_screenHeight;
    int m_screenWidth;
};

#endif
