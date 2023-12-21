#include "Vertex.hpp"

Vertex::Vertex(){

};

Vertex::~Vertex(){};

Vertex::Vertex(float px, float py, float pz, float tu, float tv, float nx, float ny, float nz){
    position = glm::vec3(px, py, pz);
    texture = glm::vec2(tu, tv);
    normal = glm::vec3(nx, ny, nz);
};

bool Vertex::operator==(const Vertex &v) const{
    bool isEqual = false;
    if(glm::all(glm::lessThan(abs(v.position - position), glm::vec3(delta)))){
        if(glm::all(glm::lessThan(abs(v.texture - texture), glm::vec2(delta)))){
            if(glm::all(glm::lessThan(abs(v.normal - normal), glm::vec3(delta)))){
                if(glm::all(glm::lessThan(abs(v.tangent - tangent), glm::vec3(delta)))){
                    if(glm::all(glm::lessThan(abs(v.bitangent - bitangent), glm::vec3(delta)))){
                        return true;
                    }
                    return false;
                }
                return false;
            }
            return false;
        } 
        return false;
    }

    return isEqual;
}