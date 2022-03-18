#pragma once
#include<vector>
#include<string>
#include"image.h"

struct Image;
using Matrix = std::vector<std::vector<float>>;

class NeuralNetwork
{
public:
	NeuralNetwork(std::vector<Matrix>&& weights,
		std::vector<std::vector<float>>&& biases);
	const std::vector<Matrix>& GetWeights()const noexcept;
	const std::vector<std::vector<float>>& GetBiases()const noexcept;
	uint8_t Predict(const Image& image)const;

private:
	//int m_layers;
	std::vector<int> m_layerSizes;
	std::string m_activation;
	std::string m_outActivation;
	std::vector<Matrix> m_weights;
	std::vector<std::vector<float>> m_biases;
	std::vector<float> feedForward(const std::vector<uint8_t>& x) const;

 
};