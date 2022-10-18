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

/**
 * @brief A class for managing configuration parameters
 *
 * Supports multiple named parameters.
 * For now, all parameters are treated as strings - if other behavior is needed,
 * clients need to parse strings.
 *
 * Nested parameters or sections currently not supported.
 */
class Config {
public:
  Config();
  /**
   * @brief Get value of parameter by its name
   *
   * @param key - a name of parameter
   * @return value of parameter
   * @throws std::out_of_range if parameter with this name is not present
   */
  std::string get(const std::string& key) const;

  /**
   * @brief Add new parameter or change value of existing parameter
   *
   * @param key - a name of parameter
   * @param value - a value of parameter
   */
  void set(const std::string& key, std::string value);

  /**
   * @brief Reads config parameters from file
   *
   * Currently file format is @c key=value
   *
   * If file not found - TBD
   * @param filename - path to a file, absolute or relative
   */
  void readFromFile(const std::string& filename);

  /**
   * @brief Writes config parameters to file
   *
   * If file doesn't exist - it will be created, otherwise it will be overwritten
   * @param filename - path to a file, absolute or relative
   */
  void writeToFile(const std::string& filename);
private:
  std::map<std::string, std::string> items_;
friend std::ostream& operator<<(std::ostream& out, const Config& config);
friend std::istream& operator>>(std::istream& in, Config& config);
};

#endif /* CONFIG_H_ */
