#include <string>
namespace Component
{
  class IndexedMesh;
}
class aiNode;
class aiScene;

namespace Mesh
{
  namespace Loader
  {
    Component::IndexedMesh LoadMeshFromFile(const std::string &filePath);
    void ProcessNode(aiNode *node, const aiScene *scene);
  }

}
