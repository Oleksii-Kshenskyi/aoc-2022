#include <iostream>
#include <functional>
#include <unordered_map>

#include "interface.hxx"

using util::VectorPipe;
using util::StringPipe;

enum class Choice {
    Rock,
    Paper,
    Scissors
};

class Game {
    public:
        Game(IT type, uint16_t day): _transformation({
            {"X", Choice::Rock},
            {"Y", Choice::Paper},
            {"Z", Choice::Scissors},
            {"A", Choice::Rock},
            {"B", Choice::Paper},
            {"C", Choice::Scissors}
        }), _choice_score({
            {Choice::Rock, 1},
            {Choice::Paper, 2},
            {Choice::Scissors, 3}
        }) {
            std::function<StringPipe(std::string)> strpipeconv = [](auto s){ return StringPipe(s); };
            std::function<VectorPipe<std::string>(StringPipe)> splitf = [](auto pipe){ return pipe.split(" "); };
            std::function<std::pair<Choice, Choice>(VectorPipe<std::string>)> strtochoice = [&](auto vec) {
                return std::make_pair(this->_transformation[vec.at(0)], this->_transformation[vec.at(1)]);
            };
            this->_scenario = util::Input(type, day)
                .lines()
                .map(strpipeconv)
                .map(splitf)
                .map(strtochoice)
                .to_vec();
        }

        uint64_t play() {
            uint64_t score = 0;
            for(const auto& round: this->_scenario) {
                score += this->_choice_score[round.second];
                score += this->winloss_score(round);
            }
            return score;
        }
    private:
        std::unordered_map<std::string, Choice> _transformation;
        std::unordered_map<Choice, uint64_t> _choice_score;
        std::vector<std::pair<Choice, Choice>> _scenario;

        uint64_t winloss_score(const std::pair<Choice, Choice>& round) {
            if(round.first == Choice::Rock && round.second == Choice::Rock) return 3;
            else if(round.first == Choice::Rock && round.second == Choice::Paper) return 6;
            else if(round.first == Choice::Rock && round.second == Choice::Scissors) return 0;
            else if(round.first == Choice::Paper && round.second == Choice::Rock) return 0;
            else if(round.first == Choice::Paper && round.second == Choice::Paper) return 3;
            else if(round.first == Choice::Paper && round.second == Choice::Scissors) return 6;
            else if(round.first == Choice::Scissors && round.second == Choice::Rock) return 6;
            else if(round.first == Choice::Scissors && round.second == Choice::Paper) return 0;
            else if(round.first == Choice::Scissors && round.second == Choice::Scissors) return 3;
            else throw "Game::winloss_score(): UNKNOWN GAME!";
        }
};

uint64_t part_one(IT type, uint16_t day) {
    return Game(type, day).play();
}

uint64_t part_two(IT type, uint16_t day) {
    (void) type;
    return day;
}

int main() {
    if(util::Input::exists(IT::SampleInput, 2)) {
        util::show_result(IT::SampleInput, 2022, 2, 1, part_one(IT::SampleInput, 2));
        util::show_result(IT::SampleInput, 2022, 2, 2, part_two(IT::SampleInput, 2));
    } else {
        std::cout << "Sample input for Day 2 does not exist." << std::endl;
    }

    if(util::Input::exists(IT::PuzzleInput, 2)) {
        util::show_result(IT::PuzzleInput, 2022, 2, 1, part_one(IT::PuzzleInput, 2));
        util::show_result(IT::PuzzleInput, 2022, 2, 2, part_two(IT::PuzzleInput, 2));
    } else {
        std::cout << "Puzzle input for Day 2 does not exist." << std::endl;
    }
    return 0;
}