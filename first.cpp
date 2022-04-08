#define _USE_MATH_DEFINES
#include <cmath>
#include "first.h"
#include <iostream>
#include <algorithm>
namespace functions {
    Rectangle::Rectangle() {
        first_coord = {0, 0};
        second_coord = {0, 0};
        third_coord = {0 , 0};
        fourth_coord = {0, 0};
        weight = 0;
    }

    void Rectangle::initFromDialog() {
        std::cout << "Enter rectangle top left(x, y) coords and bottom right(x, y) coords:\n";
        std::cin >> first_coord.first >> first_coord.second >> second_coord.first >> second_coord.second;
        std::cout << "Enter rectangle bottom left(x, y) coords and top right(x, y) coords:\n";
        std::cin >> third_coord.first >> third_coord.second >> fourth_coord.first >> first_coord.second;
        std::cout << "Enter rectangle's mass :\n";
        std::cin >> weight;
    };

    double Rectangle::square() {
        return ((first_coord.second - third_coord.second) * (fourth_coord.first - first_coord.first));
    };

    double Rectangle::perimeter() {
        return 2 * ((first_coord.second - third_coord.second) + (fourth_coord.first - first_coord.first));
    };

    double Rectangle::mass() const {
        return weight;
    };

    CVector2D Rectangle::position() {
        CVector2D answer{};
        answer.x = first_coord.first;
        answer.y = second_coord.second;
        return answer;
    };

    bool Rectangle::operator==(const IPhysObject &obj) const {
        return (weight == obj.mass());
    };

    bool Rectangle::operator<(const IPhysObject &obj) const {
        return (weight < obj.mass());
    };

    void Rectangle::draw() {
        std::cout << "Top Left Coordinates: (" << first_coord.first << "; " << first_coord.second << ") \n";
        std::cout << "Bottom Left Coordinates: (" << third_coord.first << "; " << third_coord.second << ") \n";
        std::cout << "Bottom Right Coordinates: (" << second_coord.first << "; " << second_coord.second << ") \n";
        std::cout << "Top Right Coordinates: (" << fourth_coord.first << "; " << fourth_coord.second << ") \n";
        std::cout << "Mass: " << weight << std::endl;
    }

    const char *Rectangle::classname() {
        return typeid(this).name();
    };

    unsigned int Rectangle::size() {
        return sizeof *this;
    };


    Segment::Segment() {
        first_c = {0, 0};
        second_c = {0, 0};
        weight = 0;
    }

    void Segment::initFromDialog() {
        std::cout << "Enter segment's first point coords(x, y): \n";
        std::cin >> first_c.first >> first_c.second;
        std::cout << "Enter segment's second point coords(x, y): \n";
        std::cin >> second_c.first >> second_c.second;
        std::cout << "Enter segment's mass: \n";
        std::cin >> weight;
    }

    double Segment::square() {
        return 0;
    };

    double Segment::perimeter() {
        return 0;
    };

    double Segment::mass() const {
        return weight;
    };

    CVector2D Segment::position() {
        CVector2D answer;
        answer.x = first_c.first;
        answer.y = second_c.second;
        return answer;
    };

    bool Segment::operator==(const IPhysObject &obj) const {
        return (weight == obj.mass());
    };

    bool Segment::operator<(const IPhysObject &obj) const {
        return (weight < obj.mass());
    }

    void Segment::draw() {
        std::cout << "First coord's: (" << first_c.first << "; " << first_c.second << ") \n";
        std::cout << "Second coord's: (" << second_c.first << "; " << second_c.second << ") \n";
        std::cout << "Weight: " << weight << std::endl;
    }

    const char *Segment::classname() {
        return typeid(this).name();
    };

    unsigned int Segment::size() {
        return sizeof *this;
    };

    DialogueMenu::DialogueMenu() {
        flag = 0;
    };

    void DialogueMenu::allcommands() {
        std::cout << "Choose type of the operation:\n";
        std::cout << "1 - Add Rectangle\n";
        std::cout << "2 - Add Segment\n";
        std::cout << "3 - Show all figures\n";
        std::cout << "4 - Show total square of figures\n";
        std::cout << "5 - Show total perimeter of figures\n";
        std::cout << "6 - Show center weight of all figures\n";
        std::cout << "7 - Show total memory that objects occupy\n";
        std::cout << "8 - Sort all figures by mass\n";
        std::cout << "9 - End of program \n\n";
    };

    void DialogueMenu::menufunction() {
        while(true) {
            DialogueMenu::allcommands();
            std::cout << "Enter a type of the operation: ";
            std::cin >> flag;
            if (flag == 1) {
                createFigure<Rectangle>();
                continue;
            }
            else if (flag == 2) {
                createFigure <Segment>();
                continue;
            }
            else if (flag == 3) {
                std::cout << "List of figures: " << std::endl;
                for (int i = 0; i < pointers.size(); i++) {
                    std::cout << "Number: " << i + 1 << std::endl;
                    std::cout << "          " << std::endl;
                    pointers[i]->draw();
                    std::cout << "          " << std::endl;
                }
                std::cout << std::endl << "__________" << std::endl;
            }
            else if (flag == 4) {
                std::cout << "Summary square:" << std::endl;
                std::cout << summary_sq << std::endl;
            }
            else if (flag == 5) {
                std::cout << "Summary perimeter:" << std::endl;
                std::cout << summary_perim << std::endl;
            }
            else if (flag == 6) {
                std::cout << "Summary center mass:" << std::endl;
                std::cout << summary_weight << std::endl;
            }
            else if (flag == 7) {
                std::cout << "Summary memory used:" << std::endl;
                std::cout << summary_size << std::endl;
            }
            else if (flag == 8) {
                sort(pointers.begin(), pointers.end(),
                     [](BaseFigure *lhs, BaseFigure *rhs) {
                         return *lhs < *rhs;
                     }
                );
            }
            else if (flag == 9) {
                exit(0);
            }
            else {
                std::cout << "Unknown command! " << std::endl;
            }
        }
    };
};

