/*
 * Config.h
 *
 *  Created on: Sep 15, 2022
 *      Author: KZ
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <istream>
#include <ostream>
#include <string>
#include <map>

class Config {
public:
  Config();
  std::string get(std::string key) const;
  void set(std::string key, std::string value);
  void readFromFile(std::string filename);
  void writeToFile(std::string filename);
private:
  std::map<std::string, std::string> items_;
friend std::ostream& operator<<(std::ostream& out, const Config& config);
friend std::istream& operator>>(std::istream& in, Config& config);
};

#endif /* CONFIG_H_ */
