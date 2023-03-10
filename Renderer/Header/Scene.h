#pragma once
#include "Light.h"
#include "StorageBuffer.h"
#include "Shader.h"
#include "Camera.h"

#define MAX_LIGHT 10

namespace Renderer
{
	struct DirLights
	{
		__declspec(align(4))int mSize = 0;
		DirectionalLight mData[MAX_LIGHT];
	};

	struct PointLights
	{
		__declspec(align(4))int mSize = 0;
		PointLight mData[MAX_LIGHT];
	};

	struct SpotLights
	{
		__declspec(align(4))int mSize = 0;
		SpotLight mData[MAX_LIGHT];
	};

	template <class T> class Scene
	{
		public:
			std::vector<T*> mGameObjects;

			DirLights mDirLights;
			PointLights mPointLights;
			SpotLights mSpotLights;

			StorageBuffer mStoreBuffer;

			VKRenderer& mRenderer;
			Camera& mCamera;
			

			Scene(VKRenderer& pRenderer, Camera& pCamera) : mRenderer(pRenderer), mCamera(pCamera), mStoreBuffer(pRenderer) {}

			void init()
			{
				mStoreBuffer.init(VK_SHADER_STAGE_FRAGMENT_BIT);
			}

			T* addNode(T* pNode)
			{
				mGameObjects.push_back(pNode);
				return mGameObjects.back();
			}

			void removeNode(T& pNode)
			{
				std::vector<T*>::iterator it = std::find(mGameObjects.begin(), mGameObjects.end(), &pNode);
				if (it != mGameObjects.end())
					mGameObjects.erase(it);
			}

			void draw()
			{
				for (unsigned int i = 0; i < this->mGameObjects.size(); i++)
					mGameObjects[i]->draw();
			}

			void update(float pDeltaTime)
			{
				for (unsigned int i = 0; i < this->mGameObjects.size(); i++)
					mGameObjects[i]->update(pDeltaTime);
			}

			std::vector<T*>& getGameObjects()
			{
				return mGameObjects;
			}

			~Scene()
			{
				clear();
			}

			void clear()
			{
				for (unsigned int i = 0; i < this->mGameObjects.size(); i++)
					delete mGameObjects[i];
				mGameObjects.clear();
			}

			void addLight(DirectionalLight* pLight)
			{
				mDirLights.mData[mDirLights.mSize++] = *pLight;
			}

			void removeLight(DirectionalLight* pLight)
			{
				for (unsigned int i = 0; i < mDirLights.mSize; i++)
				{
					if (mDirLights.mData[i] == *pLight)
					{
						for (unsigned int j = i; j < mDirLights.mSize - 1; j++)
							mDirLights.mData[j] = mDirLights.mData[j + 1];

						mDirLights.mSize--;
						break;
					}
				}
			}

			void addLight(PointLight* pLight)
			{
				mPointLights.mData[mPointLights.mSize++] = *pLight;
			}

			void removeLight(PointLight* pLight)
			{
				for (unsigned int i = 0; i < mPointLights.mSize; i++)
				{
					if (mPointLights.mData[i] == *pLight)
					{
						for (unsigned int j = i; j < mPointLights.mSize - 1; j++)
							mPointLights.mData[j] = mPointLights.mData[j + 1];

						mPointLights.mSize--;
						break;
					}
				}
			}

			void addLight(SpotLight* pLight)
			{
				mSpotLights.mData[mSpotLights.mSize++] = *pLight;
			}

			void removeLight(SpotLight* pLight)
			{
				for (unsigned int i = 0; i < mSpotLights.mSize; i++)
				{
					if (mSpotLights.mData[i] == *pLight)
					{
						for (unsigned int j = i; j < mSpotLights.mSize - 1; j++)
							mSpotLights.mData[j] = mSpotLights.mData[j + 1];

						mSpotLights.mSize--;
						break;
					}
				}
			}

			void sendLight(Shader& pShader)
			{
				VkDeviceSize bufferSize1 = mRenderer.padStorageBufferSize(sizeof(DirLights));
				VkDeviceSize bufferSize2 = mRenderer.padStorageBufferSize(sizeof(PointLights));
				VkDeviceSize bufferSize3 = mRenderer.padStorageBufferSize(sizeof(SpotLights));

				pShader.bind();

				if (mDirLights.mSize != 0)
					pShader.setLight(&mStoreBuffer.DescriptorSets[mRenderer.mCurrentFrame], mStoreBuffer.mDirectionalLightStorageBuffersMapped[mRenderer.mCurrentFrame], &mDirLights, bufferSize1);

				if (mPointLights.mSize != 0)
					pShader.setLight(&mStoreBuffer.DescriptorSets[mRenderer.mCurrentFrame], ((char*)mStoreBuffer.mDirectionalLightStorageBuffersMapped[mRenderer.mCurrentFrame]) + bufferSize1, &mPointLights, bufferSize2);

				if (mSpotLights.mSize != 0)
					pShader.setLight(&mStoreBuffer.DescriptorSets[mRenderer.mCurrentFrame], ((char*)mStoreBuffer.mDirectionalLightStorageBuffersMapped[mRenderer.mCurrentFrame]) + (bufferSize1 + bufferSize2), &mSpotLights, bufferSize3);
			}
	};
}