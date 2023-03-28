#include <torch/torch.h>
#include <opencv2/opencv.hpp>
class Lenet5 : public torch::nn::Module{
private:
    // 卷积特征运算
    torch::nn::Conv2d  conv1;
    torch::nn::Conv2d  conv2;
    torch::nn::Conv2d  conv3;
    torch::nn::Linear  fc1;
    torch::nn::Linear  fc2;
public:
    Lenet5():
    conv1(torch::nn::Conv2dOptions(1, 6, 5).stride(1).padding(2)),  
    conv2(torch::nn::Conv2dOptions(6, 16, 5).stride(1).padding(0)),  
    conv3(torch::nn::Conv2dOptions(16, 120, 5).stride(1).padding(0)),
    fc1(120, 84),  
    fc2(84, 10){  // 84 -> 10 (分量最大的小标就是识别的数字)
        // 注册需要学习的矩阵（Kernel Matrix）
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv3", conv3);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
    }
    torch::Tensor forward(torch::Tensor x){ 
        // 1. conv
        x = conv1->forward(x);   
        x = torch::max_pool2d(x, 2);   
        x = torch::relu(x); // 激活函数 
        // 2. conv
        x = conv2->forward(x);  
        x = torch::max_pool2d(x, 2); 
        x = torch::relu(x); // 激活函数
        // 3. conv
        x = conv3->forward(x);   
        x = torch::relu(x); // 激活函数 
        // 做数据格式转换
        x = x.view({-1, 120});   
        // 4. fc
        x = fc1->forward(x);
        x = torch::relu(x);
        // 5. fc 
        x = fc2->forward(x);
        return  torch::log_softmax(x, 1);   
    }
};
template <typename  DataLoader> 
void train(std::shared_ptr<Lenet5> &model,  DataLoader &loader,  torch::optim::Adam &optimizer){
    model->train();
    // 迭代数据
    int n = 0;
    for(torch::data::Example<torch::Tensor, torch::Tensor> &batch: loader){
        torch::Tensor data   = batch.data;
        auto target          = batch.target;
        optimizer.zero_grad(); // 清空上一次的梯度
        // 计算预测值
        torch::Tensor y = model->forward(data);
        // 计算误差
        torch::Tensor loss = torch::nll_loss(y, target);
        // 计算梯度: 前馈求导
        loss.backward();
        // 根据梯度更新参数矩阵
        optimizer.step();
    }
    // 输出误差
}
template <typename DataLoader>
void  valid(std::shared_ptr<Lenet5> &model, DataLoader &loader){
    model->eval();
    // 禁止求导的图跟踪
    torch::NoGradGuard  no_grad;
    // 循环测试集
    double sum_loss = 0.0;
    int32_t num_correct = 0;
    int32_t num_samples = 0;
    for(const torch::data::Example<> &batch: loader){
        // 每个批次预测值
        auto data = batch.data;
        auto target = batch.target;
        num_samples += data.sizes()[0];
        auto y = model->forward(data);
        // 计算纯预测的结果
        auto pred = y.argmax(1);
        // 计算损失值
        sum_loss += torch::nll_loss(y, target, {}, at::Reduction::Sum).item<double>();
        // 比较预测结果与真实的标签值
        num_correct += pred.eq(target).sum().item<int32_t>();
    }
    // 输出正确值
    std::cout << std::setw(8) << std::setprecision(4) 
        << "平均损失值：" << sum_loss / num_samples 
        << ",\t准确率：" << 100.0 * num_correct / num_samples << " %" << std::endl;
}

int main(int argc, const char** argv){
    // 数据集
    auto  cm_train = torch::data::datasets::MNIST(".\\data", torch::data::datasets::MNIST::Mode::kTrain);
    auto  cm_valid = torch::data::datasets::MNIST(".\\data", torch::data::datasets::MNIST::Mode::kTest);
    torch::data::transforms::Stack<> stack;
    // 数据批次加载器
    auto m_train = cm_train.map(stack);
    auto train_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(m_train), 1000); 
    auto m_valid = cm_valid.map(stack);
    auto valid_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(std::move(m_valid), 1000); 
    // 1. 创建模型对象
    std::shared_ptr<Lenet5> model = std::make_shared<Lenet5>();
    // 优化器（管理模型中可训练矩阵）
    torch::optim::Adam  optimizer = torch::optim::Adam(model->parameters(), torch::optim::AdamOptions(0.001)); 
    std::cout<< "开始训练" << std::endl;
    int epoch = 30;
    int interval = 1;   // 从测试间隔
    for(int e = 0; e < epoch; e++){
        std::printf("第%02d轮训练\n", e+1);
        train(model, *train_loader, optimizer);
        if (e  % interval == 0){
            valid(model, *valid_loader);
        }
    }
    std:: cout << "训练结束" << std::endl;
    torch::save(model, "model.pt");
    return 0;
}
