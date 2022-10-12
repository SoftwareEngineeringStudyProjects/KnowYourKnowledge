//
// Created by Dmytro Klishch on 10/7/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H
#define KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H

#include "doctest.h"

#include <map>
#include <vector>
#include <string>

template<class... T>
using searchCondtition = std::function<bool(std::variant<T...>)>;

template<class... T>
class SearchCriteria {
public:
    std::vector<searchCondtition<T...>> get(const std::string &component) const {
        if (!conditions_.count(component)) return std::vector<searchCondtition<T...>>();
        return conditions_.at(component);
    }

    template<class E>
    void addEqualityCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(equalityCheck(value));
    }

    template<class E>
    void addGreaterCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(greaterCheck(value));
    }

    template<class E>
    void addLowerCheck(const std::string &component, const E &value) {
        conditions_[component].push_back(lowerCheck(value));
    }

    void addCheck(const std::string &component, searchCondtition<T...> condition) {
        conditions_[component].push_back(condition);
    }

private:
    std::map<std::string, std::vector<searchCondtition<T...>>> conditions_;

    template<class E>
    searchCondtition<T...> equalityCheck(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) == value;
        };
    }

    template<class E>
    searchCondtition<T...> greaterCheck(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) < value;
        };
    }

    template<class E>
    searchCondtition<T...> lowerCheck(const E &value) {
        return [value](std::variant<T...> variant) {
            return std::get<E>(variant) > value;
        };
    }
};

TEST_CASE("Get with no conditions for component") {
    SearchCriteria<int> *criteria = new SearchCriteria<int>();
    CHECK(criteria->get("rand").empty());
    delete criteria;
}

TEST_CASE("Add equality check") {
    SearchCriteria<int> *criteria = new SearchCriteria<int>();
    criteria->addEqualityCheck("rand", 5);
    CHECK(!criteria->get("rand")[0](4));
    CHECK(criteria->get("rand")[0](5));
    CHECK(!criteria->get("rand")[0](6));
    delete criteria;
}

TEST_CASE("Add greater check") {
    SearchCriteria<int> *criteria = new SearchCriteria<int>();
    criteria->addGreaterCheck("rand", 5);
    CHECK(criteria->get("rand")[0](4));
    CHECK(!criteria->get("rand")[0](5));
    CHECK(!criteria->get("rand")[0](6));
    delete criteria;
}


TEST_CASE("Add lower check") {
    SearchCriteria<int> *criteria = new SearchCriteria<int>();
    criteria->addLowerCheck("rand", 5);
    CHECK(!criteria->get("rand")[0](4));
    CHECK(!criteria->get("rand")[0](5));
    CHECK(criteria->get("rand")[0](6));
    delete criteria;
}

TEST_CASE("Add check") {
    SearchCriteria<int> *criteria = new SearchCriteria<int>();
    auto check = [](std::variant<int> val) { return std::get<int>(val) == 3; };
    criteria->addCheck("rand", check);
    CHECK(!criteria->get("rand")[0](4));
    CHECK(criteria->get("rand")[0](3));
    delete criteria;
}



#endif //KNOWYOURKNOWLEDGEMYFORK_SEARCHCRITERIA_H
