#pragma once
// How to forward declare this?
#include <vector>
struct Vertex;

class Mesh {
public:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	//void Draw(Shader& shader);
private:
	//  render data
	unsigned int m_VAO, m_VBO, m_EBO;

	void SetupMesh();
};