#pragma once

#include"common.hpp"

template<class Derived>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    auto operator=(const Singleton&)->Singleton & = delete;
    auto operator=(Singleton&&)->Singleton & = delete;
    template<class... Args>
    static Derived& Initialize(Args&&... args) {
        std::call_once(initFlag_, [&] {
            object_.reset(new Derived(ConstructorToken{}, std::forward<Args>(args)...));
            published_.store(object_.get(), std::memory_order_release);
            });
        return *published_.load(std::memory_order_acquire);
    }
    static Derived& Instance() {
        Derived* object = published_.load(std::memory_order_acquire);
        if (object == nullptr) {
            throw std::logic_error("Singleton has not been initialized");
        }
        return *object;
    }
    static bool Initialized() noexcept {
        return published_.load(std::memory_order_acquire) != nullptr;
    }
    virtual ~Singleton() = 0;
protected:
    class ConstructorToken {
    public:
        ConstructorToken(const ConstructorToken&) = default;
    private:
        ConstructorToken() = default;
        friend class Singleton<Derived>;
    };
    explicit Singleton(ConstructorToken) noexcept {}
private:
    static void Destroy(Derived* object) noexcept {
        delete object;
    }
    using Pointer = std::unique_ptr<Derived,void (*)(Derived*)>;
    inline static Pointer object_{ nullptr,&Singleton::Destroy };
    inline static std::once_flag initFlag_;
    inline static std::atomic<Derived*> published_{nullptr};
};
template<class Derived>
Singleton<Derived>::~Singleton() = default;