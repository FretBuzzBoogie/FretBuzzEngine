#pragma once

#include "components/transform.h"
#include "components/gameobject_components/camera.h"
#include <fretbuzz.h>

namespace FRETBUZZ
{
	class  GameObject
	{
		friend class IScene;
		friend class IComponent;
			
	protected:

		std::vector<IComponent*> m_Components;
		std::vector<GameObject*> m_Children;
		bool m_bIsRoot = false;

		GameObject* m_pParentGameObject = nullptr;

		const std::string m_strName;

		// The int ID of the current gameobject
		const int m_iID;

		const std::string m_strID;

		// The total number of gameobjects, provides a unique ID for nw gameobjects.
		static int s_iID;

		bool m_bIsDontDestroy = false;

		bool m_bIsActiveSelf = true;
		bool m_bIsActiveInHierarchy = true;

		void setActiveInHierarchyRecursively(bool a_bIsActive);

		void updateComponents(const float& a_fDeltaTime);
		void updateChildren(const float& a_fDeltaTime);

		void lateUpdateComponents(const float& a_fDeltaTime);
		void lateUpdateChildren(const float& a_fDeltaTime);

		void physicsUpdateComponents(const float& a_fDeltaTime);
		void physicsUpdateChildren(const float& a_fDeltaTime);

		void renderComponents(const glm::mat4& a_mat4Transformation, const Camera& a_Camera);
		void renderChildren(const Camera& a_Camera);

		// Renders all the inspector hierarchy data.
		virtual void editorHierarchyRender(GameObject*& a_pSelectedGameObject);
			
		void addComponent(IComponent* a_IComponent);
		void resetDontDestroyParent(GameObject& a_NewParent);
		glm::mat4 m_mat4Transformation{1.0f};

		void onComponentCreated(IComponent* a_IComponent);

		GameObject(std::string a_strName, bool a_bIsRoot = true);
		GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);
		GameObject(GameObject& a_ParentGameObject, std::string a_strName, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);

		// GameObject 2D constructor
		GameObject(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Transform* a_pTransform, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);

		Transform* m_pTransform;
		virtual ~GameObject();

	public:
		Layer m_Layer;

		// Creates a GameObject, adds this GameObject to the m_Children of its a_ParentGameObject.
		// Sets its active state in hierarchy to the a_bIsActiveSelf, depends on its ParentGameObject.
		static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);
		static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);

		Transform& m_Transform;

		// Adds the GameObject a_pChildGameObject into this GameObject's m_Children.
		void addChild(GameObject* a_pChildGameObject);

		// Renders all the components and renders its child GameObjects.
		virtual void render(const Camera& a_Camera);

		// Updates all the components and renders its child GameObjects.
		virtual void update(const float& a_fDeltaTime);

		// called after update on all the gameobjects are done
		virtual void lateUpdate(const float& a_fDeltaTime);

		virtual void physicsUpdate(const float& a_fDeltaTime);

		// Does the component of type a_ComponentType exist in the m_Components list.
		bool isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const;

		// Removes this GameObject from the current parent's m_Children list.
		// Sets this GameObject as the child of the a_pParentGameObject.
		void setAsParent(GameObject* a_pParentGameObject);

		// Is the GameObject active locally, even though its not active in the scene.
		bool getIsActiveSelf() const;

		// Is the GameObject active in the scene.
		bool getIsActiveInHierarchy() const;

		// Sets the GameObject active self state,
		// If a_bIsActive = true, sets the active state to true in hierarchy if the parent is also active
		// Sets its child active in hierarchy state to true if previously false.
		// If a_bIsActive = false, sets the active state to false in hierarchy if the parent is true/false
		// Sets its child active in hierarchy state to false if previously true.
		void setActive(bool a_bIsActive);

		// Gets the name of the GameObject.
		std::string getName() const;

		// GameObject won't be destroyed on Scene change.
		GameObject* setAsDontDestroy(bool a_bIsDontDestroy = true);

		// Is the gameobject a DontDestroy type of Object.
		bool isDontDestroy() const;

		// Logs GameObject hierarchy.
		void logHierarchy(int l_iNumOfTabs);

		// Removes the GameObject from its parent m_Children container.
		// Destroys the GameObject
		static void destroy(GameObject*& a_GameObject);

#pragma region Editor
		virtual void editorInspectorRender();
		virtual void editorTransformRender();
#pragma endregion Editor
			
		// Returns all component of the game object
		inline const std::vector<IComponent*> getAllComponents()
		{
			return m_Components;
		}

		// Returns a component from the components vector, if the COMPONENT_TYPE is equal to the input.
		// If the component pointer is found it returns the component cast to the type specified else returns null.
		template<typename T_COMPONENT_TYPE, typename = typename std::enable_if<std::is_base_of<IComponent, T_COMPONENT_TYPE>::value>::type>
		T_COMPONENT_TYPE* getComponent(COMPONENT_TYPE a_COMPONENT_TYPE)
		{
			size_t l_iComponentCount = m_Components.size();
			for(size_t l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
			{
				if (m_Components[l_iComponentIndex]->m_ComponentType == a_COMPONENT_TYPE)
				{
					return dynamic_cast<T_COMPONENT_TYPE*>(m_Components[l_iComponentIndex]);
				}
			}
			return nullptr;
		}

		//Adds a component of the given type to this gameobject
		template<typename T_COMPONENT_TYPE, typename ...T_ARGS, typename = typename std::enable_if<std::is_base_of<IComponent, T_COMPONENT_TYPE>::value>::type>
		T_COMPONENT_TYPE* addComponent(T_ARGS... a_Args)
		{
			T_COMPONENT_TYPE* l_pNewComponent = new T_COMPONENT_TYPE(this, a_Args...);
			IComponent* l_pIComponent = static_cast<T_COMPONENT_TYPE*>(l_pNewComponent);
			addComponent(l_pIComponent);
			onComponentCreated(l_pIComponent);

			return l_pNewComponent;
		}
	};
}