#pragma once
#include"NeuralNetwork.h"
#include <filesystem>

class NeuralNetworkImport
{
public:
	static NeuralNetwork fromJSON(const std::filesystem::path& filePath);
};

