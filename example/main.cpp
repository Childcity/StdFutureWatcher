#include "../src/futurewatcher.hpp"

#include <QCoreApplication>
#include <future>
#include <iostream>

using Clock = std::chrono::high_resolution_clock;
using namespace std::chrono;

std::vector<int> generateVec(size_t n)
{
    std::vector<int> v(n);
    std::random_shuffle(v.begin(), v.end());
    std::sort(v.begin(), v.end(), std::greater<int>());
    return v;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    using FutureWatcher = childcity::StdFutureWatcher::FutureWatcher<std::vector<int>>;

    FutureWatcher generatedVector;

    QObject::connect(&generatedVector, &FutureWatcher::sigResultReady, &app, &QCoreApplication::quit);
    QObject::connect(&generatedVector, &FutureWatcher::sigResultReady, &app, [&generatedVector] {
        const auto t0 = Clock::now();
        const auto vec = generatedVector.getResult();
        const auto t1 = Clock::now();
        std::cout << "Time of getting result is: "
                  << duration_cast<duration<double>>(t1 - t0).count() << " s."
                  << std::endl;
    });

    std::future<std::vector<int>> future = std::async(std::launch::async, generateVec, 2000000);
    generatedVector.setFuture(std::move(future));

    return app.exec();
}
