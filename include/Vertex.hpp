#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>

// third party libraries
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/glm.hpp"

class Vertex{

    private:
        glm::vec3 position;
        glm::vec2 texture;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bitangent;
        float delta = 0.0000006;
        

    public:
        // Constructors
        Vertex();
        Vertex(float px, float py, float pz, float tu, float tv, float nx, float ny, float nz);
        
        // Destructor
        ~Vertex();

        // operators
        bool operator == (const Vertex &t) const;

        // getters
        glm::vec3 getPosition(){return position;};
        glm::vec2 getTexture(){return texture;};
        glm::vec3 getNormal(){return normal;};
        glm::vec3 getTangent(){return tangent;};
        glm::vec3 getBitangent(){return bitangent;};

        // setters
        void setBitangent(glm::vec3 bt){bitangent = bt;};
        void setTangent(glm::vec3 t){tangent = t;};
        
};

#endif