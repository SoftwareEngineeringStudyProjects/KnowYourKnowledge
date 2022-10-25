//
// Created by Dmytro Klishch on 10/25/22.
//

#ifndef KNOWYOURKNOWLEDGEMYFORK_MATCHRESULT_H
#define KNOWYOURKNOWLEDGEMYFORK_MATCHRESULT_H


struct MatchResult {
public:
    MatchResult(int total, int passed) : _passed(passed), _total(total) {}

    int total() const {
        return _total;
    }

    int passed() const {
        return _passed;
    }

private:
    int _total;
    int _passed;
};


#endif //KNOWYOURKNOWLEDGEMYFORK_MATCHRESULT_H
