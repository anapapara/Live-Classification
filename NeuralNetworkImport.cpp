#include "NeuralNetworkImport.h"
#include"json.hpp"
#include<fstream>

NeuralNetwork NeuralNetworkImport::fromJSON(const std::filesystem::path& filePath)
{
	using nlohmann::json;
	json neuralNetworkJson;
	std::ifstream stream(filePath.string());
	if (!stream) {
		throw "Invalid Json!";
	}
	stream >> neuralNetworkJson;
	auto layer = neuralNetworkJson["n_layers"];
	auto layerSizes = neuralNetworkJson["layer_sizes"];
	auto activation = neuralNetworkJson["activation"];
	auto outactivation = neuralNetworkJson["out_activation"];
	auto weights = neuralNetworkJson["weights"];
	auto biases = neuralNetworkJson["biases"];
	return NeuralNetwork(weights, biases);
}
