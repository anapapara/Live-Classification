#include "image.h"
#include "lodepng.h"
#include <filesystem>
#include"NeuralNetworkImport.h"

Image ReadPngAndLabel(const std::filesystem::path& filePath) {
    Image image;
    image.label = filePath.filename().string()[0] - '0';
    auto error = lodepng::decode(image.pixels, image.columns,image.rows,filePath.string(),LodePNGColorType::LCT_GREY);

    if (error != 0) {
        throw "Invalid!";
    }
    return std::move(image);
}


std::vector<Image> ReadAllPngs(const std::filesystem::path& folderPath) {

    std::vector<Image> images;
    for (auto it : std::filesystem::directory_iterator(folderPath))
    {
        if (it.is_regular_file()) {
            images.emplace_back(ReadPngAndLabel(it));
        }
    } 
    return images;
}


//int main()
//{
//    //Image image;
//    //image = ReadPngAndLabel(R"(C:\Users\anama\OneDrive\Desktop\SiemensSS\ConsoleApplication1\DataSet\archive\images\0_0.png)");
//    /*for (auto value : image.pixels)
//    {
//        std::cout << static_cast<int>(value);
//    }*/
//
//
//    /*std::vector<Image> images = ReadAllPngs(R"(C:\Users\anama\OneDrive\Desktop\SiemensSS\ConsoleApplication1\DataSet\archive\images)");
//    std::cout << images.size();*/
//
//    auto neuralNetwork = NeuralNetworkImport::fromJSON(R"(C:\Users\anama\OneDrive\Desktop\SiemensSS\ConsoleApplication1\DataSet\archive\learning_models\neural_net.json)");
//    std::cout << neuralNetwork.GetBiases().size();
//    return 0;
//}

