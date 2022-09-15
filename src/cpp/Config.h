/*
 * Config.h
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_map>

class Config {
public:
	Config();
	std::string get(std::string key) const;
	void set(std::string key, std::string value);
private:
	std::unordered_map<std::string, std::string> items_;
};

#endif /* CONFIG_H_ */
