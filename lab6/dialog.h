#pragma once
#include <coroutine>
#include <exception>
#include <memory>

class Dialog
{
public:
    struct promise_type;
    using handle = std::coroutine_handle<promise_type>;
    int ask(int question)
    {
        *coro.promise().question = question;
        coro.resume();
        return coro.promise().answer;
    }

    struct promise_type
    {
        int answer = 0;
        std::shared_ptr<int> question;
        promise_type(std::shared_ptr<int> question) : question(question) {}
        void unhandled_exception() { std::terminate(); }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto yield_value(int value)
        {
            answer = value;
            return std::suspend_always{};
        }
        auto get_return_object()
        {
            return Dialog{handle::from_promise(*this)};
        }
        void return_void(){}
    };

    Dialog(Dialog const &) = delete;
    Dialog(Dialog &&other) : coro(other.coro) { other.coro = nullptr; }
    ~Dialog()
    {
        if (coro)
            coro.destroy();
    }

private:
    Dialog(handle h) : coro(h) {}
    handle coro;
};
