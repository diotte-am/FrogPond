#include "SDLGraphicsProgram.hpp"
#include "Camera.hpp"

#include "Sphere.hpp"
#include "Terrain.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	m_window = NULL;
    m_width = w;
    m_height = h;

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
		//Use OpenGL 3.3 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		// We want to request a double buffer for smooth updating.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		//Create window
		m_window = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                m_width,
                                m_height,
                                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

		// Check if Window did not create.
		if( m_window == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create an OpenGL Graphics Context
		m_openGLContext = SDL_GL_CreateContext( m_window );
		if( m_openGLContext == NULL){
			errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		// Initialize GLAD Library
		if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
			errorStream << "Failed to iniitalize GLAD\n";
			success = false;
		}

		//Initialize OpenGL
		if(!InitGL()){
			errorStream << "Unable to initialize OpenGL!\n";
			success = false;
		}
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

	// SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
	GetOpenGLVersionInfo();


    // Setup our Renderer
    m_renderer = new Renderer(m_width, m_height);    
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(m_renderer!=nullptr){
        delete m_renderer;
    }


    //Destroy window
	SDL_DestroyWindow( m_window );
	// Point m_window to NULL to ensure it points to nothing.
	m_window = nullptr;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::InitGL(){
	//Success flag
	bool success = true;

	return success;
}


void SDLGraphicsProgram::LoadLibrary(){
    AssetLibrary* lib = new AssetLibrary();
    for(int i = 0; i < lib->assetCount() ; i++){
        Asset* a;
        a = lib->getAsset(i);

        switch (a->getAssetType()){
        case 0:
            std::cout << "Model" << std::endl;
            break;
        case 1: {
            SceneNode* n;
            Sphere* o = new Sphere();
            n = new SceneNode(o, a->getName());
            // filename
            o->LoadTexture(a->getTextureFile());
            // parent
            if(a->getParent() == "ROOT"){
                m_renderer->setRoot(n);
            } else{
                // find node by name "parent"
                m_renderer->setChild(0, n, a->getParent());
            }
             // position
            n->setPosition(a->getPosition());
            // scale
            n->setScale(a->getScale());
            // rotation axis
            n->setRotation(a->getRotationIncrement(), a->getRotationAxis());
            n->resetLocalMatrix();
            n->loadLocalMatrix();
            if(i == 0){
            m_renderer->setHumanPos(n);
            }
        }
            break;
        case 2: {
            Terrain* terrain = new Terrain(a->getTextureFile());
            terrain->LoadTextures(a->getColorMap(), a->getDetailMap());
            TerrainNode* terrainNode;
            terrainNode = new TerrainNode(terrain);
            m_renderer->setTerrain(terrainNode);
            terrainNode->setPosition(a->getPosition());
            // scale
            terrainNode->setScale(a->getScale());
            // rotation axis
            terrainNode->setRotation(a->getRotationIncrement(), a->getRotationAxis());
            terrainNode->resetLocalMatrix();
            terrainNode->loadLocalMatrix();
        }
            break;
        case 3:
            std::cout << "Cube" << std::endl;
            break;
        default:
            break;
        }   
        
    }
}
   

//Loops forever!
void SDLGraphicsProgram::Loop(){
    LoadLibrary();

    // Set a default position for our camera
    m_renderer->GetCamera(0)->SetCameraEyePosition(246.0f,35.0f,475.0f);

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();

    // Set the camera speed for how fast we move.
    float cameraSpeed = 5.0f;

    // While application is running
    while(!quit){
        //Handle events on queue
        while(SDL_PollEvent( &e ) != 0){
            // User posts an event to quit
            // An example is hitting the "x" in the corner of the window.
            if(e.type == SDL_QUIT){
                quit = true;
            }
            // Handle keyboard input for the camera class
            if(e.type==SDL_MOUSEMOTION){
                // Handle mouse movements
                int mouseX = e.motion.x;
                int mouseY = e.motion.y;
                m_renderer->GetCamera(0)->MouseLook(mouseX, mouseY);
            }
            switch(e.type){
                // Handle keyboard presses
                case SDL_KEYDOWN:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT: {
                            glm::vec3 newposition = glm::vec3(m_renderer->GetCamera(0)->MoveLeft(cameraSpeed));
                            m_renderer->getHumanPointer()->moveLeft(newposition);
                            break;
                        }
                             

                        case SDLK_RIGHT: {
                            glm::vec3 newposition = glm::vec3(m_renderer->GetCamera(0)->MoveRight(cameraSpeed));
                            m_renderer->getHumanPointer()->moveRight(newposition);
                            break;
                        }
                            
                        case SDLK_UP:{
                            glm::vec3 newposition = glm::vec3(m_renderer->GetCamera(0)->MoveForward(cameraSpeed));
                            m_renderer->getHumanPointer()->moveFoward(newposition);
                            break;
                        }

                        case SDLK_DOWN:{
                            glm::vec3 newposition = glm::vec3(m_renderer->GetCamera(0)->MoveBackward(cameraSpeed));
                            m_renderer->getHumanPointer()->moveBack(newposition);
                            break;
                        }
                            

                        case SDLK_RSHIFT:
                            m_renderer->GetCamera(0)->MoveUp(cameraSpeed);
                            break;

                        case SDLK_RCTRL:
                            m_renderer->GetCamera(0)->MoveDown(cameraSpeed);
                            break;

                        case SDLK_ESCAPE:
                        quit = true;
                        break;

                    }
                break;
            }
        } // End SDL_PollEvent loop.
        
        // Update our scene through our renderer
        m_renderer->Update();
        // Render our scene using our selected renderer
        m_renderer->Render();
        // Delay to slow things down just a bit!
        SDL_Delay(25);  // TODO: You can change this or implement a frame
                        // independent movement method if you like.
      	//Update screen of our specified window
      	SDL_GL_SwapWindow(GetSDLWindow());
	}
    //Disable text input
    SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return m_window;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::GetOpenGLVersionInfo(){
	SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
	SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
	SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
	SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
	SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
