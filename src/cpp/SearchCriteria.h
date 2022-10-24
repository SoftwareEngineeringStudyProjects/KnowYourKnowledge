//
// Created by Dmytro Klishch on 10/7/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H
#define KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H

#include "doctest.h"

#include <map>
#include <vector>
#include <string>

template<typename... T>
using searchCondition = std::function<bool(std::variant<T...>)>;

template<typename... T>
class SearchCriteria {
public:
    std::vector<searchCondition<T...>> get(const std::string &component) const {
        if (!conditions_.count(component)) return std::vector<searchCondition<T...>>();
        return conditions_.at(component);
    }

    template<typename E>
    void addEqualToCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(equalTo(value));
    }

    template<typename E>
    void addGreaterThanCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(greaterThan(value));
    }

    template<typename E>
    void addLessThanCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(lessThan(value));
    }

    void addContainsCheck(const std::string &component, const std::string &value) {
        conditions_[component].push_back(contains(value));
    }

    void addCheck(const std::string &component, searchCondition<T...> condition) {
        conditions_[component].push_back(condition);
    }

private:
    std::map<std::string, std::vector<searchCondition<T...>>> conditions_;

    static searchCondition<T...> contains(const std::string &value) {
        return [value](std::variant<T...> variant) {
            return value.find(std::get<std::string>(variant)) != -1;
        };
    }

    template<typename E>
    static searchCondition<T...> equalTo(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) == value;
        };
    }

    template<typename E>
    static searchCondition<T...> greaterThan(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) < value;
        };
    }

    template<typename E>
    static searchCondition<T...> lessThan(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) > value;
        };
    }
};

TEST_CASE("Get with no conditions for component") {
    SearchCriteria<int> criteria;
    CHECK(criteria.get("rand").empty());
}

TEST_CASE("Add equal to check") {
    SearchCriteria<int> criteria;
    criteria.addEqualToCheck("rand", 5);
    CHECK(!criteria.get("rand")[0](4));
    CHECK(criteria.get("rand")[0](5));
    CHECK(!criteria.get("rand")[0](6));
}

TEST_CASE("Add greater than check") {
    SearchCriteria<int> criteria;
    criteria.addGreaterThanCheck("rand", 5);
    CHECK(criteria.get("rand")[0](4));
    CHECK(!criteria.get("rand")[0](5));
    CHECK(!criteria.get("rand")[0](6));
}


TEST_CASE("Add less than check") {
    SearchCriteria<int> criteria;
    criteria.addLessThanCheck("rand", 5);
    CHECK(!criteria.get("rand")[0](4));
    CHECK(!criteria.get("rand")[0](5));
    CHECK(criteria.get("rand")[0](6));
}

TEST_CASE("Add contains check") {
    SearchCriteria<std::string> criteria;
    criteria.addContainsCheck("rand", "random");
    CHECK(criteria.get("rand")[0]("rand"));
    CHECK(!criteria.get("rand")[0]("ram"));
}

TEST_CASE("Add check") {
    SearchCriteria<int> criteria;
    auto check = [](std::variant<int> val) { return std::get<int>(val) == 3; };
    criteria.addCheck("rand", check);
    CHECK(!criteria.get("rand")[0](4));
    CHECK(criteria.get("rand")[0](3));
}


#endif //KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H
