#ifndef H_CARD
#define H_CARD

#include <iostream>

struct card
{
    card() {}

    int id_bank;
    int id_program;
    int id_card;

    friend std::ostream& operator<<(std::ostream& os, const card& card_)
    {
        os << "Number card: " << card_.convert_to_output(card_.id_bank) << " " << card_.convert_to_output(card_.id_program)
            << " " << card_.convert_to_output(card_.id_card);

        return os;
    }
private:
    std::string convert_to_output(int number) const
    {
        std::string answer = "";

        if (number < 1000 && number >= 100)
            answer += "0";
        else if (number < 100 && number >= 10)
            answer += "00";
        else if (number < 10)
            answer += "000";
        answer += std::to_string(number);

        return answer;
    }
};


#endif