//
// Created by penguin_ib on 5/18/19.
//

#include "Route.h"
#include <unordered_map>
#include <algorithm>
#include <queue>
#include "Tower.h"
#include "GameBin.h"
#include <unistd.h>

Route::Route(const std::vector<std::vector<Tile *> > &tiles, const std::vector<Tower *> &spawners) : tiles(tiles), spawners(spawners) {}

double Route::cost(Tile *, Tile *) const { return 1; }

struct Route::PriorityQueue {

    typedef std::pair<int, Tile *> PQElement;

    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement> > elements;

    inline bool empty() const {
        return elements.empty();
    }

    inline void put(Tile *item, double priority) {
        elements.emplace(priority, item);
    }

    Tile *get() {
        Tile *best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};


double Route::heuristic(Tile *a, Tile *b) const {
    return abs((int) a->getPosX() - (int) b->getPosX()) + abs((int) a->getPosY() - (int) b->getPosY());
}

std::vector<Tile *>
Route::reconstruct_path(Tile *start, Tile *goal, std::unordered_map<Tile *, Tile *> &came_from) const {
    std::vector<Tile *> path;
    Tile *current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.emplace_back(start);
    return path;
}


std::vector<Tile *> Route::findRoute(const char fromT, const char toT, const char) const {

    Tower *from = nullptr, *to = nullptr;

    for (auto &i : spawners) {
        if (i->getName() == fromT) from = i;
        if (i->getName() == toT) to = i;
    }

    std::unordered_map<Tile *, Tile *> came_from;
    std::unordered_map<Tile *, double> cost_so_far;

    PriorityQueue frontier;
    frontier.put(from, 0);

    came_from[from] = from;
    cost_so_far[from] = 0;

    while (!frontier.empty()) {

        Tile *current = frontier.get();

        if (current == to) break;

        for (Edge *a : current->edges) {

            Tile *next = a->getTo();
            double new_cost = cost_so_far[current] + cost(current, next);

            if (next->getOwner() != '*' && next->getName() != to->getName() &&
                next->getName() != from->getName())
                continue;

            if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, to);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }

    std::vector<Tile *> solution = reconstruct_path(from, to, came_from);

    return solution;

}
