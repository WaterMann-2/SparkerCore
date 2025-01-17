#include "sp_Mesh.h"

void sp_Primitive::Mesh::loadModel(string path) {
	Assimp::Importer importer;
	
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	bool result = !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode;
	SpConsole::fatalExit(result, "Assimp failed to find scene flags! " + string(importer.GetErrorString()), SP_ASSIMP_FLAGS_INCOMPLETE);


}

void sp_Primitive::Mesh::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		
	}
}