#include "../src/futurewatcher.hpp"

#include <QCoreApplication>
#include <future>
#include <iostream>

size_t findFactorial(size_t n)
{
    if ((n == 0) || (n == 1))
        return 1;
    return n * findFactorial(n - 1);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    using FutureWatcher = childcity::StdFutureWatcher::FutureWatcher<size_t>;

    FutureWatcher futureWatcher;

    QObject::connect(&futureWatcher, &FutureWatcher::sigResultReady, &app, [&futureWatcher] {
        std::cout << "\nFactorial 20 = " << futureWatcher.getResult()
                  << std::endl;
    });

    auto future = std::async(std::launch::async, findFactorial, 20);
    futureWatcher.setFuture(std::move(future));

    return app.exec();
}
