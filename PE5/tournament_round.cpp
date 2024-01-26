#include "tournament_round.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() {
}
TournamentRound::TournamentRound(std::list<MusicBand*>_bands) {
     this -> bands = _bands;
}
TournamentRound::TournamentRound(std::vector<MusicBand*>_bands) {
    bands.assign(_bands.begin(),_bands.end());
}

std::size_t TournamentRound::size() { return bands.size();}
    
//TournamentRound::TournamentRound(TournamentRound& other) { }
//TournamentRound::TournamentRound(TournamentRound&& other) { }
TournamentRound& TournamentRound::operator=(TournamentRound&& other) {
    if(this != &other){
        bands.clear();
        bands = other.bands;
    }
    return *this;
    
}
TournamentRound& TournamentRound::get_next_round() {
    std::list<MusicBand*> reverse_bands;std::list<MusicBand*> bands_;
    std::list<MusicBand*> final;
    int count = bands.size();

    for (auto it = bands.begin(); it != bands.end(); ++it) {
        reverse_bands.push_front(*it);
    }
    bands_ = bands;

    if (count % 2 == 0) {
        for (int i = 0; i < count / 2; ++i) {
            MusicBand* winner;
            MusicBand* loser;
            int score1 = (*bands_.begin())->play(*reverse_bands.begin());
            int score2 = (*reverse_bands.begin())->play(*bands_.begin());

            if (score1 < score2) {
                int fan_change = score2 - score1;
                winner = *reverse_bands.begin();
                loser = *bands_.begin();
                final.push_back(winner);
                if (fan_change < loser->get_fan_count()) {
                    winner -> set_fan_count(winner->get_fan_count() + fan_change);
                    loser->set_fan_count(loser->get_fan_count() - fan_change);
                } else {
                    winner -> set_fan_count(winner->get_fan_count() + loser->get_fan_count());
                    loser->set_fan_count(0);
                }
            } else {
                int fan_change = score1 - score2;
                winner = *bands_.begin();
                loser = *reverse_bands.begin();
                final.push_back(winner);
                if (fan_change < loser->get_fan_count()) {
                    winner -> set_fan_count(winner->get_fan_count() + fan_change);
                    loser->set_fan_count(loser->get_fan_count() - fan_change);
                } else {
                    winner -> set_fan_count(winner->get_fan_count() + loser -> get_fan_count());
                    loser->set_fan_count(0);
                }
            }

            bands_.pop_front();
            reverse_bands.pop_front();
        }
    } else {
        for (int i = 0; i < (count / 2) + 1; ++i) {
            MusicBand* winner;
            MusicBand* loser;
            int score1;
            int score2;

            if (i == (count / 2)) {
                final.push_back(*bands_.begin());
            }
            else{
                score1 = (*bands_.begin())->play(*reverse_bands.begin());
                score2 = (*reverse_bands.begin())->play(*bands_.begin());
            
                if (score1 < score2) {
                    int fan_change = score2 - score1;
                    winner = *reverse_bands.begin();
                    loser = *bands_.begin();
                    final.push_back(winner);
    
                    if (fan_change < loser->get_fan_count()) {
                        winner -> set_fan_count(winner->get_fan_count() + fan_change);
                        loser->set_fan_count(loser->get_fan_count() - fan_change);
                    } else {
                        winner -> set_fan_count(winner->get_fan_count() + loser -> get_fan_count());
                        loser->set_fan_count(0);
                    }
                } else {
                    int fan_change = score1 - score2;
                    winner = *bands_.begin();
                    loser = *reverse_bands.begin();
                    final.push_back(winner);
    
                    if (fan_change < loser->get_fan_count()) {
                        winner -> set_fan_count(winner->get_fan_count() + fan_change);
                        loser->set_fan_count(loser->get_fan_count() - fan_change);
                    } else {
                        winner -> set_fan_count(winner->get_fan_count() + loser -> get_fan_count());
                        loser->set_fan_count(0);
                    }
                }
            }

            bands_.pop_front();
            reverse_bands.pop_front();
        }
    }

    return *(new TournamentRound(final));
}
    

std::ostream& operator<< (std::ostream &os, TournamentRound &other) {
    for (auto it = other.bands.begin(); it != other.bands.end(); ++it) {
        os << (*it)->get_name();
        if (std::next(it) != other.bands.end()) {
            os << "\t";
        }
    }
    return os;
    
}