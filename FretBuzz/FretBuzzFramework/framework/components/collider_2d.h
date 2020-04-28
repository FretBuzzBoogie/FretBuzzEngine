#pragma once
#include <system/component_2d.h>
#include <components/collider_data.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Collider2D : public IComponent2D, protected b2ContactListener
		{
		public:
			using FUNC_CONTACT_EVENT = void(IComponent::*)(Collider2D*);

			void applyForceToCenter(glm::vec2 a_v2ForceDirection);
			void applyForceAtPoint(glm::vec2 a_v2ForceDirection, glm::vec2 a_v2Point);
			void applyImpulseToCenter(glm::vec2 a_v2ForceDirection);
			void applyImpulseAtPoint(glm::vec2 a_v2ForceDirection, glm::vec2 a_v2Point);
			

#pragma region GETTERS AND SETTERS
			glm::vec2 getWorldCenterOfCollider();

			void setPhysicsBodyType(PHYSICS_BODY_TYPE a_PhysicsBodyType);
			PHYSICS_BODY_TYPE getPhysicsBodyType();

			void setLinearVelocity(glm::vec2 a_v2VelocityDirection);
			glm::vec2 getLinearVelocity();

			void setAngularVelocity(float a_fAngularVelocity);
			float getAngularVelocity();

			void setSensor(bool a_bIsSensor);
			bool isSensor() const;

			void setFixedRotation(bool a_bIsFixedRotation);
			bool getIsFixedRotation();

			void setDensity(float a_fDensity);
			float getDensity();

			void setLinearDamping(float a_fLinearDamping);
			float getLinearDamping();

			void setAngularDamping(float a_fAngularDamping);
			float getAngularDamping();

			void setMaskBits(std::unordered_set<uint16> a_usetMaskBits);
			const std::unordered_set<uint16> getMaskBits() const;
			void removeMaskBit(uint16 a_BitToRemove);
			void addMaskBit(uint16 a_BitToAdd);

			void setCategoryBits(std::unordered_set<uint16> a_usetCategoryBits);
			const std::unordered_set<uint16> getCategoryBits() const;
			void removeCategoryBit(uint16 a_BitToRemove);
			void addCategoryBit(uint16 a_BitToAdd);

			uint16 GetBitField(std::unordered_set<uint16>& a_vectBits) const;

			static void ManageContacts(Collider2D* a_pColliderA, Collider2D* a_pColliderB, FUNC_CONTACT_EVENT a_pFuncCollision, FUNC_CONTACT_EVENT a_pFuncTrigger);

#pragma endregion GETTERS AND SETTERS

		protected:
			Collider2D(GameObject2D* a_GameObject2D, ColliderData& a_ColliderData);
			~Collider2D();

			void setupCollisionData();

			ColliderData m_ColliderData;
			b2Body* m_pBody = nullptr;
			b2Fixture* m_pFixture = nullptr;

			virtual void onEnable() override;
			virtual void onDisable() override;
			//void Update(float a_fDeltaTime); 
			void lateUpdate(float a_fDeltaTime) override;

			void onSiblingComponentAdded(IComponent* a_pComponent);
			void onSiblingComponentRemoved(IComponent* a_pComponent);

			void BeginContact(b2Contact* a_pContact) override;
			void EndContact(b2Contact* a_pContact) override;

			void callContactInSiblingComponents(FUNC_CONTACT_EVENT a_pFuncContact, Collider2D* a_pOtherCollider);
			void updateFilterData();
		};
	}
}