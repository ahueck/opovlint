/*
 * AstMatcherModule.hpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef ASTMATCHERMODULE_HPP_
#define ASTMATCHERMODULE_HPP_

namespace opov {

template<typename T>
void ASTMatcherModule::addMatcher(const T& matcher) {
	finder.addMatcher(matcher, this);
}

} // namespace opov

#endif /* ASTMATCHERMODULE_HPP_ */
