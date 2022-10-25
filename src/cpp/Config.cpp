/*
 * Config.cpp
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#include "Config.h"

#include "doctest.h"

#include <fstream>
#include <sstream>

Config::Config() {
	// TODO Auto-generated constructor stub

}

std::string Config::get(const std::string& key) const {
	return items_.at(key);
}

void Config::set(const std::string& key, std::string value) {
	items_[key] = value;
}

void parse_key_value(std::string line, std::string& key, std::string& value) {
	auto delimiter_position = line.find("=");
	key = line.substr(0, delimiter_position);
	value = line.substr(delimiter_position+1);
}

void Config::readFromFile(const std::string& filename) {
	  std::ifstream infile;
	  std::string line;
	  infile.open (filename);
	  if ( infile.is_open() ) {
		  infile >> *this;
	  }
	  infile.close();
}

void Config::writeToFile(const std::string& filename) {
	std::ofstream outfile;
	outfile.open(filename);
	outfile<<*this;
	outfile.close();
}

std::ostream& operator<<(std::ostream& out, const Config& config) {
	for(const auto & [ key, value ] : config.items_) {
		out<<key<<"="<<value<<std::endl;
	}
	return out;
}

std::istream& operator>>(std::istream &in, Config &config) {
	std::string line;
	while (getline(in, line)) {
		std::string key;
		std::string value;
		parse_key_value(line, key, value);
		config.items_[key] = value;
	}
	return in;
}

TEST_CASE("Set and get config data") {
	Config config;
	config.set("current_collection", "MyNotes");
	CHECK(config.get("current_collection") == "MyNotes");
}

TEST_CASE("Get non-existing key should throw exception") {
	Config config;
	config.set("current_collection", "MyNotes");
	CHECK_THROWS_AS(config.get("non_existing"), std::out_of_range);
}

TEST_CASE("Output config to stream") {
	Config config;

    config.set("current_collection", "Another with space");
    CHECK(config.get("current_collection") == "Another with space");
    config.set("something","anything");
    CHECK(config.get("something") == "anything");

    std::stringstream out;
    out<<config;
    CHECK(out.str() == "current_collection=Another with space\nsomething=anything\n");

}

TEST_CASE("Input config from stream") {
	Config config;

	std::stringstream in{"current_collection=Another with space\nsomething=anything\n"};
	in>>config;

	CHECK(config.get("current_collection") == "Another with space");
	CHECK(config.get("something") == "anything");


}
