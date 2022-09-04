#pragma once
#include "Collider.h"
#include "Rendering/GraphicsAPI/VertexArray.hpp"

#include <utility>

struct RenderableCollider {
	VertexArray vao;
	size_t	size;

	RenderableCollider() = default;
	RenderableCollider(RenderableCollider &&renderableCollider) noexcept;
};


class ColliderLoader {
public:
	std::pair<Collider, RenderableCollider> LoadCollider(const char *colliderPath);
};