:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE
is_vote_wasted(City, PoliticalParty) :-
    party(PoliticalParty, _),
    \+ (
        candidate(_, PoliticalParty, City, Row),
        elected(City, PoliticalParty, ElectedRepresentativeCount),
        Row =< ElectedRepresentativeCount
    ).
is_candidate_elected(Name, PoliticalParty) :-
    candidate(Name, PoliticalParty, City, Row),
    elected(City, PoliticalParty, ElectedRepresentativeCount),
    Row =< ElectedRepresentativeCount.

candidate_count_from_city(ListOfCandidates, GivenCity, Count) :-
    candidates_from_city_helper(ListOfCandidates, GivenCity, 0, Count).
candidates_from_city_helper([], _, Count, Count).
candidates_from_city_helper([Candidate|Rest], GivenCity, Ring, Count) :-
    candidate(Candidate, _, City, _),
    (City == GivenCity -> RingRing is Ring + 1 ; RingRing = Ring),
    candidates_from_city_helper(Rest, GivenCity, RingRing, Count).
all_parties(ListOfPoliticalParties) :-
    findall(PoliticalParty, party(PoliticalParty, _), PoliticalParties),
    length(PoliticalParties, Count),
    ListOfPoliticalParties = PoliticalParties.
all_parties(ListOfPoliticalParties) :-
    has_parties_changed(ListOfPoliticalParties,ListOfPoliticalParties).
has_parties_changed(PreviousListOfParties,CurrentList) :-
    findall(PoliticalParty, party(PoliticalParty, _), PreviousListOfParties),
    CurrentList \= PreviousListOfParties.
all_candidates_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Candidate, candidate(Candidate, PoliticalParty, _, _), ListOfCandidates).
all_elected_from_party(PoliticalParty, ListOfCandidates) :-
    findall(Name,is_candidate_elected(Name,PoliticalParty), ListOfCandidates).
election_rate(PoliticalParty, Percentage) :-
    all_candidates_from_party(PoliticalParty, AllCandidates),
    all_elected_from_party(PoliticalParty, ElectedCandidates),
    length(AllCandidates, AllCount),
    length(ElectedCandidates, ElectedCount),
    (AllCount = 0 ->
        Percentage = 0
    ;
        Percentage is (ElectedCount / AllCount)
    ).
council_percentage(PoliticalParty, Percentage) :-
    all_elected_from_party(PoliticalParty, ElectedCandidates),
    to_elect(TotalRepresentatives),
    length(ElectedCandidates, ElectedCount),
    Percentage is (ElectedCount / TotalRepresentatives).
alternative_debate_setups(DescriptionString, OrderedListOfCandidates) :-
    