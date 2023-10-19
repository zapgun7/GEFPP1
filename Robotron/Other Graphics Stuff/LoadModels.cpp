#include "cMesh.h"
#include <vector>

//extern std::vector< cMesh* > g_vec_pMeshesToDraw;

float getRandomFloat(float a, float b);

bool LoadModels(void)
{

        // bun_zipper_res2_xyz_n_rgba.ply
    // bathtub_xyz_n_rgba.ply

//    // Add some models to the "scene"
//    cMesh bunny1;   
//    bunny1.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny1.position = glm::vec3(-1.0f, 0.0f, 0.0f);
//    bunny1.scale = 10.0f;
//    bunny1.orientation.x = glm::radians(45.0f);
//
//    cMesh bunny2;
//    bunny2.meshName = "bun_zipper_res2_xyz_n_rgba.ply";
//    bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bunny2.scale = 7.5f;
//    bunny2.orientation.y = glm::radians(135.0f);
//
//    cMesh bathtub;
//    bathtub.meshName = "bathtub_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    bathtub.scale = 0.25f;
//
////    // Smart array of cMesh object
////    std::vector<cMesh> vecMeshesToDraw;
//    g_vecMeshesToDraw.push_back(bunny1);
//    g_vecMeshesToDraw.push_back(bunny2);
//    g_vecMeshesToDraw.push_back(bathtub);
//    g_vecMeshesToDraw.push_back(terrain);

//    cMesh* pTerrain = new cMesh();
//    pTerrain->meshName = "Terrain_xyz_n_rgba.ply";
//    //bunny2.position = glm::vec3(1.0f, 0.0f, 0.0f);
//    pTerrain->scale = 1.0f;
//    pTerrain->drawPosition.y = -25.0f;
//    ::g_vec_pMeshesToDraw.push_back(pTerrain);


//    cMesh* pGridGroundMesh = new cMesh();
//    pGridGroundMesh->meshName = "Flat_Grid_100x100.ply";
    //pGridGroundMesh->bIsWireframe = true;
    //pGridGroundMesh->bDoNotLight = true;
    // note this does NOT have a physProps, so is ignored by the physics update loop
//    pGridGroundMesh->drawPosition.y = 0.0f;   //  0,-10,0
//    pGridGroundMesh->friendlyName = "Ground";
//    ::g_vec_pMeshesToDraw.push_back(pGridGroundMesh);
// 
//     cMesh* pFlat_1x1_planeMesh = new cMesh();
//     pFlat_1x1_planeMesh->meshName = "Flat_1x1_plane.ply";
//     //pFlat_1x1_planeMesh->bIsWireframe = true;
//     //pFlat_1x1_planeMesh->bDoNotLight = true;
//     // note this does NOT have a physProps, so is ignored by the physics update loop
//     pFlat_1x1_planeMesh->drawPosition.y = -15.0f;   //  0,-10,0
//     pFlat_1x1_planeMesh->friendlyName = "Ground";
//    ::g_vec_pMeshesToDraw.push_back(pFlat_1x1_planeMesh);
// 
//    cMesh* pFlat_1x1_planeMesh_DEBUG = new cMesh();
//    pFlat_1x1_planeMesh_DEBUG->meshName = "Flat_1x1_plane.ply";
//    pFlat_1x1_planeMesh->bIsWireframe = true;
//    pFlat_1x1_planeMesh->bDoNotLight = true;
//    pFlat_1x1_planeMesh->bUseDebugColours = true;
//    pFlat_1x1_planeMesh->wholeObjectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//    // note this does NOT have a physProps, so is ignored by the physics update loop
//    pFlat_1x1_planeMesh_DEBUG->drawPosition.y = pFlat_1x1_planeMesh->drawPosition.y -0.01f;   //  0,-10,0
//    ::g_vec_pMeshesToDraw.push_back(pFlat_1x1_planeMesh_DEBUG);


    
    return true;
}
