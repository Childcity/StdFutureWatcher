# FutureWatcher
Simple headeronly analog of [QFutureWatcher](https://doc.qt.io/qt-5/qfuturewatcher.html) for std::future with [std::async](https://en.cppreference.com/w/cpp/thread/async)

**FutureWatcher** provides waiter thread for waiting on `std::future`. Use the `setFuture()` function to start watching a particular `std::future`. The `getFuture()` function returns the `std::shared_ptr` to future set with `setFuture()`.
After **FutureWatcher** destruction, future set with `setFuture()` will be automatic destroyed.

## How to use? 
### This is simple [example](https://github.com/Childcity/StdFutureWatcher/blob/master/example/main.cpp) of using this util class with Qt
```cpp
    // Example of using FutureWatcher
    {
        // For convenience simplify long type name
        using FutureWatcher = childcity::StdFutureWatcher::FutureWatcher<std::vector<int>>;

        // Create FutureWatcher for async task
        FutureWatcher backgroundTaskWatcher;

        // Connect sigResultReady to some slot callback, that will be executed, when future result will be available
        QObject::connect(&backgroundTaskWatcher, &FutureWatcher::sigResultReady, &myObject, &MyClass::handleResult);

        // Create and run async task (call function in background thread)
        std::future<std::vector<int>> future = std::async(std::launch::async, ...  );
        
        // Move future to backgroundTaskWatcher that immidiatly starts to wait on future in background thread
        backgroundTaskWatcher.setFuture(std::move(future));
    }
```
