/*
 * Config.cpp
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#include "Config.h"
#include <fstream>

Config::Config() {
	// TODO Auto-generated constructor stub

}

std::string Config::get(std::string key) const {
	return items_.at(key);
}

void Config::set(std::string key, std::string value) {
	items_[key] = value;
}

void Config::read_from_file(std::string filename) {
	  std::ifstream infile;
	  std::string line;
	  infile.open (filename);
	  if ( infile.is_open() ) {
		  infile >> line;
	  }
	  infile.close();
}

void Config::write_to_file(std::string filename) {
	std::ofstream outfile;
	outfile.open(filename);
	for(const auto & [ key, value ] : items_) {
		outfile<<key<<"="<<value<<std::endl;
	}
	outfile.close();
}
