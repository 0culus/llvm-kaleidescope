//
// Created by Sean Turner on 12/10/15.
//

#pragma once

#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// LLVM uses their own make_unique in the tutorial. We'll reproduce it here,
// but may not use it! The helper namespace might be useful anyway
namespace helper {
	template <class T, class... Args>
	static
		typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
		make_unique(Args &&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
};
}

/**
 * Here we define all the tokens we need; add to this to add more!
 */
enum class Token {
	tok_eof = -1,

	tok_def = -2,
	tok_extern = -3,

	tok_identifier = -4,
	tok_double = -5
};

static std::string IdentifierStr; // filled if tok_identifier
static double DoubleVal; // filled if tok_double

