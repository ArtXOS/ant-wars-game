//
// Created by penguin_ib on 5/20/19.
//

#include "Menu.h"
#include <unistd.h>
#include <cstring>

bool Menu::withUser = false;
bool Menu::newGame = true;
std::string Menu::saveFile;
std::string Menu::mapFile;
MenuState Menu::state = MainMenu;

void Menu::showMenu() const {
    clear();
    refresh();
    keypad(stdscr, TRUE);

    int ch, current = 0, last;
    bool end = false;

    while (!end) {
        switch (Menu::state) {
            case MenuState::MainMenu: {
                std::vector<std::string> select{"NEW GAME", "LOAD GAME", "EXIT"};
                last = 2;

                for (unsigned long i = 0; i <= (unsigned long) last; i++) {
                    move(5 + i * 2, 25);
                    refresh();
                    if (i == (unsigned long) current) {
                        attron(A_STANDOUT);
                        addstr(select.at(i).c_str());
                        attroff(A_STANDOUT);
                    } else
                        addstr(select.at(i).c_str());
                }

                ch = getch();
                switch (ch) {
                    case KEY_ENTER:
                    case 10:
                        if (current == 0) {
                            Menu::newGame = true;
                            current = 0;
                            Menu::state = MenuState::ChooseNewGame;
                        } else if (current == 1) {
                            Menu::newGame = false;
                            current = 0;
                            Menu::state = MenuState::ChooseSave;
                        } else if (current == 2) {
                            current = 0;
                            Menu::state = MenuState::SessionEnd;
                        }
                        break;
                    case KEY_DOWN:
                        if (current == last) current = 0;
                        else ++current;
                        break;
                    case KEY_UP:
                        if (current == 0) current = last;
                        else --current;
                        break;
                    case 'q':
                    case 'Q':
                        Menu::state = MenuState::SessionEnd;
                        break;
                    default:
                        break;
                }

                break;
            }

            case MenuState::ChooseNewGame: {

                std::vector<std::string> select{"PLAYER VS BOT", "BOT VS BOT", "EXIT"};
                last = 2;

                for (unsigned long i = 0; i <= (unsigned long) last; i++) {
                    move(5 + i * 2, 25);
                    refresh();
                    if (i == (unsigned long) current) {
                        attron(A_STANDOUT);
                        addstr(select.at(i).c_str());
                        attroff(A_STANDOUT);
                    } else
                        addstr(select.at(i).c_str());
                }

                ch = getch();
                switch (ch) {
                    case KEY_ENTER:
                    case 10:
                        if (current == 0) {
                            Menu::withUser = true;
                            current = 0;
                            Menu::state = MenuState::ChooseMap;
                        } else if (current == 1) {
                            Menu::withUser = false;
                            current = 0;
                            Menu::state = MenuState::ChooseMap;;
                        } else if (current == 2) {
                            current = 0;
                            Menu::state = MenuState::MainMenu;
                        }
                        break;
                    case KEY_DOWN:
                        if (current == last) current = 0;
                        else ++current;
                        break;
                    case KEY_UP:
                        if (current == 0) current = last;
                        else --current;
                        break;
                    case 'q':
                    case 'Q':
                        Menu::state = MenuState::MainMenu;
                        break;
                    default:
                        break;
                }

                break;
            }
            case MenuState::ChooseMap:
                mapsMenu();
                if (GameBin::state == GameBinState::GameProcess) { return; }
                break;
            case MenuState::ChooseSave:
                savesMenu();
                if (GameBin::state == GameBinState::GameProcess) { return; }
                break;
            case MenuState::SessionEnd:
                GameBin::state = GameBinState::End;
                end = true;
                break;
            default:
                break;
        }

        refresh();
        usleep(25000);
        clear();
    }
}

void Menu::mapsMenu() const {

    clear();
    refresh();

    char dir[16];
    int ch;
    strcpy(dir, GameBin::fileSystem->getMapsDir().c_str());
    std::vector<std::string> files = GameBin::fileSystem->filesInDirectory(dir);
    unsigned long last = files.size() - 1;
    unsigned long current = 0;
    bool end = false;

    while (!end) {

        try {
            for (unsigned long i = 0; i <= last; i++) {
                move(5 + i * 2, 25);
                refresh();
                if (i == current) {
                    attron(A_STANDOUT);
                    addstr(files.at(i).c_str());
                    attroff(A_STANDOUT);
                } else
                    addstr(files.at(i).c_str());
            }
        } catch (std::exception &) {
            Menu::state = MenuState::ChooseNewGame;
            break;
        }

        ch = getch();

        switch (ch) {
            case KEY_ENTER:
            case 10:
                Menu::mapFile = files.at(current);
                end = true;
                GameBin::state = GameBinState::GameProcess;
                break;
            case KEY_DOWN:
                if (current != last) ++current;
                else current = 0;
                break;
            case KEY_UP:
                if (current == 0) current = last;
                else --current;
                break;
            case 'q':
            case 'Q':
                Menu::state = MenuState::ChooseNewGame;
                end = true;
                break;
            default:
                break;
        }

        refresh();
        usleep(25000);
        clear();
    }

}

void Menu::savesMenu() const {

    clear();
    refresh();

    char dir[17];
    int ch;
    strcpy(dir, GameBin::fileSystem->getSaveDir().c_str());
    std::vector<std::string> files = GameBin::fileSystem->filesInDirectory(dir);
    unsigned long last = files.size() - 1;
    unsigned long current = 0;
    bool end = false;

    while (!end) {
        try {
            for (unsigned long i = 0; i <= last; i++) {
                move(5 + i * 2, 25);
                refresh();
                if (i == current) {
                    attron(A_STANDOUT);
                    addstr(files.at(i).c_str());
                    attroff(A_STANDOUT);
                } else
                    addstr(files.at(i).c_str());
            }

        }
        catch (std::exception &) {
            Menu::state = MenuState::MainMenu;
            break;
        }

        ch = getch();
        switch (ch) {
            case KEY_ENTER:
            case 10:
                Menu::saveFile = files.at(current);
                Menu::newGame = false;
                end = true;
                GameBin::state = GameBinState::GameProcess;
                break;
            case KEY_DOWN:
                if (current != last) ++current;
                else current = 0;
                break;
            case KEY_UP:
                if (current == 0) current = last;
                else --current;
                break;
            case 'q':
            case 'Q':
                Menu::state = MenuState::MainMenu;
                end = true;
                break;
            default:
                break;
        }

        refresh();
        usleep(25000);
        clear();
    }

}

bool Menu::printMapMenu() const {

    switch (Game::state) {
        case GameState::UserTurn: {

            Game::state = GameState::Choosing;

            while (true) {

                switch (Game::state) {

                    case GameState::Choosing: {
                        clear();
                        refresh();
                        Game::gameMap->printMap();
                        for (auto i = 0; i < Map::width; i++) addch('-');

                        addch('\n');
                        addch('\r');
                        addstr("You are red player! To attack enter 'A', to upgrade anthill 'U'"
                               "\n\rYou can make as many attacks and upgrades as is count of your towers!\n\r"
                               "If you want to exit enter 'q'; If you want to pass attack/upgrade enter 'p'\n\r");
                        addch('\n');
                        addch('\r');
                        addstr("User input > ");
                        refresh();

                        if (!GameBin::game->userInputHandle()) continue;
                        if (GameBin::state == GameBinState::GameEnd) return true;
                        break;
                    }

                    case GameState::Upgrade: {
                        clear();
                        refresh();
                        Game::gameMap->printMap();
                        for (auto i = 0; i < Map::width; i++) addch('-');

                        addch('\n');
                        addch('\r');
                        addstr("Choose your anthill. You need to have more than 20 ants in it. Then these ants will die,\n\r"
                               "but your anthill will produce ants faster");
                        addch('\n');
                        addch('\r');
                        addstr("User input > ");
                        refresh();

                        if (!GameBin::game->userInputHandle()) { continue; }
                        if (GameBin::state == GameBinState::GameEnd) return true;
                        break;
                    }

                    case GameState::Attack: {
                        clear();
                        refresh();
                        Game::gameMap->printMap();
                        for (auto i = 0; i < Map::width; i++) addch('-');

                        addch('\n');
                        addch('\r');
                        addstr("Choose start and target. Example 'A->B'. A - start, B - target. You need to have at least 5 ants in the start tower!"
                               "\n\rBe careful! If your ants will meet other ants - they will get lost(they just miss their fugleant :( )"
                               "\n\rIf you want to pass attack enter 'p'\n\r");
                        addch('\n');
                        addch('\r');
                        addstr("User input > ");
                        refresh();

                        if (!GameBin::game->userInputHandle()) { continue; }
                        else if (GameBin::state == GameBinState::GameEnd) return true;
                        break;
                    }

                    case GameState::Choosed:
                        return true;

                    default:
                        break;
                }
            }
        }

        case GameState::OtherPlayersTurns: {
            clear();
            refresh();
            Game::gameMap->printMap();
            for (auto i = 0; i < Map::width; i++) addch('-');
            addch('\n');
            addch('\r');
            addstr("Waiting for other players... If you want to exit - press 'q'. To continue enter whatever else");
            addch('\n');
            addch('\r');
            refresh();
            char ch;
            ch = (char) getch();
            ch = (char) toupper(ch);
            if (ch == 'Q') {
                Menu::state = MenuState::MainMenu;
                GameBin::state = GameBinState::GameEnd;
                Game::state = GameState::Exit;
                return true;
            }
            break;
        }

        default:
            break;
    }
    return true;
}

void Menu::quitMenu() const {

    clear();
    refresh();

    unsigned long current = 0;
    bool done = false;

    while (!done) {
        switch (Menu::state) {
            case MenuState::QuitAndSave: {

                unsigned long last = 2;
                std::vector<std::string> pos0{"CONTINUE", "SAVE", "QUIT GAME"};

                for (unsigned long i = 0; i <= last; i++) {
                    move(5 + i * 2, 25);
                    refresh();
                    if (i == current) {
                        attron(A_STANDOUT);
                        addstr(pos0.at(i).c_str());
                        attroff(A_STANDOUT);
                    } else
                        addstr(pos0.at(i).c_str());
                }

                int ch = getch();
                switch (ch) {
                    case KEY_ENTER:
                    case 10: {
                        if (current == 0) {
                            done = true;
                            GameBin::state = GameBinState::GameProcess;
                            break;
                        } else if (current == 1) {
                            Menu::state = MenuState::CreateSave;
                            current = 0;
                        } else if (current == 2) {
                            GameBin::state = GameBinState::GameEnd;
                            Menu::state = MenuState::MainMenu;
                            done = true;
                        }
                        break;
                    }
                    case KEY_DOWN:
                        if (current == last) current = 0;
                        else ++current;
                        break;
                    case KEY_UP:
                        if (current == 0) current = last;
                        else --current;
                        break;
                    case 'q':
                    case 'Q':
                        Game::state = GameState::Choosing;
                        done = true;
                        break;
                    default:
                        break;
                }

                break;
            }

            case MenuState::CreateSave: {
                move(5, 25);
                char tmp[100];
                std::string str;
                addstr("Name the save file");
                move(7, 25);
                addstr("User input > ");
                getstr(tmp);
                if (!GameBin::fileSystem->checkFileName(tmp)) continue;
                else {
                    std::string name(tmp);
                    GameBin::fileSystem->writeSave(name);
                    Menu::state = MenuState::QuitAndSave;
                }
                break;
            }

            default:
                break;
        }

        clear();
        usleep(25000);
        refresh();

    }
}
