#include "getPathToBinary.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <optional>


namespace fs = std::filesystem;
using json = nlohmann::json;

static const fs::path replyDir = "build/.cmake/api/v1/reply";

std::optional<fs::path> findFile(const std::string &prefix) {
  if (!fs::exists(replyDir) || !fs::is_directory(replyDir)) {
    return std::nullopt;
  }
  for (const auto &entry : fs::directory_iterator(replyDir)) {
    if (entry.is_regular_file() &&
        entry.path().filename().string().starts_with(prefix)) {
      return entry.path();
    }
  }
  return std::nullopt;
}

std::string getPathToBinary() {
  auto indexPath = findFile("index-");
  if (!indexPath)
    return "";

  // 1. Extract the codemodel filename from index
  std::string codemodelRel;
  {
    std::ifstream file(*indexPath);
    auto index = json::parse(file);
    codemodelRel =
        index["reply"]["codemodel-v2"]["jsonFile"].get<std::string>();
  }

  // 2. Extract build directory and the target JSON filename from codemodel
  std::string buildDir;
  std::string targetRel;
  {
    std::ifstream file(replyDir / codemodelRel);
    auto codemodel = json::parse(file);
    buildDir = codemodel["paths"]["build"].get<std::string>();

    for (const auto &target : codemodel["configurations"][0]["targets"]) {
      // Find the first target that produces an executable
      if (target.value("type", "") == "EXECUTABLE" || target.contains("jsonFile")) {
        targetRel = target["jsonFile"].get<std::string>();
        break;
      }
    }
  }

  if (targetRel.empty())
    return "";

  // 3. Extract the artifact path from the target JSON
  std::string artifactPath;
  {
    std::ifstream file(replyDir / targetRel);
    auto target = json::parse(file);
    artifactPath = target["artifacts"][0]["path"].get<std::string>();
  }

  // Combine build path with target artifact path
  return (fs::path(buildDir) / artifactPath).string();
}
