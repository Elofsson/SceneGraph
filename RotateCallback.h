#include "UpdateCallback.h"
#include "Transform.h"

#pragma once


class RotateCallback : public UpdateCallback
{
public:
	RotateCallback(std::shared_ptr<Transform> transform);
	virtual void update() override;

private:
	std::shared_ptr<Transform> m_transform;
};