#ifndef OBJFILELOADER_HPP
#define OBJFILELOADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <glad/glad.h>  
#include "glm/glm.hpp"




class ObjFileLoader{
    public:
        ObjFileLoader(const char *);
        ~ObjFileLoader();
        std::vector<glm::vec3> m_vertices; 
	    std::vector<glm::vec2> m_uvs;
	    std::vector<glm::vec3> m_normals;
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

    private:
        inline std::vector<float> parseCoords(std::string line);
        std::string mtlFile;

};

#endif
