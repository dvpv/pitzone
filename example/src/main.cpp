#include <iostream>
#include <memory>
#include <pizone/pizone.hpp>
#include <random>
#include <vector>

class ProviderOfNumbers : public pizone::Provider<int>
{
  public:
    void generateNumber()
    {
        int number = std::rand();
        notifyConsumers(number);
    }
};

class PrintNumberConsumer : public pizone::Consumer<int>
{
  public:
    PrintNumberConsumer(const std::string& name)
      : name(name)
    {
    }
    void consume(const int& number) override
    {
        std::cout << "[" << name << "] The number is: " << number << std::endl;
    }

  private:
    std::string name;
};

int
main()
{
    std::srand(1234);
    PrintNumberConsumer consumer1("consumer1");
    PrintNumberConsumer consumer2("consumer2");

    ProviderOfNumbers provider;
    provider.addConsumer(consumer1);
    provider.addConsumer(consumer2);

    for (int i = 0; i < 10; ++i)
    {
        provider.generateNumber();
    }
    return 0;
}
