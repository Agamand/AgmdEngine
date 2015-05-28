/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/FBXLoader.h>
#include <Core/Driver.h>
#include <Core/SceneNode/MeshNode.h>
#include <Core/Model/Material.h>
#include <Core/ResourceManager.h>
#include <Utilities/StringUtils.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>
#include <fbxsdk.h>


using namespace AgmdUtilities;
namespace Agmd
{

    FbxManager* g_pFbxSdkManager = NULL;
    void ProcessNode(FbxNode* node,SceneNode*parent);
    Material* LoadMaterials(FbxNode* pFbxChildNode);
    void LoadMaterial(FbxSurfaceMaterial*material, Material* mat,const char* type, a_uint32 unit);
    Material* LoadMaterials(FbxNode* pFbxChildNode)
    {
        int materialCount = pFbxChildNode->GetSrcObjectCount<FbxSurfaceMaterial>();

        // multiMaterial not supported
        for (int index = 0;  index < materialCount && index < 1; index++)
        {

            FbxSurfaceMaterial* material = (FbxSurfaceMaterial*)pFbxChildNode->GetSrcObject<FbxSurfaceMaterial>(index);
            
            Material* mat = NULL;
            if(mat = ResourceManager::Instance().Get<Material>(material->GetName()))
                return mat;
            if (material != NULL)
            {
                mat = new Material();
                std::cout << "\nmaterial: " << material->GetName() << std::endl;

                //hack for test model
                if(std::string(material->GetName()).compare("12 - Default") == 0 ||std::string(material->GetName()).compare("_TrissModel001_Material003") == 0)
                    mat->SetRenderQueue(TYPE_BLEND);
                LoadMaterial(material,mat,FbxSurfaceMaterial::sDiffuse,0);
                LoadMaterial(material,mat,FbxSurfaceMaterial::sBump,1);
                LoadMaterial(material,mat,FbxSurfaceMaterial::sSpecular,2);
                ResourceManager::Instance().Add(material->GetName(),mat);
            }
            return mat;
        }

    }
    void LoadMaterial(FbxSurfaceMaterial*material, Material* mat,const char* type, a_uint32 unit)
    {
       
        FbxProperty prop = material->FindProperty(type);

        int layeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

        if (layeredTextureCount > 0)
        {
            for (int j = 0; j < layeredTextureCount; j++)
            {
                FbxLayeredTexture* layered_texture = FbxCast<FbxLayeredTexture>(prop.GetSrcObject<FbxLayeredTexture>(j));
                int lcount = layered_texture->GetSrcObjectCount<FbxTexture>();

                for (int k = 0; k < lcount; k++)
                {
                    FbxTexture* texture = FbxCast<FbxTexture>(layered_texture->GetSrcObject<FbxTexture>(k));
                    const char* textureName = texture->GetName();
                    std::cout << "tex name --> " << textureName << std::endl;
                }
            }
        }
        else 
        {
            int textureCount = prop.GetSrcObjectCount<FbxTexture>();
            for (int j = 0; j < textureCount; j++)
            {
                FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(j));
                const char* textureName = texture->GetName();
                std::cout << textureName;

                FbxProperty p = texture->RootProperty.Find("Filename");
                FbxFileTexture *lFileTexture = FbxCast<FbxFileTexture>(texture);    

                std::cout << lFileTexture->GetFileName() << std::endl;
                Texture tex;
                tex.CreateFromFile(lFileTexture->GetFileName(),PXF_A8R8G8B8,TEX_USE_FILTER| TEX_NOMIPMAP);
                mat->SetTexture(tex,unit,(TRenderPass)(1 << TRenderPass::RENDERPASS_DIFFUSE));

            }
        }
    }
    FBXLoader::FBXLoader()
    {
        if(g_pFbxSdkManager == nullptr)
        {
            g_pFbxSdkManager = FbxManager::Create();

            FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT );
            g_pFbxSdkManager->SetIOSettings(pIOsettings);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_MATERIAL,        true);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_TEXTURE,         true);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_LINK,            false);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_SHAPE,           false);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GOBO,            false);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_ANIMATION,       true);
            (*(g_pFbxSdkManager->GetIOSettings())).SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
        }

        
    }

    FBXLoader::~FBXLoader()
    {}

    SceneNode* FBXLoader::LoadFromFile( const std::string& filename )
    {
        FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager,"");
        FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager,"");
        bool bSuccess = pImporter->Initialize(filename.c_str(), -1, g_pFbxSdkManager->GetIOSettings() );
        std::cout << "FBX import status : "<< pImporter->GetStatus().GetCode()<< ", Error : "<<pImporter->GetStatus().GetErrorString() <<", Success : "<< bSuccess << std::endl << std::endl; 
        if(!bSuccess) return NULL;
       
        pImporter->Import(pFbxScene);
        FbxAxisSystem SceneAxisSystem = pFbxScene->GetGlobalSettings().GetAxisSystem();
        FbxAxisSystem OurAxisSystem(FbxAxisSystem::eYAxis, FbxAxisSystem::eParityOdd, FbxAxisSystem::eRightHanded);
        if (SceneAxisSystem != OurAxisSystem) {
                    OurAxisSystem.ConvertScene(pFbxScene);
        }

        FbxSystemUnit SceneSystemUnit = pFbxScene->GetGlobalSettings().GetSystemUnit();


        if (fabs(SceneSystemUnit.GetScaleFactor() - 1.0) > 0.00001)
        {
            FbxSystemUnit OurSystemUnit(1.0);
            OurSystemUnit.ConvertScene(pFbxScene);
        }

        pImporter->Destroy();
          
        FbxNode* pFbxRootNode = pFbxScene->GetRootNode();

        SceneNode* root= NULL;
        //a_vector<Model::TIndex> indices;dd
        if(pFbxRootNode)
        {
                
                int cCount = pFbxRootNode->GetChildCount();
                root = new SceneNode();
                root->getTransform().rotate(-90.0f,vec3(1,0,0));
                ProcessNode(pFbxRootNode,root);

        }
        //return S_OK;
        return root;
    }
    void ProcessUV(FbxMesh* mesh,FbxStringList& uvlist, int unit,Model::TVertex* out)
    {
        const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(uvlist.GetStringAt(0));

        if(!lUVElement)
            return;

        // only support mapping mode eByPolygonVertex and eByControlPoint
        if( lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
            lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint )
            return;

        //index array, where holds the index referenced to the uv data
        const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
        const int lIndexCount= (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

        //iterating through the data by polygon
        const int lPolyCount = mesh->GetPolygonCount();

        if( lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint )
        {
            for(int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
            {
                int lUVIndex = 0;
                if( lUVElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                    lUVIndex = lVertexIndex;
                if(lUVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                    lUVIndex = lUVElement->GetIndexArray().GetAt(lVertexIndex);

                FbxVector2 lUV = lUVElement->GetDirectArray().GetAt(lUVIndex);
                out[lVertexIndex].texCoords = vec2(lUV[0],lUV[1]);
            }
//             for( int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex )
//             {
//                 // build the max index array that we need to pass into MakePoly
//                 //const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
// //                 for( int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex )
// //                 {
// //                     FbxVector2 lUVValue;
// // 
// //                     //get the index of the current vertex in control points array
// //                     int lPolyVertIndex = pMesh->GetPolygonVertex(lPolyIndex,lVertIndex);
// // 
// //                     //the UV index depends on the reference mode
// //                     int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;
// // 
// //                     lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);
// //                     out[]
// //                     //User TODO:
// //                     //Print out the value of UV(lUVValue) or log it to a file
// //                 }
//             }
        }
        else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
        {
            for(int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
            {
//                 int lUVIndex = 0;
//                 if( lUVElement->GetReferenceMode() == FbxGeometryElement::eDirect )
//                     lUVIndex = lVertexIndex;
//                 if(lUVElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//                     lUVIndex = lUVElement->GetIndexArray().GetAt(lVertexIndex);

                FbxVector2 lUV = lUVElement->GetDirectArray().GetAt(lVertexIndex);
                out[lVertexIndex].texCoords = vec2(lUV[0],lUV[1]);
            }
//             int lPolyIndexCounter = 0;
//             for( int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex )
//             {
//                 // build the max index array that we need to pass into MakePoly
//                 const int lPolySize = pMesh->GetPolygonSize(lPolyIndex);
//                 for( int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex )
//                 {
//                     if (lPolyIndexCounter < lIndexCount)
//                     {
//                         FbxVector2 lUVValue;
// 
//                         //the UV index depends on the reference mode
//                         int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;
// 
//                         lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);
// 
//                         //User TODO:
//                         //Print out the value of UV(lUVValue) or log it to a file
// 
//                         lPolyIndexCounter++;
//                     }
//                 }
//             }
        }
    }
    void ProcessNormal(FbxMesh* mesh,Model::TVertex* out)
    {
        FbxGeometryElementNormal* lNormalElement = mesh->GetElementNormal();
        if(lNormalElement)
        {

            if( lNormalElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
            {
               //mesh->GenerateNormals(true,true);
            }
            if( lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint )
            {
                for(int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
                {
                    int lNormalIndex = 0;
                    if( lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                        lNormalIndex = lVertexIndex;
                    if(lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexIndex);

                    FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
                    out[lVertexIndex].normal = vec3(lNormal[0],lNormal[1],lNormal[2]);
                }
            }
            else if(lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
            {
                int lIndexByPolygonVertex = 0;
                int *_indices = mesh->GetPolygonVertices();
                for(int lPolygonIndex = 0; lPolygonIndex < mesh->GetPolygonCount(); lPolygonIndex++)
                {
                    int lPolygonSize = mesh->GetPolygonSize(lPolygonIndex);
               
                    for(int i = 0; i < lPolygonSize; i++)
                    {
                        int lNormalIndex = 0;
                        if( lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                            lNormalIndex = lIndexByPolygonVertex;

                        if(lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                            lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

                        FbxVector4 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
                    
                       // std::cout << lIndexByPolygonVertex << " " << lNormalIndex << std::endl;                           
                        out[_indices[lPolygonIndex*3+i]].normal += vec3(lNormal[0],lNormal[1],lNormal[2]);
                        lIndexByPolygonVertex++;
                    }
                }

            }
        }
    }
    void ProcessTangentAndBinormal(FbxMesh* mesh,FbxStringList& uvlist, int unit,Model::TVertex* out)
    {
        mesh->GenerateTangentsData(uvlist.GetStringAt(unit));
        FbxGeometryElementTangent* lTangentElement = mesh->GetElementTangent();

        FbxGeometryElementBinormal* lBinormalElement = mesh->GetElementBinormal();
        int a = lBinormalElement->GetDirectArray().GetCount(),b = lTangentElement->GetDirectArray().GetCount();
        if(lTangentElement)
        {
     
            if( lTangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint )
            {
                for(int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
                {
                    int lTangentIndex = 0;
                    if( lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                        lTangentIndex = lVertexIndex;
                    if(lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        lTangentIndex = lTangentElement->GetIndexArray().GetAt(lVertexIndex);

                    FbxVector4 lTangent = lTangentElement->GetDirectArray().GetAt(lTangentIndex);
                    out[lVertexIndex].tangent = vec3(lTangent[0],lTangent[1],lTangent[2]);
                }
            }
            else if(lTangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
            {
                int lIndexByPolygonVertex = 0;
                int *_indices = mesh->GetPolygonVertices();
                for(int lPolygonIndex = 0; lPolygonIndex < mesh->GetPolygonCount(); lPolygonIndex++)
                {
                    int lPolygonSize = mesh->GetPolygonSize(lPolygonIndex);

                    for(int i = 0; i < lPolygonSize; i++)
                    {
                        int lTangentIndex = 0;
                        if( lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                            lTangentIndex = lIndexByPolygonVertex;

                        if(lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                            lTangentIndex = lTangentElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

                        FbxVector4 lTangent = lTangentElement->GetDirectArray().GetAt(lTangentIndex);

                        // std::cout << lIndexByPolygonVertex << " " << lNormalIndex << std::endl;                           
                        out[_indices[lPolygonIndex*3+i]].tangent += vec3(lTangent[0],lTangent[1],lTangent[2]);
                        lIndexByPolygonVertex++;
                    }
                }
            }
        }
        if(lBinormalElement)
        {

            if( lBinormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint )
            {
                for(int lVertexIndex = 0; lVertexIndex < mesh->GetControlPointsCount(); lVertexIndex++)
                {
                    int lBinormalIndex = 0;
                    if( lBinormalElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                        lBinormalIndex = lVertexIndex;
                    if(lBinormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        lBinormalIndex = lBinormalElement->GetIndexArray().GetAt(lVertexIndex);

                    FbxVector4 lBinormal = lBinormalElement->GetDirectArray().GetAt(lBinormalIndex);
                    out[lVertexIndex].binormal = vec3(lBinormal[0],lBinormal[1],lBinormal[2]);
                }
            }
            else if(lBinormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
            {
                int lIndexByPolygonVertex = 0;
                int *_indices = mesh->GetPolygonVertices();
                for(int lPolygonIndex = 0; lPolygonIndex < mesh->GetPolygonCount(); lPolygonIndex++)
                {
                    int lPolygonSize = mesh->GetPolygonSize(lPolygonIndex);

                    for(int i = 0; i < lPolygonSize; i++)
                    {
                        int lBinormalIndex = 0;
                        if( lBinormalElement->GetReferenceMode() == FbxGeometryElement::eDirect )
                            lBinormalIndex = lIndexByPolygonVertex;

                        if(lBinormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                            lBinormalIndex = lBinormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);

                        FbxVector4 lBinormal = lBinormalElement->GetDirectArray().GetAt(lBinormalIndex);

                        // std::cout << lIndexByPolygonVertex << " " << lNormalIndex << std::endl;                           
                        out[_indices[lPolygonIndex*3+i]].binormal += vec3(lBinormal[0],lBinormal[1],lBinormal[2]);
                        lIndexByPolygonVertex++;
                    }
                }
            }
        }
    }
    void ProcessNode(FbxNode* node,SceneNode*parent)
    {

        for(int i = 0; i < node->GetChildCount(); i++)
        {
            
            FbxNode* pFbxChildNode = node->GetChild(i);

            if(pFbxChildNode->GetNodeAttribute() == NULL)
                continue;
            
            Model* model;
           
            FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();

            if(AttributeType != FbxNodeAttribute::eMesh)
                continue;

            FbxMesh* pMesh = (FbxMesh*) pFbxChildNode->GetNodeAttribute();
            //std::string name = StringBuilder(pMesh->GetName())(i);

             if(true)//(model = ResourceManager::Instance().Get<Model>(name.c_str())) == NULL){
             {
                FbxVector4* pVertices = pMesh->GetControlPoints();
                FbxStringList UVSetNameList;

                a_vector<Model::TVertex> vertices(pMesh->GetControlPointsCount());
                a_vector<Model::TIndex> indices(pMesh->GetPolygonVertexCount());
                pMesh->GetUVSetNames( UVSetNameList );

            

                 int *_indices = pMesh->GetPolygonVertices();
                 for(int j = 0; j < pMesh->GetPolygonVertexCount();j++)
                 {
                     indices[j] = _indices[j];
                 }

                //for (int j = 0; j < pMesh->GetPolygonCount(); j++)
                //{
                    //int iNumVertices = pMesh->GetPolygonSize(j);
                    //assert( iNumVertices == 3 );
            
                ProcessNormal(pMesh,&vertices[0]);
                ProcessUV(pMesh,UVSetNameList,0,&vertices[0]);
                ProcessTangentAndBinormal(pMesh,UVSetNameList,0,&vertices[0]);
                for(int j = 0; j < pMesh->GetControlPointsCount(); j++)
                {
                    FbxVector4 vert = pMesh->GetControlPointAt(j);

                    Model::TVertex& vertex=vertices[j];
                    vertex.position[0] = (float)vert.mData[0];
                    vertex.position[1] = (float)vert.mData[1];
                    vertex.position[2] = (float)vert.mData[2];
                    vertex.normal = normalize(vertex.normal);
                    vertex.binormal = normalize(vertex.binormal);
                    vertex.tangent = normalize(vertex.tangent);
    //                 vertex.texCoords[0] = (float)uvArray[j].mData[0];
    //                 vertex.texCoords[1] = (float)uvArray[j].mData[1];
    // 
    //                 vertex.normal[0] = (float)nArray[j].mData[0];
    //                 vertex.normal[1] = (float)nArray[j].mData[1];
    //                 vertex.normal[2] = (float)nArray[j].mData[2];

    //                 FbxVector4 normal;
    //                 if(pMesh->Getcon(j,k,normal)){
    //                     vertex.normal[0] = normal[0];
    //                     vertex.normal[1] = normal[1];
    //                     vertex.normal[2] = normal[2];
    //                 }   
    // 
    //                 //if(pMesh->Gene)
    // 
    // 
    //                 FbxVector2 uv;
    //                 bool unmap;
    //                 if(UVSetNameList.GetCount() &&  pMesh->GetPolygonVertexUV(j,k,UVSetNameList.GetStringAt(0),uv,unmap)){
    //                     vertex.texCoords[0] = uv[0];
    //                     vertex.texCoords[1] = uv[1];
    //                 }

                
                    /*for (int k = 0; k < iNumVertices; k++)
                    {
                        int iControlPointIndex = pMesh->GetPolygonVertex(j, k);


                        Model::TVertex vertex;
                        vertex.position[0] = (float)pVertices[iControlPointIndex].mData[0];
                        vertex.position[1] = (float)pVertices[iControlPointIndex].mData[1];
                        vertex.position[2] = (float)pVertices[iControlPointIndex].mData[2];
                    
                        FbxVector4 normal;
                        if(pMesh->GetPolygonVertexNormal(j,k,normal)){
                            vertex.normal[0] = normal[0];
                            vertex.normal[1] = normal[1];
                            vertex.normal[2] = normal[2];
                        }   

                        //if(pMesh->Gene)


                        FbxVector2 uv;
                        bool unmap;
                        if(UVSetNameList.GetCount() &&  pMesh->GetPolygonVertexUV(j,k,UVSetNameList.GetStringAt(0),uv,unmap)){
                            vertex.texCoords[0] = uv[0];
                            vertex.texCoords[1] = uv[1];
                        }

                        vertices.push_back(vertex);
                    }*/
                }
                model = new Model(&vertices[0],vertices.size(),&indices[0],indices.size());
                //ResourceManager::Instance().Add(name.c_str(),model);
            }

            //for(int j = 0; j < pMesh->getelementpo)
            Material* mat = LoadMaterials(pFbxChildNode);
                

            MeshNode* _node = new MeshNode(model);
            _node->setMaterial(mat);
            parent->addChild(_node);
            ProcessNode(pFbxChildNode,_node);
        }
    }

    void FBXLoader::SaveToFile(const Model* object, const std::string& filename)
    {

    }


    void FBXLoader::OnError()
    {
        throw Exception("");
    }


}