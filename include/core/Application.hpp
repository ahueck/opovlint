/*
 * Application.hpp
 *
 *  Created on: Apr 27, 2016
 *      Author: ahueck
 */

#ifndef INCLUDE_APPLICATION_HPP_
#define INCLUDE_APPLICATION_HPP_

#include <core/module/Module.h>
#include <core/utility/Util.h>

#include <type_traits>

namespace opov {

template <typename T, typename... Args>
void Application::addModule(Args&&... arguments) {
  static_assert(std::is_base_of<Module, T>::value,
                "Application::addModule<T>(...) requires T to be a sub class of opov::Module.");
  std::unique_ptr<Module> module = util::make_unique<T>(std::forward<Args>(arguments)...);
  module->init(config.get());
  modules.push_back(std::move(module));
}

} /* namespace opov */

#endif /* INCLUDE_APPLICATION_HPP_ */
