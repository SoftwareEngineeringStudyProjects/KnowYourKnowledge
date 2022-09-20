/*
 * Config.h
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <ostream>
#include <string>
#include <map>

class Config {
public:
	Config();
	std::string get(std::string key) const;
	void set(std::string key, std::string value);
	void read_from_file(std::string filename);
	void write_to_file(std::string filename);
private:
	std::map<std::string, std::string> items_;
friend std::ostream& operator<<(std::ostream& out, const Config& config);
};

#endif /* CONFIG_H_ */
