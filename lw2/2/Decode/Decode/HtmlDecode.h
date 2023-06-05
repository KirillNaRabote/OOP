#pragma once

#include <string>
#include <map>

std::string HtmlDecode(const std::string& html, const std::map <std::string, std::string>& wordsToDecode);
void FillWordsToDecode(std::map <std::string, std::string>& wordsToDecode);