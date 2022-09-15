/*
 * Config.cpp
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#include "Config.h"

Config::Config() {
	// TODO Auto-generated constructor stub

}

std::string Config::get(std::string key) const {
	return items_.at(key);
}

void Config::set(std::string key, std::string value) {
	items_[key] = value;
}
