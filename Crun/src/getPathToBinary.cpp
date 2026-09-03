#include "getPathToBinary.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using json = nlohmann::json;
static const std::filesystem::path replyDir = "build/.cmake/api/v1/reply";

static std::optional<std::filesystem::path> findFileWithPrefix(const std::string& prefix) {
    if (!std::filesystem::exists(replyDir)) {
        return std::nullopt;
    }
    for (const auto& entry : std::filesystem::directory_iterator(replyDir)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.starts_with(prefix)) {
                return entry.path();
            }
        }
    }
    return std::nullopt;
}

std::string getPathToBinary() {
    try {
        auto indexPath = findFileWithPrefix("index-");
        if (!indexPath.has_value()) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Could not find CMake index reply file in '"
                      << replyDir.string() << "/'.\n"
                      << "\033[1;33m[Hint]\033[0m Ensure CMake has configured the project with File API enabled.\n";
            return "";
        }

        std::ifstream indexRaw(*indexPath);
        if (!indexRaw.is_open()) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Failed to open index file: '"
                      << indexPath->string() << "'.\n";
            return "";
        }

        json indexParsed = json::parse(indexRaw);
        if (!indexParsed.contains("reply") || !indexParsed["reply"].contains("codemodel-v2") ||
            !indexParsed["reply"]["codemodel-v2"].contains("jsonFile")) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m CMake index file does not contain a valid 'codemodel-v2' reply reference.\n";
            return "";
        }

        std::string codemodelFilename = indexParsed["reply"]["codemodel-v2"]["jsonFile"].get<std::string>();
        std::filesystem::path codemodelPath = replyDir / codemodelFilename;

        std::ifstream codemodelRaw(codemodelPath);
        if (!codemodelRaw.is_open()) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Failed to open codemodel file: '"
                      << codemodelPath.string() << "'.\n";
            return "";
        }

        json codemodelParsed = json::parse(codemodelRaw);
        if (!codemodelParsed.contains("paths") || !codemodelParsed["paths"].contains("build")) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Codemodel response missing build directory path.\n";
            return "";
        }

        std::filesystem::path buildPath = codemodelParsed["paths"]["build"].get<std::string>();

        if (!codemodelParsed.contains("configurations") || codemodelParsed["configurations"].empty() ||
            !codemodelParsed["configurations"][0].contains("targets")) {
            std::cerr << "\033[1;31m[Crun Error]\033[0m Codemodel contains no target configurations.\n";
            return "";
        }

        for (const auto& targetRef : codemodelParsed["configurations"][0]["targets"]) {
            if (!targetRef.contains("jsonFile")) continue;

            std::string targetJsonFilename = targetRef["jsonFile"].get<std::string>();
            std::filesystem::path targetJsonPath = replyDir / targetJsonFilename;

            std::ifstream targetRaw(targetJsonPath);
            if (!targetRaw.is_open()) continue;

            json targetParsed = json::parse(targetRaw);
            if (targetParsed.contains("type") && targetParsed["type"] == "EXECUTABLE") {
                if (targetParsed.contains("artifacts") && !targetParsed["artifacts"].empty() &&
                    targetParsed["artifacts"][0].contains("path")) {
                    std::string artifactRelPath = targetParsed["artifacts"][0]["path"].get<std::string>();
                    std::filesystem::path fullBinaryPath = buildPath / artifactRelPath;
                    return fullBinaryPath.string();
                }
            }
        }

        std::cerr << "\033[1;31m[Crun Error]\033[0m No executable target found in the CMake project.\n"
                  << "\033[1;33m[Hint]\033[0m Ensure your CMakeLists.txt defines an executable target with add_executable(...).\n";
        return "";
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31m[Crun Error]\033[0m Exception while resolving binary path: "
                  << e.what() << "\n";
        return "";
    }
}
