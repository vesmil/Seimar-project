#ifndef CONTROLLERCOMMAND_H
#define CONTROLLERCOMMAND_H

#include <iostream>
#include <memory>
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

class IControllerCommand {
public:
  virtual bool execute() = 0;
};

template <typename TFunc, typename... TArgs>
class ControllerCommand : public IControllerCommand
{
    static_assert(!(std::is_rvalue_reference_v<TArgs> && ...));

private:
    TFunc f;
    std::tuple<TArgs...> args;

public:
    template <typename TFwdFunc, typename... TFwdArgs, typename = std::enable_if_t<(std::is_convertible_v<TFwdArgs&&, TArgs> && ...)>>
    ControllerCommand(TFwdFunc&& func, TFwdArgs&&... args) :
        f(std::forward<TFwdFunc>(func)), args{std::forward<TFwdArgs>(args)...}
    {
    }

    bool execute() override
    {
        std::apply(f, args);
    }
};

template <typename TFunc, typename... TArgs>
auto makeCommand(TFunc&& f, TArgs&&... args)
{
    return std::make_unique<ControllerCommand<std::decay_t<TFunc>, std::remove_cv_t<std::remove_reference_t<TArgs>>...>>(std::forward<TFunc>(f), std::forward<TArgs>(args)...);
}

#endif // CONTROLLERCOMMAND_H
