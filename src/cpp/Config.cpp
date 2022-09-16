/*
 * Config.cpp
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#include "Config.h"

#include "doctest.h"

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

void parse_key_value(std::string line, std::string& key, std::string& value) {
	auto delimiter_position = line.find("=");
	key = line.substr(0, delimiter_position);
	value = line.substr(delimiter_position+1);
}

void Config::read_from_file(std::string filename) {
	  std::ifstream infile;
	  std::string line;
	  infile.open (filename);
	  if ( infile.is_open() ) {
		  while(getline(infile, line)) {
			  std::string key;
			  std::string value;
			  parse_key_value(line, key, value);
			  items_[key] = value;
		  }
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

TEST_CASE("Set and get config data") {
	Config config;
	config.set("current_collection", "MyNotes");
	CHECK(config.get("current_collection") == "MyNotes");
}
