#include <fstream>
#include <filesystem>
#include <limits>
#include "../include/MindMapper.h"

MindMapper::MindMapper() : m_first(nullptr), m_last(nullptr), m_Length(0)
{
}

MindMapper::~MindMapper()
{
    while (m_first) {
        Idea* tmp = m_first;
        m_first = m_first->next;
        delete tmp;
    }
    m_first = m_last = nullptr;
}

void MindMapper::mainMenu()
{
    std::cout << "\n---------- Mind Mapper ----------\n" << std::endl;
    std::cout << "1. Form a new Idea" << std::endl;
    std::cout << "2. Delete an Idea" << std::endl;
    std::cout << "3. View all Ideas" << std::endl;
    std::cout << "4. Select an Idea" << std::endl;
    std::cout << "5. Mark/Unmark Idea as done" << std::endl;
    std::cout << "6. Load/Save session" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

void MindMapper::run()
{
    int choice;
    do {
        mainMenu();
        std::cout << "Enter your choice: ";
        cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        switch (choice)
        {
        case 1:
            formIdea();
            break;
        case 2:
            removeIdea();
            break;
        case 3:
            traverseIdeas();
            break;
        case 4:
            editIdea();
            break;
        case 5:
            markIdeaDone();
            break;
        case 6:
            // loadOrSave();
            break;
        case 7:
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Enter a valid option." << std::endl;
        }
    } while (choice != 7);
}

void MindMapper::thinkMenu()
{
    std::cout << std::endl;
    std::cout << "-------------Form Idea-------------" << std::endl;
    std::cout << "1. Add a thought" << std::endl;
    std::cout << "2. Remove last thought" << std::endl;
    std::cout << "3. Show trail of thoughts" << std::endl;
    std::cout << "4. To Main Menu" << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

void MindMapper::formIdea()
{
    String title;
    char ch;
    
    std::cout << "Enter a title for this new Idea: ";
    do {
        std::cin >> std::noskipws >> ch;
        if (ch != '\n')
            title.append(ch);
    } while (ch != '!');
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    
    Stack thoughts(title);
    int choice;

    do {
        String thought;
        thinkMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

        switch (choice)
        {
        case 1:
            std::cout << "Enter a new thought - end it with '!':" << std::endl;
            ch = 0;
            do {
                std::cin >> std::noskipws >> ch;
                if (ch != '\n')
                    thought.append(ch);
            } while (ch != '!');
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            thoughts.push(thought);
            break;
        case 2:
            std::cout << "Removed last thought!" << std::endl;
            thoughts.pop();
            break;
        case 3:
            cout << endl;
            cout << "Trail of thoughts: " << endl;
            thoughts.display(thoughts.getTop());
            break;
        case 4:
            break;
        default:
            std::cout << "Invalid input, try again" << std::endl;
        }
    } while (choice != 4);

    addIdea(thoughts);
}

void MindMapper::addIdea(const Stack &t)
{
    Idea *tmp = new Idea(t);
    if (!tmp) {
        std::cout << "List is full!" << std::endl;
        return;
    }
    if (!m_first) {
        m_first = tmp;
        m_last = m_first;
    } else {
        m_last->next = tmp;
        m_last = tmp;
    }
    m_Length++;
}

void MindMapper::removeIdea()
{
    int ndx = selectIdea();
    if (ndx < 0 || ndx >= m_Length) {
        std::cout << "Invalid index" << std::endl;
        return;
    }

    Idea *p = m_first, *q = nullptr;

    if (m_first) {
        if (ndx == 0) {
            m_first = m_first->next;
        } else {
            for (int i = 0; i < ndx; i++) {
                q = p;
                p = p->next;
            }
            q->next = p->next;
        }
        delete p;
        m_Length--;
    }
}

void MindMapper::editIdea()
{
    int sel = selectIdea();
    Idea *p = m_first;
    if (p) {
        if (sel == -1) {
            std::cout << "Wrong # of Idea selected" << std::endl;
            return;
        } else if (sel > 0) {
            for (int i = 0; i < sel; i++)
                p = p->next;
        }
    }

    int choice;
    do {
        String thought;
        char ch;
        thinkMenu();
        std::cout << "Enter your choice: ";
        cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
        
        switch (choice)
        {
        case 1:
            std::cout << "Enter a new thought - end it with '!'" << std::endl;
            ch = 0;
            do {
                cin >> noskipws >> ch;
                if (ch != '\n')
                    thought.append(ch);
            } while (ch != '!');
            p->thoughts.push(thought);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
            break;
        case 2:
            std::cout << "Removed last thought!" << std::endl;
            p->thoughts.pop();
            break;
        case 3:
            cout << endl;
            cout << "Trail of thoughts: " << endl;
            p->thoughts.display(p->thoughts.getTop());
            break;
        case 4:
            break;
        default:
            std::cout << "Invalid input, try again" << std::endl;
        }
    } while (choice != 4);
}

int MindMapper::selectIdea()
{
    int sel;
    traverseIdeas();
    std::cout << "Choose an idea: ";
    cin >> sel;
    sel--;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    if (sel < 0 || sel >= m_Length)
        return -1;
    return sel;
}

void MindMapper::traverseIdeas()
{
    Idea *p = m_first;
    int i = 1;
    while (p) {
        std::cout << "Idea #" << i++ << ": " << p->thoughts.getTitle().c_str();
        if (p->thoughts.isDone())
            std::cout << " (Done)";
        std::cout << std::endl;
        p = p->next;
    }
}

void MindMapper::markIdeaDone()
{
    int choice;
    std::cout << "1. Mark Idea done" << std::endl;
    std::cout << "2. Unmark Idea as done" << std::endl;
    cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

    if (choice < 1 || choice > 2) {
        std::cout << "Invalid entry!" << std::endl;
        return; 
    }
    int sel = selectIdea();
    Idea *p = m_first;
    if (p) {
        if (sel == -1) {
            std::cout << "Wrong # of Idea selected" << std::endl;
            return;
        } else if (sel > 0) {
            for (int i = 0; i < sel; i++)
                p = p->next;
        }
    }

    if (choice == 1 && p->thoughts.isDone()) {
        std::cout << "Idea already done!" << std::endl;
    } else if (choice == 1 && !p->thoughts.isDone()) {
        p->thoughts.setStatus(true);
    } else if (choice == 2 && p->thoughts.isDone()) {
        p->thoughts.setStatus(false);
    } else {
        std::cout << "Idea already not done!" << std::endl;
    }
}

// void MindMapper::loadOrSave()
// {
    // int choice;
    // std::cout << "1. Save current session." << std::endl;
    // std::cout << "2. Load previous session." << std::endl;
    // std::cout << "3. Go back to previous menu." << std::endl;
    // std::cout << "Enter: ";
    // std::cin >> choice;
    // if (choice == 1) {
    //     std::string session;
    //     std::cout << "Enter a name for your session (no spaces): ";
    //     std::cin >> session;
    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer
    //     serialize(session);
    // } else if (choice == 2) {
    //     std::string session;
    //     std::cout << "Listing saved sessions:" << std::endl;
    //     try {
    //         for (const auto& entry : filesystem::directory_iterator()) {
    //             if (filesystem::is_regular_file(entry.status())) {
    //                 if (entry.path().extension() == ".bin") {
    //                     std::cout << entry.path().filename().string() << std::endl;
    //                 }
    //             }
    //         }
    //     } catch (const filesystem::filesystem_error& e) {
    //         std::cerr << "Error accessing directory: " << e.what() << std::endl;
    //     }
    //     std::cout << "Please enter the name of the session to load: ";
    //     std::cin >> session;

    //     *this = MindMapper::deserialize(session);
    // } else {
    //     return;
    // }
// }

// void MindMapper::serialize(const std::string& filename)
// {
    // ofstream file(filename, ios::binary);
    // if (!file.is_open()) {
    //     std::cerr << "Error: Failed to open file for writing." << std::endl;
    //     return;
    // }
    // file.close();
    // std::cout << "Saved!" << std::endl;
// }

// MindMapper MindMapper::deserialize(const std::string& filename)
// {
    // MindMapper mind;
    // ifstream file(filename, ios::binary);
    // if (!file.is_open()) {
    //     std::cerr << "Error: Failed to open file for reading." << std::endl;
    //     return;
    // }
    // file.close();
    // std::cout << "Loaded!" << std::endl;
    // return mind;
// }

// void MindMapper::traverseThoughts()
// {
//     Idea *p = m_first;
//     int i = 1;
//     while (p) {
//         std::cout << "Idea #" << i++ << std::endl;
//         p->thoughts.display(p->thoughts.getTop());
//         std::cout << std::endl;
//         p = p->next;
//     }
// }
