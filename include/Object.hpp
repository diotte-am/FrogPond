
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>

#include <vector>
#include <string>
#include "Camera.hpp"
#include "Shader.hpp"
#include "VertexBufferLayout.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Geometry.hpp"

#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Purpose:
// An abstraction to create multiple objects
//
//
class Object{
public:
    // Object Constructor
    Object();
    // Object destructor
    ~Object();

    // Create a textured quad
   // void MakeTexturedQuad(std::string fileName);
    // How to draw the object
    virtual void Render();
    virtual void Update(glm::mat4 projectionMatrix, Camera* camera);
protected: // Classes that inherit from Object are intended to be overridden.

	// Helper method for when we are ready to draw or update our object
	void Bind();
    // For now we have one buffer per object.
    VertexBufferLayout m_vertexBufferLayout;
    // For now we have one diffuse map and one normal map per object
    Texture m_textureDiffuse;
    Texture m_detailMap;
    Texture m_colorMap;
    // Store the objects Geometry
	Geometry m_geometry;

};


#endif
