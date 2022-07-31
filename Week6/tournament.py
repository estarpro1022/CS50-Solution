# Simulate a sports tournament

import csv
import sys
import random
import math

# Number of simluations to run
N = 1000


def main():
    global number
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO: Read teams into memory from file
    file = open(sys.argv[1], "r")
    reader = csv.DictReader(file)

    for row in reader:
        team = dict()
        team["team"] = row["team"]
        team["rating"] = row["rating"]
        teams.append(team)


    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    for team in teams:
        counts[team["team"]] = 0

    for i in range(N):
        counts[simulate_tournament(teams)] += 1


    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

    file.close()

def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((int(rating2) - int(rating1)) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    round = 1
    number = len(teams)
    while True:
        if int(math.pow(2, round)) == number:
            break
        round += 1
    winners = teams[:]
    for i in range(round):
        winners = simulate_round(winners)
    return winners[0]["team"]



if __name__ == "__main__":
    main()
