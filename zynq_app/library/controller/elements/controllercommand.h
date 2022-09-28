#ifndef CONTROLLERCOMMAND_H
#define CONTROLLERCOMMAND_H

#include <memory>
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

#include "global/logcategories.h"

//! \brief Interface for something executable
class IControllerCommand {
public:
  virtual bool execute() = 0;
};

//! \brief Wrapper for function with variable number of parameters - to store it as an object
//! \note It implicitly also works with member functions as you can pass object as first parameter
template <typename TFunc, typename... TArgs>
class ControllerCommand : public IControllerCommand
{
private:
    TFunc function;
    std::tuple<TArgs...> args;

public:
    template <typename TFwdFunc, typename... TFwdArgs, typename = std::enable_if_t<(std::is_convertible_v<TFwdArgs&&, TArgs> && ...)>>
    explicit ControllerCommand(TFwdFunc&& func, TFwdArgs&&... args) :
        function(std::forward<TFwdFunc>(func)), args{std::forward<TFwdArgs>(args)...}
    {
    }

    bool execute() override
    {
        return std::apply(function, args);
    }
};

//! \brief Helper function to create ControllerCommand without specifying template parameters
template <typename TFunc, typename... TArgs>
auto makeCommand(TFunc&& f, TArgs&&... args)
{
    return std::make_unique<ControllerCommand<std::decay_t<TFunc>, std::remove_cv_t<std::remove_reference_t<TArgs>>...>>(std::forward<TFunc>(f), std::forward<TArgs>(args)...);
}

#endif // CONTROLLERCOMMAND_H
