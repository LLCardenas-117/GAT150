#include "Mesh.h"
#include "Renderer.h"

namespace errera {
	/// <summary>
	/// 
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	bool Mesh::Load(const std::string& filename) {
		std::string buffer;
		if (!file::ReadTextFile(filename, buffer)) {
			Logger::Error("Could not read file!");
		}

		std::stringstream stream(buffer);

		// Read color
		stream >> _color;

		// Read points
		vec2 point;
		while (stream >> point) {
			_points.push_back(point);
		}

		return true;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void Mesh::Draw(Renderer& renderer, const vec2& position, float rotation, float scale){
		// Checks if points are empty, if so then return
		if (_points.empty()) return;

		renderer.SetColor(_color.r, _color.g, _color.b);

		// Iterate through all points, draw line
		for (int i = 0; i < (_points.size() - 1); i++) {
			vec2 p1 = (_points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (_points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	/// <param name="transform"></param>
	void Mesh::Draw(Renderer& renderer, const Transform& transform) {
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// 
	/// </summary>
	void Mesh::CalculateRadius() {
		_radius = 0;
		for (auto& point : _points) {
			float length = point.Length();
			if (length > _radius) _radius = length;
		}
	}
}

