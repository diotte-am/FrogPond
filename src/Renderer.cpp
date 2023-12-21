#include "Renderer.hpp"



// Sets the height and width of our renderer
Renderer::Renderer(unsigned int w, unsigned int h){
    m_screenWidth = w;
    m_screenHeight = h;

    // By default create one camera per render
    // TODO: You could abstract out further functions to create
    //       a camera as a scene node and attach them at various levels.
    Camera* defaultCamera = new Camera();
    // Add our single camera
    m_cameras.push_back(defaultCamera);

    

}

// Sets the height and width of our renderer
Renderer::~Renderer(){
    // Delete all of our camera pointers
    for(int i=0; i < m_cameras.size(); i++){
        delete m_cameras[i];
    }
}

void Renderer::Update(){
    // Here we apply the projection matrix which creates perspective.
    // The first argument is 'field of view'
    // Then perspective
    // Then the near and far clipping plane.
    // Note I cannot see anything closer than 0.1f units from the screen.
    m_projectionMatrix = glm::perspective(glm::radians(45.0f),((float)m_screenWidth)/((float)m_screenHeight),0.1f,512.0f);

    // Perform the update
    if(!m_roots.empty()){
        // TODO: By default, we will only have one camera
        //       You may otherwise not want to hardcode
        //       a value of '0' here.
        for(int i = 0; i < m_roots.size(); i++){
            m_roots[i]->Update(m_projectionMatrix, m_cameras[0]);
        }
    }

    if(!m_terrain.empty()){
        for(int j = 0; j < m_terrain.size(); j++){
            m_terrain[j]->Update(m_projectionMatrix, m_cameras[0]);
        }
    }

}

// Initialize clear color
// Setup our OpenGL State machine
// Then render the scene
void Renderer::Render(){

    // What we are doing, is telling opengl to create a depth(or Z-buffer) 
    // for us that is stored every frame.
   // glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D); 
    // This is the background of the screen.
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glClearColor( 0.01f, 0.01f, 0.01f, 1.f );
    // Clear color buffer and Depth Buffer
    // Remember that the 'depth buffer' is our
    // z-buffer that figures out how far away items are every frame
    // and we have to do this every frame!
    glClear(GL_COLOR_BUFFER_BIT);

    // Nice way to debug your scene in wireframe!
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    
    // Now we render our objects from our scenegraph
    if(!m_roots.empty()){
        for(int i = 0; i < m_roots.size(); i++){
            m_roots[i]->Draw();
        }
    }

    if(!m_terrain.empty()){
        for(int j = 0; j < m_terrain.size(); j++){
            m_terrain[j]->Draw();
        }
    }
}

// Determines what the root is of the renderer, so the
// scene can be drawn.
void Renderer::setRoot(SceneNode* startingNode){
    m_roots.push_back(startingNode);
}

void Renderer::setTerrain(TerrainNode* node){
    m_terrain.push_back(node);
}

// index is position in root list, node is new child at root
void Renderer::setChild(unsigned int index, SceneNode* child){
    m_roots[index]->AddChild(child);
    
}

// index is position of root, node1 is new child, node2 is parent
void Renderer::setChild(unsigned int index, SceneNode* child, SceneNode* parent){
    parent->AddChild(child);
    
}

// index is position of root, node1 is new child, node2 is parent
void Renderer::setChild(unsigned int index, SceneNode* child, std::string parent){
        
        if(m_roots[index]->nameMatches(parent)){
            m_roots[index]->AddChild(child);
        }
}

