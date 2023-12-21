#include <SDL2/SDL.h>



#include "Texture.hpp"

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <memory>

// Default Constructor
Texture::Texture(){

}


// Default Destructor
Texture::~Texture(){
	// Delete our texture from the GPU
	glDeleteTextures(1,&m_textureID);

    // Delete our image
    if(m_image != nullptr){
        delete m_image;
    }

}

void Texture::LoadTexture(const std::string filepath){
	// Set member variable
    m_filepath = filepath;
    // Load our actual image data
    // This method loads .ppm files of pixel data
    m_image = new Image(filepath);
    m_image->LoadPPM(true);

    glEnable(GL_TEXTURE_2D); 
	// Generate a buffer for our texture
    glGenTextures(1,&m_textureID);
    // Similar to our vertex buffers, we now 'select'
    // a texture we want to bind to.
    // Note the type of data is 'GL_TEXTURE_2D'
    glBindTexture(GL_TEXTURE_2D, m_textureID);
	
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// At this point, we are now ready to load and send some data to OpenGL.
	glTexImage2D(GL_TEXTURE_2D,
							0 ,
						GL_RGB,
                        m_image->GetWidth(),
                        m_image->GetHeight(),
						0,
						GL_RGB,
						GL_UNSIGNED_BYTE,
						 m_image->GetPixelDataPtr()); // Here is the raw pixel data
    // We are done with our texture data so we can unbind.
    // Generate a mipmap
    glGenerateMipmap(GL_TEXTURE_2D);                        
	// We are done with our texture data so we can unbind.    
	glBindTexture(GL_TEXTURE_2D, 0);
}


// slot tells us which slot we want to bind to.
// We can have multiple slots. By default, we
// will set our slot to 0 if it is not specified.
void Texture::Bind(unsigned int slot) const{
	// Using OpenGL 'state' machine we set the active texture
	// slot that we want to occupy. Again, there could
	// be multiple at once.
	// At the time of writing, OpenGL supports 8-32 depending
	// on your hardware.
    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}


