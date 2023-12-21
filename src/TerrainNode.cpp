#include "TerrainNode.hpp"

#include <string>
#include <iostream>

// The constructor
TerrainNode::TerrainNode(Object* ob){
	std::cout << "(TerrainNode.cpp) Constructor called\n";
	m_object = ob;

    // Create shader
    m_shader = Shader();
	// Setup shaders for the node.
	std::string vertexShader   = m_shader.LoadShader("./shaders/terrain_vert.glsl");
	std::string fragmentShader = m_shader.LoadShader("./shaders/terrain_frag.glsl");

	// Actually create our shader
	m_shader.CreateShader(vertexShader,fragmentShader);       
}

// The destructor 
TerrainNode::~TerrainNode(){

}


// Draw simply draws the current nodes
// object and all of its children. This is done by calling directly
// the objects draw method.
void TerrainNode::Draw(){
	// Bind the shader for this node or series of nodes
	m_shader.Bind();
	// Render our object
	if(m_object!=nullptr){
		// Render our object
		m_object->Render();
		// For any 'child nodes' also call the drawing routine.
		for(int i =0; i < m_children.size(); ++i){
			m_children[0]->Draw();
		}
	}	
}

// Update simply updates the current nodes
// object. This is done by calling directly
// the objects update method.
// TODO: Consider not passting projection and camera here
void TerrainNode::Update(glm::mat4 projectionMatrix, Camera* camera){
    if(m_object!=nullptr){
        m_localTransform.incrementRadians();
		m_localTransform.setRotation(m_localTransform.getRadians(), m_localTransform.getRotationAxis().x,
		m_localTransform.getRotationAxis().y, m_localTransform.getRotationAxis().z);
		m_localTransform.LoadIdentity();
		m_localTransform.updateLocal();
    
    
    	// Now apply our shader 
		m_shader.Bind();
    	// Set the uniforms in our current shader

        // For our object, we apply the texture in the following way
        // Note that we set the value to 0, because we have bound
        // our texture to slot 0.
        m_shader.SetUniform1i("u_DiffuseMap",0);  
        // TODO: This assumes every SceneNode is a 'Terrain' so this shader setup code
        //       needs to be moved preferably to 'Object' or 'Terrain'
        m_shader.SetUniform1i("u_DetailMap",1);  
        // Set the MVP Matrix for our object
        // Send it into our shader
        m_shader.SetUniformMatrix4fv("model", &m_worldTransform.GetInternalMatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("view", &camera->GetWorldToViewmatrix()[0][0]);
        m_shader.SetUniformMatrix4fv("projection", &projectionMatrix[0][0]);

        m_shader.SetUniform3f("u_cameraPosition", camera->GetEyeXPosition() + camera->GetViewXDirection(),
           camera->GetEyeYPosition() + camera->GetViewYDirection(),
           camera->GetEyeZPosition() + camera->GetViewZDirection());

        // Create a 'light'
        // Create a first 'light'
        m_shader.SetUniform3f("pointLights[0].lightColor",1.0f,1.0f,1.0f);
        m_shader.SetUniform3f("pointLights[0].lightPos",
           camera->GetEyeXPosition() + camera->GetViewXDirection(),
           camera->GetEyeYPosition() + camera->GetViewYDirection() + 30,
           camera->GetEyeZPosition() + camera->GetViewZDirection() + 50);
        m_shader.SetUniform1f("pointLights[0].ambientIntensity",5.0f);
        m_shader.SetUniform1f("pointLights[0].specularStrength",10.0f);
        m_shader.SetUniform1f("pointLights[0].constant",1.0f);
        m_shader.SetUniform1f("pointLights[0].linear",0.3f);
        m_shader.SetUniform1f("pointLights[0].quadratic",0.0f);

		// Create a second light
        m_shader.SetUniform3f("pointLights[1].lightColor",1.0f,1.0f,1.0f);
        m_shader.SetUniform3f("pointLights[1].lightPos",
           camera->GetEyeXPosition(),
           camera->GetEyeYPosition(),
           camera->GetEyeZPosition());

        m_shader.SetUniform1f("pointLights[1].ambientIntensity",20.0f);
        m_shader.SetUniform1f("pointLights[1].specularStrength",10.0f);
        m_shader.SetUniform1f("pointLights[1].constant",0.1f);
        m_shader.SetUniform1f("pointLights[1].linear",1.0);
        m_shader.SetUniform1f("pointLights[1].quadratic",1.0f);

	
		// Iterate through all of the children
		for(int i =0; i < m_children.size(); ++i){
			m_children[0]->Update(projectionMatrix, camera);
		}
	}
}

// Returns the actual local transform stored in our SceneNode
// which can then be modified
Transform& TerrainNode::GetLocalTransform(){
    return m_localTransform; 
}

// Returns the worled  transform stored in our SceneNode
// which can then be modified
Transform& TerrainNode::GetWorldTransform(){
    return m_worldTransform; 
}