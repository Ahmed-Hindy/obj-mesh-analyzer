#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

#include <fmt/core.h>
#include <glm/vec3.hpp>
#include <tiny_obj_loader.h>

namespace {

struct MeshData {
    std::vector<glm::vec3> vertices;
    std::size_t shape_count{};
    std::size_t triangle_count{};
};

struct BoundingBox {
    glm::vec3 min{};
    glm::vec3 max{};
};

void print_vec3(const char* label, const glm::vec3& value) {
    fmt::println("{}: ({:.3f}, {:.3f}, {:.3f})", label, value.x, value.y, value.z);
}

MeshData load_obj_mesh(const std::filesystem::path& file_path) {
    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning;
    std::string error;

    const std::string input_file = file_path.string();
    const bool loaded = tinyobj::LoadObj(
        &attributes,
        &shapes,
        &materials,
        &warning,
        &error,
        input_file.c_str(),
        nullptr,
        true
    );

    if (!loaded) {
        throw std::runtime_error("Could not load OBJ file: " + input_file + "\n" + error);
    }

    MeshData mesh;
    mesh.shape_count = shapes.size();

    for (std::size_t i = 0; i + 2 < attributes.vertices.size(); i += 3) {
        mesh.vertices.emplace_back(
            attributes.vertices[i],
            attributes.vertices[i + 1],
            attributes.vertices[i + 2]
        );
    }

    for (const tinyobj::shape_t& shape : shapes) {
        mesh.triangle_count += shape.mesh.num_face_vertices.size();
    }

    return mesh;
}

BoundingBox calculate_bounding_box(const std::vector<glm::vec3>& points) {
    if (points.empty()) {
        throw std::runtime_error("Cannot calculate a bounding box with no vertices.");
    }

    BoundingBox box;
    box.min = points[0];
    box.max = points[0];

    for (const glm::vec3& point : points) {
        box.min.x = std::min(box.min.x, point.x);
        box.min.y = std::min(box.min.y, point.y);
        box.min.z = std::min(box.min.z, point.z);

        box.max.x = std::max(box.max.x, point.x);
        box.max.y = std::max(box.max.y, point.y);
        box.max.z = std::max(box.max.z, point.z);
    }

    return box;
}

}  // namespace

int main() {
    try {
        const std::filesystem::path file_path{"assets/cube.obj"};
        const MeshData mesh = load_obj_mesh(file_path);
        const BoundingBox bounds = calculate_bounding_box(mesh.vertices);
        const glm::vec3 center = (bounds.min + bounds.max) * 0.5f;
        const glm::vec3 size = bounds.max - bounds.min;

        fmt::println("Mesh analysis for {}", file_path.string());
        fmt::println("Shapes: {}", mesh.shape_count);
        fmt::println("Vertices: {}", mesh.vertices.size());
        fmt::println("Triangles: {}", mesh.triangle_count);
        print_vec3("Bounds min", bounds.min);
        print_vec3("Bounds max", bounds.max);
        print_vec3("Bounds center", center);
        print_vec3("Bounds size", size);
    } catch (const std::exception& error) {
        fmt::println(stderr, "Error: {}", error.what());
        return 1;
    }

    return 0;
}
