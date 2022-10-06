#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "CharacterComponent.h"


namespace anthemum
{
	class PlayerComponent : public CharacterComponent
	{
	public:
	PlayerComponent() = default;

	void Initialize() override;
	void Update() override;

	CLASS_DECLARATION(PlayerComponent)

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

	virtual void OnCollisionEnter(Actor* other) override;
	virtual void OnCollisionExit(Actor* other) override;
	public:
	float jump = 0 ;
	int m_groundCount = 0;
	
	virtual void OnNotify(const Event& event) override;
	};
}