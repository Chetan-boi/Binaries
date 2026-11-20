#include "getPathToBinary.hpp"
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

  std::string codemodelRel;
  {
    std::ifstream file(*indexPath);
    auto index = json::parse(file);
    codemodelRel =
        index["reply"]["codemodel-v2"]["jsonFile"].get<std::string>();
  }

  std::string buildDir;
  std::string artifactPath;
  {
    std::ifstream file(replyDir / codemodelRel);
    auto codemodel = json::parse(file);
    buildDir = codemodel["paths"]["build"].get<std::string>();

    for (const auto &entry : codemodel["configurations"][0]["targets"]) {
      std::ifstream targetFile(replyDir / entry["jsonFile"].get<std::string>());
      auto target = json::parse(targetFile);
      if (target.value("type", "") == "EXECUTABLE") {
        artifactPath = target["artifacts"][0]["path"].get<std::string>();
        break;
      }
    }
  }

  if (artifactPath.empty())
    return "";

  return (fs::path(buildDir) / artifactPath).string();
}
