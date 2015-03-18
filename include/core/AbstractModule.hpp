/*
 * AbstractModule.hpp
 *
 *  Created on: Jun 9, 2014
 *      Author: ahueck
 */

#ifndef ABSTRACTMODULE_HPP_
#define ABSTRACTMODULE_HPP_

#include <core/ModuleContext.h>
#include <core/Configuration.h>
#include <core/Issue.h>
#include <core/ClangUtil.h>

namespace opov {


template<typename NODE>
void AbstractModule::addIssue(NODE node, std::string description) {
	auto& ctx_issues = context->getIssues();
	clang::SourceManager& sm = context->getSourceManager();
	Issue* issue = new opov::Issue();
	auto pos = clutil::posOf(sm, node);
	std::string source = clutil::node2str(sm, node);
	issue->setDescription(description);
	issue->setCode(source);
	issue->setLineStart(std::get<0>(pos));
	issue->setLineEnd(std::get<1>(pos));
	issue->setColumnStart(std::get<2>(pos));
	issue->setColumnEnd(std::get<3>(pos));
	issue->setFile(clutil::fileOf(sm, node));
	ctx_issues.push_back(issue);
}
} // namespace opov

#endif /* ABSTRACTMODULE_HPP_ */
