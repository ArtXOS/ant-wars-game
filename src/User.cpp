//
// Created by penguin_ib on 5/12/19.
//

#include "User.h"
#include "Move.h"
#include "GameBin.h"
#include <unistd.h>

User::User(const char id) : Player(id) {}

Move *User::makeMove() const { return nullptr; }

bool User::handleInput() const {
    char ch;
    switch (Game::state) {
        case GameState::Choosing: {
            ch = (char) getch();
            ch = (char) toupper(ch);
            if (ch != 'A' && ch != 'U' && ch != 'Q' && ch != 'P') { return false; }
            switch (ch) {
                case 'A':
                    Game::state = GameState::Attack;
                    return true;
                case 'U':
                    Game::state = GameState::Upgrade;
                    return true;
                case 'Q':
                    Menu::state = MenuState::QuitAndSave;
                    GameBin::menu->quitMenu();
                    return true;
                case 'P':
                    Game::state = GameState::Choosed;
                    return true;
            }
            break;
        }

        case GameState::Upgrade: {
            bool found = false;
            for (auto &i : spawners) {
                if (i->getOwner() == 'A' && i->getUCount() >= 20) found = true;
            }

            if (!found) {
                Game::state = GameState::Attack;
                return true;
            }

            ch = (char) getch();
            ch = (char) toupper(ch);

            if (ch == 'P') {
                Game::state = GameState::Attack;
                return true;
            }

            for (auto &i : spawners) {
                if (i->getName() == ch) {
                    if (i->getOwner() == 'A' && i->getUCount() >= 20) {
                        i->upgrade();
                        Game::state = GameState::Attack;
                        return true;
                    }
                }

            }
            break;
        }

        case GameState::Attack: {

            Tower *start = nullptr, *target = nullptr;

            ch = (char) getch();
            ch = (char) toupper(ch);

            if (ch == 'P') {
                Game::state = GameState::Choosed;
                return true;
            }
            if (ch == 'Q') {
                Menu::state = MenuState::QuitAndSave;
                GameBin::menu->quitMenu();
                return true;
            }

            bool found = false;

            for (auto &i : playerTowers) {
                if (i->getUCount() >= 5) found = true;
            }

            if (!found) {
                Game::state = GameState::Choosed;
                return true;
            }

            found = false;

            for (auto &i : playerTowers) {
                if (i->getName() == ch) {
                    found = true;
                    start = i;
                }
            }

            if (!found) return false;

            if (start->getUCount() < 5) return false;

            ch = (char) getch();
            if (ch != '-') return false;
            ch = (char) getch();
            if (ch != '>') return false;

            ch = (char) getch();
            ch = (char) toupper(ch);

            found = false;
            for (auto &i : spawners) {
                if (i->getName() == ch && i != start) {
                    found = true;
                    target = i;
                }
            }
            if (!found) return false;

            start->minusForTurn();
            Game::state = GameState::Choosed;

            GameBin::game->addMove(new Move(start->getName(), target->getName(), this->getID()));

            break;
        }

        default:
            return false;
    }
    return false;
}
