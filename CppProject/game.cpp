#include "game.h"
#include "graphics.h"
#include "config.h"
#include "grid.h"
#include <cmath>
#include <algorithm>



Game::Game() : grid(nullptr) {}

Game::~Game() {
    delete grid;
}


Game& Game::getInstance() {
    static Game instance;
    return instance;
}

void Game::init() {
    grid = new Grid(12, 20);

    grid->start = grid->get(2, 2);
    grid->start->type = cellType::Start;

    grid->goal = grid->get(9, 15);
    grid->goal->type = cellType::Goal;
}

void Game::update(float dt) {
    graphics::MouseState ms;
    graphics::getMouseState(ms);


    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        grid->resetSearch();
        runAStar();
        return;
    }

    if (!ms.button_left_pressed) {
        return;
    }

    Node* n = grid->getNodeAt(ms.cur_pos_x, ms.cur_pos_y);
    if (!n) return;


    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        if (grid->start)
            grid->start->type = cellType::Empty;
        grid->start = n;
        n->type = cellType::Start;
        return;
    }

    if (graphics::getKeyState(graphics::SCANCODE_G)) {
        if (grid->goal)
            grid->goal->type = cellType::Empty;

        grid->goal = n;
        n->type = cellType::Goal;
        return;
    }


    if (n->type == cellType::Path ||
        n->type == cellType::Open ||
        n->type == cellType::Closed ||
        n->type == cellType::Start ||
        n->type == cellType::Goal
        )
        return;

    grid->resetSearch();

    if (n->type == cellType::Empty)
        n->type = cellType::Obstacle;
    else if (n->type == cellType::Obstacle)
        n->type = cellType::Empty;


}
    
    



void Game::draw() {

    if (!grid) return;

    for (auto n : grid->nodes) {
        n->draw();
    }


}

static float heuristic(Node* a, Node* b) {
    return float(abs(a->row - b->row) + abs(a->col - b->col));
}

void Game::runAStar() {
    
    if (!grid->start || !grid->goal) return;

    std::vector<Node*> open;
    std::vector<Node*> closed;

    Node* start = grid->start;
    Node* goal = grid->goal;

    start->g = 0.0f;
    start->h = heuristic(start, goal);
    start->f = start->h;
    open.push_back(start);

    while (!open.empty()) {
        Node* current = *std::min_element(
            open.begin(), open.end(),
            [](Node* a, Node* b) {return a->f < b->f; }
        );

        if (current == goal) {
            Node* p = goal->parent;
            while (p && p != start) {
                p->type = cellType::Path;
                p = p->parent;
            }
            return;
        }

        open.erase(std::remove(open.begin(), open.end(), current), open.end());
        closed.push_back(current);

        if (current != start && current != goal)
            current->type = cellType::Closed;
        for (Node* neighbor : grid->getNeighbors(current)) {
            if (std::find(closed.begin(), closed.end(), neighbor) != closed.end())
                continue;
            float tentativeG = current->g + 1.0f;
            bool inOpen = std::find(open.begin(), open.end(), neighbor) != open.end();

            if (!inOpen || tentativeG < neighbor->g) {
                neighbor->parent = current;
                neighbor->g = tentativeG;
                neighbor->h = heuristic(neighbor, goal);
                neighbor->f = neighbor->g + neighbor->h;

                if (!inOpen) {
                    open.push_back(neighbor);
                    if (neighbor != goal)
                        neighbor->type = cellType::Open;
                }
            }
        }
    }
}

