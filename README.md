# StdFutureWatcher
Simple headeronly analog of QFutureWatcher for std::future with std::async

## How to use? 
### This is simple [example](https://github.com/Childcity/StdFutureWatcher/blob/master/example/main.cpp) of using this util class with Qt
```cpp
  #include "../src/futurewatcher.hpp"

  #include <QCoreApplication>
  #include <future>
  #include <iostream>

  using Clock = std::chrono::high_resolution_clock;
  using namespace std::chrono;

  /*
   * Function to simulate long running task
   */
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

      // Example of using FutureWatcher
      {
          // For convenience simplify long type name
          using FutureWatcher = childcity::StdFutureWatcher::FutureWatcher<std::vector<int>>;

          // Create FutureWatcher for async task
          FutureWatcher backgroundTaskWatcher;

          // Connect sigResultReady to slot QCoreApplication::quit
          QObject::connect(&backgroundTaskWatcher, &FutureWatcher::sigResultReady, &app, &QCoreApplication::quit);

          // Connect sigResultReady to some call_back, that will be executed, when future result will be available
          QObject::connect(&backgroundTaskWatcher, &FutureWatcher::sigResultReady, &app, [&backgroundTaskWatcher] {
              const auto t0 = Clock::now();
              const auto vec = backgroundTaskWatcher.getResult(); // move resullt of async task to vector
              const auto t1 = Clock::now();

              std::cout << "Time of getting result is: "
                        << duration_cast<duration<double>>(t1 - t0).count() << " s."
                        << std::endl; // This will print: "Time of getting result is: 0 s."
          });

          // Create and run async task (call function generateVec in background thread)
          std::future<std::vector<int>> future = std::async(std::launch::async, generateVec, 2000000);
          // Move future to backgroundTaskWatcher that immidiatly starts to wait on future in background thread
          backgroundTaskWatcher.setFuture(std::move(future));
      }

      return app.exec();
  }
```
