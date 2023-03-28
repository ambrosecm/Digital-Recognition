#ifndef C_LENET_H
#define C_LENET_H
#include <torch/torch.h>
class Lenet5 : public torch::nn::Module{
private:
    torch::nn::Conv2d  conv1;
    torch::nn::Conv2d  conv2;
    torch::nn::Conv2d  conv3;
    torch::nn::Linear  fc1;
    torch::nn::Linear  fc2;
public:
    Lenet5();
    torch::Tensor forward(torch::Tensor x);
};
#endif
